#include "tcpclientwrapper.h"

TcpClientWrapper::TcpClientWrapper(TcpClient *_client, QObject *parent)
    :QObject(parent), m_client(_client),
    m_Speed(0),
    m_EngineLoad(0),
    m_CoolantTemp(0),
    m_IntakePressure(0),
    m_Rpm(0),
    m_IntakeTemp(0),
    m_Maf(0),
    m_ThrottlePos(0)
{

    connect(m_client, &TcpClient::engineLoadSent, this, &TcpClientWrapper::engineLoadReceived);
    connect(m_client, &TcpClient::coolantTempSent, this, &TcpClientWrapper::coolantTempReceived);
    connect(m_client, &TcpClient::intakePressureSent, this, &TcpClientWrapper::intakePressureReceived);
    connect(m_client, &TcpClient::rpmSent, this, &TcpClientWrapper::rpmReceived);
    connect(m_client, &TcpClient::speedSent, this, &TcpClientWrapper::speedReceived);
    connect(m_client, &TcpClient::intakeTempSent, this, &TcpClientWrapper::intakeTempReceived);
    connect(m_client, &TcpClient::mafSent, this, &TcpClientWrapper::mafReceived);
    connect(m_client, &TcpClient::throttlePosSent, this, &TcpClientWrapper::throttlePosReceived);

}

qreal TcpClientWrapper::getSpeed() const
{
    return m_Speed;
}

qreal TcpClientWrapper::getEngineLoad() const
{
    return m_EngineLoad;
}

qreal TcpClientWrapper::getCoolantTemp() const
{
    return m_CoolantTemp;
}

qreal TcpClientWrapper::getIntakePressure() const
{
    return m_IntakePressure;
}

qreal TcpClientWrapper::getRpm() const
{
    return m_Rpm;
}

qreal TcpClientWrapper::getIntakeTemp() const
{
    return m_IntakeTemp;
}

qreal TcpClientWrapper::getMaf() const
{
    return m_Maf;
}

qreal TcpClientWrapper::getThrottlePos() const
{
    return m_ThrottlePos;
}



void TcpClientWrapper::setSpeed(const qreal &speed)
{
    if(m_Speed == speed)
        return;

    m_Speed = speed;
    emit speedChanged();
}

void TcpClientWrapper::setEngineLoad(const qreal &EngineLoad)
{
    if(m_EngineLoad == EngineLoad)
        return;

    m_EngineLoad = EngineLoad;
    emit engineLoadChanged();
}

void TcpClientWrapper::setCoolantTemp(const qreal &CoolantTemp)
{
    if(m_CoolantTemp == CoolantTemp)
        return;

    m_CoolantTemp = CoolantTemp;
    emit coolantTempChanged();
}

void TcpClientWrapper::setIntakePressure(const qreal &IntakePressure)
{
    if(m_IntakePressure == IntakePressure)
        return;

    m_IntakePressure = IntakePressure;
    emit intakePressureChanged();
}

void TcpClientWrapper::setRpm(const qreal &Rpm)
{
    if(m_Rpm == Rpm)
        return;

    m_Rpm = Rpm;
    emit rpmChanged();
}

void TcpClientWrapper::setIntakeTemp(const qreal &IntakeTemp)
{
    if(m_IntakeTemp == IntakeTemp)
        return;

    m_IntakeTemp = IntakeTemp;
    emit intakeTempChanged();
}

void TcpClientWrapper::setMaf(const qreal &Maf)
{
    if(m_Maf == Maf)
        return;

    m_Maf = Maf;
    emit mafChanged();
}

void TcpClientWrapper::setThrottlePos(const qreal &ThrottlePos)
{
    if(m_ThrottlePos == ThrottlePos)
        return;

    m_ThrottlePos = ThrottlePos;
    emit throttlePosChanged();
}

void TcpClientWrapper::engineLoadReceived(const qreal &_engineload){
    setEngineLoad(_engineload);
}
void TcpClientWrapper::coolantTempReceived(const qreal &_coolantemp){
    setCoolantTemp(_coolantemp);
}
void TcpClientWrapper::intakePressureReceived(const qreal &_intakepressure){
    setIntakePressure(_intakepressure);
}
void TcpClientWrapper::rpmReceived(const qreal &_rpm){
    setRpm(_rpm);
}
void TcpClientWrapper::speedReceived(const qreal &_speed){
    setSpeed(_speed);
}
void TcpClientWrapper::intakeTempReceived(const qreal &_intaketemp){
    setIntakeTemp(_intaketemp);
}
void TcpClientWrapper::mafReceived(const qreal &_maf){
    setMaf(_maf);
}
void TcpClientWrapper::throttlePosReceived(const qreal &_throttlepos){
    setThrottlePos(_throttlepos);
}
