#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    void download(const QUrl&);
signals:
    void downloadProgress(qint64,qint64);
    void done(const QUrl &,const QByteArray &);
    void error(const QString &);
private slots:
    void slotFinished(QNetworkReply *);
private:
    QNetworkAccessManager *pnam;
};

#endif // DOWNLOADER_H
