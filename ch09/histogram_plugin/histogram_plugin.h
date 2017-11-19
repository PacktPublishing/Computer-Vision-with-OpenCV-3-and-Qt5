#ifndef HISTOGRAM_PLUGIN_H
#define HISTOGRAM_PLUGIN_H

#include "histogram_plugin_global.h"
#include "cvplugininterface.h"

namespace Ui {
    class PluginGui;
}

class HISTOGRAM_PLUGIN_SHARED_EXPORT Histogram_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Histogram_Plugin();
    ~Histogram_Plugin();

    QString title();
    QString version();
    QString description();
    QString help();
    void setupUi(QWidget *parent);
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage);

signals:
    void updateNeeded();
    void errorMessage(QString msg);
    void infoMessage(QString msg);

private slots:
    void on_grayRadio_toggled(bool);

    void on_rgbRadio_toggled(bool checked);

    void on_hsvRadio_toggled(bool checked);

    void on_binsSpin_valueChanged(int arg1);

    void on_widthSpin_valueChanged(int arg1);

    void on_heightSpin_valueChanged(int arg1);

    void on_uniformCheck_toggled(bool checked);

private:
    Ui::PluginGui *ui;

    void grayScaleHist(const cv::Mat &inputImage, cv::Mat &outputImage);
    void rgbHist(const cv::Mat &inputImage, cv::Mat &outputImage);
    void hsvHist(const cv::Mat &inputImage, cv::Mat &outputImage);

};

#endif // HISTOGRAM_PLUGIN_H
