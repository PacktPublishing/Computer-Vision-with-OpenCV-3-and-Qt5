#include "pixelcounter.h"

PixelCounter::PixelCounter(QObject *parent) : QObject(parent)
{

}

int PixelCounter::countPixels(QString fname)
{
    cv::Mat image = cv::imread(fname.toStdString());
    if(image.empty())
    {
        return 0;
    }
    else
    {
        return image.rows * image.cols;
    }
}
