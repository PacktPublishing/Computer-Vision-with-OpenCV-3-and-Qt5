#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "qimageprocessor.h"
#include "qimageviewer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<QImageProcessor>("com.amin.classes", 1, 0, "ImageProcessor");
    qmlRegisterType<QImageViewer>("com.amin.classes", 1, 0, "ImageViewer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
