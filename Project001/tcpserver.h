#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QList>
#include <QDateTime>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr);


private slots:
    void newConnection();
    void readData();
    //void writeData();
    void clientDisconnected();

private:
    QByteArray buffer;
    QTcpServer* server;
    QList<QTcpSocket *> clients;
    QTcpSocket *clientSocket;

    void writeData(QTcpSocket *clientSocket, const QByteArray &data);
};


#endif // TCPSERVER_H
