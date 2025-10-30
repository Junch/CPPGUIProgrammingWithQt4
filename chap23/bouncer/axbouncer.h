#ifndef AXBOUNCER_H
#define AXBOUNCER_H

#include <QWidget>

#ifdef Q_OS_WIN
#include <QAxBindable>
#endif

#ifdef Q_OS_WIN
class AxBouncer : public QWidget, public QAxBindable
#else
class AxBouncer : public QWidget
#endif
{
    Q_OBJECT
    Q_ENUMS(SpeedValue)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(SpeedValue speed READ speed WRITE setSpeed)
    Q_PROPERTY(int radius READ radius WRITE setRadius)
    Q_PROPERTY(bool running READ isRunning)

public:
    enum SpeedValue { Slow, Normal, Fast };

    AxBouncer(QWidget *parent = 0);

    void setSpeed(SpeedValue newSpeed);
    SpeedValue speed() const { return ballSpeed; }
    void setRadius(int newRadius);
    int radius() const { return ballRadius; }
    void setColor(const QColor &newColor);
    QColor color() const { return ballColor; }
    bool isRunning() const { return myTimerId != 0; }
    QSize sizeHint() const;
#ifdef Q_OS_WIN
    QAxAggregated *createAggregate();
#endif

public slots:
    void start();
    void stop();

signals:
    void bouncing();

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    int intervalInMilliseconds() const;

    QColor ballColor;
    SpeedValue ballSpeed;
    int ballRadius;
    int myTimerId;
    int x;
    int delta;
};

#endif
