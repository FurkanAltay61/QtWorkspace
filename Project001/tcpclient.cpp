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

    connect(&m_timer,&QTimer::timeout, this, &TcpClient::updateDashboard);

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
    writeData("AT E0\rAT L0\rAT H0\rAT S1\rAT AT 1\rAT ST 32\r");
    sendTimer->start(SENDING_PERIOD);
    m_timer.start(SAMPLE_PERIOD);
    //m_RpmStruct->prevTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
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
    static int count{0};
    if (!datas.isEmpty()) {
        writeData(datas[count++]);
        if (count >= datas.size())
            count = 0;
    }

    // static int count{0};
    // static int tickcount{0};

    // if (!datas.isEmpty()) {
    //     if(datas[count] == 0x0105 && tickcount == 1200)     //Engine coolant temperature //60sn
    //         writeData(datas[count]);
    //     else if(datas[count] == 0x010B && tickcount == 50) //Intake manifold absolute pressure //5sn
    //         writeData(datas[count]);
    //     else if(datas[count] == 0x010F && tickcount == 50) //Intake air temperature //10sn
    //         writeData(datas[count]);
    //     else if(datas[count] == 0x0111 && tickcount == 50) //Throttle position //10sn
    //         writeData(datas[count]);
    //     else
    //         writeData(datas[count]);

    //     count++;
    //     if (count >= datas.size())
    //         count = 0;

    //     tickcount++;
    //     if (tickcount >= 1200)
    //         tickcount = 0;
    // }

    //writeData("ATI\r");
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
                m_SpeedStruct->prevValue = m_SpeedStruct->currValue;
                double load = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
                m_SpeedStruct->currValue = load;
                m_SpeedStruct->slope = (m_SpeedStruct->currValue - m_SpeedStruct->prevValue) /
                                     static_cast<double>(m_SpeedStruct->currTime - m_SpeedStruct->prevTime);
                m_SpeedStruct->prevTime = m_SpeedStruct->currTime;

                // qDebug() << "Engine load :" << load;
                // emit engineLoadSent(load);
            } else if (pid == "05") {
                m_CoolantTempStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_CoolantTempStruct->prevValue = m_CoolantTempStruct->currValue;
                int cooltemp = parsedstr[2].toInt(nullptr, 16) - 40;
                m_CoolantTempStruct->currValue = cooltemp;
                m_CoolantTempStruct->slope = (m_CoolantTempStruct->currValue - m_CoolantTempStruct->prevValue) /
                                       static_cast<double>(m_CoolantTempStruct->currTime - m_CoolantTempStruct->prevTime);
                m_CoolantTempStruct->prevTime = m_CoolantTempStruct->currTime;

                // qDebug() << "Coolant temperature :" << cooltemp << "°C";
                // emit coolantTempSent(cooltemp);
            } else if (pid == "0B") {
                m_IntakePressStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_IntakePressStruct->prevValue = m_IntakePressStruct->currValue;
                int intakepressure = parsedstr[2].toInt(nullptr, 16);
                m_IntakePressStruct->currValue = intakepressure;
                m_IntakePressStruct->slope = (m_IntakePressStruct->currValue - m_IntakePressStruct->prevValue) /
                                             static_cast<double>(m_IntakePressStruct->currTime - m_IntakePressStruct->prevTime);
                m_IntakePressStruct->prevTime = m_IntakePressStruct->currTime;

                // qDebug() << "Intake manifold absolute pressure :" << intakepressure << "kPa";
                // emit intakePressSent(intakepressure);
            } else if (pid == "0C") {
                m_RpmStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_RpmStruct->prevValue = m_RpmStruct->currValue;
                double rpm = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 4.0;
                m_RpmStruct->currValue = rpm;
                m_RpmStruct->slope = (m_RpmStruct->currValue - m_RpmStruct->prevValue) /
                                             static_cast<double>(m_RpmStruct->currTime - m_RpmStruct->prevTime);
                m_RpmStruct->prevTime = m_RpmStruct->currTime;

                // qDebug() << "Engine rpm :" << rpm << "rpm";
                // emit rpmSent(rpm);
            } else if (pid == "0D") {
                m_SpeedStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_SpeedStruct->prevValue = m_SpeedStruct->currValue;
                int speed = parsedstr[2].toInt(nullptr, 16);
                m_SpeedStruct->currValue = speed;
                m_SpeedStruct->slope = (m_SpeedStruct->currValue - m_SpeedStruct->prevValue) /
                                     static_cast<double>(m_SpeedStruct->currTime - m_SpeedStruct->prevTime);
                m_SpeedStruct->prevTime = m_SpeedStruct->currTime;

                // qDebug() << "Vehicle speed :" << speed << "km/h";
                // emit speedSent(speed);
            } else if (pid == "0F") {
                m_IntakeTempStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_IntakeTempStruct->prevValue = m_IntakeTempStruct->currValue;
                int intaketemp = parsedstr[2].toInt(nullptr, 16) - 40;
                m_IntakeTempStruct->currValue = intaketemp;
                m_IntakeTempStruct->slope = (m_IntakeTempStruct->currValue - m_IntakeTempStruct->prevValue) /
                                       static_cast<double>(m_IntakeTempStruct->currTime - m_IntakeTempStruct->prevTime);
                m_IntakeTempStruct->prevTime = m_IntakeTempStruct->currTime;

                // qDebug() << "Intake air temperature :" << intaketemp << "°C";
                // emit intakeTempSent(intaketemp);
            } else if (pid == "10") {
                m_FlowRateStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_FlowRateStruct->prevValue = m_FlowRateStruct->currValue;
                double flowrate = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 100.0;
                m_FlowRateStruct->currValue = flowrate;
                m_FlowRateStruct->slope = (m_FlowRateStruct->currValue - m_FlowRateStruct->prevValue) /
                                            static_cast<double>(m_FlowRateStruct->currTime - m_FlowRateStruct->prevTime);
                m_FlowRateStruct->prevTime = m_FlowRateStruct->currTime;

                // qDebug() << "Mass air flow-rate :" << flowrate << "g/s";
                // emit massAirFlowSent(flowrate);
            } else if (pid == "11") {
                m_ThrottlePosStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
                m_ThrottlePosStruct->prevValue = m_ThrottlePosStruct->currValue;
                double throttlepos = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
                m_ThrottlePosStruct->currValue = throttlepos;
                m_ThrottlePosStruct->slope = (m_ThrottlePosStruct->currValue - m_ThrottlePosStruct->prevValue) /
                                          static_cast<double>(m_ThrottlePosStruct->currTime - m_ThrottlePosStruct->prevTime);
                m_ThrottlePosStruct->prevTime = m_ThrottlePosStruct->currTime;

                // qDebug() << "Throttle position :" << throttlepos;
                // emit throttlePosSent(throttlepos);
            }
        } else if(parsedstr[0] == "OK") {
            qDebug() << "Message from server:" << parsedstr[0];
        } else {
            qDebug() << "Message from server:" << message;


            // m_RpmStruct->currTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

            // m_RpmStruct->prevValue = m_counter;
            // static bool direction = true;
            // if(m_counter >= 8000)
            //     direction = false;
            // else if(m_counter <= 0.1)
            //     direction = true;

            // m_counter += direction ? 250 : -250;
            // m_RpmStruct->currValue = m_counter;

            // m_RpmStruct->slope = (m_RpmStruct->currValue - m_RpmStruct->prevValue) / static_cast<double>(m_RpmStruct->currTime - m_RpmStruct->prevTime);
            // //qDebug() << "slope is :" << m_RpmStruct->slope;

            // m_RpmStruct->prevTime = m_RpmStruct->currTime;
        }
    }
}

void TcpClient::updateDashboard() {

    if(m_EngineLoadStruct->slope != 0){
        m_EngineLoadStruct->sampledValue = m_EngineLoadStruct->prevValue + (m_EngineLoadStruct->slope * SAMPLE_PERIOD);
        m_EngineLoadStruct->prevValue = m_EngineLoadStruct->sampledValue;
        qDebug() << "sampled value is :" << m_EngineLoadStruct->sampledValue;
        emit engineLoadSent(m_EngineLoadStruct->sampledValue);
    }
    if(m_CoolantTempStruct->slope != 0){
        m_CoolantTempStruct->sampledValue = m_CoolantTempStruct->prevValue + (m_CoolantTempStruct->slope * SAMPLE_PERIOD);
        m_CoolantTempStruct->prevValue = m_CoolantTempStruct->sampledValue;
        qDebug() << "sampled value is :" << m_CoolantTempStruct->sampledValue;
        emit coolantTempSent(m_CoolantTempStruct->sampledValue);
    }
    if(m_IntakePressStruct->slope != 0){
        m_IntakePressStruct->sampledValue = m_IntakePressStruct->prevValue + (m_IntakePressStruct->slope * SAMPLE_PERIOD);
        m_IntakePressStruct->prevValue = m_IntakePressStruct->sampledValue;
        qDebug() << "sampled value is :" << m_IntakePressStruct->sampledValue;
        emit intakePressSent(m_IntakePressStruct->sampledValue);
    }
    if(m_RpmStruct->slope != 0){
        m_RpmStruct->sampledValue = m_RpmStruct->prevValue + (m_RpmStruct->slope * SAMPLE_PERIOD);
        m_RpmStruct->prevValue = m_RpmStruct->sampledValue;
        qDebug() << "sampled value is :" << m_RpmStruct->sampledValue;
        emit rpmSent(m_RpmStruct->sampledValue);
    }
    if(m_SpeedStruct->slope != 0){
        m_SpeedStruct->sampledValue = m_SpeedStruct->prevValue + (m_SpeedStruct->slope * SAMPLE_PERIOD);
        m_SpeedStruct->prevValue = m_SpeedStruct->sampledValue;
        qDebug() << "sampled value is :" << m_SpeedStruct->sampledValue;
        emit speedSent(m_SpeedStruct->sampledValue);
    }
    if(m_IntakeTempStruct->slope != 0){
        m_IntakeTempStruct->sampledValue = m_IntakeTempStruct->prevValue + (m_IntakeTempStruct->slope * SAMPLE_PERIOD);
        m_IntakeTempStruct->prevValue = m_IntakeTempStruct->sampledValue;
        qDebug() << "sampled value is :" << m_IntakeTempStruct->sampledValue;
        emit intakeTempSent(m_IntakeTempStruct->sampledValue);
    }
    if(m_FlowRateStruct->slope != 0){
        m_FlowRateStruct->sampledValue = m_FlowRateStruct->prevValue + (m_FlowRateStruct->slope * SAMPLE_PERIOD);
        m_FlowRateStruct->prevValue = m_FlowRateStruct->sampledValue;
        qDebug() << "sampled value is :" << m_FlowRateStruct->sampledValue;
        emit massAirFlowSent(m_FlowRateStruct->sampledValue);
    }
    if(m_ThrottlePosStruct->slope != 0){
        m_ThrottlePosStruct->sampledValue = m_ThrottlePosStruct->prevValue + (m_ThrottlePosStruct->slope * SAMPLE_PERIOD);
        m_ThrottlePosStruct->prevValue = m_ThrottlePosStruct->sampledValue;
        qDebug() << "sampled value is :" << m_ThrottlePosStruct->sampledValue;
        emit throttlePosSent(m_ThrottlePosStruct->sampledValue);
    }




}
