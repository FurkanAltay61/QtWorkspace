import QtQuick 2.15
import QtQuick.Window 2.15
import Dashboardqml 1.0
import QtQuick.Shapes 1.12
import QtQuick.Controls 2.15
//import QtGraphicalEffects 1.15

Window {
    visible: true
    width: 1024
    height: 600
    title: qsTr("Speedometer")
    color: "black"
    //visibility:  "FullScreen"

    property int animationDuration : 1600

    Shape {
        width: 1024
        height: 600
        anchors.centerIn: parent
        ShapePath {
            strokeWidth: 3
            strokeColor: "gray"
            fillColor: "transparent"
            // Starting point
            startX: 175
            startY: 5
            // Hexagon points
            // Draw an arc to the next side
            PathLine { x: 175; y: 5 }
            PathLine { x: 850; y: 5 }
            PathLine { x: 1000;  y: 300 }
            PathLine { x: 850;   y: 575 }
            PathLine { x: 175;   y: 575 }
            PathLine { x: 25;  y: 300 }
            PathLine { x: 175;  y: 5 } // Closes the path
        }
    }

    FpsCounter {
        x : 934
        y : 0
        width: 50
        height : 20
        id : fpsItem
    }


    Button {
        x : 949
        y : 580
        width: 70
        height : 20
        id: closebutton
        text: "Close"
        font.pointSize: 10
        font.bold : true
        background: Rectangle {
            id: closebackground
            color: closebutton.pressed ? "gray" : "darkgray"
            radius: 5
            gradient: Gradient {
                GradientStop { position: 0.0; color: closebutton.pressed ? "gray" : "darkgray" }
                GradientStop { position: 1.0; color: closebutton.pressed ? "red" : "darkred" }
            }
        }
        onPressed: {
            Qt.quit()
        }
    }

    Button {
        x : 874
        y : 580
        width: 70
        height : 20
        id: resetbutton
        text: "Reset"
        font.pointSize: 10
        font.bold : true
        background: Rectangle {
            id: resetbackground
            color: resetbutton.pressed ? "gray" : "darkgray"
            radius: 5
            gradient: Gradient {
                GradientStop { position: 0.0; color: resetbutton.pressed ? "gray" : "darkgray" }
                GradientStop { position: 1.0; color: resetbutton.pressed ? "red" : "darkred" }
            }
        }
        onPressed: {
            tcpClient.resetSignal()
        }
    }

    Button {
        x : 799
        y : 580
        width: 70
        height : 20
        id: connectbutton
        text: "Connect"
        font.pointSize: 10
        font.bold : true
        background: Rectangle {
            id: connectbackground
            radius: 5
            gradient: Gradient {
                GradientStop { position: 0.0; color: connectbutton.pressed ? "gray" : "darkgray" }
                GradientStop { position: 1.0; color: connectbutton.pressed ? "red" : "darkred" }
            }
        }
        onPressed: {
            tcpClient.connectSignal()
        }
    }

    Button {
        x : 724
        y : 580
        width: 70
        height : 20
        id: rebootbutton
        text: "Reboot"
        //anchors.centerIn: parent
        font.pointSize: 10
        font.bold : true
        background: Rectangle {
            id: background
            color: rebootbutton.pressed ? "gray" : "darkgray"
            radius: 5
            gradient: Gradient {
                GradientStop { position: 0.0; color: rebootbutton.pressed ? "gray" : "darkgray" }
                GradientStop { position: 1.0; color: rebootbutton.pressed ? "red" : "darkred" }
            }
        }
        onPressed: {
            tcpClient.rebootSignal()
        }
    }


    Dashboard
    {
        x : 312
        y : 100
        width: 400
        height: 400
        gaugeName: "RPM"
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
        //arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        // innerArcWidth : innerArcWidth
        // innerArcPos : innerArcPos
        progressBarPos: 45
        progressBarThickness: 75
        // innerCircleSize: innerCircleSize
        textBarSize: 30
        // tickPosOffset: tickPosOffset
        textPosOffset: 50
        // tickMarkLength: tickMarkLength
        arcTextSize: 20
        progBarArcPos: 85
        unit: "km/h"
        unitTextSize: 12
        unitOffset: 80
        gaugeNameOffset: 240
        gaugeNameTextSize: 25
        minorticks: 20

        Text {
            x : 295
            y : 275
            id: text
            font.family: "Helvetica"
            font.italic: true
            font.bold: true
            font.pixelSize: 20
            color: "white"
            rotation: 38
            text: qsTr("x1000")
        }
    }

    Dashboard
    {
        x : 150
        y : 12
        width: 200
        height: 200
        gaugeName: "ENGINE"
        //startAngle: startAngle
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
//        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        // innerArcWidth : innerArcWidth
        // innerArcPos : innerArcPos
        progressBarPos: 22.5
        progressBarThickness: 38
        // innerCircleSize: innerCircleSize
        textBarSize: 10
        // tickPosOffset: tickPosOffset
        textPosOffset: 20
        // tickMarkLength: tickMarkLength
        arcTextSize: 6
        progBarArcPos: 42.5
        unit: "%"
        unitTextSize: 8
        unitOffset: 40
        gaugeNameOffset: 120
        gaugeNameTextSize: 7.5
    }


    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 62
        y : 200
        gaugeName: "COOLANT"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 120
        val: tcpClient.coolanttemp
        interval: 30
//        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        // innerArcWidth : initialSpeedometerSize / 60
        // innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: 22.5
        progressBarThickness: 38
        // innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: 10
        // tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: 20
        // tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: 6
        progBarArcPos: 42.5
        unit: "°C"
        unitTextSize: 8
        unitOffset: 40
        gaugeNameOffset: 120
        gaugeNameTextSize: 7.5
    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 150
        y : 388
        gaugeName: "IMP"
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
//        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    //     innerArcWidth : initialSpeedometerSize / 60
    //     innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: 22.5
        progressBarThickness: 38
    //     innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: 10
    //     tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: 20
    //     tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: 6
        progBarArcPos: 42.5
        unit: "kPa"
        unitTextSize: 8
        unitOffset: 40
        gaugeNameOffset: 120
        gaugeNameTextSize: 7.5
    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 674
        y : 12
        gaugeName: "IAT"
        width: initialSpeedometerSize
        height: initialSpeedometerSize
        startAngle: startAngle
        lowestRange: -40
        highestRange: 255
        interval: 20
        val: tcpClient.intaketemp
        // arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        // innerArcWidth : initialSpeedometerSize / 60
        // innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: 22.5
        progressBarThickness: 38
        // innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: 10
        // tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: 20
        // tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: 6
        progBarArcPos: 42.5
        unit: "°C"
        unitTextSize: 8
        unitOffset: 40
        gaugeNameOffset: 120
        gaugeNameTextSize: 7.5
    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 762
        y : 200
        gaugeName: "MAF"
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
//        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        // innerArcWidth : initialSpeedometerSize / 60
        // innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: 22.5
        progressBarThickness: 38
        // innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: 10
        // tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: 20
        // tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: 6
        progBarArcPos: 42.5
        unit: "g/s"
        unitTextSize: 8
        unitOffset: 40
        gaugeNameOffset: 120
        gaugeNameTextSize: 7.5
    }

    Dashboard
    {
        property real initialSpeedometerSize: 200
        x : 674
        y : 388
        gaugeName: "THROTTLE"
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
//        arcWidth: initialSpeedometerSize / 60
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        // innerArcWidth : initialSpeedometerSize / 60
        // innerArcPos : initialSpeedometerSize / 6.67
        progressBarPos: 22.5
        progressBarThickness: 38
        // innerCircleSize: initialSpeedometerSize / 4.5
        textBarSize: 10
        // tickPosOffset: -initialSpeedometerSize / 50
        textPosOffset: 20
        // tickMarkLength: initialSpeedometerSize / 15
        arcTextSize: 6
        progBarArcPos: 42.5
        unit: "%"
        unitTextSize: 8
        unitOffset: 40
        gaugeNameOffset: 120
        gaugeNameTextSize: 7.5

    }

}
