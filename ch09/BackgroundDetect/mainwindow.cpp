#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    backDetect = new QCvBackgroundDetect();
    connect(backDetect, SIGNAL(newFrame(QPixmap)), this, SLOT(onNewFrame(QPixmap)));
    backDetect->start();

    ui->graphicsView->scene()->addItem(&pixmap);
}

MainWindow::~MainWindow()
{
    backDetect->requestInterruption();
    backDetect->wait();
    delete backDetect;

    delete ui;
}

void MainWindow::onNewFrame(QPixmap newFrm)
{
    pixmap.setPixmap(newFrm);
}
