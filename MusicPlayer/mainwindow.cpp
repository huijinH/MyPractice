#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player_(nullptr)
    , playlist_(nullptr)
    , durationTime_("")
    , positionTime_("")
{
    ui->setupUi(this);
    player_ = new QMediaPlayer(this);
    playlist_ = new QMediaPlaylist(this);
    playlist_->setPlaybackMode(QMediaPlaylist::Loop);
    player_->setPlaylist(playlist_);

    connect(player_, &QMediaPlayer::stateChanged, this, [=](QMediaPlayer::State state){
        ui->playBtn->setEnabled(!(state == QMediaPlayer::PlayingState));
        ui->pauseBtn->setEnabled(state == QMediaPlayer::PlayingState);
        ui->stopBtn->setEnabled(state == QMediaPlayer::PlayingState);
    });
    connect(player_, &QMediaPlayer::positionChanged, this, [=](qint64 position){
        if (ui->positionSlider->isSliderDown()) {
            return;  // 处于手动调节，返回
        }
        ui->positionSlider->setSliderPosition(position);
        int secs = position / 1000;
        int mins = secs / 60;
        secs = secs % 60;
        positionTime_ = QString::asprintf("%d:%d", mins, secs);
        ui->positionLabel->setText(positionTime_ + "/" + durationTime_);
    });
    connect(player_, &QMediaPlayer::durationChanged, this, [=](qint64 duration){
        ui->positionSlider->setMaximum(duration);
        int secs = duration / 1000;
        int mins = secs / 60;
        secs = secs % 60;
        durationTime_ = QString::asprintf("%d:%d", mins, secs);
        ui->positionLabel->setText(positionTime_ + "/" + durationTime_);
    });
    connect(playlist_, &QMediaPlaylist::currentIndexChanged, this, [=](int idx){
        ui->listWidget->setCurrentRow(idx);
        QListWidgetItem* item = ui->listWidget->currentItem();
        if (item) {
            ui->nameLabel->setText(item->text());
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

