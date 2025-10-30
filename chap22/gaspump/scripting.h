#ifndef SCRIPTING_H
#define SCRIPTING_H

#include <QDate>
#include <QObject>
#include <QTime>

class QJSValue;
class PumpFilter;

bool runScript(const QString &fileName, const QStringList &args);

QJSValue pumpFilterConstructor(const QJSValue &value);

class PumpFilterPrototype : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate fromDate READ fromDate WRITE setFromDate)
    Q_PROPERTY(QDate toDate READ toDate WRITE setToDate)
    Q_PROPERTY(QTime fromTime READ fromTime WRITE setFromTime)
    Q_PROPERTY(QTime toTime READ toTime WRITE setToTime)
    Q_PROPERTY(QString pump READ pump WRITE setPump)
    Q_PROPERTY(QString company READ company WRITE setCompany)
    Q_PROPERTY(QString user READ user WRITE setUser)
    Q_PROPERTY(double fromQuantity READ fromQuantity
               WRITE setFromQuantity)
    Q_PROPERTY(double toQuantity READ toQuantity WRITE setToQuantity)
    Q_PROPERTY(QString status READ status WRITE setStatus)

public:
    PumpFilterPrototype(QObject *parent = 0);

    void setFilter(PumpFilter *filter) { m_filter = filter; }
    PumpFilter *filter() const { return m_filter; }

    void setFromDate(const QDate &date);
    QDate fromDate() const;
    void setToDate(const QDate &date);
    QDate toDate() const;

    void setFromTime(const QTime &time);
    QTime fromTime() const;
    void setToTime(const QTime &time);
    QTime toTime() const;

    void setPump(const QString &pump);
    QString pump() const;
    void setCompany(const QString &company);
    QString company() const;
    void setUser(const QString &user);
    QString user() const;

    void setFromQuantity(double quantity);
    double fromQuantity() const;
    void setToQuantity(double quantity);
    double toQuantity() const;

    void setStatus(const QString &status);
    QString status() const;

private:
    PumpFilter *m_filter;
    PumpFilter *wrappedFilter() const;
};

#endif
