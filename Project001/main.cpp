#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <dashboard.h>
#include <unistd.h>
#include <tcpclient.h>
#include <QThread>
#include <QQmlContext>
#include <tcpclientwrapper.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Dashboard mydashboard;
    TcpClient *client = new TcpClient("192.168.0.10", (quint16)35000);
    QThread clientThread;
    TcpClientWrapper *clientWrapper = new TcpClientWrapper(client);

    qmlRegisterType<Dashboard>("Dashboardqml", 1, 0, "Dashboard");

    client->moveToThread(&clientThread);
    //QObject::connect(&clientThread, &QThread::started, client, &TcpClient::connectToServer);
    QObject::connect(&clientThread, &QThread::finished, client, &QObject::deleteLater);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &clientThread, &QThread::quit);
    QObject::connect(clientWrapper, &TcpClientWrapper::resetSignal,client, &TcpClient::handleResetSignal);
    QObject::connect(clientWrapper, &TcpClientWrapper::connectSignal,client, &TcpClient::handleConnectSignal);
    QObject::connect(clientWrapper, &TcpClientWrapper::rebootSignal,client, &TcpClient::handleRebootSignal);

    clientThread.start();

    engine.rootContext()->setContextProperty("mydashboard",&mydashboard);
    engine.rootContext()->setContextProperty("tcpClient", clientWrapper);

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

    int ret = app.exec();
    clientThread.wait();

    qDebug() << "thread quitted";
    return ret;
}



