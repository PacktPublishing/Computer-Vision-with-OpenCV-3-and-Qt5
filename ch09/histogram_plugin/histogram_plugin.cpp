#include "histogram_plugin.h"

#include "ui_plugin.h"

#include <QDebug>

Histogram_Plugin::Histogram_Plugin()
{
    // Insert initialization codes here ...
}

Histogram_Plugin::~Histogram_Plugin()
{
    // Insert cleanup codes here ...
}

QString Histogram_Plugin::title()
{
    return this->metaObject()->className();
}

QString Histogram_Plugin::version()
{
    return "1.0.0";
}

QString Histogram_Plugin::description()
{
    return "Histogram plugin";
}

QString Histogram_Plugin::help()
{
    return "A plugin for playing around with histograms.";
}

void Histogram_Plugin::setupUi(QWidget *parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(parent);

    connect(ui->grayRadio, SIGNAL(toggled(bool)), this, SLOT(on_grayRadio_toggled(bool)));
    connect(ui->rgbRadio, SIGNAL(toggled(bool)), this, SLOT(on_rgbRadio_toggled(bool)));
    connect(ui->hsvRadio, SIGNAL(toggled(bool)), this, SLOT(on_hsvRadio_toggled(bool)));
    connect(ui->binsSpin, SIGNAL(valueChanged(int)), this, SLOT(on_binsSpin_valueChanged(int)));
    connect(ui->widthSpin, SIGNAL(valueChanged(int)), this, SLOT(on_widthSpin_valueChanged(int)));
    connect(ui->heightSpin, SIGNAL(valueChanged(int)), this, SLOT(on_heightSpin_valueChanged(int)));
    connect(ui->uniformCheck, SIGNAL(toggled(bool)), this, SLOT(on_uniformCheck_toggled(bool)));
}

void Histogram_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    if(ui->grayRadio->isChecked())
    {
        grayScaleHist(inputImage, outputImage);
    }
    else if(ui->rgbRadio->isChecked())
    {
        rgbHist(inputImage, outputImage);
    }
    else if(ui->hsvRadio->isChecked())
    {
        hsvHist(inputImage, outputImage);
    }
}

void Histogram_Plugin::on_grayRadio_toggled(bool)
{
    emit updateNeeded();
}

void Histogram_Plugin::on_rgbRadio_toggled(bool)
{
    emit updateNeeded();
}

void Histogram_Plugin::on_hsvRadio_toggled(bool)
{
    emit updateNeeded();
}

void Histogram_Plugin::on_binsSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Histogram_Plugin::grayScaleHist(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    using namespace cv;
    Mat grayImg;
    cvtColor(inputImage, grayImg, CV_BGR2GRAY);


    int channels[] = {0}; // only the first channel
    int histSize[] = {ui->binsSpin->value()}; // number of bins

    float rangeGray[] = {0,255}; // range of grayscale
    const float* ranges[] = { rangeGray };

    Mat histogram;

    calcHist(&grayImg,
             1, // number of images
             channels,
             Mat(), // no masks, an empty Mat
             histogram,
             1, // dimensionality
             histSize,
             ranges);

    /*
    for(int i=0; i<histogram.rows; i++)
    {
        if(i < 40) // threshold
            histogram.at<float>(i,0) = 255;
        else
            histogram.at<float>(i,0) = 0;
    }

    Mat backprojection;
    calcBackProject(&grayImg,
                    1,
                    channels,
                    histogram,
                    backprojection,
                    ranges);
    */

    double maxVal = 0;
    minMaxLoc(histogram,
              Q_NULLPTR, // don't need min
              &maxVal,
              Q_NULLPTR, // don't need index min
              Q_NULLPTR // don't need index max
              );

    outputImage.create(ui->heightSpin->value(), // any image width
                       ui->widthSpin->value(), // any image height
                       CV_8UC(3));

    outputImage = Scalar::all(128); // empty grayish image

    //imshow("grayImg", grayImg);

    Point p1(0,0), p2(0,0);
    for(int i=0; i<ui->binsSpin->value(); i++)
    {
        float value = histogram.at<float>(i,0);
        value = maxVal - value; // invert
        value = value / maxVal * outputImage.rows;
        line(outputImage,
             p1,
             Point(p1.x,value),
             Scalar(0,0,0));
        p1.y = p2.y = value;
        p2.x = float(i+1) * float(outputImage.cols) / float(ui->binsSpin->value());
        line(outputImage,
             p1, p2,
             Scalar(0,0,0));
        p1.x = p2.x;
    }
}

void Histogram_Plugin::rgbHist(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    using namespace cv;
    using namespace std;

    int channels[] = {0};
    int histSize[] = {ui->binsSpin->value()}; // number of bins

    float range[] = {0,255}; // range of colors
    const float* ranges[] = { range };

    Mat histograms[3];

    vector<Mat> planes;
    split(inputImage, planes);

    double maxVal[3] = {0,0,0};

    for(int i=0; i<3; i++)
    {
        calcHist(&planes[i],
                 1, // number of images
                 channels,
                 Mat(), // no masks, an empty Mat
                 histograms[i],
                 1, // dimensionality
                 histSize,
                 ranges);

        minMaxLoc(histograms[i],
                  Q_NULLPTR, // don't need min
                  &maxVal[i],
                  Q_NULLPTR, // don't need index min
                  Q_NULLPTR // don't need index max
                  );
    }

    outputImage.create(ui->heightSpin->value(), // any image width
                       ui->widthSpin->value(), // any image height
                       CV_8UC(3));

    outputImage = Scalar::all(0); // empty black image

    Point p1[3], p2[3];
    for(int i=0; i<ui->binsSpin->value(); i++)
    {
        for(int j=0; j<3; j++)
        {
            float value = histograms[j].at<float>(i,0);
            value = maxVal[j] - value; // invert
            value = value / maxVal[j] * outputImage.rows;
            line(outputImage,
                 p1[j],
                 Point(p1[j].x,value),
                 Scalar(j==0 ? 255:0,
                        j==1 ? 255:0,
                        j==2 ? 255:0),
                 2);
            p1[j].y = p2[j].y = value;
            p2[j].x = float(i+1) * float(outputImage.cols) / float(ui->binsSpin->value());
            line(outputImage,
                 p1[j], p2[j],
                 Scalar(j==0 ? 255:0,
                        j==1 ? 255:0,
                        j==2 ? 255:0),
                 2);
            p1[j].x = p2[j].x;
        }
    }
}

void Histogram_Plugin::hsvHist(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    using namespace cv;
    Mat hsvImg;
    cvtColor(inputImage, hsvImg, CV_BGR2HSV);

    int channels[] = {0}; // only the first channel
    int histSize[] = {ui->binsSpin->value()}; // number of bins

    float rangeHue[] = {0,179}; // range of Hue channel
    const float* ranges[] = { rangeHue };

    Mat histogram;

    calcHist(&hsvImg,
             1, // number of images
             channels,
             Mat(), // no masks, an empty Mat
             histogram,
             1, // dimensionality
             histSize,
             ranges);

    double maxVal = 0;
    minMaxLoc(histogram,
              Q_NULLPTR, // don't need min
              &maxVal,
              Q_NULLPTR, // don't need index min
              Q_NULLPTR // don't need index max
              );

    outputImage.create(ui->heightSpin->value(), // any image width
                       ui->widthSpin->value(), // any image height
                       CV_8UC(3));

    outputImage = Scalar::all(0); // empty black image

    Mat colors(1, ui->binsSpin->value(), CV_8UC3);
    for(int i=0; i<ui->binsSpin->value(); i++)
    {
        colors.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>((i+1)*180.0/ui->binsSpin->value()), 255, 255);
    }
    cvtColor(colors, colors, COLOR_HSV2BGR);

    Point p1(0,0), p2(0,outputImage.rows-1);
    for(int i=0; i<ui->binsSpin->value(); i++)
    {
        float value = histogram.at<float>(i,0);
        value = maxVal - value; // invert
        value = value / maxVal * outputImage.rows; // scale
        p1.y = value;
        p2.x = float(i+1) * float(outputImage.cols) / float(ui->binsSpin->value());
        rectangle(outputImage,
                  p1,
                  p2,
                  Scalar(colors.at<Vec3b>(i)),
                  CV_FILLED);
        p1.x = p2.x;
    }

}

void Histogram_Plugin::on_widthSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Histogram_Plugin::on_heightSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Histogram_Plugin::on_uniformCheck_toggled(bool)
{
    emit updateNeeded();
}
