#ifndef CVPLUGININTERFACE_H
#define CVPLUGININTERFACE_H

#include <QObject>
#include <QString>
#include "opencv2/opencv.hpp"

class CvPluginInterface
{
public:
    virtual ~CvPluginInterface() {}
    virtual QString description() = 0;
    virtual void processImage(const cv::Mat &inputImage, cv::Mat &outputImage) = 0;
};

#define CVPLUGININTERFACE_IID "com.amin.cvplugininterface"
Q_DECLARE_INTERFACE(CvPluginInterface, CVPLUGININTERFACE_IID)

#endif // CVPLUGININTERFACE_H
