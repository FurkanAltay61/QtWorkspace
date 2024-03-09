#include "tcpclient.h"

TcpClient::TcpClient(const QString& ip, quint16 port, QObject* parent)
    : QObject(parent), serverIP(ip), serverPort(port) {

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
    writeData("AT E0\rAT L0\rAT H0\rAT S1\rAT AT 1\rAT ST 32\r");
    sendTimer->start(50); // Example: Send data every 50 ms
    prevtime = std::chrono::high_resolution_clock::now();
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
#ifdef METHOD1
    static int count{0};
    if (!datas.isEmpty()) {
        writeData(datas[count++]);
        if (count >= datas.size())
            count = 0;
    }
#endif
#ifdef METHOD2
    writeData(alldata);
#endif
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
    if (!parsedstr.isEmpty() && parsedstr[0] == "41") {
        QString pid = parsedstr[1];
        if (pid == "04") {
            double load = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
            qDebug() << "Engine load :" << load;
        } else if (pid == "05") {
            int cooltemp = parsedstr[2].toInt(nullptr, 16) - 40;
            qDebug() << "Coolant temperature :" << cooltemp << "°C";
        } else if (pid == "0B") {
            int intakepressure = parsedstr[2].toInt(nullptr, 16);
            qDebug() << "Intake manifold absolute pressure :" << intakepressure << "kPa";
        } else if (pid == "0C") {
            double rpm = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 4.0;
            qDebug() << "Engine rpm :" << rpm << "rpm";
        } else if (pid == "0D") {
            int speed = parsedstr[2].toInt(nullptr, 16);
            qDebug() << "Vehicle speed :" << speed << "km/h";
        } else if (pid == "0F") {
            int intaketemp = parsedstr[2].toInt(nullptr, 16) - 40;
            qDebug() << "Intake air temperature :" << intaketemp << "°C";
        } else if (pid == "10") {
            double flowrate = (256 * parsedstr[2].toInt(nullptr, 16) + parsedstr[3].toInt(nullptr, 16)) / 100.0;
            qDebug() << "Mass air flow-rate :" << flowrate << "g/s";
        } else if (pid == "11") {
            double throttlepos = (100.0 * parsedstr[2].toInt(nullptr, 16)) / 255.0;
            qDebug() << "Throttle position :" << throttlepos;
        }
    } else {
        qDebug() << "Message from server:" << message;
    }

    auto currtime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currtime-prevtime);
    qDebug() << duration.count() << "ms";
    prevtime = currtime;

    emit dataSent("Data Geldi");
}

