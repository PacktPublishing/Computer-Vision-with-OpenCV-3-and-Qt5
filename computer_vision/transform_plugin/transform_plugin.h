#ifndef TRANSFORM_PLUGIN_H
#define TRANSFORM_PLUGIN_H

#include "transform_plugin_global.h"
#include "cvplugininterface.h"
#include <QObject>
#include <QtMath>

namespace Ui {
    class PluginGui;
}

class TRANSFORM_PLUGINSHARED_EXPORT Transform_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Transform_Plugin();
    ~Transform_Plugin();

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


    void on_resizeHalfRadio_toggled(bool checked);

    void on_resizeDoubleRadio_toggled(bool checked);

    void on_remapRadio_toggled(bool checked);

    void on_affineRadio_toggled(bool checked);

    void on_perspectiveRadio_toggled(bool checked);

    void on_borderTypeCombo_currentIndexChanged(int index);

    void on_interpolationCombo_currentIndexChanged(int index);

private:
    Ui::PluginGui *ui;

};

#endif // TRANSFORM_PLUGIN_H
