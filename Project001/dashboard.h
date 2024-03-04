#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>

class Dashboard : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal speedometerSize READ getSpeedometerSize WRITE setSpeedometerSize NOTIFY speedometerSizeChanged)
    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal alignAngle READ getAlignAngle WRITE setAlignAngle NOTIFY alignAngleChanged)
    Q_PROPERTY(qreal lowestRange READ getLowestRange WRITE setLowestRange NOTIFY lowestRangeChanged)
    Q_PROPERTY(qreal highestRange READ getHighestRange WRITE setHighestRange NOTIFY highestRangeChanged)
    Q_PROPERTY(qreal speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int arcWidth READ getArcWidth WRITE setArcWidth NOTIFY arcWidthChanged)
    Q_PROPERTY(QColor outerColor READ getOuterColor WRITE setOuterColor NOTIFY outerColorChanged)
    Q_PROPERTY(QColor innerColor READ getInnerColor WRITE setInnerColor NOTIFY innerColorChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
    Dashboard(QQuickItem *parent = 0);
    virtual void paint(QPainter *painter);

    qreal   getSpeedometerSize();
    qreal   getStartAngle();
    qreal   getAlignAngle();
    qreal   getLowestRange();
    qreal   getHighestRange();
    qreal   getSpeed();
    int     getArcWidth();
    QColor  getOuterColor();
    QColor  getInnerColor();
    QColor  getTextColor();
    QColor  getBackgroundColor();
    QPointF calculatePosition(const QRectF &rect, qreal angle, qreal offset);

    void    setSpeedometerSize(qreal size);
    void    setStartAngle(qreal startAngle);
    void    setAlignAngle(qreal angle);
    void    setLowestRange(qreal losbwestRange);
    void    setHighestRange(qreal highestRange);
    void    setSpeed(qreal speed);
    void    setArcWidth(int arcWidth);
    void    setOuterColor(QColor outerColor);
    void    setInnerColor(QColor innerColor);
    void    setTextColor(QColor textColor);
    void    setBackgroundColor(QColor backgroundColor);

public slots:
    void updateDashboard();

signals:
    void    speedometerSizeChanged();
    void    startAngleChanged();
    void    alignAngleChanged();
    void    lowestRangeChanged();
    void    highestRangeChanged();
    void    speedChanged();
    void    arcWidthChanged();
    void    outerColorChanged();
    void    innerColorChanged();
    void    textColorChanged();
    void    backgroundColorChanged();

private:
    QTimer  m_timer;
    qreal   m_val;
    bool    m_direction;
    qreal   m_SpeedometerSize;
    qreal   m_StartAngle;
    qreal   m_AlignAngle;
    qreal   m_LowestRange;
    qreal   m_HighestRange;
    qreal   m_Speed;
    int     m_ArcWidth;
    QColor  m_OuterColor;
    QColor  m_InnerColor;
    QColor  m_TextColor;
    QColor  m_BackgroundColor;
    int     m_InnerArcWidth;
    int     m_InnerArcPos;
};

#endif // DASHBOARD_H
