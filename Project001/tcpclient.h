#ifndef TCPCLIENT_H
#define TCPCLIENT_H

/* Values to be supported */
/*
 * 0101 -> Monitor status since DTCs cleared.
 * 0104 -> Calculated engine load
 * 0105 -> Engine coolant temperature
 * 010B -> Intake manifold absolute pressure
 * 010C -> Engine speed
 * 010D -> Vehicle speed
 * 010F -> Intake air temperature
 * 0110 -> Mass air flow sensor (MAF) air flow rate
 * 0111 -> Throttle position
 * 011C -> OBD standards this vehicle conforms to
 * 0120 -> PIDs supported [$21 - $40]
 */

//#define METHOD1
//#define METHOD2

#include <QTcpSocket>
#include <QTimer>
#include <QObject>
#include <chrono>
#include <QStringList>
#include <QByteArray>
#include <QCoreApplication>

class TcpClient : public QObject {
    Q_OBJECT
public:
    explicit TcpClient(const QString& ip, quint16 port, QObject* parent = nullptr);
    void connectToServer();

private slots:
    void onConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
    void onSendData();

signals:
    void dataSent(const QString &data);
    void engineLoadSent(const double load);
    void coolantTempSent(const int cooltemp);
    void intakePressSent(const int inpress);
    void rpmSent(const double rpm);
    void speedSent(const int speed);
    void IntakeTempSent(const int intemp);
    void MassAirFlowSent(const double maf);
    void ThrottlePosSent(const double throtpos);


private:
    QTcpSocket* tcpSocket;
    QString serverIP;
    quint16 serverPort;
    QTimer* sendTimer;
    QByteArray buffer;
#ifdef METHOD1
    QStringList datas{"0104\r", "0105\r", "010B\r", "010C\r",
                      "010D\r", "010F\r", "0110\r", "0111\r"};
#endif
#ifdef METHOD2
    QString alldata{"0104\r0105\r010B\r010C\r010D\r010F\r0110\r0111\r"};
#endif
    std::chrono::high_resolution_clock::time_point prevtime;
    void writeData(const QString& data);
    void processMessage(const QByteArray& message);
};


#endif // TCPCLIENT_H
