#ifndef FOURIER_PLUGIN_H
#define FOURIER_PLUGIN_H

#include "fourier_plugin_global.h"
#include "cvplugininterface.h"

namespace Ui {
    class PluginGui;
}

class FOURIER_PLUGINSHARED_EXPORT Fourier_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Fourier_Plugin();
    ~Fourier_Plugin();

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

private:
    Ui::PluginGui *ui;

};

#endif // FOURIER_PLUGIN_H
