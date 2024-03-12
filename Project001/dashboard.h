#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>
#include <QGradient>

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

    Q_PROPERTY(qreal speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double engineload READ getEngineLoad WRITE setEngineLoad NOTIFY engineLoadChanged)
    Q_PROPERTY(int coolanttemp READ getCoolantTemp WRITE setCoolantTemp NOTIFY coolantTempChanged)
    Q_PROPERTY(int intakepressure READ getIntakePressure WRITE setIntakePressure NOTIFY intakePressureChanged)
    Q_PROPERTY(double rpm READ getRpm WRITE setRpm NOTIFY rpmChanged)
    Q_PROPERTY(int intaketemp READ getIntakeTemp WRITE setIntakeTemp NOTIFY intakeTempChanged)
    Q_PROPERTY(double maf READ getMaf WRITE setMaf NOTIFY mafChanged)
    Q_PROPERTY(double throttlepos READ getThrottlePos WRITE setThrottlePos NOTIFY throttlePosChanged)
    Q_PROPERTY(qreal val READ getVal WRITE setVal NOTIFY valChanged)


public:
    Dashboard(QQuickItem *parent = 0);
    virtual void paint(QPainter *painter);

    qreal   getSpeedometerSize();
    qreal   getStartAngle();
    qreal   getAlignAngle();
    qreal   getLowestRange();
    qreal   getHighestRange();
    int     getArcWidth();
    QColor  getOuterColor();
    QColor  getInnerColor();
    QColor  getTextColor();
    QColor  getBackgroundColor();

    int     getInnerArcWidth();
    int     getInnerArcPos();
    qreal   getProgressBarPos();
    qreal   getProgressBarThickness();
    qreal   getInnerCircleSize();
    int     getInterval();
    qreal   getTextBarSize();
    qreal   getTickPosOffset();
    qreal   getTextPosOffset();
    qreal   getTickMarkLength();
    qreal   getArcTextSize();
    qreal   getProgBarArcPos();
    QString getUnit();
    QString getGaugeName();
    qreal   getUnitOffset();
    qreal   getGaugeNameOffset();
    qreal   getUnitTextSize();
    qreal   getGaugeNameTextSize();

    qreal   getSpeed();
    double  getEngineLoad();
    int     getCoolantTemp();
    int     getIntakePressure();
    double  getRpm();
    int     getIntakeTemp();
    double  getMaf();
    double  getThrottlePos();

    qreal   getVal();

    QPointF calculatePosition(const QRectF &rect, qreal angle, qreal offset);

    void    setSpeedometerSize(qreal size);
    void    setStartAngle(qreal startAngle);
    void    setAlignAngle(qreal angle);
    void    setLowestRange(qreal losbwestRange);
    void    setHighestRange(qreal highestRange);
    void    setArcWidth(int arcWidth);
    void    setOuterColor(QColor outerColor);
    void    setInnerColor(QColor innerColor);
    void    setTextColor(QColor textColor);
    void    setBackgroundColor(QColor backgroundColor);

    void    setInnerArcWidth(int InnerArcWidth);
    void    setInnerArcPos(int InnerArcPos);
    void    setProgressBarPos(qreal ProgressBarPos);
    void    setProgressBarThickness(qreal ProgressBarThickness);
    void    setInnerCircleSize(qreal InnerCircleSize);
    void    setInterval(int Interval);
    void    setTextBarSize(qreal TextBarSize);
    void    setTickPosOffset(qreal TickPosOffset);
    void    setTextPosOffset(qreal TextPosOffset);
    void    setTickMarkLength(qreal TickMarkLength);
    void    setArcTextSize(qreal ArcTextSize);
    void    setProgBarArcPos(qreal ProgBarArcPos);
    void    setUnit(QString unit);
    void    setGaugeName(QString GaugeName);
    void    setUnitOffset(qreal UnitOffset);
    void    setGaugeNameOffset(qreal GaugeNameOffset);
    void    setUnitTextSize(qreal UnitTextSize);
    void    setGaugeNameTextSize(qreal GaugeNameTextSize);

    void    setSpeed(qreal Speed);
    void    setEngineLoad(double EngineLoad);
    void    setCoolantTemp(int CoolantTemp);
    void    setIntakePressure(int IntakePressure);
    void    setRpm(double Rpm);
    void    setIntakeTemp(int IntakeTemp);
    void    setMaf(double Maf);
    void    setThrottlePos(double ThrottlePos);

    void    setVal(qreal val);

public slots:
    void updateDashboard();
    void speedReceived(const int speed);
    void onDataReceived(const QString &data);
    void engineLoadReceived(const double EngineLoad);
    void coolantTempReceived(const int CoolantTemp);
    void intakePressReceived(const int IntakePressure);
    void rpmReceived(const double Rpm);
    void IntakeTempReceived(const int IntakeTemp);
    void MassAirFlowReceived(const double Maf);
    void ThrottlePosReceived(const double ThrottlePos);

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

    void    speedChanged();
    void    engineLoadChanged();
    void    coolantTempChanged();
    void    intakePressureChanged();
    void    rpmChanged();
    void    intakeTempChanged();
    void    mafChanged();
    void    throttlePosChanged();
    void    valChanged();

private:
    QTimer  m_timer;
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

    qreal   m_Speed;
    double  m_EngineLoad;
    int     m_CoolantTemp;
    int     m_IntakePressure;
    double  m_Rpm;
    int     m_IntakeTemp;
    double  m_Maf;
    double  m_ThrottlePos;
    qreal   m_Val;

};

#endif // DASHBOARD_H
