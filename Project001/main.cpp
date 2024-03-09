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
    QObject::connect(&client, &TcpClient::dataSent,&mydashboard,&Dashboard::onDataReceived);

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



