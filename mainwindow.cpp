#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    player = new QMediaPlayer(this);
    Vw = new QVideoWidget(this);
    player->setVideoOutput(Vw);
    this->setCentralWidget(Vw);

    slider= new QSlider(this);
    bar= new QProgressBar(this);

    slider->setOrientation(Qt::Horizontal);


    ui->statusbar->addPermanentWidget(slider);
    ui->statusbar->addPermanentWidget(bar);

    connect(player, &QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player, &QMediaPlayer::durationChanged,slider,&QSlider::setValue);
    connect(slider, &QSlider::sliderMoved,player, &QMediaPlayer::setPosition);


    connect(player, &QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);
    connect(player, &QMediaPlayer::durationChanged,bar,&QProgressBar::setValue);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOtworz_triggered()
{
    QString filename= QFileDialog::getOpenFileName(this,"Otworz plik","","Plik Video ( *.*)");
    on_actionstop_triggered();

    player->setMedia(QUrl::fromLocalFile(filename));

    on_actiongraj_triggered();
}

void MainWindow::on_actiongraj_triggered()
{
    player ->play();
    ui->statusbar->showMessage("Odtwarzanie");
}

void MainWindow::on_actionpauza_triggered()
{
    player ->pause();
    ui->statusbar->showMessage("Wstrzymano");
}

void MainWindow::on_actionstop_triggered()
{
    player ->stop();
    ui->statusbar->showMessage("Zatrzymano");
}
