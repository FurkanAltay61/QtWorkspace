#ifndef TCPCLIENTWRAPPER_H
#define TCPCLIENTWRAPPER_H

#include "tcpclient.h"

class TcpClientWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qreal engineload READ getEngineLoad WRITE setEngineLoad NOTIFY engineLoadChanged)
    Q_PROPERTY(qreal coolanttemp READ getCoolantTemp WRITE setCoolantTemp NOTIFY coolantTempChanged)
    Q_PROPERTY(qreal intakepressure READ getIntakePressure WRITE setIntakePressure NOTIFY intakePressureChanged)
    Q_PROPERTY(qreal rpm READ getRpm WRITE setRpm NOTIFY rpmChanged)
    Q_PROPERTY(qreal intaketemp READ getIntakeTemp WRITE setIntakeTemp NOTIFY intakeTempChanged)
    Q_PROPERTY(qreal maf READ getMaf WRITE setMaf NOTIFY mafChanged)
    Q_PROPERTY(qreal throttlepos READ getThrottlePos WRITE setThrottlePos NOTIFY throttlePosChanged)
public:
    TcpClientWrapper(TcpClient *_client = nullptr, QObject *parent = nullptr);

    void    setSpeed(const qreal &Speed);
    void    setEngineLoad(const qreal &EngineLoad);
    void    setCoolantTemp(const qreal &CoolantTemp);
    void    setIntakePressure(const qreal &IntakePressure);
    void    setRpm(const qreal &Rpm);
    void    setIntakeTemp(const qreal &IntakeTemp);
    void    setMaf(const qreal &Maf);
    void    setThrottlePos(const qreal &ThrottlePos);

    qreal   getSpeed() const;
    qreal   getEngineLoad() const;
    qreal   getCoolantTemp() const;
    qreal   getIntakePressure() const;
    qreal   getRpm() const;
    qreal   getIntakeTemp() const;
    qreal   getMaf() const;
    qreal   getThrottlePos() const;

signals:
    void    speedChanged();
    void    engineLoadChanged();
    void    coolantTempChanged();
    void    intakePressureChanged();
    void    rpmChanged();
    void    intakeTempChanged();
    void    mafChanged();
    void    throttlePosChanged();

public slots:
    void    engineLoadReceived(const qreal &_engineload);
    void    coolantTempReceived(const qreal &_coolantemp);
    void    intakePressureReceived(const qreal &_intakepressure);
    void    rpmReceived(const qreal &_rpm);
    void    speedReceived(const qreal &_speed);
    void    intakeTempReceived(const qreal &_intaketemp);
    void    mafReceived(const qreal &_maf);
    void    throttlePosReceived(const qreal &_throttlepos);

private:
    TcpClient *m_client;
    qreal   m_Speed;
    qreal   m_EngineLoad;
    qreal   m_CoolantTemp;
    qreal   m_IntakePressure;
    qreal   m_Rpm;
    qreal   m_IntakeTemp;
    qreal   m_Maf;
    qreal   m_ThrottlePos;
};

#endif // TCPCLIENTWRAPPER_H
