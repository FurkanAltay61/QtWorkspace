#include "dashboard.h"
#include <QPainter>
#include <cmath>
#include <QtMath>

Dashboard::Dashboard(QQuickItem *parent)
    :QQuickPaintedItem(parent),
    m_SpeedometerSize(200), // touch screen is 800 x 480
    m_StartAngle(-140),
    m_AlignAngle(260), // it should be 360 - m_StartAngle*3 for good looking
    m_LowestRange(0),
    m_HighestRange(240),
    m_ArcWidth(5),
    m_OuterColor(QColor(Qt::blue)),
    m_InnerColor(QColor(51,88,255,80)),
    m_TextColor(QColor(255,255,255)),
    m_BackgroundColor(Qt::transparent),
    m_InnerArcWidth(50),
    m_InnerArcPos(45),
    m_ProgressBarPos(42.5),
    m_ProgressBarThickness(13),
    m_InnerCircleSize(50),
    m_Interval(20),
    m_TextBarSize(10),
    m_TickPosOffset(28.5),
    m_TextPosOffset(20),
    m_TickMarkLength(10),
    m_ArcTextSize(8),
    m_ProgBarArcPos(38),
    m_Unit("NULL"),
    m_GaugeName("NULL"),
    m_UnitOffset(50),
    m_GaugeNameOffset(100),
    m_UnitTextSize(7),
    m_GaugeNameTextSize(10),
    m_Speed(0),
    m_EngineLoad(0),
    m_CoolantTemp(0),
    m_IntakePressure(0),
    m_Rpm(0),
    m_IntakeTemp(0),
    m_Maf(0),
    m_ThrottlePos(0),
    m_Val(0)
{
    drawBackgroundPixmap();
}


void Dashboard::engineLoadReceived(const qreal &load){
    setEngineLoad(load);
}
void Dashboard::coolantTempReceived(const qreal &cooltemp){
    setCoolantTemp(cooltemp);
}
void Dashboard::intakePressReceived(const qreal &inpress){
    setIntakePressure(inpress);
}
void Dashboard::rpmReceived(const qreal &rpm){
    setRpm(rpm);
}
void Dashboard::speedReceived(const qreal &speed){
    setSpeed(speed);
}
void Dashboard::IntakeTempReceived(const qreal &intemp){
    setIntakeTemp(intemp);
}
void Dashboard::MassAirFlowReceived(const qreal &maf){
    setMaf(maf);
}
void Dashboard::ThrottlePosReceived(const qreal &throtpos){
    setThrottlePos(throtpos);
}

void Dashboard::drawBackgroundPixmap(){
    m_BackgroundPixmap = QPixmap(300,300);
    m_BackgroundPixmap.fill(Qt::transparent);
    QPainter painter(&m_BackgroundPixmap);
    QRectF rect = this->boundingRect();

    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = painter.pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

    startAngle = m_StartAngle;
    spanAngle = 0 - m_AlignAngle;

    //all arc
    painter.save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_InnerColor);
    painter.setPen(pen);
    painter.drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, spanAngle * 16);
    painter.restore();

    //inner circle
    painter.save();
    painter.setBrush(QBrush(QColor(m_InnerColor)));
    painter.drawEllipse(rect.center(), m_InnerCircleSize, m_InnerCircleSize);
    painter.restore();

    painter.save();
    QFont font("Halvetica",m_TextBarSize,QFont::Bold);
    painter.setFont(font);
    pen.setColor(m_TextColor);
    painter.setPen(pen);
    font.setPointSize(m_UnitTextSize);
    painter.setFont(font);
    painter.drawText(rect.adjusted(m_TextBarSize, m_TextBarSize,
                                    -m_TextBarSize, -m_TextBarSize + m_UnitOffset),
                      Qt::AlignCenter, m_Unit);

    font.setPointSize(m_GaugeNameTextSize);
    painter.setFont(font);
    painter.drawText(rect.adjusted(m_TextBarSize, m_TextBarSize,
                                    -m_TextBarSize, -m_TextBarSize + m_GaugeNameOffset),
                      Qt::AlignCenter, m_GaugeName);

    painter.restore();

    painter.save();
    pen.setWidth(1);
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawArc(rect.adjusted(m_ProgBarArcPos, m_ProgBarArcPos, -m_ProgBarArcPos, -m_ProgBarArcPos), startAngle * 16, spanAngle * 16);
    painter.restore();

    painter.save();
    QColor tickMarkColor = Qt::white;
    painter.setPen(tickMarkColor);

    // Draw tick marks and speed values
    int numTicks = (m_HighestRange - m_LowestRange) / m_Interval;
    font.setPointSize(m_ArcTextSize);
    painter.setFont(font);
    QFontMetrics metrics(painter.font());

    for (int i = 0; i <= numTicks; ++i) {
        int speedValue = m_LowestRange + i * m_Interval;
        qreal angle = startAngle + ((speedValue - m_LowestRange) / (m_HighestRange - m_LowestRange)) * spanAngle;

        // Calculate position for the tick mark
        QPointF tickPos = calculatePosition(rect, angle, m_TickPosOffset);
        QPointF textPos = calculatePosition(rect, angle, m_TextPosOffset - metrics.height());

        // Draw the tick mark
        painter.drawLine(tickPos, QPointF(tickPos.x() + m_TickMarkLength * cos(qDegreesToRadians(angle)), tickPos.y() - m_TickMarkLength * sin(qDegreesToRadians(angle))));  // 10 is the length of the tick mark

        // Prepare to draw the text
        QString text = QString::number(speedValue);
        QRect textRect = metrics.boundingRect(text);
        textRect.moveCenter(textPos.toPoint());

        // Adjust for alignment and draw the text
        painter.drawText(textRect, Qt::AlignCenter, text);
    }
    painter.restore();


}

void Dashboard::paint(QPainter *painter){

    painter->drawPixmap(0,0,m_BackgroundPixmap);

    QRectF rect = this->boundingRect();

    // painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

    startAngle = m_StartAngle;
    spanAngle = 0 - m_AlignAngle;

    //text which shows the value
    painter->save();
    QFont font("Halvetica",m_TextBarSize,QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_TextBarSize, m_TextBarSize,
                                    -m_TextBarSize, -m_TextBarSize),
                                    Qt::AlignCenter, QString::number((m_Val),'f',1));
    painter->restore();

    //current active progress

    painter->save();
     // Set up the gradient
    QLinearGradient gradient(rect.topLeft(),rect.topRight());
    gradient.setColorAt(0.0, QColor(0,255,0, 200)); // Start with fully transparent
    gradient.setColorAt(0.5, QColor(0,0,255, 200)); // Half-way point with semi-transparency
    gradient.setColorAt(1.0, QColor(255,0,0, 200)); // End with fully opaque

    // Set up the pen with the gradient
    QPen gradientPen;
    gradientPen.setWidth(m_ProgressBarThickness);
    gradientPen.setBrush(gradient);
    gradientPen.setCapStyle(Qt::FlatCap);

    // Draw the arc with the gradient pen
    painter->setPen(gradientPen);
    qreal valueToAngle = ((m_Val - m_LowestRange)/(m_HighestRange - m_LowestRange)) * spanAngle;
    painter->drawArc(rect.adjusted(m_ProgressBarPos, m_ProgressBarPos, -m_ProgressBarPos, -m_ProgressBarPos), startAngle * 16, valueToAngle * 16);
    painter->restore();
}

QPointF Dashboard::calculatePosition(const QRectF &rect, qreal angle, qreal offset) {
    qreal radian = qDegreesToRadians(angle);
    qreal x = rect.center().x() + (rect.width() / 2.5 - offset) * cos(radian);
    qreal y = rect.center().y() - (rect.height() / 2.5 - offset) * sin(radian);
    return QPointF(x, y);
}


qreal Dashboard::getSpeedometerSize() const
{
    return m_SpeedometerSize;
}

qreal Dashboard::getStartAngle() const
{
    return m_StartAngle;
}

qreal Dashboard::getAlignAngle() const
{
    return m_AlignAngle;
}

qreal Dashboard::getLowestRange() const
{
    return m_LowestRange;
}

qreal Dashboard::getHighestRange() const
{
    return m_HighestRange;
}

int Dashboard::getArcWidth() const
{
    return m_ArcWidth;
}

QColor Dashboard::getOuterColor() const
{
    return m_OuterColor;
}

QColor Dashboard::getInnerColor() const
{
    return m_InnerColor;
}

QColor Dashboard::getTextColor() const
{
    return m_TextColor;
}

QColor Dashboard::getBackgroundColor() const
{
    return m_BackgroundColor;
}

int Dashboard::getInnerArcWidth() const
{
    return m_InnerArcWidth;
}

int Dashboard::getInnerArcPos() const
{
    return m_InnerArcPos;
}

qreal Dashboard::getProgressBarPos() const
{
    return m_ProgressBarPos;
}

qreal Dashboard::getProgressBarThickness() const
{
    return m_ProgressBarThickness;
}

qreal Dashboard::getInnerCircleSize() const
{
    return m_InnerCircleSize;
}

int Dashboard::getInterval() const
{
    return m_Interval;
}

qreal Dashboard::getTextBarSize() const
{
    return m_TextBarSize;
}

qreal Dashboard::getTickPosOffset() const
{
    return m_TickPosOffset;
}

qreal Dashboard::getTextPosOffset() const
{
    return m_TextPosOffset;
}

qreal Dashboard::getTickMarkLength() const
{
    return m_TickMarkLength;
}

qreal Dashboard::getArcTextSize() const
{
    return m_ArcTextSize;
}

qreal Dashboard::getProgBarArcPos() const
{
    return m_ProgBarArcPos;
}

QString Dashboard::getUnit() const
{
    return m_Unit;
}

QString Dashboard::getGaugeName() const
{
    return m_GaugeName;
}

qreal Dashboard::getUnitOffset() const
{
    return m_UnitOffset;
}

qreal Dashboard::getGaugeNameOffset() const
{
    return m_GaugeNameOffset;
}

qreal Dashboard::getUnitTextSize() const
{
    return m_UnitTextSize;
}

qreal Dashboard::getGaugeNameTextSize() const
{
    return m_GaugeNameTextSize;
}

qreal Dashboard::getSpeed() const
{
    return m_Speed;
}

double Dashboard::getEngineLoad() const
{
    return m_EngineLoad;
}

int Dashboard::getCoolantTemp() const
{
    return m_CoolantTemp;
}

int Dashboard::getIntakePressure() const
{
    return m_IntakePressure;
}

double Dashboard::getRpm() const
{
    return m_Rpm;
}

int Dashboard::getIntakeTemp() const
{
    return m_IntakeTemp;
}

double Dashboard::getMaf() const
{
    return m_Maf;
}

double Dashboard::getThrottlePos() const
{
    return m_ThrottlePos;
}

qreal  Dashboard::getVal() const
{
    return m_Val;
}



void Dashboard::setSpeedometerSize(const qreal &size)
{
    if(m_SpeedometerSize == size)
        return;
    m_SpeedometerSize = size;
    drawBackgroundPixmap();
    update();
    emit speedometerSizeChanged();
}

void Dashboard::setStartAngle(const qreal &startAngle)
{
    if(m_StartAngle == startAngle)
        return;

    m_StartAngle = startAngle;
    drawBackgroundPixmap();
    update();
    emit startAngleChanged();
}

void Dashboard::setAlignAngle(const qreal &angle)
{
    if(m_StartAngle == angle)
        return;

    m_StartAngle = angle;
    drawBackgroundPixmap();
    update();
    emit alignAngleChanged();
}

void Dashboard::setLowestRange(const qreal &lowestRange)
{
    if(m_LowestRange == lowestRange)
        return;

    m_LowestRange = lowestRange;
    drawBackgroundPixmap();
    update();
    emit lowestRangeChanged();
}

void Dashboard::setHighestRange(const qreal &highestRange)
{
    if(m_HighestRange == highestRange)
        return;

    m_HighestRange = highestRange;
    drawBackgroundPixmap();
    update();
    emit highestRangeChanged();
}

void Dashboard::setArcWidth(const int &arcWidth)
{
    if(m_ArcWidth == arcWidth)
        return;

    m_ArcWidth = arcWidth;
    drawBackgroundPixmap();
    update();
    emit arcWidthChanged();
}

void Dashboard::setOuterColor(const QColor &outerColor)
{
    if(m_OuterColor == outerColor)
        return;

    m_OuterColor = outerColor;
    drawBackgroundPixmap();
    update();
    emit outerColorChanged();
}

void Dashboard::setInnerColor(const QColor &innerColor)
{
    if(m_InnerColor == innerColor)
        return;

    m_InnerColor = innerColor;
    drawBackgroundPixmap();
    update();
    emit innerColorChanged();
}

void Dashboard::setTextColor(const QColor &textColor)
{
    if(m_TextColor == textColor)
        return;

    m_TextColor = textColor;
    drawBackgroundPixmap();
    update();
    emit textColorChanged();
}

void Dashboard::setBackgroundColor(const QColor &backgroundColor)
{
    if(m_BackgroundColor == backgroundColor)
        return;

    m_BackgroundColor = backgroundColor;
    drawBackgroundPixmap();
    update();
    emit backgroundColorChanged();
}



void Dashboard::setInnerArcWidth(const int &InnerArcWidth){
    if(m_InnerArcWidth == InnerArcWidth)
        return;

    m_InnerArcWidth = InnerArcWidth;
    drawBackgroundPixmap();
    update();
    emit innerArcWidthChanged();
}

void Dashboard::setInnerArcPos(const int &InnerArcPos){
    if(m_InnerArcPos == InnerArcPos)
        return;

    m_InnerArcPos = InnerArcPos;
    drawBackgroundPixmap();
    update();
    emit innerArcPosChanged();
}

void Dashboard::setProgressBarPos(const qreal &ProgressBarPos){
    if(m_ProgressBarPos == ProgressBarPos)
        return;

    m_ProgressBarPos = ProgressBarPos;
    drawBackgroundPixmap();
    update();
    emit progressBarPosChanged();
}

void Dashboard::setProgressBarThickness(const qreal &ProgressBarThickness){
    if(m_ProgressBarThickness == ProgressBarThickness)
        return;

    m_ProgressBarThickness = ProgressBarThickness;
    drawBackgroundPixmap();
    update();
    emit progressBarThicknessChanged();
}

void Dashboard::setInnerCircleSize(const qreal &InnerCircleSize){
    if(m_InnerCircleSize == InnerCircleSize)
        return;

    m_InnerCircleSize = InnerCircleSize;
    drawBackgroundPixmap();
    update();
    emit innerCircleSizeChanged();
}

void Dashboard::setInterval(const int &Interval){
    if(m_Interval == Interval)
        return;

    m_Interval = Interval;
    drawBackgroundPixmap();
    update();
    emit intervalChanged();
}

void Dashboard::setTextBarSize(const qreal &TextBarSize){
    if(m_TextBarSize == TextBarSize)
        return;

    m_TextBarSize = TextBarSize;
    drawBackgroundPixmap();
    update();
    emit textBarSizeChanged();
}

void Dashboard::setTickPosOffset(const qreal &TickPosOffset){
    if(m_TickPosOffset == TickPosOffset)
        return;

    m_TickPosOffset = TickPosOffset;
    drawBackgroundPixmap();
    update();
    emit tickPosOffsetChanged();
}

void Dashboard::setTextPosOffset(const qreal &TextPosOffset){
    if(m_TextPosOffset == TextPosOffset)
        return;

    m_TextPosOffset = TextPosOffset;
    drawBackgroundPixmap();
    update();
    emit textPosOffsetChanged();
}

void Dashboard::setTickMarkLength(const qreal &TickMarkLength){
    if(m_TickMarkLength == TickMarkLength)
        return;

    m_TickMarkLength = TickMarkLength;
    drawBackgroundPixmap();
    update();
    emit tickMarkLengthChanged();
}


void Dashboard::setArcTextSize(const qreal &ArcTextSize){
    if(m_ArcTextSize == ArcTextSize)
        return;
    m_ArcTextSize = ArcTextSize;
    drawBackgroundPixmap();
    update();
    emit arcTextSizeChanged();
}

void Dashboard::setProgBarArcPos(const qreal &ProgBarArcPos){
    if(m_ProgBarArcPos == ProgBarArcPos)
        return;
    m_ProgBarArcPos = ProgBarArcPos;
    drawBackgroundPixmap();
    update();
    emit progBarArcPosChanged();
}

void Dashboard::setUnit(const QString &Unit){
    if(m_Unit == Unit)
        return;
    m_Unit = Unit;
    drawBackgroundPixmap();
    update();
    emit unitChanged();
}

void Dashboard::setGaugeName(const QString &GaugeName){
    if(m_GaugeName == GaugeName)
        return;
    m_GaugeName = GaugeName;
    drawBackgroundPixmap();
    update();
    emit gaugeNameChanged();
}

void Dashboard::setUnitOffset(const qreal &UnitOffset){
    if(m_UnitOffset == UnitOffset)
        return;
    m_UnitOffset = UnitOffset;
    drawBackgroundPixmap();
    update();
    emit unitOffsetChanged();
}

void Dashboard::setGaugeNameOffset(const qreal &GaugeNameOffset){
    if(m_GaugeNameOffset == GaugeNameOffset)
        return;
    m_GaugeNameOffset = GaugeNameOffset;
    drawBackgroundPixmap();
    update();
    emit gaugeNameOffsetChanged();
}

void Dashboard::setUnitTextSize(const qreal &UnitTextSize){
    if(m_UnitTextSize == UnitTextSize)
        return;
    m_UnitTextSize = UnitTextSize;
    drawBackgroundPixmap();
    update();
    emit unitTextSizeChanged();
}
void Dashboard::setGaugeNameTextSize(const qreal &GaugeNameTextSize){
    if(m_GaugeNameTextSize == GaugeNameTextSize)
        return;
    m_GaugeNameTextSize = GaugeNameTextSize;
    drawBackgroundPixmap();
    update();
    emit gaugeNameTextSizeChanged();
}



void Dashboard::setSpeed(const qreal &speed)
{
    if(m_Speed == speed)
        return;

    m_Speed = speed;
    //update();
    emit speedChanged();
}

void Dashboard::setEngineLoad(const qreal &EngineLoad)
{
    if(m_EngineLoad == EngineLoad)
        return;

    m_EngineLoad = EngineLoad;
    //update();
    emit engineLoadChanged();
}

void Dashboard::setCoolantTemp(const qreal &CoolantTemp)
{
    if(m_CoolantTemp == CoolantTemp)
        return;

    m_CoolantTemp = CoolantTemp;
    //update();
    emit coolantTempChanged();
}

void Dashboard::setIntakePressure(const qreal &IntakePressure)
{
    if(m_IntakePressure == IntakePressure)
        return;

    m_IntakePressure = IntakePressure;
    //update();
    emit intakePressureChanged();
}

void Dashboard::setRpm(const qreal &Rpm)
{
    if(m_Rpm == Rpm)
        return;

    m_Rpm = Rpm;
    //update();
    emit rpmChanged();
}

void Dashboard::setIntakeTemp(const qreal &IntakeTemp)
{
    if(m_IntakeTemp == IntakeTemp)
        return;

    m_IntakeTemp = IntakeTemp;
    //update();
    emit intakeTempChanged();
}

void Dashboard::setMaf(const qreal &Maf)
{
    if(m_Maf == Maf)
        return;

    m_Maf = Maf;
    //update();
    emit mafChanged();
}

void Dashboard::setThrottlePos(const qreal &ThrottlePos)
{
    if(m_ThrottlePos == ThrottlePos)
        return;

    m_ThrottlePos = ThrottlePos;
    //update();
    emit throttlePosChanged();
}

void Dashboard::setVal(const qreal &mval){
    if(m_Val == mval)
        return;

    m_Val = mval;
    update();
    emit valChanged();
}

