#include "segmentation_plugin.h"

#include "ui_plugin.h"

Segmentation_Plugin::Segmentation_Plugin()
{
    // Insert initialization codes here ...
}

Segmentation_Plugin::~Segmentation_Plugin()
{
    // Insert cleanup codes here ...
}

QString Segmentation_Plugin::title()
{
    return this->metaObject()->className();
}

QString Segmentation_Plugin::version()
{
    return "1.0.0";
}

QString Segmentation_Plugin::description()
{
    return "";
}

QString Segmentation_Plugin::help()
{
    return "";
}

void Segmentation_Plugin::setupUi(QWidget *parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(parent);

    ui->threshAdaptiveCombo->addItems(
                QStringList()
                << "ADAPTIVE_THRESH_MEAN_C"
                << "ADAPTIVE_THRESH_GAUSSIAN_C");

    ui->threshTypeCombo->addItems(
                QStringList()
                << "THRESH_BINARY"
                << "THRESH_BINARY_INV"
                << "THRESH_TRUNC"
                << "THRESH_TOZERO"
                << "THRESH_TOZERO_INV");
    connect(ui->threshAdaptiveCheck, SIGNAL(toggled(bool)), this, SLOT(on_threshAdaptiveCheck_toggled(bool)));
    connect(ui->threshAdaptiveCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_threshAdaptiveCombo_currentIndexChanged(int)));
    connect(ui->threshTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_threshTypeCombo_currentIndexChanged(int)));
    connect(ui->threshSlider, SIGNAL(valueChanged(int)), this, SLOT(on_threshSlider_valueChanged(int)));
    connect(ui->threshMaxSlider, SIGNAL(valueChanged(int)), this, SLOT(on_threshMaxSlider_valueChanged(int)));

}

void Segmentation_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    using namespace cv;

    Mat grayScale;
    cvtColor(inputImage, grayScale, CV_BGR2GRAY);

    if(ui->threshAdaptiveCheck->isChecked())
    {
        adaptiveThreshold(grayScale,
                          grayScale,
                          ui->threshMaxSlider->value(),
                          ui->threshAdaptiveCombo->currentIndex(),
                          ui->threshTypeCombo->currentIndex(),
                          7,
                          0);
    }
    else
    {
        threshold(grayScale,
                  grayScale,
                  ui->threshSlider->value(),
                  ui->threshMaxSlider->value(),
                  ui->threshTypeCombo->currentIndex());
    }
    cvtColor(grayScale, outputImage, CV_GRAY2BGR);
}

void Segmentation_Plugin::on_threshAdaptiveCheck_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit updateNeeded();
}

void Segmentation_Plugin::on_threshAdaptiveCombo_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    emit updateNeeded();
}

void Segmentation_Plugin::on_threshTypeCombo_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    emit updateNeeded();
}

void Segmentation_Plugin::on_threshSlider_valueChanged(int value)
{
    emit infoMessage(QString::number(value));
    emit updateNeeded();
}

void Segmentation_Plugin::on_threshMaxSlider_valueChanged(int value)
{
    emit infoMessage(QString::number(value));
    emit updateNeeded();
}
