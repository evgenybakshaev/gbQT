#include "unittest.h"
#include "mainwindow.h"

UnitTest::UnitTest(QObject *parent)
    : QObject(parent)
{

}

void UnitTest::testChangeTheme()
{
    MainWindow w;
    w.show();
    w.changeTheme("Aqua");

    QFile qssFile(QString(":/qss/%1.qss").arg("Aqua"));
    qssFile.open(QFile::ReadOnly);
    QString qssStr = qssFile.readAll();

    QCOMPARE(qApp->styleSheet(), qssStr);
}

void UnitTest::testOn_actioninsertDateTime_triggered()
{
    MainWindow w;
    w.show();

    w.on_actioninsertDateTime_triggered();
    QDateTime dt = QDateTime::currentDateTime();
    QString text = w.getCurEdit()->toPlainText();
    QCOMPARE(text/*.left(text.length()-2)*/, dt.toString("dd.MM.yyyy hh:mm:ss"));
}
