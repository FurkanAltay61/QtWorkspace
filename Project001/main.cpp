#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <dashboard.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    qmlRegisterType<Dashboard>("Dashboardqml", 1, 0, "Dashboard");
    QQmlApplicationEngine engine;

    const QUrl mainQmlUrl(QStringLiteral("qrc:/main.qml"));

    // Now load the QML file
    engine.load(mainQmlUrl);

    // Check if the engine loaded the QML file successfully
    if (engine.rootObjects().isEmpty()) {
        qWarning() << "Error: No root objects were loaded from QML.";
        return -1;
    }

    return app.exec();
}



