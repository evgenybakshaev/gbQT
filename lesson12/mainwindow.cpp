#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , downloader(new Downloader(this))
{
    ui->setupUi(this);

    connect(downloader,SIGNAL(downloadProgress(qint64,qint64)), SLOT(slotDownloadProgress(qint64,qint64)));
    connect(downloader,SIGNAL(done(const QUrl&, const QByteArray&)), SLOT(slotDone(const QUrl&, const QByteArray&)));
    connect(downloader,SIGNAL(error(const QString &)), SLOT(slotError(const QString &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPic(const QString &path)
{
    QPixmap pix(path);
    //pix = pix.scaled(pix.size());
    QString name = QString("label_%1").arg(++j);
    QLabel *pLabel = this->findChild<QLabel *>(name);
    //QLabel *pLabel = new QLabel();
    pLabel->setPixmap(pix);
    pLabel->setFixedSize((pix.size()));

    if(j == 3) j = 0;
}

void MainWindow::slotError(const QString &str)
{
    QMessageBox::critical(this, "Error",str);
}

void MainWindow::slotDownloadProgress(qint64 recived, qint64 total)
{
    if(total > 0)
    {
        ui->progressBar->setValue(100*recived/total);
    }
}

void MainWindow::slotDone(const QUrl &url, const QByteArray &ba)
{

    int j = 0;
    if(url.path()=="/images/search")
    {
        QString str(ba);

        QRegularExpression re("<img class=\"serp-item__thumb justifier__thumb\" src=\"//(.*?)\"");
        QRegularExpressionMatchIterator i = re.globalMatch(str);

        while(i.hasNext() && j++ < 3){
            QRegularExpressionMatch match = i.next();
            QString nexturl = QString("https://") + match.captured(1);

            downloader->download(QUrl(nexturl));

            //qDebug() << "url " << nexturl;
        }
    }
    else
    {
        QFile file(url.path().section('/',-1));
        if(file.open(QIODevice::WriteOnly))
        {
            file.write(ba);
            file.close();
        }
        showPic(file.fileName());
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString url = "https://yandex.ru/images/search?text=";
    url.append(ui->lineEdit->text());
    downloader->download(QUrl(url));

    ui->progressBar->setValue(0);

}
