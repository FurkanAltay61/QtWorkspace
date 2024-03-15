#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <dashboard.h>
#include <unistd.h>
#include <tcpclient.h>
#include <QThread>
#include <QQmlContext>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    Dashboard mydashboard;
    qmlRegisterType<Dashboard>("Dashboardqml", 1, 0, "Dashboard");
    QQmlApplicationEngine engine;
    TcpClient client("192.168.0.10", (quint16)35000);
    QThread clientThread;
    client.moveToThread(&clientThread);
    clientThread.start();
    QObject::connect(&client, &TcpClient::engineLoadSent,&mydashboard,&Dashboard::engineLoadReceived);
    QObject::connect(&client, &TcpClient::coolantTempSent,&mydashboard,&Dashboard::coolantTempReceived);
    QObject::connect(&client, &TcpClient::intakePressSent,&mydashboard,&Dashboard::intakePressReceived);
    QObject::connect(&client, &TcpClient::rpmSent,&mydashboard,&Dashboard::rpmReceived);
    QObject::connect(&client, &TcpClient::speedSent,&mydashboard,&Dashboard::speedReceived);
    QObject::connect(&client, &TcpClient::intakeTempSent,&mydashboard,&Dashboard::IntakeTempReceived);
    QObject::connect(&client, &TcpClient::massAirFlowSent,&mydashboard,&Dashboard::MassAirFlowReceived);
    QObject::connect(&client, &TcpClient::throttlePosSent,&mydashboard,&Dashboard::ThrottlePosReceived);

    engine.rootContext()->setContextProperty("mydashboard",&mydashboard);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    // Check if the engine loaded the QML file successfully
    if (engine.rootObjects().isEmpty()) {
        qWarning() << "Error: No root objects were loaded from QML.";
        return -1;
    }

    return app.exec();
}



