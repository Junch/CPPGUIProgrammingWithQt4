#include <QtWidgets>

#include "axbouncer.h"

#ifdef Q_OS_WIN
#include "objectsafetyimpl.h"
#endif

AxBouncer::AxBouncer(QWidget *parent)
    : QWidget(parent)
{
    ballColor = Qt::blue;
    ballSpeed = Normal;
    ballRadius = 15;
    myTimerId = 0;
    x = 20;
    delta = 2;
}

void AxBouncer::setColor(const QColor &newColor)
{
#ifdef Q_OS_WIN
    if (newColor != ballColor && requestPropertyChange("color")) {
        ballColor = newColor;
        update();
        propertyChanged("color");
    }
#else
    if (newColor != ballColor) {
        ballColor = newColor;
        update();
    }
#endif
}

void AxBouncer::setSpeed(SpeedValue newSpeed)
{
#ifdef Q_OS_WIN
    if (newSpeed != ballSpeed && requestPropertyChange("speed")) {
        ballSpeed = newSpeed;

        if (isRunning()) {
            killTimer(myTimerId);
            myTimerId = startTimer(intervalInMilliseconds());
        }
        propertyChanged("speed");
    }
#else
    if (newSpeed != ballSpeed) {
        ballSpeed = newSpeed;

        if (isRunning()) {
            killTimer(myTimerId);
            myTimerId = startTimer(intervalInMilliseconds());
        }
    }
#endif
}

int AxBouncer::intervalInMilliseconds() const
{
    switch (ballSpeed) {
    case Slow:
        return 50;
    case Fast:
        return 10;
    default:
        return 30;
    }
}

void AxBouncer::setRadius(int newRadius)
{
#ifdef Q_OS_WIN
    if (newRadius != ballRadius && requestPropertyChange("radius")) {
        ballRadius = newRadius;
        update();
        updateGeometry();
        propertyChanged("radius");
    }
#else
    if (newRadius != ballRadius) {
        ballRadius = newRadius;
        update();
        updateGeometry();
    }
#endif
}

QSize AxBouncer::sizeHint() const
{
    return QSize(250, 5 * radius());
}

#ifdef Q_OS_WIN
QAxAggregated *AxBouncer::createAggregate()
{
    return new ObjectSafetyImpl;
}
#endif

void AxBouncer::start()
{
#ifdef Q_OS_WIN
    if (!isRunning() && requestPropertyChange("running")) {
        myTimerId = startTimer(intervalInMilliseconds());
        propertyChanged("running");
    }
#else
    if (!isRunning()) {
        myTimerId = startTimer(intervalInMilliseconds());
    }
#endif
}

void AxBouncer::stop()
{
#ifdef Q_OS_WIN
    if (isRunning() && requestPropertyChange("running")) {
        killTimer(myTimerId);
        myTimerId = 0;
        propertyChanged("running");
    }
#else
    if (isRunning()) {
        killTimer(myTimerId);
        myTimerId = 0;
    }
#endif
}

void AxBouncer::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setPen(ballColor);
    painter.setBrush(ballColor);
    painter.drawEllipse(x - radius(), height() / 2 - radius(),
                        2 * radius(), 2 * radius());
}

void AxBouncer::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == myTimerId) {
        if ((delta > 0 && x >= width() - radius())
                || (delta < 0 && x <= radius())) {
            delta = -delta;
            emit bouncing();
        }
        x += delta;
        update();
    } else {
        QWidget::timerEvent(event);
    }
}
