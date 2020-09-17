#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QRegExp>

#include "customlistmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plainTextEdit_textChanged();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_released();

    void on_pushButton_4_released();

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> symb;

    CustomListModel *itemModel;
    QStandardItemModel *tableModel;
    QSize listGridSize;
    QSize iconGridSize;

};
#endif // MAINWINDOW_H
