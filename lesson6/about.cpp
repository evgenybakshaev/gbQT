#include "about.h"
#include "ui_about.h"
#include <QFile>
#include <QTextStream>
About::About(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QFile f(":/readme.txt");
    if(f.open(QFile::ReadOnly | QFile::ExistingOnly | QFile::Text))
    {
        QTextStream stream(&f);
        stream.setCodec("UTF-8");
        ui->label->setText(stream.readAll());
        f.close();
    }
}

About::~About()
{
    delete ui;
}

void About::on_pushButton_released()
{
    this->close();
}
