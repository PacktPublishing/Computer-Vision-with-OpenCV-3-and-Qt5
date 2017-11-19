#ifndef KEYPOINT_PLUGIN_H
#define KEYPOINT_PLUGIN_H

#include "keypoint_plugin_global.h"
#include "cvplugininterface.h"

namespace Ui {
    class PluginGui;
}

class KEYPOINT_PLUGINSHARED_EXPORT Keypoint_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Keypoint_Plugin();
    ~Keypoint_Plugin();

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
    void on_toolBox_currentChanged(int index);

    void on_agastThreshSpin_valueChanged(int arg1);

    void on_agastNonmaxCheck_toggled(bool checked);

    void on_agastTypeCombo_currentIndexChanged(int index);

    void on_kazeAcceleratedCheck_toggled(bool checked);

    void on_kazeExtendCheck_toggled(bool checked);

    void on_kazeUprightCheck_toggled(bool checked);

    void on_akazeDescriptCombo_currentIndexChanged(int index);

    void on_kazeThreshSpin_valueChanged(double arg1);

    void on_kazeOctaveSpin_valueChanged(int arg1);

    void on_kazeLayerSpin_valueChanged(int arg1);

    void on_kazeDiffCombo_currentIndexChanged(int index);

    void on_briskThreshSpin_valueChanged(int arg1);

    void on_briskOctaveSpin_valueChanged(int arg1);

    void on_briskScaleSpin_valueChanged(double arg1);

    void on_fastThreshSpin_valueChanged(int arg1);

    void on_fastNonmaxCheck_toggled(bool checked);

    void on_fastTypeCombo_currentIndexChanged(int index);

    void on_harrisCheck_toggled(bool checked);

    void on_harrisKSpin_valueChanged(double arg1);

    void on_gfttBlockSpin_valueChanged(int arg1);

    void on_gfttMaxSpin_valueChanged(int arg1);

    void on_gfttDistSpin_valueChanged(double arg1);

    void on_gfttQualitySpin_valueChanged(double arg1);

    void on_orbFeaturesSpin_valueChanged(int arg1);

    void on_orbScaleSpin_valueChanged(double arg1);

    void on_orbLevelsSpin_valueChanged(int arg1);

    void on_orbPatchSpin_valueChanged(int arg1);

    void on_orbWtaSpin_valueChanged(int arg1);

    void on_orbFastCheck_toggled(bool checked);

    void on_orbFastSpin_valueChanged(int arg1);

    void on_browseBtn_pressed();

    void on_keypointCombo_currentIndexChanged(int index);

    void on_descriptorCombo_currentIndexChanged(int index);

    void on_matcherCombo_currentIndexChanged(int index);

private:
    Ui::PluginGui *ui;

    cv::Mat secondImage;

    void fillFeature2D(QString algName, cv::Ptr<cv::Feature2D> &algorithm);

};

#endif // KEYPOINT_PLUGIN_H
