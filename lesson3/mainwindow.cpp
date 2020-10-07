#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QRegularExpression>

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


//void MainWindow::on_actionUndo_triggered()
//{
//    ui->plainTextEdit->undo();
//}

//void MainWindow::on_actionRedo_triggered()
//{
//    ui->plainTextEdit->redo();
//}

void MainWindow::on_plainTextEdit_textChanged()
{

}

void MainWindow::on_actionAbout_triggered()
{
    uiAbout.show();
}

void MainWindow::on_actionNew_triggered()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_actionOpen_triggered()
{
    QString s = QFileDialog::getOpenFileName(this, "Заголовок окна", QDir::current().path(), "Text(*.txt);;HTML(*.html);;ALL(*.*)");
    if (s.length() > 0)
    {
       int index = s.indexOf(".txt");
       if (index != -1 && s.length() - 4 == index)
       {
           QFile file(s);
           if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
           {
               QTextStream stream(&file);
               ui->plainTextEdit->setPlainText(stream.readAll());
               file.close();
           }
       }

       index = s.indexOf(".html");
       if (index != -1 && s.length() - 5 == index)
       {
           QFile file(s);
           if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
           {
                QTextStream stream(&file);
                stream.setCodec("UTF-8");
                QString data = stream.readAll();
                QString text;
                QRegularExpression re;
                text.append("Погода:\n");
                re.setPattern("<a name=\"clb1221590\" class=\"weather__city svelte-bjx6w8\".*?>(.*?)</a>.*?class=\"weather__temp svelte-bjx6w8\">(.*?)</span>.*?class=\"weather__info svelte-bjx6w8\" title=\"(.*?)\"><div class=\"weather__description svelte-bjx6w8\">(.*?)</div>.*?<div class=\"weather__humidity svelte-bjx6w8\">");
                QRegularExpressionMatch match = re.match(data);
                if(match.hasMatch())
                {
                   text.append(match.captured(1).append(", "));
                   text.append(match.captured(2).append(", "));
                   text.append(match.captured(4).append(", "));
                   text.append(match.captured(3).append("\n"));
                }
                text.append("Прогноз:\n");
                re.setPattern("<div class=\"weather__item\" title=\"(.*?)\".*?<div class=\"weather__period svelte-bjx6w8\">(.*?)</div>.*?<span class=\"weather__temp-period svelte-bjx6w8\">(.*?)</span></div>");
                QRegularExpressionMatchIterator i = re.globalMatch(data);
                while (i.hasNext()) {
                    QRegularExpressionMatch match = i.next();
                    text.append(match.captured(2).append(", "));
                    text.append(match.captured(3).append(", "));
                    text.append(match.captured(1).append("\n"));
                }

                text.append("\nКурс валют:\n");
                re.setPattern("<a href=\"https://news\\.mail\\.ru/currency/(?:\\w+/)+(\\w+)/\".*?([\\d.]+)</div>");
                i = re.globalMatch(data);
                while (i.hasNext()) {
                    QRegularExpressionMatch match = i.next();
                    text.append(match.captured(1).append(" "));
                    text.append(match.captured(2).append("\n"));
                }
                ui->plainTextEdit->setPlainText(text);
                file.close();
           }
       }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString s = QFileDialog::getSaveFileName(this, "Заголовок окна", QDir::current().path(), "Text(*.txt);;ALL(*.*)");
    if (s.length() > 0)
    {
      QString ext = QString(&(s.data()[s.length() - 4]));
      if (ext == ".txt")
       {
           QFile file(s);
           if (file.open(QFile::WriteOnly))
           {
               QTextStream stream(&file);
               stream << ui->plainTextEdit->toPlainText();
               file.close();
           }
       }
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
