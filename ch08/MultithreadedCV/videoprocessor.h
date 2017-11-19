#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <QMutex>
#include <QReadWriteLock>
#include <QSemaphore>
#include <QWaitCondition>
#include "opencv2/opencv.hpp"

class VideoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent = nullptr);

signals:
    void inDisplay(QPixmap pixmap);
    void outDisplay(QPixmap pixmap);

public slots:
    void startVideo();
    void stopVideo();

private:
    bool stopped;

};

#endif // VIDEOPROCESSOR_H
