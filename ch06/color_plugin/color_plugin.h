#ifndef COLOR_PLUGIN_H
#define COLOR_PLUGIN_H

#include "color_plugin_global.h"
#include "cvplugininterface.h"

namespace Ui {
    class PluginGui;
}

class COLOR_PLUGINSHARED_EXPORT Color_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Color_Plugin();
    ~Color_Plugin();

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
    void on_colorMapCombo_currentIndexChanged(int index);

private:
    Ui::PluginGui *ui;

};

#endif // COLOR_PLUGIN_H
