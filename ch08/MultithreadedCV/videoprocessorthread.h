#ifndef VIDEOPROCESSORTHREAD_H
#define VIDEOPROCESSORTHREAD_H

#include <QObject>
#include <QThread>
#include <QPixmap>
#include "opencv2/opencv.hpp"

class VideoProcessorThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoProcessorThread(QObject *parent = nullptr);

signals:
    void inDisplay(QPixmap pixmap);
    void outDisplay(QPixmap pixmap);

public slots:

private:
    void run() override;

};

#endif // VIDEOPROCESSORTHREAD_H
