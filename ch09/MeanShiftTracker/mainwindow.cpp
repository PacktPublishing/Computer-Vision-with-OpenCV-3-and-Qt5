#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    connect(ui->graphicsView, SIGNAL(rubberBandChanged(QRect,QPointF,QPointF)),
            this, SLOT(onRubberBandChanged(QRect,QPointF,QPointF)));

    meanshift = new QCvMeanShiftThread();
    connect(meanshift, SIGNAL(newFrame(QPixmap)), this, SLOT(onNewFrame(QPixmap)));
    meanshift->start();

    ui->graphicsView->scene()->addItem(&pixmap);
}

MainWindow::~MainWindow()
{
    meanshift->requestInterruption();
    meanshift->wait();
    delete meanshift;

    delete ui;
}

void MainWindow::onRubberBandChanged(QRect rect, QPointF, QPointF)
{
    meanshift->setTrackRect(rect);
}

void MainWindow::onNewFrame(QPixmap newFrm)
{
    pixmap.setPixmap(newFrm);
}
