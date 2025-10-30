#include <QtCore>
#include <QtNetwork>
#include <iostream>

#include "ftpget.h"

FtpGet::FtpGet(QObject *parent)
    : QObject(parent)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)), 
            this, SLOT(downloadFinished(QNetworkReply*)));
}

bool FtpGet::getFile(const QUrl &url)
{
    if (!url.isValid()) {
        std::cerr << "Error: Invalid URL" << std::endl;
        return false;
    }

    if (url.scheme() != "ftp") {
        std::cerr << "Error: URL must start with 'ftp:'" << std::endl;
        return false;
    }

    if (url.path().isEmpty()) {
        std::cerr << "Error: URL has no path" << std::endl;
        return false;
    }

    QString localFileName = QFileInfo(url.path()).fileName();
    if (localFileName.isEmpty())
        localFileName = "ftpget.out";

    file.setFileName(localFileName);
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable(file.fileName()) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }

    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
            this, SLOT(downloadProgress(qint64, qint64)));
    
    return true;
}

void FtpGet::downloadFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error: " << qPrintable(reply->errorString())
                  << std::endl;
    } else {
        file.write(reply->readAll());
        std::cerr << "File downloaded as "
                  << qPrintable(file.fileName()) << std::endl;
    }
    file.close();
    reply->deleteLater();
    emit done();
}

void FtpGet::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        std::cerr << "Downloaded " << bytesReceived << " of " 
                  << bytesTotal << " bytes\r" << std::flush;
    }
}
