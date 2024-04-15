#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent){

    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &TcpServer::newConnection);

    if (!server->listen(QHostAddress::Any, (quint16)35000)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}


void TcpServer::newConnection()
{
    clientSocket = server->nextPendingConnection();
    clients.append(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServer::readData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &TcpServer::clientDisconnected);
    qDebug() << "Client connected!";

    qDebug() << "client socket peer address :" << server->serverAddress() << "port is :" << clientSocket->peerPort();
}


void TcpServer::readData()
{
    clientSocket = qobject_cast<QTcpSocket *>(sender());
    QByteArray data = clientSocket->readAll();
    buffer += data;
    QByteArray message;
    while (buffer.contains('\r')) {
        int crIndex = buffer.indexOf('\r');
        message = buffer.left(crIndex);
        buffer.remove(0, crIndex + 1);
        buffer.remove(0, buffer.indexOf('>') + 1);
    }

    qDebug() << message;

    QByteArray response;

    if(message == "0104"){
        static int val = 0;
        static int count = 0;
        static bool direction = true;
        val = count;
        if(count >= 255){
            direction = false;
        }else if(count <= 0){
            direction = true;
        }
        count += direction ? 10 : -10;
        response = "41 04 " + QByteArray::number(val,16).toUpper() + "\r";
        clientSocket->write(response);

    } else if(message == "0105") {
        static int val = 0;
        static int count = 40;
        static bool direction = true;
        val = count;
        if(count >= 160){
            direction = false;
        }else if(count <= 40){
            direction = true;
        }

        count += direction ? 10 : -10;
        response = "41 05 " + QByteArray::number(val,16).toUpper() + "\r";
        clientSocket->write(response);

    } else if(message == "010B") {
        static int val = 0;
        static int count = 0;
        static bool direction = true;
        val = count;
        if(count >= 250){
            direction = false;
        }else if(count <= 0){
            direction = true;
        }

        count += direction ? 10 : -10;
        response = "41 0B " + QByteArray::number(val,16).toUpper() + "\r";
        clientSocket->write(response);

    } else if(message == "010C") {
        static int val = 0;
        static int count = 0;
        static bool direction = true;
        val = count * 4;
        if(count >= 5000){
            direction = false;
        }else if(count <= 0){
            direction = true;
        }

        count += direction ? 250 : -250;
        response = "41 0C " + QByteArray::number(val,16).rightJustified(4 , '0').toUpper().insert(2, ' ') + "\r";
        clientSocket->write(response);

    } else if(message == "010D") {
        static int val = 0;
        static int count = 0;
        static bool direction = true;
        val = count;
        if(count >= 240){
            direction = false;
        }else if(count <= 0){
            direction = true;
        }

        count += direction ? 10 : -10;
        response = "41 0D " + QByteArray::number(val,16).toUpper() + "\r";
        clientSocket->write(response);

    } else if(message == "010F") {
        static int val = 0;
        static int count = 40;
        static bool direction = true;
        val = count;
        if(count >= 290){
            direction = false;
        }else if(count <= 40){
            direction = true;
        }

        count += direction ? 5 : -5;
        response = "41 0F " + QByteArray::number(val,16).toUpper() + "\r";
        clientSocket->write(response);

    } else if(message == "0110") {
        static int val = 0;
        static int count = 0;
        static bool direction = true;
        val = count;
        if(count >= 250*100){
            direction = false;
        }else if(count <= 0){
            direction = true;
        }

        count += direction ? 1000 : -1000;
        response = "41 10 " + QByteArray::number(val,16).rightJustified(4 , '0').toUpper().insert(2, ' ') + "\r";
        clientSocket->write(response);

    } else if(message == "0111") {
        static int val = 0;
        static int count = 0;
        static bool direction = true;
        val = count;
        if(count >= 255){
            direction = false;
        }else if(count <= 0){
            direction = true;
        }

        count += direction ? 10 : -10;
        response = "41 11 " + QByteArray::number(val,16).toUpper() + "\r";
        clientSocket->write(response);
    }
}

void TcpServer::clientDisconnected()
{
    clientSocket = qobject_cast<QTcpSocket *>(sender());
    clients.removeAll(clientSocket);
    clientSocket->deleteLater();
}

