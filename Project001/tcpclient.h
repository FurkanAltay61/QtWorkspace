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
    const int SAMPLE_PERIOD = 100;
    const int SENDING_PERIOD = 300;
public:
    explicit TcpClient(const QString& ip, quint16 port, QObject* parent = nullptr);
    void connectToServer();
    struct Datapoint
    {
        uint64_t prevTime;
        uint64_t currTime;
        double prevValue;
        double currValue;
        double   slope;
        double   sampledValue;
    };

private slots:
    void onConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
    void onSendData();

public slots:
    void updateDashboard();

signals:
    void dataSent(const QString &data);
    void engineLoadSent(const double load);
    void coolantTempSent(const int cooltemp);
    void intakePressSent(const int inpress);
    void rpmSent(const double rpm);
    void speedSent(const int speed);
    void intakeTempSent(const int intemp);
    void massAirFlowSent(const double maf);
    void throttlePosSent(const double throtpos);


private:
    QTcpSocket* tcpSocket;
    QString serverIP;
    quint16 serverPort;
    QTimer* sendTimer;
    QByteArray buffer;
    QStringList datas{"0104\r", "0105\r", "010B\r", "010C\r",
                      "010D\r", "010F\r", "0110\r", "0111\r"};
    std::chrono::high_resolution_clock::time_point prevtime;
    void writeData(const QString& data);
    void processMessage(const QByteArray& message);
    QTimer  m_timer;
    volatile qreal m_counter;

    std::shared_ptr<Datapoint> m_EngineLoadStruct;
    std::shared_ptr<Datapoint> m_CoolantTempStruct;
    std::shared_ptr<Datapoint> m_IntakePressStruct;
    std::shared_ptr<Datapoint> m_RpmStruct;
    std::shared_ptr<Datapoint> m_SpeedStruct;
    std::shared_ptr<Datapoint> m_IntakeTempStruct;
    std::shared_ptr<Datapoint> m_FlowRateStruct;
    std::shared_ptr<Datapoint> m_ThrottlePosStruct;
};


#endif // TCPCLIENT_H
