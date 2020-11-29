#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "downloader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Downloader *downloader;
//    QProgressBar *ppb;
//    QLineEdit   *txt;
//    QPushButton *pbutton;
    void showPic(const QString &);
    uint j = 0;
private slots:
    void slotError(const QString &);
    void slotDownloadProgress(qint64,qint64);
    void slotDone(const QUrl &, const QByteArray &);
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
