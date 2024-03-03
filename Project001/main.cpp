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

    // Connect before loading the QML to ensure the slot is connected in time.
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [&](QObject *obj, const QUrl &objUrl) {
        if (mainQmlUrl != objUrl) {
            return;
        }

        // // Use the proper root object instead of obj, which is the component that was just created
        // QObject *rootObject = engine.rootObjects().first();
        // QObject *dashboardmeter = rootObject->findChild<QObject*>("dashboardMeter");
        // if (!dashboardmeter) {
        //     qWarning() << "Error: dashboardMeter object not found.";
        //     return;
        // }

        // Dashboard *ptrdashboardmeter = qobject_cast<Dashboard*>(dashboardmeter);
        // if (!ptrdashboardmeter) {
        //     qWarning() << "Error: Unable to cast to Dashboard type.";
        //     return;
        // }

        // qDebug() << "Successfully accessed Dashboard";
        // // Now you can safely use ptrdashboardmeter
        // QTimer *timer = new QTimer(ptrdashboardmeter); // Use ptrdashboardmeter as the parent for proper cleanup

        // QObject::connect(timer, &QTimer::timeout, ptrdashboardmeter, [ptrdashboardmeter]() {
        //     static bool direction = true;
        //     static qreal val = 0;

        //     ptrdashboardmeter->setSpeed(val);
        //     if (val >= 4000) {
        //         direction = false;
        //     } else if (val <= 0.1) {
        //         direction = true;
        //     }

        //     val += direction ? 10 : -10;
        //     qDebug() << "Value updated to" << val;
        // });

        // timer->start(16);
    });

    // Now load the QML file
    engine.load(mainQmlUrl);

    // Check if the engine loaded the QML file successfully
    if (engine.rootObjects().isEmpty()) {
        qWarning() << "Error: No root objects were loaded from QML.";
        return -1;
    }

    return app.exec();
}



