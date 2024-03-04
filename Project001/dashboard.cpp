#include "dashboard.h"
#include <QPainter>
#include <cmath>

Dashboard::Dashboard(QQuickItem *parent)
    :QQuickPaintedItem(parent),
    m_SpeedometerSize(300), // touch screen is 800 x 480
    m_StartAngle(-140),
    m_AlignAngle(260), // it should be 360 - m_StartAngle*3 for good looking
    m_LowestRange(0),
    m_HighestRange(240),
    m_Speed(2430),
    m_ArcWidth(10),
    m_OuterColor(QColor(12,16,247)),
    m_InnerColor(QColor(51,88,255,80)),
    m_TextColor(QColor(255,255,255)),
    m_BackgroundColor(Qt::transparent),
    m_InnerArcWidth(50),
    m_InnerArcPos(45)
{
    connect(&m_timer,&QTimer::timeout, this, &Dashboard::updateDashboard);
    m_timer.start(100);
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
    // painter->drawRect(rect);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();

    //inner pie
    int pieSize = m_SpeedometerSize/4;
    painter->setBrush(QBrush(QColor("black")));
    painter->drawEllipse(rect.center(), pieSize, pieSize);
    painter->save();
    pen.setWidth(m_ArcWidth/2);
    pen.setColor(m_OuterColor);
    painter->setBrush(m_InnerColor);
    painter->setPen(pen);
    painter->drawPie(rect.adjusted(pieSize, pieSize, -pieSize, -pieSize), startAngle * 16, spanAngle * 16);
    painter->restore();

    //text which shows the value
    painter->save();
    QFont font("Halvetica",15,QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_SpeedometerSize/30, m_SpeedometerSize/30, -m_SpeedometerSize/30, -m_SpeedometerSize/4), Qt::AlignCenter  ,QString::number((m_Speed),'f',1));
    painter->restore();

    //current active progress
    painter->save();
    pen.setWidth(m_InnerArcWidth);
    pen.setColor(m_OuterColor);
    qreal valueToAngle = ((m_Speed - m_LowestRange)/(m_HighestRange - m_LowestRange)) * spanAngle;
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(m_InnerArcPos, m_InnerArcPos, -m_InnerArcPos, -m_InnerArcPos), startAngle * 16, valueToAngle * 16);
    painter->restore();
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
