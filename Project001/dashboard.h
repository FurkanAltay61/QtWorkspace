#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>
#include <QGradient>
#include <QPixmap>


class Dashboard : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal speedometerSize READ getSpeedometerSize WRITE setSpeedometerSize NOTIFY speedometerSizeChanged)
    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal alignAngle READ getAlignAngle WRITE setAlignAngle NOTIFY alignAngleChanged)
    Q_PROPERTY(qreal lowestRange READ getLowestRange WRITE setLowestRange NOTIFY lowestRangeChanged)
    Q_PROPERTY(qreal highestRange READ getHighestRange WRITE setHighestRange NOTIFY highestRangeChanged)
    Q_PROPERTY(int arcWidth READ getArcWidth WRITE setArcWidth NOTIFY arcWidthChanged)
    Q_PROPERTY(QColor outerColor READ getOuterColor WRITE setOuterColor NOTIFY outerColorChanged)
    Q_PROPERTY(QColor innerColor READ getInnerColor WRITE setInnerColor NOTIFY innerColorChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(int   innerArcWidth READ getInnerArcWidth WRITE setInnerArcWidth NOTIFY innerArcWidthChanged)
    Q_PROPERTY(int   innerArcPos READ getInnerArcPos WRITE setInnerArcPos NOTIFY innerArcPosChanged)
    Q_PROPERTY(qreal progressBarPos READ getProgressBarPos WRITE setProgressBarPos NOTIFY progressBarPosChanged)
    Q_PROPERTY(qreal progressBarThickness READ getProgressBarThickness WRITE setProgressBarThickness NOTIFY progressBarThicknessChanged)
    Q_PROPERTY(qreal innerCircleSize READ getInnerCircleSize WRITE setInnerCircleSize NOTIFY innerCircleSizeChanged)
    Q_PROPERTY(int   interval READ getInterval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(qreal textBarSize READ getTextBarSize WRITE setTextBarSize NOTIFY textBarSizeChanged)
    Q_PROPERTY(qreal tickPosOffset READ getTickPosOffset WRITE setTickPosOffset NOTIFY tickPosOffsetChanged)
    Q_PROPERTY(qreal textPosOffset READ getTextPosOffset WRITE setTextPosOffset NOTIFY textPosOffsetChanged)
    Q_PROPERTY(qreal tickMarkLength READ getTickMarkLength WRITE setTickMarkLength NOTIFY tickMarkLengthChanged)
    Q_PROPERTY(qreal arcTextSize READ getArcTextSize WRITE setArcTextSize NOTIFY arcTextSizeChanged)
    Q_PROPERTY(qreal progBarArcPos READ getProgBarArcPos WRITE setProgBarArcPos NOTIFY progBarArcPosChanged)
    Q_PROPERTY(QString unit READ getUnit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(QString gaugeName READ getGaugeName WRITE setGaugeName NOTIFY gaugeNameChanged)
    Q_PROPERTY(qreal unitOffset READ getUnitOffset WRITE setUnitOffset NOTIFY unitOffsetChanged)
    Q_PROPERTY(qreal gaugeNameOffset READ getGaugeNameOffset WRITE setGaugeNameOffset NOTIFY gaugeNameOffsetChanged)
    Q_PROPERTY(qreal unitTextSize READ getUnitTextSize WRITE setUnitTextSize NOTIFY unitTextSizeChanged)
    Q_PROPERTY(qreal gaugeNameTextSize READ getGaugeNameTextSize WRITE setGaugeNameTextSize NOTIFY gaugeNameTextSizeChanged)
    Q_PROPERTY(qreal val READ getVal WRITE setVal NOTIFY valChanged)


public:
    Dashboard(QQuickItem *parent = 0);
    virtual void paint(QPainter *painter);

    qreal   getSpeedometerSize() const;
    qreal   getStartAngle() const;
    qreal   getAlignAngle() const;
    qreal   getLowestRange() const;
    qreal   getHighestRange() const;
    int     getArcWidth() const;
    QColor  getOuterColor() const;
    QColor  getInnerColor() const;
    QColor  getTextColor() const;
    QColor  getBackgroundColor() const;

    int     getInnerArcWidth() const;
    int     getInnerArcPos() const;
    qreal   getProgressBarPos() const;
    qreal   getProgressBarThickness() const;
    qreal   getInnerCircleSize() const;
    int     getInterval() const;
    qreal   getTextBarSize() const;
    qreal   getTickPosOffset() const;
    qreal   getTextPosOffset() const;
    qreal   getTickMarkLength() const;
    qreal   getArcTextSize() const;
    qreal   getProgBarArcPos() const;
    QString getUnit() const;
    QString getGaugeName() const;
    qreal   getUnitOffset() const;
    qreal   getGaugeNameOffset() const;
    qreal   getUnitTextSize() const;
    qreal   getGaugeNameTextSize() const;

    qreal   getVal() const;

    QPointF calculatePosition(const QRectF &rect, qreal angle, qreal offset);

    void    setSpeedometerSize(const qreal &size);
    void    setStartAngle(const qreal &startAngle);
    void    setAlignAngle(const qreal &angle);
    void    setLowestRange(const qreal &lowestRange);
    void    setHighestRange(const qreal &highestRange);
    void    setArcWidth(const int &arcWidth);
    void    setOuterColor(const QColor &outerColor);
    void    setInnerColor(const QColor &innerColor);
    void    setTextColor(const QColor &textColor);
    void    setBackgroundColor(const QColor &backgroundColor);

    void    setInnerArcWidth(const int &InnerArcWidth);
    void    setInnerArcPos(const int &InnerArcPos);
    void    setProgressBarPos(const qreal &ProgressBarPos);
    void    setProgressBarThickness(const qreal &ProgressBarThickness);
    void    setInnerCircleSize(const qreal &InnerCircleSize);
    void    setInterval(const int &Interval);
    void    setTextBarSize(const qreal &TextBarSize);
    void    setTickPosOffset(const qreal &TickPosOffset);
    void    setTextPosOffset(const qreal &TextPosOffset);
    void    setTickMarkLength(const qreal &TickMarkLength);
    void    setArcTextSize(const qreal &ArcTextSize);
    void    setProgBarArcPos(const qreal &ProgBarArcPos);
    void    setUnit(const QString &unit);
    void    setGaugeName(const QString &GaugeName);
    void    setUnitOffset(const qreal &UnitOffset);
    void    setGaugeNameOffset(const qreal &GaugeNameOffset);
    void    setUnitTextSize(const qreal &UnitTextSize);
    void    setGaugeNameTextSize(const qreal &GaugeNameTextSize);

    void    setVal(const qreal &val);

    void    drawBackgroundPixmap();

public slots:

signals:
    void    speedometerSizeChanged();
    void    startAngleChanged();
    void    alignAngleChanged();
    void    lowestRangeChanged();
    void    highestRangeChanged();
    void    arcWidthChanged();
    void    outerColorChanged();
    void    innerColorChanged();
    void    textColorChanged();
    void    backgroundColorChanged();

    void    innerArcWidthChanged();
    void    innerArcPosChanged();
    void    progressBarPosChanged();
    void    progressBarThicknessChanged();
    void    innerCircleSizeChanged();
    void    intervalChanged();
    void    textBarSizeChanged();
    void    tickPosOffsetChanged();
    void    textPosOffsetChanged();
    void    tickMarkLengthChanged();
    void    arcTextSizeChanged();
    void    progBarArcPosChanged();
    void    unitChanged();
    void    gaugeNameChanged();
    void    unitOffsetChanged();
    void    gaugeNameOffsetChanged();
    void    unitTextSizeChanged();
    void    gaugeNameTextSizeChanged();

    void    valChanged();

private:
    qreal   m_val;
    bool    m_direction;
    qreal   m_SpeedometerSize;
    qreal   m_StartAngle;
    qreal   m_AlignAngle;
    qreal   m_LowestRange;
    qreal   m_HighestRange;
    int     m_ArcWidth;
    QColor  m_OuterColor;
    QColor  m_InnerColor;
    QColor  m_TextColor;
    QColor  m_BackgroundColor;

    int     m_InnerArcWidth;
    int     m_InnerArcPos;
    qreal   m_ProgressBarPos;
    qreal   m_ProgressBarThickness;
    qreal   m_InnerCircleSize;
    int     m_Interval;
    qreal   m_TextBarSize;
    qreal   m_TickPosOffset;
    qreal   m_TextPosOffset;
    qreal   m_TickMarkLength;
    qreal   m_ArcTextSize;
    qreal   m_ProgBarArcPos;
    QString m_Unit;
    QString m_GaugeName;
    qreal   m_UnitOffset;
    qreal   m_GaugeNameOffset;
    qreal   m_UnitTextSize;
    qreal   m_GaugeNameTextSize;


    qreal   m_Val;

    QPixmap m_BackgroundPixmap;

};

#endif // DASHBOARD_H
