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

    Q_PROPERTY(qreal speed_duration READ getSpeedDuration WRITE setSpeedDuration NOTIFY speedDurationChanged)
    Q_PROPERTY(qreal engineload_duration READ getEngineLoadDuration WRITE setEngineLoadDuration NOTIFY engineLoadDurationChanged)
    Q_PROPERTY(qreal coolanttemp_duration READ getCoolantTempDuration WRITE setCoolantTempDuration NOTIFY coolantTempDurationChanged)
    Q_PROPERTY(qreal intakepressure_duration READ getIntakePressureDuration WRITE setIntakePressureDuration NOTIFY intakePressureDurationChanged)
    Q_PROPERTY(qreal rpm_duration READ getRpmDuration WRITE setRpmDuration NOTIFY rpmDurationChanged)
    Q_PROPERTY(qreal intaketemp_duration READ getIntakeTempDuration WRITE setIntakeTempDuration NOTIFY intakeTempDurationChanged)
    Q_PROPERTY(qreal maf_duration READ getMafDuration WRITE setMafDuration NOTIFY mafDurationChanged)
    Q_PROPERTY(qreal throttlepos_duration READ getThrottlePosDuration WRITE setThrottlePosDuration NOTIFY throttlePosDurationChanged)

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

    void    setSpeedDuration(const qreal &_SpeedDuration);
    void    setEngineLoadDuration(const qreal &_EngineLoadDuration);
    void    setCoolantTempDuration(const qreal &_CoolantTempDuration);
    void    setIntakePressureDuration(const qreal &_IntakePressureDuration);
    void    setRpmDuration(const qreal &_RpmDuration);
    void    setIntakeTempDuration(const qreal &_IntakeTempDuration);
    void    setMafDuration(const qreal &_MafDuration);
    void    setThrottlePosDuration(const qreal &_ThrottlePosDuration);

    qreal   getSpeedDuration() const;
    qreal   getEngineLoadDuration() const;
    qreal   getCoolantTempDuration() const;
    qreal   getIntakePressureDuration() const;
    qreal   getRpmDuration() const;
    qreal   getIntakeTempDuration() const;
    qreal   getMafDuration() const;
    qreal   getThrottlePosDuration() const;

signals:
    void    speedChanged();
    void    engineLoadChanged();
    void    coolantTempChanged();
    void    intakePressureChanged();
    void    rpmChanged();
    void    intakeTempChanged();
    void    mafChanged();
    void    throttlePosChanged();

    void    resetSignal();

    void    speedDurationChanged();
    void    engineLoadDurationChanged();
    void    coolantTempDurationChanged();
    void    intakePressureDurationChanged();
    void    rpmDurationChanged();
    void    intakeTempDurationChanged();
    void    mafDurationChanged();
    void    throttlePosDurationChanged();

public slots:
    void    engineLoadReceived(const qreal &_engineload);
    void    coolantTempReceived(const qreal &_coolantemp);
    void    intakePressureReceived(const qreal &_intakepressure);
    void    rpmReceived(const qreal &_rpm);
    void    speedReceived(const qreal &_speed);
    void    intakeTempReceived(const qreal &_intaketemp);
    void    mafReceived(const qreal &_maf);
    void    throttlePosReceived(const qreal &_throttlepos);

    void    engineLoadDurationReceived(const qreal &_engineload);
    void    coolantTempDurationReceived(const qreal &_coolantemp);
    void    intakePressureDurationReceived(const qreal &_intakepressure);
    void    rpmDurationReceived(const qreal &_rpm);
    void    speedDurationReceived(const qreal &_speed);
    void    intakeTempDurationReceived(const qreal &_intaketemp);
    void    mafDurationReceived(const qreal &_maf);
    void    throttlePosDurationReceived(const qreal &_throttlepos);

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

    qreal   m_SpeedDuration;
    qreal   m_EngineLoadDuration;
    qreal   m_CoolantTempDuration;
    qreal   m_IntakePressureDuration;
    qreal   m_RpmDuration;
    qreal   m_IntakeTempDuration;
    qreal   m_MafDuration;
    qreal   m_ThrottlePosDuration;
};

#endif // TCPCLIENTWRAPPER_H
