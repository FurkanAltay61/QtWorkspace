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
    m_Speed(0),
    m_ArcWidth(5),
    m_OuterColor(QColor(Qt::blue)),
    m_InnerColor(QColor(51,88,255,80)),
    m_TextColor(QColor(255,255,255)),
    m_BackgroundColor(Qt::transparent),
    m_InnerArcWidth(50),
    m_InnerArcPos(45),
    m_ProgressBarPos(m_SpeedometerSize / 4.7),
    m_ProgressBarThickness(13),
    m_InnerCircleSize(m_SpeedometerSize / 4),
    m_Interval(20),
    m_TextBarSize(10),
    m_TickPosOffset(28.5),
    m_TextPosOffset(20)
{
    connect(&m_timer,&QTimer::timeout, this, &Dashboard::updateDashboard);
    m_timer.start(50);
}


void Dashboard::updateDashboard() {
    if(m_val >= 240)
        m_direction = false;
    else if(m_val <= 0.1)
        m_direction = true;

    m_val += m_direction ? 1 : -1;

    setSpeed(m_val);
}

void Dashboard::paint(QPainter *painter){
    QRectF rect = this->boundingRect();

    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

    startAngle = m_StartAngle;
    spanAngle = 0 - m_AlignAngle;

    //all arc
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_InnerColor);
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();

    //inner circle
    painter->save();
    painter->setBrush(QBrush(QColor(m_InnerColor)));
    painter->drawEllipse(rect.center(), m_InnerCircleSize, m_InnerCircleSize);
    painter->restore();

    //text which shows the value
    painter->save();
    QFont font("Halvetica",m_TextBarSize,QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_TextBarSize, m_TextBarSize,
                                    -m_TextBarSize, -m_TextBarSize),
                                    Qt::AlignCenter, QString::number((m_Speed),'f',1));
    painter->restore();

    painter->save();
    QColor tickMarkColor = Qt::white;
    painter->setPen(tickMarkColor);

    // Draw tick marks and speed values
    int numTicks = (m_HighestRange - m_LowestRange) / m_Interval;
    QFontMetrics metrics(painter->font());

    for (int i = 0; i <= numTicks; ++i) {
        int speedValue = m_LowestRange + i * m_Interval;
        qreal angle = startAngle + ((speedValue - m_LowestRange) / (m_HighestRange - m_LowestRange)) * spanAngle;

        // Calculate position for the tick mark
        QPointF tickPos = calculatePosition(rect, angle, m_TickPosOffset);
        QPointF textPos = calculatePosition(rect, angle, m_TextPosOffset - metrics.height());

        // Draw the tick mark
        painter->drawLine(tickPos, QPointF(tickPos.x() + 10 * cos(qDegreesToRadians(angle)), tickPos.y() - 10 * sin(qDegreesToRadians(angle))));  // 10 is the length of the tick mark

        // Prepare to draw the text
        QString text = QString::number(speedValue);
        QRect textRect = metrics.boundingRect(text);
        textRect.moveCenter(textPos.toPoint());

        // Adjust for alignment and draw the text
        painter->drawText(textRect, Qt::AlignCenter, text);
    }
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
    qreal valueToAngle = ((m_Speed - m_LowestRange)/(m_HighestRange - m_LowestRange)) * spanAngle;
    painter->drawArc(rect.adjusted(m_ProgressBarPos, m_ProgressBarPos, -m_ProgressBarPos, -m_ProgressBarPos), startAngle * 16, valueToAngle * 16);
    painter->restore();
}

QPointF Dashboard::calculatePosition(const QRectF &rect, qreal angle, qreal offset) {
    qreal radian = qDegreesToRadians(angle);
    qreal x = rect.center().x() + (rect.width() / 2.5 - offset) * cos(radian);
    qreal y = rect.center().y() - (rect.height() / 2.5 - offset) * sin(radian);
    return QPointF(x, y);
}


qreal Dashboard::getSpeedometerSize()
{
    return m_SpeedometerSize;
}

qreal Dashboard::getStartAngle()
{
    return m_StartAngle;
}


qreal Dashboard::getAlignAngle()
{
    return m_AlignAngle;
}


qreal Dashboard::getLowestRange()
{
    return m_LowestRange;
}

qreal Dashboard::getHighestRange()
{
    return m_HighestRange;
}

qreal Dashboard::getSpeed()
{
    return m_Speed;
}

int Dashboard::getArcWidth()
{
    return m_ArcWidth;
}

QColor Dashboard::getOuterColor()
{
    return m_OuterColor;
}

QColor Dashboard::getInnerColor()
{
    return m_InnerColor;
}

QColor Dashboard::getTextColor()
{
    return m_TextColor;
}

QColor Dashboard::getBackgroundColor()
{
    return m_BackgroundColor;
}

int Dashboard::getInnerArcWidth(){
    return m_InnerArcWidth;
}

int Dashboard::getInnerArcPos(){
    return m_InnerArcPos;
}

qreal Dashboard::getProgressBarPos(){
    return m_ProgressBarPos;
}

qreal Dashboard::getProgressBarThickness(){
    return m_ProgressBarThickness;
}

qreal Dashboard::getInnerCircleSize(){
    return m_InnerCircleSize;
}

int Dashboard::getInterval(){
    return m_Interval;
}

qreal Dashboard::getTextBarSize(){
    return m_TextBarSize;
}

qreal Dashboard::getTickPosOffset(){
    return m_TickPosOffset;
}

qreal Dashboard::getTextPosOffset(){
    return m_TextPosOffset;
}





void Dashboard::setSpeedometerSize(qreal size)
{
    if(m_SpeedometerSize == size)
        return;
    m_SpeedometerSize = size;

    emit speedometerSizeChanged();
}

void Dashboard::setStartAngle(qreal startAngle)
{
    if(m_StartAngle == startAngle)
        return;

    m_StartAngle = startAngle;

    emit startAngleChanged();
}

void Dashboard::setAlignAngle(qreal angle)
{
    if(m_StartAngle == angle)
        return;

    m_StartAngle = angle;

    emit alignAngleChanged();
}

void Dashboard::setLowestRange(qreal lowestRange)
{
    if(m_LowestRange == lowestRange)
        return;

    m_LowestRange = lowestRange;

    emit lowestRangeChanged();
}

void Dashboard::setHighestRange(qreal highestRange)
{
    if(m_HighestRange == highestRange)
        return;

    m_HighestRange = highestRange;

    emit highestRangeChanged();
}

void Dashboard::setSpeed(qreal speed)
{
    if(m_Speed == speed)
        return;

    m_Speed = speed;
    update();
    emit speedChanged();
}

void Dashboard::setArcWidth(int arcWidth)
{
    if(m_ArcWidth == arcWidth)
        return;

    m_ArcWidth = arcWidth;

    emit arcWidthChanged();
}

void Dashboard::setOuterColor(QColor outerColor)
{
    if(m_OuterColor == outerColor)
        return;

    m_OuterColor = outerColor;

    emit outerColorChanged();
}

void Dashboard::setInnerColor(QColor innerColor)
{
    if(m_InnerColor == innerColor)
        return;

    m_InnerColor = innerColor;

    emit innerColorChanged();
}

void Dashboard::setTextColor(QColor textColor)
{
    if(m_TextColor == textColor)
        return;

    m_TextColor = textColor;

    emit textColorChanged();
}

void Dashboard::setBackgroundColor(QColor backgroundColor)
{
    if(m_BackgroundColor == backgroundColor)
        return;

    m_BackgroundColor = backgroundColor;

    emit backgroundColorChanged();
}



void Dashboard::setInnerArcWidth(int InnerArcWidth){
    if(m_InnerArcWidth == InnerArcWidth)
        return;

    m_InnerArcWidth = InnerArcWidth;

    emit innerArcWidthChanged();
}

void Dashboard::setInnerArcPos(int InnerArcPos){
    if(m_InnerArcPos == InnerArcPos)
        return;

    m_InnerArcPos = InnerArcPos;

    emit innerArcPosChanged();
}

void Dashboard::setProgressBarPos(qreal ProgressBarPos){
    if(m_ProgressBarPos == ProgressBarPos)
        return;

    m_ProgressBarPos = ProgressBarPos;

    emit progressBarPosChanged();
}

void Dashboard::setProgressBarThickness(qreal ProgressBarThickness){
    if(m_ProgressBarThickness == ProgressBarThickness)
        return;

    m_ProgressBarThickness = ProgressBarThickness;

    emit progressBarThicknessChanged();
}

void Dashboard::setInnerCircleSize(qreal InnerCircleSize){
    if(m_InnerCircleSize == InnerCircleSize)
        return;

    m_InnerCircleSize = InnerCircleSize;

    emit innerCircleSizeChanged();
}

void Dashboard::setInterval(int Interval){
    if(m_Interval == Interval)
        return;

    m_Interval = Interval;

    emit intervalChanged();
}

void Dashboard::setTextBarSize(qreal TextBarSize){
    if(m_TextBarSize == TextBarSize)
        return;

    m_TextBarSize = TextBarSize;

    emit textBarSizeChanged();
}

void Dashboard::setTickPosOffset(qreal TickPosOffset){
    if(m_TickPosOffset == TickPosOffset)
        return;

    m_TickPosOffset = TickPosOffset;

    emit tickPosOffsetChanged();
}

void Dashboard::setTextPosOffset(qreal TextPosOffset){
    if(m_TextPosOffset == TextPosOffset)
        return;

    m_TextPosOffset = TextPosOffset;

    emit textPosOffsetChanged();
}
