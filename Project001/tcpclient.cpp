#include "tcpclient.h"

TcpClient::TcpClient(const QString& ip, quint16 port, QObject* parent)
    : QObject(parent), serverIP(ip), serverPort(port) {

    m_counter = 0;

    m_EngineLoadStruct = std::make_shared<Datapoint>();
    m_CoolantTempStruct = std::make_shared<Datapoint>();
    m_IntakePressStruct = std::make_shared<Datapoint>();
    m_RpmStruct = std::make_shared<Datapoint>();
    m_SpeedStruct = std::make_shared<Datapoint>();
    m_IntakeTempStruct = std::make_shared<Datapoint>();
    m_FlowRateStruct = std::make_shared<Datapoint>();
    m_ThrottlePosStruct = std::make_shared<Datapoint>();

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &TcpClient::onError);

    sendTimer = new QTimer(this);
    connect(sendTimer, &QTimer::timeout, this, &TcpClient::onSendData);

    // Start connection
    connectToServer();
}

void TcpClient::connectToServer() {
    tcpSocket->connectToHost(serverIP, serverPort);
    if (!tcpSocket->waitForConnected()) {
        qDebug() << "Failed to connect to the server:" << tcpSocket->errorString();
        QCoreApplication::exit(EXIT_FAILURE);
    }
    qDebug() << "Connected to the server!";
    // Setup OBD-II communication
    writeData("AT E0\rAT L0\rAT H0\rAT S1\rAT AT1\r");
    sendTimer->start(SENDING_PERIOD);
}

void TcpClient::onConnected(){
    qDebug() << "Connected to the server!";
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
    QCoreApplication::exit(EXIT_FAILURE);
}

void TcpClient::onSendData() {
    // static int count{0};
    // if (!datas.isEmpty()) {
    //     if(retval != "NO DATA")
    //         writeData(datas[count++]);
    //     if (count >= datas.size())
    //         count = 0;
    // }


    // static int count{0};
    // static int tickcount{0};

    // if (!datas.isEmpty()) {
    //     if(datas[count] == "0105\r" && tickcount == 250)     //Engine coolant temperature //60sn
    //         writeData(datas[count]);
    //     else if(datas[count] == "010B\r" && tickcount == 25) //Intake manifold absolute pressure //5sn
    //         writeData(datas[count]);
    //     else if(datas[count] == "010F\r" && tickcount == 50) //Intake air temperature //10sn
    //         writeData(datas[count]);
    //     else if(datas[count] == "0111\r" && tickcount == 5) //Throttle position //10sn
    //         writeData(datas[count]);
    //     else
    //         writeData(datas[count]);

    //     if(retval == "YES")
    //         count++;

    //     if (count >= datas.size())
    //         count = 0;

    //     tickcount++;
    //     if (tickcount > 250)
    //         tickcount = 0;
    // }

    writeData("ATI\r");
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
                m_SpeedStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                double load = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
                qDebug() << "Engine load :" << load << "duration :" << m_SpeedStruct->currTime - m_SpeedStruct->prevTime;
                m_SpeedStruct->prevTime = m_SpeedStruct->currTime;
                emit engineLoadSent(load);
            } else if (pid == "05") {
                m_CoolantTempStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                int cooltemp = parsedstr[2].toInt(nullptr, 16) - 40;
                qDebug() << "Coolant temperature :" << cooltemp << "°C" << "duration :" << m_CoolantTempStruct->currTime - m_CoolantTempStruct->prevTime;
                m_CoolantTempStruct->prevTime = m_CoolantTempStruct->currTime;
                emit coolantTempSent(cooltemp);
            } else if (pid == "0B") {
                m_IntakePressStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                int intakepressure = parsedstr[2].toInt(nullptr, 16);
                qDebug() << "Intake manifold absolute pressure :" << intakepressure << "kPa" << "duration :" << m_IntakePressStruct->currTime - m_IntakePressStruct->prevTime;
                m_IntakePressStruct->prevTime = m_IntakePressStruct->currTime;
                emit intakePressSent(intakepressure);
            } else if (pid == "0C") {
                m_RpmStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                double rpm = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 4.0;
                qDebug() << "Engine rpm :" << rpm << "rpm" << "duration :" << m_RpmStruct->currTime - m_RpmStruct->prevTime;
                m_RpmStruct->prevTime = m_RpmStruct->currTime;
                emit rpmSent(rpm);
            } else if (pid == "0D") {
                m_SpeedStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                int speed = parsedstr[2].toInt(nullptr, 16);
                qDebug() << "Vehicle speed :" << speed << "km/h" << "duration :" << m_SpeedStruct->currTime - m_SpeedStruct->prevTime;
                m_SpeedStruct->prevTime = m_SpeedStruct->currTime;
                emit speedSent(speed);
            } else if (pid == "0F") {
                m_IntakeTempStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                int intaketemp = parsedstr[2].toInt(nullptr, 16) - 40;
                qDebug() << "Intake air temperature :" << intaketemp << "°C" << "duration :" << m_IntakeTempStruct->currTime - m_IntakeTempStruct->prevTime;
                m_IntakeTempStruct->prevTime = m_IntakeTempStruct->currTime;
                emit intakeTempSent(intaketemp);
            } else if (pid == "10") {
                m_FlowRateStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                double flowrate = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 100.0;
                qDebug() << "Mass air flow-rate :" << flowrate << "g/s" << "duration :" << m_FlowRateStruct->currTime - m_FlowRateStruct->prevTime;
                m_FlowRateStruct->prevTime = m_FlowRateStruct->currTime;
                emit massAirFlowSent(flowrate);
            } else if (pid == "11") {
                m_ThrottlePosStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                double throttlepos = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
                qDebug() << "Throttle position :" << throttlepos << "duration :" << m_ThrottlePosStruct->currTime - m_ThrottlePosStruct->prevTime;
                m_ThrottlePosStruct->prevTime = m_ThrottlePosStruct->currTime;
                emit throttlePosSent(throttlepos);
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

