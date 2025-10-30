#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStringList>

class QFile;

class Spider : public QObject
{
    Q_OBJECT

public:
    Spider(QObject *parent = 0);

    bool getDirectory(const QUrl &url);

signals:
    void done();

private slots:
    void replyFinished(QNetworkReply *reply);

private:
    void processNextDirectory();

    QNetworkAccessManager manager;
    QList<QFile *> openedFiles;
    QString currentDir;
    QString currentLocalDir;
    QStringList pendingDirs;
};

#endif
