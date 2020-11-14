#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QShortcut>
#include "QStandardItemModel"
#include "QStandardItem"
#include <QStringList>
#include <QMdiArea>
#include <QPlainTextEdit>
#include "about.h"
#include "shortcuts.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class UnitTest;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();
    void on_actionRussian_triggered();
    void on_actionEnglish_triggered();
    void on_actionOpen_ReadOnly_triggered();
    void on_actionShortcuts_triggered();
    void on_actionThemeElegantDark_triggered();
    void on_actionThemeAqua_triggered();
    void on_actionThemeDefault_triggered();
    void on_actionPrint_triggered();
    void on_actionLeft_triggered();
    void on_actionRight_triggered();
    void on_actionCenter_triggered();
    void on_actionJustify_triggered();
    void on_actionCopyFormat_triggered();
    void on_actionPasteFormat_triggered();
    void on_actionFont_triggered();
    void on_actioninsertDateTime_triggered();

private:

    Ui::MainWindow *ui;
    About uiAbout;
    Shortcuts uiShortcuts;
    QTranslator translator;
    void changeTheme(QString theme);
    QTextCharFormat fmt;

public:
    QTextEdit * getCurEdit();
public slots:
    void shortcuts_changed(QList<QString>);

};
#endif // MAINWINDOW_H
