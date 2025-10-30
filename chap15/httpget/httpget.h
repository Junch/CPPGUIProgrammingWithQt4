#ifndef HTTPGET_H
#define HTTPGET_H

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QUrl;

class HttpGet : public QObject
{
    Q_OBJECT

public:
    HttpGet(QObject *parent = 0);

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
