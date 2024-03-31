#include "tcpclient.h"

TcpClient::TcpClient(const QString& ip, quint16 port, QObject* parent)
    : QObject(parent), serverIP(ip), serverPort(port),
    m_EngineLoadStruct(std::make_shared<Datapoint>()),
    m_CoolantTempStruct(std::make_shared<Datapoint>()),
    m_IntakePressStruct(std::make_shared<Datapoint>()),
    m_RpmStruct(std::make_shared<Datapoint>()),
    m_SpeedStruct(std::make_shared<Datapoint>()),
    m_IntakeTempStruct(std::make_shared<Datapoint>()),
    m_FlowRateStruct(std::make_shared<Datapoint>()),
    m_ThrottlePosStruct(std::make_shared<Datapoint>())
{


    m_counter = 0;
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &TcpClient::onError);

    sendTimer = new QTimer(this);
    connect(sendTimer, &QTimer::timeout, this, &TcpClient::onSendData);
}

TcpClient::~TcpClient(){
    qDebug() << "destructor called ";
    tcpSocket->close();
    sendTimer->stop();
    delete tcpSocket;
    delete sendTimer;
}

void TcpClient::connectToServer() {
    if(tcpSocket->state() == tcpSocket->UnconnectedState){
        tcpSocket->connectToHost(serverIP, serverPort);
        if (!tcpSocket->waitForConnected()) {
            qDebug() << "Failed to connect to the server:" << tcpSocket->errorString();
            emit statMsgSent("[TcpClient::connectToServer] : " + tcpSocket->errorString());
            //QCoreApplication::exit(EXIT_FAILURE);
            return;
        }
        qDebug() << "Connected to the server!";
        emit statMsgSent("[TcpClient::connectToServer] : Connect signal is handled");
        // Setup OBD-II communication
        configureOBDII();
        sendTimer->start(SENDING_PERIOD);
    }


}

void TcpClient::configureOBDII(){
    writeData("AT E0\rAT L0\rAT H0\rAT S1\rAT AT1\r");
    emit statMsgSent("[TcpClient::configureOBDII] : Obd2 device is configured");
}

void TcpClient::onConnected(){
    qDebug() << "Connected to the server!";
    emit statMsgSent("[TcpClient::onConnected] : Connected to the server!");
}

void TcpClient::onReadyRead() {
    QByteArray data = tcpSocket->readAll();
    buffer += data;
    while (buffer.contains('\r')) {
        int crIndex = buffer.indexOf('\r');
        QByteArray message = buffer.left(crIndex);
        buffer.remove(0, crIndex + 1);
        buffer.remove(0, buffer.indexOf('>') + 1);
        processMessage(message);
    }
}

void TcpClient::onError(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError);
    qDebug() << "Socket error:" << tcpSocket->errorString();
    emit statMsgSent("[TcpClient::onError] : " + tcpSocket->errorString());
    //QCoreApplication::exit(EXIT_FAILURE);
}

void TcpClient::onSendData() {
    // static int count{0};
    // if (!datas.isEmpty()) {
    //     if(retval != "NO DATA")
    //         writeData(datas[count++]);
    //     if (count >= datas.size())
    //         count = 0;
    // }

#ifdef  TEST_MODE
    writeData("ATI\r");
#else
    static int count{0};
    static int tickcount{0};


if (!datas.isEmpty()) {
    if(datas[count] == "0105\r" && tickcount == 250)     //Engine coolant temperature //60sn
        writeData(datas[count]);
    else if(datas[count] == "010B\r" && tickcount == 25) //Intake manifold absolute pressure //5sn
        writeData(datas[count]);
    else if(datas[count] == "010F\r" && tickcount == 50) //Intake air temperature //10sn
        writeData(datas[count]);
    else if(datas[count] == "0111\r" && tickcount == 5) //Throttle position //10sn
        writeData(datas[count]);
    else
        writeData(datas[count]);

    if(retval == "YES")
        count++;

    if (count >= datas.size())
        count = 0;

    tickcount++;
    if (tickcount > 250)
        tickcount = 0;
}
#endif
}

void TcpClient::writeData(const QString& data) {
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(data.toUtf8());
        tcpSocket->waitForBytesWritten();
    }
}


void TcpClient::processMessage(const QByteArray& message) {
    QStringList parsedstr = QString::fromLatin1(message).split(' ', Qt::SkipEmptyParts);

    if(!parsedstr.isEmpty()){
        if (parsedstr[0] == "41") {
            QString pid = parsedstr[1];
            if (pid == "04") {
                m_EngineLoadStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_EngineLoadStruct->data = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
                m_EngineLoadStruct->duration = m_EngineLoadStruct->currTime - m_EngineLoadStruct->prevTime;
                qDebug() << "Engine load :" << m_EngineLoadStruct->data << "duration :" << m_EngineLoadStruct->duration;
                m_EngineLoadStruct->prevTime = m_EngineLoadStruct->currTime;
                if(m_EngineLoadStruct->duration < 10000)
                emit engineLoadDurationSent(m_EngineLoadStruct->duration);
                emit engineLoadSent(m_EngineLoadStruct->data);
            } else if (pid == "05") {
                m_CoolantTempStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_CoolantTempStruct->data = parsedstr[2].toInt(nullptr, 16) - 40;
                m_CoolantTempStruct->duration = m_CoolantTempStruct->currTime - m_CoolantTempStruct->prevTime;
                qDebug() << "Coolant temperature :" << m_CoolantTempStruct->data << "°C" << "duration :" << m_CoolantTempStruct->duration;
                m_CoolantTempStruct->prevTime = m_CoolantTempStruct->currTime;
                if(m_CoolantTempStruct->duration < 10000)
                emit coolantTempDurationSent(m_CoolantTempStruct->duration);
                emit coolantTempSent(m_CoolantTempStruct->data);
            } else if (pid == "0B") {
                m_IntakePressStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_IntakePressStruct->data = parsedstr[2].toInt(nullptr, 16);
                m_IntakePressStruct->duration = m_IntakePressStruct->currTime - m_IntakePressStruct->prevTime;
                qDebug() << "Intake manifold absolute pressure :" << m_IntakePressStruct->data << "kPa" << "duration :" << m_IntakePressStruct->duration;
                m_IntakePressStruct->prevTime = m_IntakePressStruct->currTime;
                if(m_IntakePressStruct->duration < 10000)
                emit intakePressureDurationSent(m_IntakePressStruct->duration);
                emit intakePressureSent(m_IntakePressStruct->data);
            } else if (pid == "0C") {
                m_RpmStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_RpmStruct->data = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 4.0;
                m_RpmStruct->duration = m_RpmStruct->currTime - m_RpmStruct->prevTime;
                qDebug() << "Engine rpm :" << m_RpmStruct->data << "rpm" << "duration :" << m_RpmStruct->duration;
                m_RpmStruct->prevTime = m_RpmStruct->currTime;
                if(m_RpmStruct->duration < 10000)
                emit rpmDurationSent(m_RpmStruct->duration);
                emit rpmSent(m_RpmStruct->data);
            } else if (pid == "0D") {
                m_SpeedStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_SpeedStruct->data = parsedstr[2].toInt(nullptr, 16);
                m_SpeedStruct->duration = m_SpeedStruct->currTime - m_SpeedStruct->prevTime;
                qDebug() << "Vehicle speed :" << m_SpeedStruct->data << "km/h" << "duration :" << m_SpeedStruct->duration;
                m_SpeedStruct->prevTime = m_SpeedStruct->currTime;
                if(m_SpeedStruct->duration < 10000)
                emit speedDurationSent(m_SpeedStruct->duration);
                emit speedSent(m_SpeedStruct->data);
            } else if (pid == "0F") {
                m_IntakeTempStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_IntakeTempStruct->data = parsedstr[2].toInt(nullptr, 16) - 40;
                m_IntakeTempStruct->duration = m_IntakeTempStruct->currTime - m_IntakeTempStruct->prevTime;
                qDebug() << "Intake air temperature :" << m_IntakeTempStruct->data << "°C" << "duration :" << m_IntakeTempStruct->duration;
                m_IntakeTempStruct->prevTime = m_IntakeTempStruct->currTime;
                if(m_IntakeTempStruct->duration < 10000)
                emit intakeTempDurationSent(m_IntakeTempStruct->duration);
                emit intakeTempSent(m_IntakeTempStruct->data);
            } else if (pid == "10") {
                m_FlowRateStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_FlowRateStruct->data = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 100.0;
                m_FlowRateStruct->duration = m_FlowRateStruct->currTime - m_FlowRateStruct->prevTime;
                qDebug() << "Mass air flow-rate :" << m_FlowRateStruct->data << "g/s" << "duration :" << m_FlowRateStruct->duration;
                m_FlowRateStruct->prevTime = m_FlowRateStruct->currTime;
                if(m_FlowRateStruct->duration < 10000)
                emit mafDurationSent(m_FlowRateStruct->duration);
                emit mafSent(m_FlowRateStruct->data);
            } else if (pid == "11") {
                m_ThrottlePosStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_ThrottlePosStruct->data = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
                m_ThrottlePosStruct->duration = m_ThrottlePosStruct->currTime - m_ThrottlePosStruct->prevTime;
                qDebug() << "Throttle position :" << m_ThrottlePosStruct->data << "duration :" << m_ThrottlePosStruct->duration;
                m_ThrottlePosStruct->prevTime = m_ThrottlePosStruct->currTime;
                if(m_ThrottlePosStruct->duration < 10000)
                emit throttlePosDurationSent(m_ThrottlePosStruct->duration);
                emit throttlePosSent(m_ThrottlePosStruct->data);
            }
            retval = "YES";
        } else if(parsedstr[0] == "OK") {
            qDebug() << "Message from server:" << parsedstr[0];
        } else {
            qDebug() << "Message from server:" << message;

            retval = message;

            static bool direction = true;
            if(m_counter >= 8000)
                direction = false;
            else if(m_counter <= 0.1)
                direction = true;

            m_counter += direction ? 250 : -250;

            emit rpmSent(m_counter);

        }
    }
}

void TcpClient::handleResetSignal(){
    qDebug() << "Reset signal is handled";
    writeData("ATZ\r");
    sendTimer->stop();
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        tcpSocket->disconnectFromHost();
        if(tcpSocket->state() != QAbstractSocket::UnconnectedState)
            tcpSocket->waitForDisconnected();
    }

    emit statMsgSent("[TcpClient::handleResetSignal] : Reset signal is handled");
}

void TcpClient::handleConnectSignal(){
    qDebug() << "connect signal is handled";
    connectToServer();
}

void TcpClient::handleRebootSignal(){
    QProcess process;
    process.start("reboot",QStringList());
    process.waitForFinished();
}
