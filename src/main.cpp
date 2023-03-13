#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QStringList>
#include <QQmlComponent>

#include "performer.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app{argc, argv};

    // The values are used by the QSettings class when it is constructed using the empty constructor.
    // This saves having to repeat this information each time a QSettings object is created.
    app.setOrganizationName("YVY");
    app.setOrganizationDomain("github.com/uvuu/word-matching-trainer");
    app.setApplicationName("word-matching-trainer");

    QQmlApplicationEngine engine;
    const QUrl url{QStringLiteral("qrc:/main.qml")};
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("performer", new Performer{});
    engine.load(url);

    return app.exec();
}
