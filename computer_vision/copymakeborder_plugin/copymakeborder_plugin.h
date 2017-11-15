#ifndef COPYMAKEBORDER_PLUGIN_H
#define COPYMAKEBORDER_PLUGIN_H

#include "copymakeborder_plugin_global.h"
#include "cvplugininterface.h"

namespace Ui {
    class PluginGui;
}

class COPYMAKEBORDER_PLUGINSHARED_EXPORT CopyMakeBorder_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    CopyMakeBorder_Plugin();
    ~CopyMakeBorder_Plugin();

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
    void on_borderTypeComboBox_currentIndexChanged(int index);

private:
    Ui::PluginGui *ui;

};

#endif // COPYMAKEBORDER_PLUGIN_H
