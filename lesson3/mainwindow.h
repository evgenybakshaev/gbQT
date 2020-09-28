#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"

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
    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_plainTextEdit_textChanged();

    void on_actionAbout_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    About uiAbout;
};
#endif // MAINWINDOW_H
