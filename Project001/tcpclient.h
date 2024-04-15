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
#include <QDateTime>
#include <QProcess>
#include <QMap>
#include <QString>

#define TEST_MODE

class TcpClient : public QObject {
    Q_OBJECT


public:
    explicit TcpClient(const QString& ip, quint16 port, QObject* parent = nullptr);
    ~TcpClient();
    void connectToServer();
    struct Datapoint
    {
        uint64_t prevTime;
        qreal    data;
    };

private slots:
    void onConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
    void updateData();

public slots:
    void handleResetSignal();
    void handleConnectSignal();
    void handleRebootSignal();

signals:
    void    engineLoadSent(const qreal &_engineload);
    void    coolantTempSent(const qreal &_coolantemp);
    void    intakePressureSent(const qreal &_intakepressure);
    void    rpmSent(const qreal &_rpm);
    void    speedSent(const qreal &_speed);
    void    intakeTempSent(const qreal &_intaketemp);
    void    mafSent(const qreal &_maf);
    void    throttlePosSent(const qreal &_throttlepos);

    void    engineLoadDurationSent(const qreal &_engineloadduration);
    void    coolantTempDurationSent(const qreal &_coolantempduration);
    void    intakePressureDurationSent(const qreal &_intakepressureduration);
    void    rpmDurationSent(const qreal &_rpmduration);
    void    speedDurationSent(const qreal &_speedduration);
    void    intakeTempDurationSent(const qreal &_intaketempduration);
    void    mafDurationSent(const qreal &_mafduration);
    void    throttlePosDurationSent(const qreal &_throttleposduration);

    void    statMsgSent(const QString &_statMsg);

private:
    QTcpSocket* tcpSocket;
    QString serverIP;
    quint16 serverPort;
    QByteArray buffer;

    void processMessage(const QByteArray& message);
    void writeData(const QString& data);
    void configureOBDII();

    std::shared_ptr<Datapoint> m_EngineLoadStruct;
    std::shared_ptr<Datapoint> m_CoolantTempStruct;
    std::shared_ptr<Datapoint> m_IntakePressStruct;
    std::shared_ptr<Datapoint> m_RpmStruct;
    std::shared_ptr<Datapoint> m_SpeedStruct;
    std::shared_ptr<Datapoint> m_IntakeTempStruct;
    std::shared_ptr<Datapoint> m_FlowRateStruct;
    std::shared_ptr<Datapoint> m_ThrottlePosStruct;

    QTimer *timer;

    struct Request {
        QString type;
        QString command;
        qint64 lastRequested;
        int interval;
        int retryCount;
        bool isSent;

        Request(QString t, QString cmd, qint64 lr, int i, int rtrcount) :
            type(t), command(cmd), lastRequested(lr), interval(i), retryCount(rtrcount) {
            isSent = true;
        }
    };

    std::vector<Request> requests;
    size_t currentRequestIndex = 0; // Tracks the current request index
};

#endif // TCPCLIENT_H
