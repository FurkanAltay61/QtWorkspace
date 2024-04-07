import QtQuick 2.15
import QtQuick.Window 2.15
import Dashboardqml 1.0


Window {
    visible: true
    width: 1024
    height: 600
    title: qsTr("Speedometer")
    color: "black"
    //visibility:  "FullScreen"

    // property real initialSpeedometerSize : 300
    // property real initialStartAngle : - initialSpeedometerSize / 2.14
    // property real initialAlignAngle : initialSpeedometerSize / 1.15
    // property real initialLowestRange : 0
    // property real initialHighestRange : 240
    // property int initialArcWidth : initialSpeedometerSize / 60
    // property color initialOuterColor : "blue"
    // property color initialInnerColor : Qt.rgba(51,88,255,80)
    // property color initialTextColor : Qt.rgba(255,255,255)
    // property color initialBackgroundColor : Qt.transparent
    // property int   initialInnerArcWidth : initialSpeedometerSize / 60
    // property int   initialInnerArcPos : initialSpeedometerSize / 6.67
    // property real initialProgressBarPos : initialSpeedometerSize / 7.0
    // property real initialProgressBarThickness : initialSpeedometerSize / 23.07
    // property real initialInnerCircleSize : initialSpeedometerSize / 4
    // property int   initialInterval : initialSpeedometerSize / 15
    // property real initialTextBarSize : initialSpeedometerSize / 30
    // property real initialTickPosOffset : initialSpeedometerSize / 50
    // property real initialTextPosOffset : initialSpeedometerSize / 15
    // property real initialTickMarkLength : initialSpeedometerSize / 15
    // property real initialArcTextSize : initialSpeedometerSize / 37.5
    // property real initialProgBarArcPos : initialSpeedometerSize / 5.75
    // property string initialUnit : "NULL"
    // property string initialGaugeName : "NULL"
    // property real initialUnitOffset : initialSpeedometerSize / 5
    // property real initialGaugeNameOffset : initialSpeedometerSize / 3
    // property real initialUnitTextSize : initialSpeedometerSize / 43
    // property real initialGaugeNameTextSize : initialSpeedometerSize / 30

    property real initialSpeed : 0
    property real initialEngineLoad : 0
    property real initialCoolantTemp : 0
    property real initialIntakePressure : 0
    property real initialRpm : 0
    property real initialIntakeTemp : 0
    property real initialMaf : 0
    property real initialThrottlePos : 0
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
            id: close
            text: qsTr("close")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                Qt.quit()
            }
        }
    }

    Rectangle {
        x : 919
        y : 580
        width: 50
        height : 20
        Text {
            id: reset
            text: qsTr("reset")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                //Reset command should send here
                console.log("Clicked")
                tcpClient.resetSignal()
            }
        }
    }


    Rectangle {
        x : 845
        y : 580
        width: 70
        height : 20
        Text {
            id: obd2connect
            text: qsTr("connect")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                //Reset command should send here
                console.log("Clicked")
                tcpClient.connectSignal()
            }
        }
    }


    // Rectangle {
    //     x : 310
    //     y : 20
    //     width: 400
    //     height : 125
    //     Text {
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         anchors.verticalCenter: parent.verticalCenter
    //         id: dashboardstatus
    //         text: qsTr(tcpClient.statmsg)
    //         wrapMode: Text.WordWrap  // Enable word wrapping
    //         elide: Text.ElideRight   // Truncate text with an ellipsis on the right if it doesn't fit
    //         width: parent.width      // Ensure the text width is the same as the parent Rectangle

    //     }
    // }

    // Rectangle {
    //     x : 310
    //     y : 425
    //     width: 400
    //     height : 125
    //     Text {
    //         anchors.centerIn: parent
    //         id: dashboardstatus2
    //         text: qsTr("Status2")
    //     }
    // }


    Rectangle {
        x : 770
        y : 580
        width: 70
        height : 20
        Text {
            id: reboot
            text: qsTr("reboot")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                //Reset command should send here
                console.log("Clicked")
                tcpClient.rebootSignal()
            }
        }
    }

    Dashboard
    {
        property real initialSpeedometerSize: 400
        x : 312
        y : 100
        gaugeName: "Rpm"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        //startAngle: startAngle - 90
        //alignAngle: alignAngle + 90
        lowestRange: lowestRange
        highestRange: 5000
        interval: 1000
        val: tcpClient.rpm
        Behavior on val {
            PropertyAnimation {
                duration : tcpClient.testMode ? tcpClient.sendingPeriod : tcpClient.rpm_duration
                easing.type: Easing.Linear
                // onDurationChanged: {
                //     console.log("Duration changed to:", tcpClient.rpm_duration);
                // }
            }
        }
        valtext: tcpClient.speed
        Behavior on valtext {
            PropertyAnimation {
                duration : tcpClient.testMode ? tcpClient.sendingPeriod : tcpClient.speed_duration
                easing.type: Easing.Linear
                // onDurationChanged: {
                //     console.log("Duration changed to:", tcpClient.rpm_duration);
                // }
            }
        }
        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerArcWidth : initialSpeedometerSize / 60
        innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: initialSpeedometerSize / 4.5
        progressBarThickness: initialSpeedometerSize / 10
        innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: initialSpeedometerSize / 30
        tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: initialSpeedometerSize / 12
        tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: initialSpeedometerSize / 25
        progBarArcPos: initialSpeedometerSize / 5.75
        unit: "km/h"
        unitOffset: initialSpeedometerSize / 5
        gaugeNameOffset: initialSpeedometerSize / 2
        unitTextSize: initialSpeedometerSize / 43
        gaugeNameTextSize: initialSpeedometerSize / 30
        minorticks: 20

    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 150
        y : 12
        gaugeName: "Engine Load"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 100
        interval: 10
        val: tcpClient.engineload
        Behavior on val {
            PropertyAnimation {
                duration : tcpClient.engineload_duration
                easing.type: Easing.Linear
            }
        }
        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerArcWidth : initialSpeedometerSize / 60
        innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: initialSpeedometerSize / 4.5
        progressBarThickness: initialSpeedometerSize / 10
        innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: initialSpeedometerSize / 30
        tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: initialSpeedometerSize / 15
        tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: initialSpeedometerSize / 37.5
        progBarArcPos: initialSpeedometerSize / 5.75
        unit: "km/h"
        unitOffset: initialSpeedometerSize / 5
        gaugeNameOffset: initialSpeedometerSize / 2
        unitTextSize: initialSpeedometerSize / 43
        gaugeNameTextSize: initialSpeedometerSize / 30
    }


    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 62
        y : 200
        gaugeName: "Coolant Temp"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 120
        val: tcpClient.coolanttemp
        interval: 30
        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerArcWidth : initialSpeedometerSize / 60
        innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: initialSpeedometerSize / 4.5
        progressBarThickness: initialSpeedometerSize / 10
        innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: initialSpeedometerSize / 30
        tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: initialSpeedometerSize / 15
        tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: initialSpeedometerSize / 37.5
        progBarArcPos: initialSpeedometerSize / 5.75
        unit: "km/h"
        unitOffset: initialSpeedometerSize / 5
        gaugeNameOffset: initialSpeedometerSize / 2
        unitTextSize: initialSpeedometerSize / 43
        gaugeNameTextSize: initialSpeedometerSize / 30
    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 150
        y : 388
        gaugeName: "Intake Pressure"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 255
        interval: 25
        val: tcpClient.intakepressure
        Behavior on val {
            PropertyAnimation {
                duration : tcpClient.intakepressure_duration
                easing.type: Easing.Linear
            }
        }
        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerArcWidth : initialSpeedometerSize / 60
        innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: initialSpeedometerSize / 4.5
        progressBarThickness: initialSpeedometerSize / 10
        innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: initialSpeedometerSize / 30
        tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: initialSpeedometerSize / 15
        tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: initialSpeedometerSize / 37.5
        progBarArcPos: initialSpeedometerSize / 5.75
        unit: "km/h"
        unitOffset: initialSpeedometerSize / 5
        gaugeNameOffset: initialSpeedometerSize / 2
        unitTextSize: initialSpeedometerSize / 43
        gaugeNameTextSize: initialSpeedometerSize / 30
    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 674
        y : 12
        gaugeName: "Intake Temp"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        startAngle: startAngle
        lowestRange: -40
        highestRange: 255
        interval: 20
        val: tcpClient.intaketemp
        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerArcWidth : initialSpeedometerSize / 60
        innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: initialSpeedometerSize / 4.5
        progressBarThickness: initialSpeedometerSize / 10
        innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: initialSpeedometerSize / 30
        tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: initialSpeedometerSize / 15
        tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: initialSpeedometerSize / 37.5
        progBarArcPos: initialSpeedometerSize / 5.75
        unit: "km/h"
        unitOffset: initialSpeedometerSize / 5
        gaugeNameOffset: initialSpeedometerSize / 2
        unitTextSize: initialSpeedometerSize / 43
        gaugeNameTextSize: initialSpeedometerSize / 30
    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 762
        y : 200
        gaugeName: "Maf"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 255
        interval: 25
        val: tcpClient.maf
        Behavior on val {
            PropertyAnimation {
                duration : tcpClient.maf_duration
                easing.type: Easing.Linear
            }
        }
        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerArcWidth : initialSpeedometerSize / 60
        innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: initialSpeedometerSize / 4.5
        progressBarThickness: initialSpeedometerSize / 10
        innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: initialSpeedometerSize / 30
        tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: initialSpeedometerSize / 15
        tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: initialSpeedometerSize / 37.5
        progBarArcPos: initialSpeedometerSize / 5.75
        unit: "km/h"
        unitOffset: initialSpeedometerSize / 5
        gaugeNameOffset: initialSpeedometerSize / 2
        unitTextSize: initialSpeedometerSize / 43
        gaugeNameTextSize: initialSpeedometerSize / 30
    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 674
        y : 388
        gaugeName: "Throttle Pos"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 100
        interval: 10
        val: tcpClient.throttlepos
        Behavior on val {
            PropertyAnimation {
                duration : tcpClient.throttlepos_duration
                easing.type: Easing.Linear
            }
        }
        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerArcWidth : initialSpeedometerSize / 60
        innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: initialSpeedometerSize / 4.5
        progressBarThickness: initialSpeedometerSize / 23.0
        innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: initialSpeedometerSize / 30
        tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: initialSpeedometerSize / 15
        tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: initialSpeedometerSize / 37.5
        progBarArcPos: initialSpeedometerSize / 5.75
        unit: "km/h"
        unitOffset: initialSpeedometerSize / 5
        gaugeNameOffset: initialSpeedometerSize / 2
        unitTextSize: initialSpeedometerSize / 43
        gaugeNameTextSize: initialSpeedometerSize / 30

    }

}
