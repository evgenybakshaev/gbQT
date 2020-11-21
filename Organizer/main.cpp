#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "basedbreader.h"
#include "tablemodel.h"

int main(int argc, char *argv[])
{
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

   QGuiApplication app(argc, argv);

   QQmlApplicationEngine engine;
   const QUrl url(QStringLiteral("qrc:/main.qml"));
   QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                    &app, [url](QObject *obj, const QUrl &objUrl) {
       if (!obj && url == objUrl)
           QCoreApplication::exit(-1);
   }, Qt::QueuedConnection);
// Зарегистрируем класс
   qmlRegisterType<BaseDBReader>("BaseDBReader", 1, 0, "BaseDBReader");
   qmlRegisterType<TableModel>("TableModel", 1, 0, "TableModel");
   engine.load(url);

   return app.exec();
}
