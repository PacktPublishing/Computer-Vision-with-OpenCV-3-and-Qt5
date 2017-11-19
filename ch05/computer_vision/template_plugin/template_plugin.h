#ifndef TEMPLATE_PLUGIN_H
#define TEMPLATE_PLUGIN_H

#include "template_plugin_global.h"
#include "cvplugininterface.h"

namespace Ui {
    class PluginGui;
}

class TEMPLATE_PLUGINSHARED_EXPORT Template_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Template_Plugin();
    ~Template_Plugin();

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

private:
    Ui::PluginGui *ui;

};

#endif // TEMPLATE_PLUGIN_H
