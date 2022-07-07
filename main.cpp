#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bacteriahandler.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    BacteriaHandler bacterie_handler; //making instance of Bacteria handler

    QQmlApplicationEngine engine;

//    exposing bacteria handler to QML
    engine.rootContext()->setContextProperty("Bacteria_Handler", &bacterie_handler);

    //rest of the code
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
