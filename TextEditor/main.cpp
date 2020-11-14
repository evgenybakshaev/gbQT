#include "mainwindow.h"

#include <QApplication>
#include "unittest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    MainWindow w;
//    w.show();
    QTest::qExec(new UnitTest(), argc, argv); // Запускаем выполнения теста

    //return a.exec();
    return 0;
}
