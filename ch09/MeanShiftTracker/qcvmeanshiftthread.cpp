#include "qcvmeanshiftthread.h"

QCvMeanShiftThread::QCvMeanShiftThread(QObject *parent) : QThread(parent)
{

}

void QCvMeanShiftThread::run()
{
    using namespace cv;

    VideoCapture video;
    Mat hist;
    video.open(0);

    while(video.isOpened() && !this->isInterruptionRequested())
    {
        //this->msleep(100);

        Mat frame;
        video >> frame;
        if(frame.empty())
            break; // or continue if this should be tolerated

        if(trackRect.size().area() > 0)
        {
            QMutexLocker locker(&rectMutex);

            Mat hsv, hue;
            cvtColor(frame, hsv, CV_BGR2HSV);
            hue.create(hsv.size(), hsv.depth());
            float hrange[] = {0, 179};
            const float* ranges[] = {hrange};
            int bins[] = {24};
            int fromto[] = {0, 0};
            mixChannels(&hsv, 1, &hue, 1, fromto, 1);

            if(updateHistogram)
            {
                Mat roi(hue, trackRect);
                calcHist(&roi, 1, 0, Mat(), hist, 1, bins, ranges);

                normalize(hist,
                          hist,
                          0,
                          255,
                          NORM_MINMAX);

                updateHistogram = false;
            }

            Mat backProj;
            calcBackProject(&hue,
                            1,
                            0,
                            hist,
                            backProj,
                            ranges);

            TermCriteria criteria;
            criteria.maxCount = 5;
            criteria.epsilon = 3;
            criteria.type = TermCriteria::EPS;
            RotatedRect rotRec = CamShift(backProj, trackRect, criteria);

            rectangle(frame, trackRect, Scalar(0,0,255), 2);
            ellipse(frame, rotRec, Scalar(0,255,0), 2);

//            cvtColor(backProj, backProj, CV_GRAY2BGR);
//            frame = backProj;
//            rectangle(frame, trackRect, Scalar(0,0,255), 2);

        }

        emit newFrame(
                    QPixmap::fromImage(
                        QImage(
                            frame.data,
                            frame.cols,
                            frame.rows,
                            frame.step,
                            QImage::Format_RGB888)
                        .rgbSwapped()));

    }
}

void QCvMeanShiftThread::setTrackRect(QRect rect)
{
    QMutexLocker locker(&rectMutex);
    if((rect.width()>2) && (rect.height()>2))
    {
        trackRect.x = rect.left();
        trackRect.y = rect.top();
        trackRect.width = rect.width();
        trackRect.height = rect.height();
        updateHistogram = true;
    }
}
