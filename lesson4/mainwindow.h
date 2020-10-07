#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QShortcut>
#include "QStandardItemModel"
#include "QStandardItem"
#include <QStringList>
#include "about.h"
#include "shortcuts.h"

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

    void on_actionAbout_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();

    void on_actionOpen_ReadOnly_triggered();

    void on_actionShortcuts_triggered();

private:
    Ui::MainWindow *ui;
    About uiAbout;
    Shortcuts uiShortcuts;
    QTranslator translator;
public slots:
    void shortcuts_changed(QList<QString>);

};
#endif // MAINWINDOW_H
