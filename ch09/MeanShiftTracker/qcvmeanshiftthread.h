#ifndef QCVMEANSHIFTTHREAD_H
#define QCVMEANSHIFTTHREAD_H

#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QMutex>
#include "opencv2/opencv.hpp"

class QCvMeanShiftThread : public QThread
{
    Q_OBJECT
public:
    explicit QCvMeanShiftThread(QObject *parent = nullptr);

    void setTrackRect(QRect rect);

signals:
    void newFrame(QPixmap pix);

public slots:

private:
    void run() override;
    cv::Rect trackRect;
    QMutex rectMutex;
    bool updateHistogram;

};

#endif // QCVMEANSHIFTTHREAD_H
