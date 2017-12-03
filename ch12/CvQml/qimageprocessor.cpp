#include "qimageprocessor.h"

QImageProcessor::QImageProcessor(QObject *parent) : QObject(parent)
{

}

void QImageProcessor::processImage(const QString &path)
{
    using namespace cv;
    Mat imageM = imread(path.toStdString());
    if(!imageM.empty())
    {
        bitwise_not(imageM, imageM); // or any OpenCV code
        QImage imageQ(imageM.data,
                      imageM.cols,
                      imageM.rows,
                      imageM.step,
                      QImage::Format_RGB888);
        emit imageProcessed(imageQ.rgbSwapped());
    }
    else
    {
        qDebug() << path << "does not exist!";
    }
}
