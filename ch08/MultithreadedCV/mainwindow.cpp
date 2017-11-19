#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    processor = new VideoProcessor();

    processor->moveToThread(new QThread(this));

    connect(processor->thread(),
            SIGNAL(started()),
            processor,
            SLOT(startVideo()));

    connect(processor->thread(),
            SIGNAL(finished()),
            processor,
            SLOT(deleteLater()));

    connect(processor,
            SIGNAL(inDisplay(QPixmap)),
            ui->inVideo,
            SLOT(setPixmap(QPixmap)));

    connect(processor,
            SIGNAL(outDisplay(QPixmap)),
            ui->outVideo,
            SLOT(setPixmap(QPixmap)));

    processor->thread()->start();
}

MainWindow::~MainWindow()
{
    processor->stopVideo();
    processor->thread()->quit();
    processor->thread()->wait();

    delete ui;
}
