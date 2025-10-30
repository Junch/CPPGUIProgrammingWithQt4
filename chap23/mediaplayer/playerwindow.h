#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QWidget>

#ifdef Q_OS_WIN
class QAxWidget;
#else
class QMediaPlayer;
class QVideoWidget;
#endif

class QSlider;
class QToolButton;

class PlayerWindow : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ReadyStateConstants)

public:
    enum PlayStateConstants { Stopped = 0, Paused = 1, Playing = 2 };
    enum ReadyStateConstants { Uninitialized = 0, Loading = 1,
                               Interactive = 3, Complete = 4 };

    PlayerWindow();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
#ifdef Q_OS_WIN
    void onPlayStateChange(int oldState, int newState);
    void onReadyStateChange(ReadyStateConstants readyState);
    void onPositionChange(double oldPos, double newPos);
#else
    void onStateChanged(int state);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void play();
    void pause();
    void stop();
#endif
    void sliderValueChanged(int newValue);
    void openFile();

private:
#ifdef Q_OS_WIN
    QAxWidget *wmp;
#else
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
#endif
    QToolButton *openButton;
    QToolButton *playPauseButton;
    QToolButton *stopButton;
    QSlider *seekSlider;
    QString fileFilters;
    int updateTimer;
};

#endif
