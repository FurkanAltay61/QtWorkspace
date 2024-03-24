import QtQuick 2.15
import QtQuick.Window 2.15
import Dashboardqml 1.0
import QtQuick.Timeline 1.0


Window {
    visible: true
    width: 1024
    height: 600
    title: qsTr("Speedometer")
    color: "black"
    //visibility:  "FullScreen"

    property real initialSpeedometerSize : 200
    property real initialStartAngle : -140
    property real initialAlignAngle : 260
    property real initialLowestRange : 0
    property real initialHighestRange : 240
    property int initialArcWidth : 5
    property color initialOuterColor : "blue"
    property color initialInnerColor : Qt.rgba(51,88,255,80)
    property color initialTextColor : Qt.rgba(255,255,255)
    property color initialBackgroundColor : Qt.transparent
    property int   initialInnerArcWidth : 50
    property int   initialInnerArcPos : 45
    property real initialProgressBarPos : 42.5
    property real initialProgressBarThickness : 13
    property real initialInnerCircleSize : 50
    property int   initialInterval : 20
    property real initialTextBarSize : 10
    property real initialTickPosOffset : 28.5
    property real initialTextPosOffset : 20
    property real initialTickMarkLength : 10
    property real initialArcTextSize : 8
    property real initialProgBarArcPos : 38
    property string initialUnit : "NULL"
    property string initialGaugeName : "NULL"
    property real initialUnitOffset : 50
    property real initialGaugeNameOffset : 100
    property real initialUnitTextSize : 7
    property real initialGaugeNameTextSize : 10

    property real initialSpeed : 0
    property double initialEngineLoad : 0
    property int initialCoolantTemp : 0
    property int initialIntakePressure : 0
    property double initialRpm : 0
    property int initialIntakeTemp : 0
    property double initialMaf : 0
    property double initialThrottlePos : 0
    property real initialVal : 0

    property int animationDuration : 1600

    FpsCounter {
        id : fpsItem
        anchors.right: parent.right
    }

    Rectangle {
        x : 974
        y : 580
        width: 50
        height : 20
        Text {
            id: name
            text: qsTr("text")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                Qt.quit()
            }
        }
    }


    Dashboard
    {
        x : 212
        y : 150
        gaugeName: "Speed"
        width: speedometerSize + 100
        height: speedometerSize + 100
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        val: mydashboard.speed
        Behavior on val {
            PropertyAnimation {
                duration : animationDuration
                easing.type: Easing.Linear
            }
        }
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        progressBarPos: initialProgressBarPos + 16
        innerCircleSize: initialInnerCircleSize + 25
        textBarSize: initialTextBarSize + 10
        tickMarkLength: initialTickMarkLength + 10
        tickPosOffset: initialTickPosOffset + 10
        textPosOffset: initialTextPosOffset - 5
        progressBarThickness: initialProgressBarThickness + 8
        arcTextSize: initialArcTextSize + 2
        progBarArcPos: initialProgBarArcPos + 10
        unit: "km/h"
        unitOffset: initialUnitOffset + 10
        gaugeNameOffset: initialGaugeNameOffset + 75
        unitTextSize: unitTextSize
        gaugeNameTextSize: initialGaugeNameTextSize + 5
    }


    Dashboard
    {
        x : 512
        y : 150
        gaugeName: "Rpm"
        width: speedometerSize + 100
        height: speedometerSize + 100
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 8000
        interval: 1000
        val: mydashboard.rpm
        Behavior on val {
            PropertyAnimation {
                duration : animationDuration
                easing.type: Easing.Linear
            }
        }
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        progressBarPos: initialProgressBarPos + 16
        innerCircleSize: initialInnerCircleSize + 25
        textBarSize: initialTextBarSize + 10
        tickMarkLength: initialTickMarkLength + 10
        tickPosOffset: initialTickPosOffset + 10
        textPosOffset: initialTextPosOffset - 5
        progressBarThickness: initialProgressBarThickness + 8
        arcTextSize: initialArcTextSize + 2
        progBarArcPos: initialProgBarArcPos + 10
        unit: "x1000"
        unitOffset: initialUnitOffset + 10
        gaugeNameOffset: initialGaugeNameOffset + 75
        unitTextSize: unitTextSize
        gaugeNameTextSize: initialGaugeNameTextSize + 5
    }

    Dashboard
    {
        x : 100
        y : 12
        gaugeName: "Engine Load"
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 100
        interval: 10
        val: mydashboard.engineload
        Behavior on val {
            PropertyAnimation {
                duration : animationDuration
                easing.type: Easing.Linear
            }
        }
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        progressBarPos: initialProgressBarPos + 2
        innerCircleSize: initialInnerCircleSize - 5
        progressBarThickness: progressBarThickness
        unit: "%"
        gaugeNameTextSize: initialGaugeNameTextSize - 2
    }


    Dashboard
    {
        x : 12
        y : 200
        gaugeName: "Coolant Temp"
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 120
        val: mydashboard.coolanttemp
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        interval: 30
        innerCircleSize: initialInnerCircleSize - 5
        progressBarPos: initialProgressBarPos + 2
        gaugeNameTextSize: initialGaugeNameTextSize - 2

        unit: "°C"

    }

    Dashboard
    {
        x : 100
        y : 388
        gaugeName: "Intake Pressure"
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 255
        interval: 25
        val: mydashboard.intakepressure
        Behavior on val {
            PropertyAnimation {
                duration : animationDuration
                easing.type: Easing.Linear
            }
        }
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerCircleSize: initialInnerCircleSize - 5
        progressBarPos: initialProgressBarPos + 2
        gaugeNameTextSize: initialGaugeNameTextSize - 2
        unit: "kPa"

    }

    Dashboard
    {
        x : 724
        y : 12
        gaugeName: "Intake Temp"
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: -40
        highestRange: 255
        interval: 25
        val: mydashboard.intaketemp
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerCircleSize: initialInnerCircleSize - 5
        progressBarPos: initialProgressBarPos + 2
        gaugeNameTextSize: initialGaugeNameTextSize - 2
        unit: "°C"

    }

    Dashboard
    {
        x : 812
        y : 200
        gaugeName: "Maf"
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 255
        interval: 25
        val: mydashboard.maf
        Behavior on val {
            PropertyAnimation {
                duration : animationDuration
                easing.type: Easing.Linear
            }
        }
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerCircleSize: initialInnerCircleSize - 5
        progressBarPos: initialProgressBarPos + 2
        gaugeNameTextSize: initialGaugeNameTextSize - 2
        unit: "g/s"

    }

    Dashboard
    {
        x : 724
        y : 388
        gaugeName: "Throttle Pos"
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 100
        interval: 10
        val: mydashboard.throttlepos
        Behavior on val {
            PropertyAnimation {
                duration : animationDuration
                easing.type: Easing.Linear
            }
        }
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerCircleSize: initialInnerCircleSize - 5
        progressBarPos: initialProgressBarPos + 2
        gaugeNameTextSize: initialGaugeNameTextSize - 2
        unit: "%"

    }

    // Dashboard
    // {
    //     x : 412
    //     y : 0
    //     width: speedometerSize
    //     height: speedometerSize
    //     startAngle: startAngle
    //     lowestRange: lowestRange
    //     highestRange: highestRange
    //     speed: mydashboard.speed
    //     Behavior on val {
    //         PropertyAnimation {
    //             duration : animationDuration
    //         }
    //     }
    //     arcWidth: arcWidth
    //     outerColor: outerColor
    //     innerColor: innerColor
    //     textColor: textColor
    //     backgroundColor: backgroundColor
    //     gaugeNameTextSize: initialGaugeNameTextSize - 2
    //     progressBarPos: initialProgressBarPos + 2
    // }



}
