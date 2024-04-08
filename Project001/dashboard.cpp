#include "dashboard.h"
#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include <QtMath>

Dashboard::Dashboard(QQuickItem *parent)
    :QQuickPaintedItem(parent),
    m_SpeedometerSize(400), // touch screen is 800 x 480
    m_StartAngle(m_SpeedometerSize / 1.95),
    m_AlignAngle(-m_SpeedometerSize / 1.75), // it should be 360 - m_StartAngle*3 for good looking
    m_LowestRange(0),
    m_HighestRange(240),
    m_ArcWidth(m_SpeedometerSize/80),
    m_OuterColor(QColor(Qt::blue)),
    m_InnerColor(QColor(51,88,255,80)),
    m_TextColor(QColor(255,255,255)),
    m_BackgroundColor(Qt::transparent),
    m_InnerArcWidth(m_SpeedometerSize / 60),
    m_InnerArcPos(m_SpeedometerSize / 6.67),
    m_InnerCircleSize(m_SpeedometerSize / 4.5),
    m_Interval(m_SpeedometerSize / 15),
    m_TextBarSize(m_SpeedometerSize / 30),
    m_TickPosOffset(m_SpeedometerSize / -50),
    m_TextPosOffset(m_SpeedometerSize / 12),
    m_TickMarkLength(m_SpeedometerSize / 15),
    m_ArcTextSize(m_SpeedometerSize / 25),
    m_ProgBarArcPos(m_SpeedometerSize / 5.75),
    m_Unit("NULL"),
    m_GaugeName("NULL"),
    m_UnitOffset(m_SpeedometerSize / 5),
    m_GaugeNameOffset(m_SpeedometerSize / 2),
    m_UnitTextSize(m_SpeedometerSize / 43),
    m_GaugeNameTextSize(m_SpeedometerSize / 30),
    m_Val(0),
    m_ValText(0),
    m_MinorTicks(5)
{
    qDebug() << "Constructor";
    QObject::connect(this,&QQuickItem::widthChanged, this, &Dashboard::handleUpdatePixmap);
    QObject::connect(this,&QQuickItem::heightChanged, this, &Dashboard::handleUpdatePixmap);
    //drawBackgroundPixmap();
}

void Dashboard::handleUpdatePixmap(){

    m_ArcWidth = width() / 80;
    m_InnerArcWidth = width() / 60;
    m_InnerArcPos = width() / 6.67;
    m_InnerCircleSize = width() / 4.5;
    m_TickPosOffset = width() / -50;
    m_TickMarkLength = width() / 15;

    if(width() > 0 && height() > 0){
        drawBackgroundPixmap();
        drawNeedlePixmap();
        //update();
    }

}

void Dashboard::drawBackgroundPixmap(){
    if(width() > 0 && height() > 0) {
        qDebug() << "width: " << width() << "height : " << height();
        m_BackgroundPixmap = QPixmap(width(),height());
        m_BackgroundPixmap.fill(Qt::transparent);
        QPainter painter(&m_BackgroundPixmap);
        QRectF rect = m_BackgroundPixmap.rect();

        painter.setRenderHint(QPainter::Antialiasing);
        QPen pen = painter.pen();
        pen.setCapStyle(Qt::FlatCap);

        //all arc
        qDebug() << "arc width :" << m_ArcWidth;
        painter.save();
        pen.setWidth(m_ArcWidth);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), m_StartAngle * 17, m_AlignAngle * 18);
        painter.restore();


        //red zone
        painter.save();
        QPointF center = rect.center();
        QConicalGradient conicalGradient(center, 45); // 0 is the angle where the gradient starts

        // Set gradient stops to create the light effect
        conicalGradient.setColorAt(0.0, QColor(83, 83, 83, 100)); // Fully transparent color stop
        conicalGradient.setColorAt(0.5, QColor(83, 83, 83, 255)); // Half-way point with light color
        conicalGradient.setColorAt(0.7, QColor(255, 0, 0, 255)); // Half-way point with light color
        conicalGradient.setColorAt(1.0, QColor(255, 0, 0, 50)); // Back to transparent

        //QBrush brush(conicalGradient);
        QPen pen2;
        pen2.setBrush(conicalGradient);
        pen2.setWidth(m_ProgressBarThickness);
        pen2.setCapStyle(Qt::FlatCap);
        painter.setPen(pen2);
        painter.drawArc(rect.adjusted(m_ProgressBarPos, m_ProgressBarPos,
                                      -m_ProgressBarPos, -m_ProgressBarPos),
                                      m_StartAngle * 17, m_AlignAngle * 18);
        painter.restore();


        //inner circle
        painter.save();
        QPen InnerCirclePen(Qt::white, 2); // Black color, 2 pixels width
        painter.setPen(InnerCirclePen);
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(rect.center(), m_InnerCircleSize, m_InnerCircleSize);
        QRadialGradient radianGradient(center,m_InnerCircleSize * 1.25,center); // 0 is the angle where the gradient starts

        // Set gradient stops to create the light effect
        radianGradient.setColorAt(0.0, QColor(83, 83, 83, 255)); // Fully transparent color stop
        radianGradient.setColorAt(0.3, QColor(83, 83, 83, 200)); // Fully transparent color stop
        radianGradient.setColorAt(0.5, QColor(83, 83, 83, 150)); // Fully transparent color stop
        radianGradient.setColorAt(0.8, QColor(83, 83, 83, 100)); // Fully transparent color stop
        radianGradient.setColorAt(1.0, QColor(83, 83, 83, 0)); // Half-way point with light color
        painter.setBrush(radianGradient);
        painter.drawEllipse(rect.center(), m_InnerCircleSize, m_InnerCircleSize);
        painter.restore();

        painter.save();
        QFont font("Halvetica",m_TextBarSize,QFont::Bold);
        font.setItalic(true);
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
        pen.setWidth(2);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawArc(rect.adjusted(m_ProgBarArcPos, m_ProgBarArcPos,
                                      -m_ProgBarArcPos, -m_ProgBarArcPos), m_StartAngle * 17, m_AlignAngle * 18);
        painter.restore();

        painter.save();
        QColor tickMarkColor = Qt::white;
        painter.setPen(tickMarkColor);

        // Draw tick marks and speed values
        int numTicks = (m_HighestRange - m_LowestRange) / m_Interval;
        font.setPointSize(m_ArcTextSize * 1.2);
        painter.setFont(font);
        QFontMetrics metrics(painter.font());

        for (int i = 0; i <= numTicks; ++i) {
            int speedValue = m_LowestRange + i * m_Interval;
            qreal majorAngle = m_StartAngle + ((speedValue - m_LowestRange) / (m_HighestRange - m_LowestRange)) * m_AlignAngle;

            // Draw major tick mark and text
            QPointF majorTickPos = calculatePosition(rect, majorAngle, m_TickPosOffset);
            painter.drawLine(majorTickPos, QPointF(majorTickPos.x() + m_TickMarkLength * cos(qDegreesToRadians(majorAngle)), majorTickPos.y() - m_TickMarkLength * sin(qDegreesToRadians(majorAngle))));
            QPointF textPos = calculatePosition(rect, majorAngle, m_TextPosOffset - metrics.height());
            QString text = QString::number(m_GaugeName == "RPM" ? speedValue / 1000 : speedValue);
            QRect textRect = metrics.boundingRect(text);
            textRect.moveCenter(textPos.toPoint());
            painter.drawText(textRect, Qt::AlignCenter, text);

            // Draw minor tick marks
            if (i < numTicks) {  // Avoid drawing minor ticks beyond the last major tick
                for (int j = 1; j < m_MinorTicks; ++j) {
                    qreal minorAngle = majorAngle + (j * (m_Interval / static_cast<qreal>(m_MinorTicks)) / (m_HighestRange - m_LowestRange)) * m_AlignAngle;
                    QPointF minorTickPos = calculatePosition(rect, minorAngle, m_TickPosOffset * 2.5);
                    QPointF minorTickEndPos = QPointF(minorTickPos.x() + (m_TickMarkLength / 2) * cos(qDegreesToRadians(minorAngle)), minorTickPos.y() - (m_TickMarkLength / 2) * sin(qDegreesToRadians(minorAngle)));  // Half the length for minor ticks
                    painter.drawLine(minorTickPos, minorTickEndPos);
                }
            }
        }
        painter.restore();
    }

}

void Dashboard::drawNeedlePixmap(){
    if(width() > 0 && height() > 0) {
        qDebug() << "width: " << width() << "height : " << height();
        m_NeedlePixmap = QPixmap(width(),height());
        m_NeedlePixmap.fill(Qt::transparent);
        QPainter painter(&m_NeedlePixmap);
        QRectF rect = m_NeedlePixmap.rect();

        painter.save();

        // Calculate the angle for the needle based on the current speed
        qreal needleAngle = m_StartAngle + ((m_Val - m_LowestRange) / (m_HighestRange - m_LowestRange)) * m_AlignAngle;

        // Calculate the position of the needle's tip
        qreal needleLength = rect.width() / 2 * 0.8;  // 80% of the radius
        QPointF needleTip(
            rect.center().x() + (needleLength * 1.1) * cos(qDegreesToRadians(-needleAngle)),
            rect.center().y() + (needleLength * 1.1) * sin(qDegreesToRadians(-needleAngle))
            );

        // Calculate the position of the needle's base at the inner circle's edge
        QPointF needleBase(
            rect.center().x() + (m_InnerCircleSize * 1.3) * cos(qDegreesToRadians(-needleAngle)),
            rect.center().y() + (m_InnerCircleSize * 1.3) * sin(qDegreesToRadians(-needleAngle))
            );

        // Draw the needle
        QPen needlePen(Qt::red, rect.width()/100);  // White color, 4 pixels width
        painter.setPen(needlePen);
        painter.drawLine(needleBase, needleTip);

        // Create a light effect using a radial gradient
        QRadialGradient lightGradient(needleTip, needleLength / 4);
        lightGradient.setColorAt(0, QColor(255, 255, 255, 150));  // Light color at the center
        lightGradient.setColorAt(1, QColor(255, 255, 255, 0));    // Transparent towards the edges

        // Draw the light effect
        painter.setBrush(lightGradient);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPointF(needleTip.x(), needleTip.y()), needleLength / 4, needleLength / 4);
        painter.restore();
        painter.setRenderHint(QPainter::Antialiasing);
    }
}

void Dashboard::paint(QPainter *painter){

    painter->drawPixmap(0,0,m_BackgroundPixmap);

    QRectF rect = this->boundingRect();

    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    //text which shows the value
    painter->save();
    QFont font("Halvetica",m_TextBarSize,QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_TextBarSize, m_TextBarSize,
                                    -m_TextBarSize, -m_TextBarSize),
                                    Qt::AlignCenter, QString::number((m_ValText),'f',1));
    painter->restore();

    // Apply transformations for needle
    painter->save();
    qreal m_NeedleAngle = 0 + ((-m_Val - m_LowestRange) / (m_HighestRange - m_LowestRange)) * m_AlignAngle;
    painter->translate(rect.center()); // Move the coordinate system to the center of the widget
    painter->rotate(m_NeedleAngle); // Rotate the coordinate system

    // Now draw the needle pixmap
    // The drawing should be offset by half its width and height so the rotation occurs around the center
    painter->drawPixmap(-m_NeedlePixmap.width() / 2, -m_NeedlePixmap.height() / 2, m_NeedlePixmap);
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

// int Dashboard::getArcWidth() const
// {
//     return m_ArcWidth;
// }

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

// int Dashboard::getInnerArcWidth() const
// {
//     return m_InnerArcWidth;
// }

// int Dashboard::getInnerArcPos() const
// {
//     return m_InnerArcPos;
// }

qreal Dashboard::getProgressBarPos() const
{
    return m_ProgressBarPos;
}

qreal Dashboard::getProgressBarThickness() const
{
    return m_ProgressBarThickness;
}

// qreal Dashboard::getInnerCircleSize() const
// {
//     return m_InnerCircleSize;
// }

int Dashboard::getInterval() const
{
    return m_Interval;
}

qreal Dashboard::getTextBarSize() const
{
    return m_TextBarSize;
}

// qreal Dashboard::getTickPosOffset() const
// {
//     return m_TickPosOffset;
// }

qreal Dashboard::getTextPosOffset() const
{
    return m_TextPosOffset;
}

// qreal Dashboard::getTickMarkLength() const
// {
//     return m_TickMarkLength;
// }

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

qreal  Dashboard::getVal() const
{
    return m_Val;
}

qreal Dashboard::getValText() const
{
    return m_ValText;
}

qreal  Dashboard::getMinorTicks() const {
    return m_MinorTicks;
}


void Dashboard::setSpeedometerSize(const qreal &size)
{
    if(m_SpeedometerSize == size)
        return;
    m_SpeedometerSize = size;
    emit speedometerSizeChanged();
}

void Dashboard::setStartAngle(const qreal &startAngle)
{
    if(m_StartAngle == startAngle)
        return;

    m_StartAngle = startAngle;
    emit startAngleChanged();
}

void Dashboard::setAlignAngle(const qreal &angle)
{
    if(m_StartAngle == angle)
        return;

    m_StartAngle = angle;
    emit alignAngleChanged();
}

void Dashboard::setLowestRange(const qreal &lowestRange)
{
    if(m_LowestRange == lowestRange)
        return;

    m_LowestRange = lowestRange;
    emit lowestRangeChanged();
}

void Dashboard::setHighestRange(const qreal &highestRange)
{
    if(m_HighestRange == highestRange)
        return;

    m_HighestRange = highestRange;
    emit highestRangeChanged();
}

// void Dashboard::setArcWidth(const int &arcWidth)
// {
//     if(m_ArcWidth == arcWidth)
//         return;

//     m_ArcWidth = arcWidth;
//     //drawBackgroundPixmap();
//     //update();
//     emit arcWidthChanged();
// }

void Dashboard::setOuterColor(const QColor &outerColor)
{
    if(m_OuterColor == outerColor)
        return;

    m_OuterColor = outerColor;
    emit outerColorChanged();
}

void Dashboard::setInnerColor(const QColor &innerColor)
{
    if(m_InnerColor == innerColor)
        return;

    m_InnerColor = innerColor;
    emit innerColorChanged();
}

void Dashboard::setTextColor(const QColor &textColor)
{
    if(m_TextColor == textColor)
        return;

    m_TextColor = textColor;
    emit textColorChanged();
}

void Dashboard::setBackgroundColor(const QColor &backgroundColor)
{
    if(m_BackgroundColor == backgroundColor)
        return;

    m_BackgroundColor = backgroundColor;
    emit backgroundColorChanged();
}



// void Dashboard::setInnerArcWidth(const int &InnerArcWidth){
//     if(m_InnerArcWidth == InnerArcWidth)
//         return;

//     m_InnerArcWidth = InnerArcWidth;
//     //drawBackgroundPixmap();
//     //update();
//     emit innerArcWidthChanged();
// }

// void Dashboard::setInnerArcPos(const int &InnerArcPos){
//     if(m_InnerArcPos == InnerArcPos)
//         return;

//     m_InnerArcPos = InnerArcPos;
//     //drawBackgroundPixmap();
//     //update();
//     emit innerArcPosChanged();
// }

void Dashboard::setProgressBarPos(const qreal &ProgressBarPos){
    if(m_ProgressBarPos == ProgressBarPos)
        return;

    m_ProgressBarPos = ProgressBarPos;
    emit progressBarPosChanged();
}

void Dashboard::setProgressBarThickness(const qreal &ProgressBarThickness){
    if(m_ProgressBarThickness == ProgressBarThickness)
        return;

    m_ProgressBarThickness = ProgressBarThickness;
    emit progressBarThicknessChanged();
}

// void Dashboard::setInnerCircleSize(const qreal &InnerCircleSize){
//     if(m_InnerCircleSize == InnerCircleSize)
//         return;

//     m_InnerCircleSize = InnerCircleSize;
//     //drawBackgroundPixmap();
//     //update();
//     emit innerCircleSizeChanged();
// }

void Dashboard::setInterval(const int &Interval){
    if(m_Interval == Interval)
        return;

    m_Interval = Interval;
    emit intervalChanged();
}

void Dashboard::setTextBarSize(const qreal &TextBarSize){
    if(m_TextBarSize == TextBarSize)
        return;

    m_TextBarSize = TextBarSize;
    emit textBarSizeChanged();
}

// void Dashboard::setTickPosOffset(const qreal &TickPosOffset){
//     if(m_TickPosOffset == TickPosOffset)
//         return;

//     m_TickPosOffset = TickPosOffset;
//     //drawBackgroundPixmap();
//     //update();
//     emit tickPosOffsetChanged();
// }

void Dashboard::setTextPosOffset(const qreal &TextPosOffset){
    if(m_TextPosOffset == TextPosOffset)
        return;

    m_TextPosOffset = TextPosOffset;
    emit textPosOffsetChanged();
}

// void Dashboard::setTickMarkLength(const qreal &TickMarkLength){
//     if(m_TickMarkLength == TickMarkLength)
//         return;

//     m_TickMarkLength = TickMarkLength;
//     //drawBackgroundPixmap();
//     //update();
//     emit tickMarkLengthChanged();
// }


void Dashboard::setArcTextSize(const qreal &ArcTextSize){
    if(m_ArcTextSize == ArcTextSize)
        return;
    m_ArcTextSize = ArcTextSize;
    emit arcTextSizeChanged();
}

void Dashboard::setProgBarArcPos(const qreal &ProgBarArcPos){
    if(m_ProgBarArcPos == ProgBarArcPos)
        return;
    m_ProgBarArcPos = ProgBarArcPos;
    emit progBarArcPosChanged();
}

void Dashboard::setUnit(const QString &Unit){
    if(m_Unit == Unit)
        return;
    m_Unit = Unit;
    emit unitChanged();
}

void Dashboard::setGaugeName(const QString &GaugeName){
    if(m_GaugeName == GaugeName)
        return;
    m_GaugeName = GaugeName;
    emit gaugeNameChanged();
}

void Dashboard::setUnitOffset(const qreal &UnitOffset){
    if(m_UnitOffset == UnitOffset)
        return;
    m_UnitOffset = UnitOffset;
    //drawBackgroundPixmap();
    //update();
    emit unitOffsetChanged();
}

void Dashboard::setGaugeNameOffset(const qreal &GaugeNameOffset){
    if(m_GaugeNameOffset == GaugeNameOffset)
        return;
    m_GaugeNameOffset = GaugeNameOffset;
    //drawBackgroundPixmap();
    //update();
    emit gaugeNameOffsetChanged();
}

void Dashboard::setUnitTextSize(const qreal &UnitTextSize){
    if(m_UnitTextSize == UnitTextSize)
        return;
    m_UnitTextSize = UnitTextSize;
    emit unitTextSizeChanged();
}
void Dashboard::setGaugeNameTextSize(const qreal &GaugeNameTextSize){
    if(m_GaugeNameTextSize == GaugeNameTextSize)
        return;
    m_GaugeNameTextSize = GaugeNameTextSize;
    //drawBackgroundPixmap();
    //update();
    emit gaugeNameTextSizeChanged();
}

void Dashboard::setMinorTicks(const qreal &_minorticks){
    if(m_MinorTicks == _minorticks)
        return;
    m_MinorTicks = _minorticks;
    emit minorTicksChanged();
}

void Dashboard::setVal(const qreal &mval){
    if(m_Val == mval)
        return;

    m_Val = mval;
    update();
    emit valChanged();
}

void Dashboard::setValText(const qreal &_mvaltext){
    if(m_ValText == _mvaltext)
        return;

    m_ValText = _mvaltext;
    update();
    emit valTextChanged();
}

