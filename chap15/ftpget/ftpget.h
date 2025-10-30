#ifndef FTPGET_H
#define FTPGET_H

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QUrl;

class FtpGet : public QObject
{
    Q_OBJECT

public:
    FtpGet(QObject *parent = 0);

    bool getFile(const QUrl &url);

signals:
    void done();

private slots:
    void downloadFinished(QNetworkReply *reply);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QNetworkAccessManager manager;
    QFile file;
};

#endif
