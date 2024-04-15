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
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &TcpClient::onError);

#ifdef TEST_MODE
    // Initialize requests with their types and intervals
    requests.emplace_back("ELoad", "0104\r", 0, 100, 0);
    requests.emplace_back("Coolant", "0105\r", 0, 100, 0);
    requests.emplace_back("Map","010B\r", 0, 100, 0);
    requests.emplace_back("Rpm","010C\r", 0, 100, 0);
    requests.emplace_back("Speed", "010D\r", 0, 100, 0);
    requests.emplace_back("Iat", "010F\r", 0, 100, 0);
    requests.emplace_back("Maf", "0110\r", 0, 100, 0);
    requests.emplace_back("Throttle", "0111\r", 0, 100, 0);
#else
    // Initialize requests with their types and intervals
    requests.emplace_back("Rpm","010C\r", 0, 200, 0);
    requests.emplace_back("ELoad", "0104\r", 0, 300, 0);
    requests.emplace_back("Speed", "010D\r", 0, 400, 0);
    requests.emplace_back("Map","010B\r", 0, 500, 0);
    requests.emplace_back("Maf", "0110\r", 0, 600, 0);
    requests.emplace_back("Throttle", "0111\r", 0, 400, 0);
    requests.emplace_back("Coolant", "0105\r", 0, 60000, 0);
    requests.emplace_back("Iat", "010F\r", 0, 10000, 0);
#endif
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TcpClient::updateData);
}

TcpClient::~TcpClient(){
    qDebug() << "destructor called ";
    tcpSocket->close();
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
        timer->setTimerType(Qt::PreciseTimer);
        timer->start(10);
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
    if(data.isEmpty())
        return;
    buffer += data;
    QByteArray message;
    while (buffer.contains('\r')) {
        int crIndex = buffer.indexOf('\r');
        message = buffer.left(crIndex);
        buffer.remove(0, crIndex + 1);
        buffer.remove(0, buffer.indexOf('>') + 1);
    }

    processMessage(message);
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
    uint64_t currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

    if(!parsedstr.isEmpty()){
        if (parsedstr[0] == "41") {
            QString pid = parsedstr[1];
            if (pid == "04") {
                m_EngineLoadStruct->data = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
                emit engineLoadDurationSent(currTime - m_EngineLoadStruct->prevTime);
                emit engineLoadSent(m_EngineLoadStruct->data);
                qDebug() << "Engine load :" << m_EngineLoadStruct->data << "duration :" << currTime - m_EngineLoadStruct->prevTime;
                m_EngineLoadStruct->prevTime = currTime;
            } else if (pid == "05") {
                m_CoolantTempStruct->data = parsedstr[2].toInt(nullptr, 16) - 40;
                emit coolantTempDurationSent(currTime - m_CoolantTempStruct->prevTime);
                emit coolantTempSent(m_CoolantTempStruct->data);
                qDebug() << "Coolant temperature :" << m_CoolantTempStruct->data << "°C" << "duration :" << currTime - m_CoolantTempStruct->prevTime;
                m_CoolantTempStruct->prevTime = currTime;
            } else if (pid == "0B") {
                m_IntakePressStruct->data = parsedstr[2].toInt(nullptr, 16);
                emit intakePressureDurationSent(currTime - m_IntakePressStruct->prevTime);
                emit intakePressureSent(m_IntakePressStruct->data);
                qDebug() << "Intake manifold absolute pressure :" << m_IntakePressStruct->data << "kPa" << "duration :" << currTime - m_IntakePressStruct->prevTime;
                m_IntakePressStruct->prevTime = currTime;
            } else if (pid == "0C") {
                m_RpmStruct->data = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 4.0;
                emit rpmDurationSent(currTime - m_RpmStruct->prevTime);
                emit rpmSent(m_RpmStruct->data);
                qDebug() << "Engine rpm :" << m_RpmStruct->data << "rpm" << "duration :" << currTime - m_RpmStruct->prevTime;
                m_RpmStruct->prevTime = currTime;
            } else if (pid == "0D") {
                m_SpeedStruct->data = parsedstr[2].toInt(nullptr, 16);
                emit speedDurationSent(currTime - m_SpeedStruct->prevTime);
                emit speedSent(m_SpeedStruct->data);
                qDebug() << "Vehicle speed :" << m_SpeedStruct->data << "km/h" << "duration :" << currTime - m_SpeedStruct->prevTime;
                m_SpeedStruct->prevTime = currTime;
            } else if (pid == "0F") {
                m_IntakeTempStruct->data = parsedstr[2].toInt(nullptr, 16) - 40;
                emit intakeTempDurationSent(currTime - m_IntakeTempStruct->prevTime);
                emit intakeTempSent(m_IntakeTempStruct->data);
                qDebug() << "Intake air temperature :" << m_IntakeTempStruct->data << "°C" << "duration :" << currTime - m_IntakeTempStruct->prevTime;
                m_IntakeTempStruct->prevTime = currTime;
            } else if (pid == "10") {
                m_FlowRateStruct->data = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 100.0;
                emit mafDurationSent(currTime - m_FlowRateStruct->prevTime);
                emit mafSent(m_FlowRateStruct->data);
                qDebug() << "Mass air flow-rate :" << m_FlowRateStruct->data << "g/s" << "duration :" << currTime - m_FlowRateStruct->prevTime;
                m_FlowRateStruct->prevTime = currTime;
            } else if (pid == "11") {
                m_ThrottlePosStruct->data = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
                emit throttlePosDurationSent(currTime - m_ThrottlePosStruct->prevTime);
                emit throttlePosSent(m_ThrottlePosStruct->data);
                qDebug() << "Throttle position :" << m_ThrottlePosStruct->data << "duration :" << currTime - m_ThrottlePosStruct->prevTime;
                m_ThrottlePosStruct->prevTime = currTime;
            }
            //retval = "YES";
        } else if(parsedstr[0] == "OK") {
            qDebug() << "Message from server:" << parsedstr[0];
        } else {
            qDebug() << "Message from server:" << message;
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
    timer->stop();
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

void TcpClient::updateData() {
    qint64 current_time = QDateTime::currentMSecsSinceEpoch();
    Request& currentRequest = requests[currentRequestIndex];

    if(current_time - currentRequest.lastRequested >= currentRequest.interval) {
        currentRequest.lastRequested = current_time;
        writeData(currentRequest.command);
    }
    // Move to the next request type
    currentRequestIndex = (currentRequestIndex + 1) % requests.size();
}


/*********************************************WorkerClass*****************************************/


