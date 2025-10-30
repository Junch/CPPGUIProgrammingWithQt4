#include <QtCore>
#include <QtNetwork>
#include <iostream>

#include "spider.h"

Spider::Spider(QObject *parent)
    : QObject(parent)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

bool Spider::getDirectory(const QUrl &url)
{
    if (!url.isValid()) {
        std::cerr << "Error: Invalid URL" << std::endl;
        return false;
    }

    if (url.scheme() != "ftp") {
        std::cerr << "Error: URL must start with 'ftp:'" << std::endl;
        return false;
    }

    std::cerr << "Note: FTP directory listing is not supported in Qt5." << std::endl;
    std::cerr << "This example has been simplified to demonstrate basic FTP download." << std::endl;
    std::cerr << "For full FTP functionality, consider using third-party libraries." << std::endl;
    
    // Simplified version: just try to download the URL as a file
    QString path = url.path();
    if (path.isEmpty() || path.endsWith('/')) {
        std::cerr << "Error: Please specify a file to download, not a directory" << std::endl;
        return false;
    }

    QString fileName = QFileInfo(path).fileName();
    currentLocalDir = "downloads";
    QDir(".").mkpath(currentLocalDir);
    
    QFile *file = new QFile(currentLocalDir + "/" + fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable(file->fileName()) << ": "
                  << qPrintable(file->errorString()) << std::endl;
        delete file;
        return false;
    }
    
    openedFiles.append(file);
    QNetworkRequest request(url);
    manager.get(request);

    return true;
}

void Spider::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error: " << qPrintable(reply->errorString()) << std::endl;
    } else {
        if (!openedFiles.isEmpty()) {
            QFile *file = openedFiles.first();
            file->write(reply->readAll());
            file->close();
            std::cout << "Downloaded to "
                      << qPrintable(QDir::toNativeSeparators(
                                    QFileInfo(file->fileName()).absoluteFilePath()))
                      << std::endl;
        }
    }

    qDeleteAll(openedFiles);
    openedFiles.clear();
    reply->deleteLater();
    
    emit done();
}

void Spider::processNextDirectory()
{
    // This function is no longer used in the simplified version
    emit done();
}
