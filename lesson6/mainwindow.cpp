#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QRegularExpression>
#include <QPlainTextEdit>
#include <QMdiSubWindow>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)  
    , uiShortcuts(this)
{
    ui->setupUi(this);
    ui->mdiArea->addSubWindow(new QPlainTextEdit(this));
    //ui->mdiArea->addSubWindow(new QPlainTextEdit(this));

    QStringList horizontalHeader;
    horizontalHeader.append("Action");
    horizontalHeader.append("Shortcut");
    uiShortcuts.model->setHorizontalHeaderLabels(horizontalHeader);
    QStandardItem *item;
    //actionNew
    item = new QStandardItem(ui->actionNew->iconText());
    item->setFlags(Qt::ItemIsEnabled);
    uiShortcuts.model->setItem(0, 0, item);
    item = new QStandardItem(ui->actionNew->shortcut().toString());
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    uiShortcuts.model->setItem(0, 1, item);
    //actionOpen
    item = new QStandardItem(ui->actionOpen->iconText());
    item->setFlags(Qt::ItemIsEnabled);
    uiShortcuts.model->setItem(1, 0, item);
    item = new QStandardItem(ui->actionOpen->shortcut().toString());
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    uiShortcuts.model->setItem(1, 1, item);
    //actionSave
    item = new QStandardItem(ui->actionSave->iconText());
    item->setFlags(Qt::ItemIsEnabled);
    uiShortcuts.model->setItem(2, 0, item);
    item = new QStandardItem(ui->actionSave->shortcut().toString());
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    uiShortcuts.model->setItem(2, 1, item);
    //actionExit
    item = new QStandardItem(ui->actionExit->iconText());
    item->setFlags(Qt::ItemIsEnabled);
    uiShortcuts.model->setItem(3, 0, item);
    item = new QStandardItem(ui->actionExit->shortcut().toString());
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    uiShortcuts.model->setItem(3, 1, item);
    connect(&uiShortcuts, SIGNAL(shortcuts_changed(QList<QString>)), this, SLOT(shortcuts_changed(QList<QString>)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    uiAbout.show();
}

void MainWindow::on_actionNew_triggered()
{
    ui->actionSave->setEnabled(true);
    QPlainTextEdit *curEdit = new QPlainTextEdit(this);
    ui->mdiArea->addSubWindow(curEdit);
    curEdit->setWindowTitle("New");
    curEdit->show();
    //QPlainTextEdit *curEdit = (QPlainTextEdit*) ui->mdiArea->activeSubWindow();
    //curEdit->setEnabled(true);
    //curEdit->clear();
}

void MainWindow::on_actionOpen_triggered()
{
    QString s = QFileDialog::getOpenFileName(this, tr("Open text file"), QDir::current().path(), "Text(*.txt);;ALL(*.*)");
    QPlainTextEdit *curEdit = new QPlainTextEdit(this);
    if (s.length() > 0)
    {
       int index = s.indexOf(".txt");
       if (index != -1 && s.length() - 4 == index)
       {
           QFile file(s);
           if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
           {

               QTextStream stream(&file);
               stream.setCodec("UTF-8");
               curEdit->setPlainText(stream.readAll());
               file.close();
           }
       }
    }
    ui->actionSave->setEnabled(true);
    //curEdit->setEnabled(true);

    ui->mdiArea->addSubWindow(curEdit);
    curEdit->setWindowTitle(s);
    curEdit->show();

}

void MainWindow::on_actionSave_triggered()
{

    QPlainTextEdit *curEdit = ((QPlainTextEdit*)ui->mdiArea->activeSubWindow()->widget());
    QString s = QFileDialog::getSaveFileName(this, tr("Save As"), QDir::current().path(), "Text(*.txt);;ALL(*.*)");
    curEdit->setWindowTitle(s);
    if (s.length() > 0)
    {
      QString ext = QString(&(s.data()[s.length() - 4]));
      if (ext == ".txt")
       {
           QFile file(s);
           if (file.open(QFile::WriteOnly))
           {
               QTextStream stream(&file);
               stream.setCodec("UTF-8");

               stream << curEdit->toPlainText();
               file.close();
           }
       }
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionRussian_triggered()
{
    translator.load(":/lang/LangRU.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actionEnglish->setChecked(false);

    uiShortcuts.model->item(0,0)->setText(ui->actionNew->iconText());
    uiShortcuts.model->item(1,0)->setText(ui->actionOpen->iconText());
    uiShortcuts.model->item(2,0)->setText(ui->actionSave->iconText());
    uiShortcuts.model->item(3,0)->setText(ui->actionExit->iconText());

//    ui->widget->rebuildModel("d:/");
}

void MainWindow::on_actionEnglish_triggered()
{
    translator.load("");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actionRussian->setChecked(false);

    uiShortcuts.model->item(0,0)->setText(ui->actionNew->iconText());
    uiShortcuts.model->item(1,0)->setText(ui->actionOpen->iconText());
    uiShortcuts.model->item(2,0)->setText(ui->actionSave->iconText());
    uiShortcuts.model->item(3,0)->setText(ui->actionExit->iconText());
}

void MainWindow::on_actionOpen_ReadOnly_triggered()
{
    on_actionOpen_triggered();
    QPlainTextEdit *curEdit = (QPlainTextEdit*) ui->mdiArea->activeSubWindow();
    ui->actionSave->setEnabled(false);
    curEdit->setEnabled(false);
}

void MainWindow::on_actionShortcuts_triggered()
{

    uiShortcuts.show();
}

void MainWindow::changeTheme(QString theme)
{
    QFile qssFile(QString(":/qss/%1.qss").arg(theme));
    qssFile.open(QFile::ReadOnly);
    QString qssStr = qssFile.readAll();
    qApp->setStyleSheet(qssStr);
    qssFile.close();
}

void MainWindow::shortcuts_changed(QList<QString> shortcuts)
{
//    foreach(auto shortcut, shortcuts)
//        qDebug() << shortcut;

    ui->actionNew->setShortcut(shortcuts[0]);
    ui->actionOpen->setShortcut(shortcuts[1]);
    ui->actionSave->setShortcut(shortcuts[2]);
    ui->actionExit->setShortcut(shortcuts[3]);
}

void MainWindow::on_actionThemeElegantDark_triggered()
{
    ui->actionThemeDefault->setChecked(false);
    ui->actionThemeAqua->setChecked(false);

    changeTheme("ElegantDark");
}

void MainWindow::on_actionThemeAqua_triggered()
{
    ui->actionThemeElegantDark->setChecked(false);
    ui->actionThemeDefault->setChecked(false);

    changeTheme("Aqua");
}

void MainWindow::on_actionThemeDefault_triggered()
{
    ui->actionThemeElegantDark->setChecked(false);
    ui->actionThemeAqua->setChecked(false);

    changeTheme("");
}

void MainWindow::on_actionPrint_triggered()
{
    QPlainTextEdit *curEdit = ((QPlainTextEdit*)ui->mdiArea->activeSubWindow()->widget());
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;
    curEdit->print(&printer);
}
