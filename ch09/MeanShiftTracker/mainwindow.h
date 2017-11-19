#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QDebug>
#include "qcvmeanshiftthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onRubberBandChanged(QRect rect, QPointF, QPointF);
    void onNewFrame(QPixmap newFrm);

private:
    Ui::MainWindow *ui;

    QCvMeanShiftThread *meanshift;
    QGraphicsPixmapItem pixmap;

};

#endif // MAINWINDOW_H
