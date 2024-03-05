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


    Dashboard
    {
        x : 0
        y : 0
        objectName: "dashboardMeter"
        //anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
   //     alignAngle: alignAngle
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
        x : 300
        y : 0
        objectName: "dashboardMeter"
        //anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
   //     alignAngle: alignAngle
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
        objectName: "dashboardMeter"
        //anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
   //     alignAngle: alignAngle
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
        y : 300
        objectName: "dashboardMeter"
        //anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
   //     alignAngle: alignAngle
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
        x : 300
        y : 300
        objectName: "dashboardMeter"
        //anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
   //     alignAngle: alignAngle
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
        y : 300
        objectName: "dashboardMeter"
        //anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
   //     alignAngle: alignAngle
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
