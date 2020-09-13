#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pb_Calc_released();

    void on_pb_Calc_2_released();

    void on_rbRadians_toggled(bool checked);

    void on_pbEdit1toEdit2_released();

    void on_pbEdit2toEdit1_released();

    void on_pbResetEdit1_released();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
