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

    connect(m_client, &TcpClient::engineLoadDurationSent, this, &TcpClientWrapper::engineLoadDurationReceived);
    connect(m_client, &TcpClient::coolantTempDurationSent, this, &TcpClientWrapper::coolantTempDurationReceived);
    connect(m_client, &TcpClient::intakePressureDurationSent, this, &TcpClientWrapper::intakePressureDurationReceived);
    connect(m_client, &TcpClient::rpmDurationSent, this, &TcpClientWrapper::rpmDurationReceived);
    connect(m_client, &TcpClient::speedDurationSent, this, &TcpClientWrapper::speedDurationReceived);
    connect(m_client, &TcpClient::intakeTempDurationSent, this, &TcpClientWrapper::intakeTempDurationReceived);
    connect(m_client, &TcpClient::mafDurationSent, this, &TcpClientWrapper::mafDurationReceived);
    connect(m_client, &TcpClient::throttlePosDurationSent, this, &TcpClientWrapper::throttlePosDurationReceived);

    connect(m_client, &TcpClient::statMsgSent, this, &TcpClientWrapper::statMsgReceived);

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




qreal TcpClientWrapper::getSpeedDuration() const
{
    return m_SpeedDuration;
}

qreal TcpClientWrapper::getEngineLoadDuration() const
{
    return m_EngineLoadDuration;
}

qreal TcpClientWrapper::getCoolantTempDuration() const
{
    return m_CoolantTempDuration;
}

qreal TcpClientWrapper::getIntakePressureDuration() const
{
    return m_IntakePressureDuration;
}

qreal TcpClientWrapper::getRpmDuration() const
{
    return m_RpmDuration;
}

qreal TcpClientWrapper::getIntakeTempDuration() const
{
    return m_IntakeTempDuration;
}

qreal TcpClientWrapper::getMafDuration() const
{
    return m_MafDuration;
}

qreal TcpClientWrapper::getThrottlePosDuration() const
{
    return m_ThrottlePosDuration;
}



void TcpClientWrapper::setSpeedDuration(const qreal &_SpeedDuration)
{
    if(m_SpeedDuration == _SpeedDuration)
        return;

    m_SpeedDuration = _SpeedDuration;
    emit speedDurationChanged();
}

void TcpClientWrapper::setEngineLoadDuration(const qreal &_EngineLoadDuration)
{
    if(m_EngineLoadDuration == _EngineLoadDuration)
        return;

    m_EngineLoadDuration = _EngineLoadDuration;
    emit engineLoadDurationChanged();
}

void TcpClientWrapper::setCoolantTempDuration(const qreal &_CoolantTempDuration)
{
    if(m_CoolantTempDuration == _CoolantTempDuration)
        return;

    m_CoolantTempDuration = _CoolantTempDuration;
    emit coolantTempDurationChanged();
}

void TcpClientWrapper::setIntakePressureDuration(const qreal &_IntakePressureDuration)
{
    if(m_IntakePressureDuration == _IntakePressureDuration)
        return;

    m_IntakePressureDuration = _IntakePressureDuration;
    emit intakePressureDurationChanged();
}

void TcpClientWrapper::setRpmDuration(const qreal &_RpmDuration)
{
    if(m_RpmDuration == _RpmDuration)
        return;

    m_RpmDuration = _RpmDuration;
    //qDebug()<< "m_RpmDuration :" << m_RpmDuration;
    emit rpmDurationChanged();
}

void TcpClientWrapper::setIntakeTempDuration(const qreal &_IntakeTempDuration)
{
    if(m_IntakeTempDuration == _IntakeTempDuration)
        return;

    m_IntakeTempDuration = _IntakeTempDuration;
    emit intakeTempDurationChanged();
}

void TcpClientWrapper::setMafDuration(const qreal &_MafDuration)
{
    if(m_MafDuration == _MafDuration)
        return;

    m_MafDuration = _MafDuration;
    emit mafDurationChanged();
}

void TcpClientWrapper::setThrottlePosDuration(const qreal &_ThrottlePosDuration)
{
    if(m_ThrottlePosDuration == _ThrottlePosDuration)
        return;

    m_ThrottlePosDuration = _ThrottlePosDuration;
    emit throttlePosDurationChanged();
}


void TcpClientWrapper::setStatMsg(QString _statMsg){
    if(m_StatMsg == _statMsg)
        return;

    m_StatMsg = _statMsg;
    emit statMsgChanged();
}

QString TcpClientWrapper::getStatMsg(){
    return m_StatMsg;
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


void TcpClientWrapper::engineLoadDurationReceived(const qreal &_engineloadduration){
    setEngineLoadDuration(_engineloadduration);
}
void TcpClientWrapper::coolantTempDurationReceived(const qreal &_coolantempduration){
    setCoolantTempDuration(_coolantempduration);
}
void TcpClientWrapper::intakePressureDurationReceived(const qreal &_intakepressureduration){
    setIntakePressureDuration(_intakepressureduration);
}
void TcpClientWrapper::rpmDurationReceived(const qreal &_rpmduration){
    //qDebug() << "Geldi :" << _rpmduration;
    setRpmDuration(_rpmduration);
}
void TcpClientWrapper::speedDurationReceived(const qreal &_speedduration){
    setSpeedDuration(_speedduration);
}
void TcpClientWrapper::intakeTempDurationReceived(const qreal &_intaketempduration){
    setIntakeTempDuration(_intaketempduration);
}
void TcpClientWrapper::mafDurationReceived(const qreal &_mafduration){
    setMafDuration(_mafduration);
}
void TcpClientWrapper::throttlePosDurationReceived(const qreal &_throttleposduration){
    setThrottlePosDuration(_throttleposduration);
}

void TcpClientWrapper::statMsgReceived(const QString &_statMsg){
    setStatMsg(_statMsg);
}

bool TcpClientWrapper::getTestMode(){
#ifdef TEST_MODE
    return true;
#else
    return false;
#endif
}

qreal TcpClientWrapper::getSendingPeriod(){
    return 200;
}
