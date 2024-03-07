import QtQuick 2.15
import QtQuick.Window 2.15
import Dashboardqml 1.0


Window {
    visible: true
    width: 1024
    height: 600
    title: qsTr("Speedometer")
    color: "black"
    visibility:  "FullScreen"


    Dashboard
    {
        x : 0
        y : 0
        id: "speedometer"
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 200
        y : 0
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: 8
        interval: 1
        speed: speed / 30
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 400
        y : 0
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }


    Dashboard
    {
        x : 600
        y : 0
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 800
        y : 0
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 0
        y : 200
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 200
        y : 200
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 400
        y : 200
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 600
        y : 200
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }


    Dashboard
    {
        x : 800
        y : 200
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }


    Dashboard
    {
        x : 0
        y : 400
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 200
        y : 400
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 400
        y : 400
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 600
        y : 400
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

    Dashboard
    {
        x : 800
        y : 400
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }


}
