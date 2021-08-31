#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QFontDatabase>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    //加载字体并打印名称
    const int font_id = QFontDatabase::addApplicationFont(":/font/fontawesome-webfont.ttf");
    qDebug() << QFontDatabase::applicationFontFamilies(font_id);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
