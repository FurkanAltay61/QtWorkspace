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

    FpsCounter {
        x : 10
        y : 10
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
        speed: mydashboard.speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        progressBarPos: progressBarPos + 16
        innerCircleSize: innerCircleSize + 25
        textBarSize: textBarSize + 10
        tickMarkLength: tickMarkLength + 10
        tickPosOffset: tickPosOffset + 10
        textPosOffset: textPosOffset - 5
        progressBarThickness: progressBarThickness + 8
        arcTextSize: arcTextSize + 2
        progBarArcPos: progBarArcPos + 10
        unit: "km/h"
        unitOffset: unitOffset + 10
        gaugeNameOffset: gaugeNameOffset + 75
        unitTextSize: unitTextSize
        gaugeNameTextSize: gaugeNameTextSize + 5
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
        highestRange: 8
        interval: 1
        speed: mydashboard.speed / 30
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        progressBarPos: progressBarPos + 16
        innerCircleSize: innerCircleSize + 25
        textBarSize: textBarSize + 10
        tickMarkLength: tickMarkLength + 10
        tickPosOffset: tickPosOffset + 10
        textPosOffset: textPosOffset - 5
        progressBarThickness: progressBarThickness + 8
        arcTextSize: arcTextSize + 2
        progBarArcPos: progBarArcPos + 10
        unit: "x1000"
        unitOffset: unitOffset + 10
        gaugeNameOffset: gaugeNameOffset + 75
        unitTextSize: unitTextSize
        gaugeNameTextSize: gaugeNameTextSize + 5
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
        speed: mydashboard.speed / 2.4
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        progressBarPos: progressBarPos + 2
        innerCircleSize: innerCircleSize - 5
        progressBarThickness: progressBarThickness
        unit: "%"
        gaugeNameTextSize: gaugeNameTextSize - 2
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
        speed: mydashboard.speed / 2
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        interval: 30
        innerCircleSize: innerCircleSize - 5
        progressBarPos: progressBarPos + 2
        gaugeNameTextSize: gaugeNameTextSize - 2

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
        speed: mydashboard.speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerCircleSize: innerCircleSize - 5
        progressBarPos: progressBarPos + 2
        gaugeNameTextSize: gaugeNameTextSize - 2
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
        speed: mydashboard.speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerCircleSize: innerCircleSize - 5
        progressBarPos: progressBarPos + 2
        gaugeNameTextSize: gaugeNameTextSize - 2
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
        speed: mydashboard.speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerCircleSize: innerCircleSize - 5
        progressBarPos: progressBarPos + 2
        gaugeNameTextSize: gaugeNameTextSize - 2
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
        speed: mydashboard.speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        innerCircleSize: innerCircleSize - 5
        progressBarPos: progressBarPos + 2
        gaugeNameTextSize: gaugeNameTextSize - 2
        unit: "%"

    }

    Dashboard
    {
        x : 412
        y : 0
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: mydashboard.speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
        gaugeNameTextSize: gaugeNameTextSize - 2
        progressBarPos: progressBarPos + 2
    }



}
