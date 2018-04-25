#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>

#include "qmllog.h"
#include "ffmpeg.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<QMLLog>("QMLLog", 1, 0, "QMLLog");

    QQuickView view;
    view.engine()->rootContext()->setContextProperty("ffmpeg", FFMpeg::getInstance());
    view.setSource(QUrl("qrc:/main.qml"));
    view.setMinimumSize(QSize(800, 480));
    view.show();

    return app.exec();
}
