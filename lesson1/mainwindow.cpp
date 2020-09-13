#include "mainwindow.h"
#include "ui_mainwindow.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Calc_released()
{
    float x1,x2;
    int a = ui->le_a->text().toInt();
    int b = ui->le_b->text().toInt();
    int c = ui->le_c->text().toInt();

    if(a == 0){
        x1 = -c/b;
        ui->te_Result->setText(QString("X = %1").arg(x1));
    }
    else
    {
        int D = b*b - 4*a*c;

        if(D > 0)
        {
            x1 = (-b - sqrt(D))/2*a;
            x2 = (-b + sqrt(D))/2*a;
            ui->te_Result->setText(QString("X1 = %1\nX2 = %2").arg(x1).arg(x2));
        }
        else if(D == 0)
        {
            x1 = -b/2*a;
            ui->te_Result->setText(QString("X = %1").arg(x1));
        }
        else
        {
            ui->te_Result->setText("Нет корней");
        }
    }

}

void MainWindow::on_pb_Calc_2_released()
{
    double alpha,a,b,c;
    a = ui->leA->text().toDouble();
    b = ui->leB->text().toDouble();
    alpha = ui->leAlpha->text().toDouble();

    if(!ui->rbRadians->isChecked())
        alpha*=M_PI/180.0;

    c = sqrt(a*a + b*b - 2*a*b*cos(alpha));
    ui->teResult2->setText(QString("c = %1").arg(c));
}

void MainWindow::on_rbRadians_toggled(bool checked)
{
    double alpha = ui->leAlpha->text().toDouble();
    if(checked)
        alpha*=M_PI/180.0;
    else
         alpha*=180.0/M_PI;

    ui->leAlpha->setText(QString("%1").arg(alpha));
}

void MainWindow::on_pbEdit1toEdit2_released()
{
    ui->ptEdit2->appendPlainText(ui->ptEdit1->toPlainText());
}

void MainWindow::on_pbEdit2toEdit1_released()
{
    ui->ptEdit1->setPlainText(ui->ptEdit2->toPlainText());
}

void MainWindow::on_pbResetEdit1_released()
{
    ui->ptEdit1->appendHtml("<font color='red'>Это виджет plainText1</font>");
}
