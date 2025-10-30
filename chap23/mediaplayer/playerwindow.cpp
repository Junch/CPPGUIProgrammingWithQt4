#include <QtWidgets>

#ifdef Q_OS_WIN
#include <QAxWidget>
#else
#include <QMediaPlayer>
#include <QVideoWidget>
#endif

#include "playerwindow.h"

PlayerWindow::PlayerWindow()
{
#ifdef Q_OS_WIN
    wmp = new QAxWidget;
    wmp->setControl("{22D6F312-B0F6-11D0-94AB-0080C74C7E95}");
    wmp->setProperty("ShowControls", false);
    wmp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(wmp, SIGNAL(PlayStateChange(int, int)),
            this, SLOT(onPlayStateChange(int, int)));
    connect(wmp, SIGNAL(ReadyStateChange(ReadyStateConstants)),
            this, SLOT(onReadyStateChange(ReadyStateConstants)));
    connect(wmp, SIGNAL(PositionChange(double, double)),
            this, SLOT(onPositionChange(double, double)));
#else
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);
    videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    connect(player, &QMediaPlayer::stateChanged, this, &PlayerWindow::onStateChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &PlayerWindow::onDurationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &PlayerWindow::onPositionChanged);
#endif

    openButton = new QToolButton;
    openButton->setText(tr("&Open..."));
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    playPauseButton = new QToolButton;
    playPauseButton->setText(tr("&Play"));
    playPauseButton->setEnabled(false);
#ifdef Q_OS_WIN
    connect(playPauseButton, SIGNAL(clicked()), wmp, SLOT(Play()));
#else
    connect(playPauseButton, SIGNAL(clicked()), this, SLOT(play()));
#endif

    stopButton = new QToolButton;
    stopButton->setText(tr("&Stop"));
    stopButton->setEnabled(false);
#ifdef Q_OS_WIN
    connect(stopButton, SIGNAL(clicked()), wmp, SLOT(Stop()));
#else
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
#endif

    seekSlider = new QSlider(Qt::Horizontal);
    seekSlider->setEnabled(false);
    connect(seekSlider, SIGNAL(valueChanged(int)),
            this, SLOT(sliderValueChanged(int)));
#ifdef Q_OS_WIN
    connect(seekSlider, SIGNAL(sliderPressed()),
            wmp, SLOT(Pause()));
#else
    connect(seekSlider, SIGNAL(sliderPressed()),
            this, SLOT(pause()));
#endif

    fileFilters = tr("Video files (*.mpg *.mpeg *.avi *.wmv *.mp4)\n"
                     "Audio files (*.mp3 *.wav)");
    updateTimer = 0;

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(playPauseButton);
    buttonLayout->addWidget(stopButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
#ifdef Q_OS_WIN
    mainLayout->addWidget(wmp);
#else
    mainLayout->addWidget(videoWidget);
#endif
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(seekSlider);
    setLayout(mainLayout);

    setWindowTitle(tr("Media Player"));
    setMouseTracking(true);
}

void PlayerWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == updateTimer) {
#ifdef Q_OS_WIN
        double curPos = wmp->property("CurrentPosition").toDouble();
        onPositionChange(-1, curPos);
#endif
    } else {
        QWidget::timerEvent(event);
    }
}

#ifdef Q_OS_WIN
void PlayerWindow::onPlayStateChange(int, int newState)
{
    playPauseButton->disconnect(wmp);

    switch (newState) {
    case Stopped:
        if (updateTimer) {
            killTimer(updateTimer);
            updateTimer = 0;
        }
        // fall through
    case Paused:
        connect(playPauseButton, SIGNAL(clicked()), wmp, SLOT(Play()));
        stopButton->setEnabled(false);
        playPauseButton->setText(tr("&Play"));
        break;
    case Playing:
        if (!updateTimer)
            updateTimer = startTimer(100);
        connect(playPauseButton, SIGNAL(clicked()),
                wmp, SLOT(Pause()));
        stopButton->setEnabled(true);
        playPauseButton->setText(tr("&Pause"));
    }
}

void PlayerWindow::onReadyStateChange(ReadyStateConstants ready)
{
    if (ready == Complete) {
        double duration = 60 * wmp->property("Duration").toDouble();
        seekSlider->setMinimum(0);
        seekSlider->setMaximum(int(duration));
        seekSlider->setEnabled(true);
        playPauseButton->setEnabled(true);
    }
}

void PlayerWindow::onPositionChange(double, double newPos)
{
    seekSlider->blockSignals(true);
    seekSlider->setValue(int(newPos * 60));
    seekSlider->blockSignals(false);
}

void PlayerWindow::sliderValueChanged(int newValue)
{
    seekSlider->blockSignals(true);
    wmp->setProperty("CurrentPosition", double(newValue) / 60);
    seekSlider->blockSignals(false);
}

void PlayerWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Select File"), ".", fileFilters);
    if (!fileName.isEmpty())
        wmp->setProperty("FileName",
                         QDir::toNativeSeparators(fileName));
}
#else
void PlayerWindow::onStateChanged(int state)
{
    switch (state) {
    case QMediaPlayer::StoppedState:
        if (updateTimer) {
            killTimer(updateTimer);
            updateTimer = 0;
        }
        stopButton->setEnabled(false);
        playPauseButton->setText(tr("&Play"));
        playPauseButton->disconnect();
        connect(playPauseButton, SIGNAL(clicked()), this, SLOT(play()));
        break;
    case QMediaPlayer::PausedState:
        stopButton->setEnabled(false);
        playPauseButton->setText(tr("&Play"));
        playPauseButton->disconnect();
        connect(playPauseButton, SIGNAL(clicked()), this, SLOT(play()));
        break;
    case QMediaPlayer::PlayingState:
        if (!updateTimer)
            updateTimer = startTimer(100);
        stopButton->setEnabled(true);
        playPauseButton->setText(tr("&Pause"));
        playPauseButton->disconnect();
        connect(playPauseButton, SIGNAL(clicked()), this, SLOT(pause()));
        break;
    }
}

void PlayerWindow::onDurationChanged(qint64 duration)
{
    seekSlider->setMinimum(0);
    seekSlider->setMaximum(duration);
    seekSlider->setEnabled(true);
    playPauseButton->setEnabled(true);
}

void PlayerWindow::onPositionChanged(qint64 position)
{
    seekSlider->blockSignals(true);
    seekSlider->setValue(position);
    seekSlider->blockSignals(false);
}

void PlayerWindow::sliderValueChanged(int newValue)
{
    player->setPosition(newValue);
}

void PlayerWindow::play()
{
    player->play();
}

void PlayerWindow::pause()
{
    player->pause();
}

void PlayerWindow::stop()
{
    player->stop();
}

void PlayerWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Select File"), ".", fileFilters);
    if (!fileName.isEmpty())
        player->setMedia(QUrl::fromLocalFile(fileName));
}
#endif
