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

    setupTimers();

}

TcpClient::~TcpClient(){
    qDebug() << "destructor called ";
    tcpSocket->close();
    deleteTimers();
    delete tcpSocket;
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
        //QThread::sleep(5);
        startTimers();
    }


}

void TcpClient::configureOBDII(){
    writeData("AT E0\rAT L0\rAT H0\rAT S1\rAT AT2\r");
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
            //retval = "YES";
        } else if(parsedstr[0] == "OK") {
            qDebug() << "Message from server:" << parsedstr[0];
        } else {
            qDebug() << "Message from server:" << message;

#ifdef TEST_MODE
            static bool direction = true;
            if(m_counter >= 8000)
                direction = false;
            else if(m_counter <= 0.1)
                direction = true;

            m_counter += direction ? 250 : -250;

            emit rpmSent(m_counter);
#endif
        }
    }
}

void TcpClient::handleResetSignal(){
    qDebug() << "Reset signal is handled";
    writeData("ATZ\r");
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        tcpSocket->disconnectFromHost();
        if(tcpSocket->state() != QAbstractSocket::UnconnectedState)
            tcpSocket->waitForDisconnected();
    }
    stopTimers();
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

void TcpClient::setupTimers() {
    engineLoadTimer = new QTimer(this);
    engineLoadTimer->setInterval(500);
    connect(engineLoadTimer, &QTimer::timeout, this, &TcpClient::requestEngineLoad);

    coolTempTimer = new QTimer(this);
    coolTempTimer->setInterval(60000);
    connect(coolTempTimer, &QTimer::timeout, this, &TcpClient::requestCoolTemp);

    mapTimer = new QTimer(this);
    mapTimer->setInterval(600);
    connect(mapTimer, &QTimer::timeout, this, &TcpClient::requestMap);

    rpmTimer = new QTimer(this);
    rpmTimer->setInterval(200);
    connect(rpmTimer, &QTimer::timeout, this, &TcpClient::requestRpm);

    speedTimer = new QTimer(this);
    speedTimer->setInterval(400);
    connect(speedTimer, &QTimer::timeout, this, &TcpClient::requestSpeed);

    iatTimer = new QTimer(this);
    iatTimer->setInterval(5000);
    connect(iatTimer, &QTimer::timeout, this, &TcpClient::requestIat);

    mafTimer = new QTimer(this);
    mafTimer->setInterval(500);
    connect(mafTimer, &QTimer::timeout, this, &TcpClient::requestMaf);

    throtPosTimer = new QTimer(this);
    throtPosTimer->setInterval(1000);
    connect(throtPosTimer, &QTimer::timeout, this, &TcpClient::requestThrotPos);
}

void TcpClient::startTimers() {
    engineLoadTimer->start();
    coolTempTimer->start();
    mapTimer->start();
    rpmTimer->start();
    speedTimer->start();
    iatTimer->start();
    mafTimer->start();
    //throtPosTimer->start();
}

void TcpClient::stopTimers() {
    engineLoadTimer->stop();
    coolTempTimer->stop();
    mapTimer->stop();
    rpmTimer->stop();
    speedTimer->stop();
    iatTimer->stop();
    mafTimer->stop();
    //throtPosTimer->stop();
}

void TcpClient::deleteTimers(){
    delete engineLoadTimer;
    delete coolTempTimer;
    delete mapTimer;
    delete rpmTimer;
    delete speedTimer;
    delete iatTimer;
    delete mafTimer;
    delete throtPosTimer;
}

void TcpClient::requestEngineLoad(){
    QString message = "0104\r";
    //qDebug() << "requestEngineLoad";
    writeData(message);
}

void TcpClient::requestCoolTemp(){
    QString message = "0105\r";
    //qDebug() << "requestCoolTemp";
    writeData(message);
}

void TcpClient::requestMap(){
    QString message = "010B\r";
    //qDebug() << "requestMap";
    writeData(message);
}

void TcpClient::requestRpm(){
    QString message = "010C\r";
    //qDebug() << "requestRpm";
    writeData(message);
}

void TcpClient::requestSpeed(){
    QString message = "010D\r";
    //qDebug() << "requestSpeed";
    writeData(message);
}

void TcpClient::requestIat(){
    QString message = "010F\r";
    //qDebug() << "requestIat";
    writeData(message);
}

void TcpClient::requestMaf(){
    QString message = "0110\r";
    //qDebug() << "requestMaf";
    writeData(message);
}

void TcpClient::requestThrotPos(){
    QString message = "0111\r";
    //qDebug() << "requestThrotPos";
    writeData(message);
}

/*********************************************WorkerClass*****************************************/


