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

#include <QTcpSocket>
#include <QTimer>
#include <QObject>
#include <chrono>
#include <QStringList>
#include <QByteArray>
#include <QCoreApplication>
#include <QDateTime>
#include <memory>
#include <cmath>

class TcpClient : public QObject {
    Q_OBJECT
    const int SENDING_PERIOD = 200;
public:
    explicit TcpClient(const QString& ip, quint16 port, QObject* parent = nullptr);
    ~TcpClient();
    void connectToServer();
    struct Datapoint
    {
        uint64_t prevTime;
        uint64_t currTime;
        qreal    data;
    };

private slots:
    void onConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
    void onSendData();

public slots:

signals:
    void dataSent(const QString &data);
    void engineLoadSent(const qreal &load);
    void coolantTempSent(const qreal &cooltemp);
    void intakePressSent(const qreal &inpress);
    void rpmSent(const qreal &rpm);
    void speedSent(const qreal &speed);
    void intakeTempSent(const qreal &intemp);
    void massAirFlowSent(const qreal &maf);
    void throttlePosSent(const qreal &throtpos);


private:
    QTcpSocket* tcpSocket;
    QString serverIP;
    quint16 serverPort;
    QTimer* sendTimer;
    QByteArray buffer;
    QStringList datas{"0104\r", "0105\r", "010B\r", "010C\r",
                      "010D\r", "010F\r", "0110\r", "0111\r"};
    //QStringList datas{"0104\r","010C\r","010D\r","0110\r"};

    std::chrono::high_resolution_clock::time_point prevtime;
    void writeData(const QString& data);
    void processMessage(const QByteArray& message);
    qreal m_counter;

    std::shared_ptr<Datapoint> m_EngineLoadStruct;
    std::shared_ptr<Datapoint> m_CoolantTempStruct;
    std::shared_ptr<Datapoint> m_IntakePressStruct;
    std::shared_ptr<Datapoint> m_RpmStruct;
    std::shared_ptr<Datapoint> m_SpeedStruct;
    std::shared_ptr<Datapoint> m_IntakeTempStruct;
    std::shared_ptr<Datapoint> m_FlowRateStruct;
    std::shared_ptr<Datapoint> m_ThrottlePosStruct;

    QString retval{""};
};


#endif // TCPCLIENT_H
