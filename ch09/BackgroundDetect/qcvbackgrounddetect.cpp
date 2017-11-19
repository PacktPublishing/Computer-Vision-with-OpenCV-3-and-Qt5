#include "qcvbackgrounddetect.h"

QCvBackgroundDetect::QCvBackgroundDetect(QObject *parent) : QThread(parent)
{

}

void QCvBackgroundDetect::run()
{
    using namespace cv;

    Mat foreground;
    VideoCapture video;
    video.open("d:/back-test.mp4");

    //Ptr<BackgroundSubtractorMOG2> subtractor = createBackgroundSubtractorMOG2();
    Ptr<BackgroundSubtractorKNN> subtractor = createBackgroundSubtractorKNN();

    while(video.isOpened() && !this->isInterruptionRequested())
    {
        //this->msleep(100);

        Mat frame;
        video >> frame;
        if(frame.empty())
            break; // or continue if this should be tolerated

        subtractor->apply(frame, foreground);

        Mat foregroundBgr;
        //bitwise_and(frame, foreground, foreground);
        frame.copyTo(foregroundBgr, foreground);

        emit newFrame(
                    QPixmap::fromImage(
                        QImage(
                            foregroundBgr.data,
                            foregroundBgr.cols,
                            foregroundBgr.rows,
                            foregroundBgr.step,
                            QImage::Format_RGB888)
                        .rgbSwapped()));

    }
}
