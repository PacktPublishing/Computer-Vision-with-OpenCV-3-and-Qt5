#include "color_plugin.h"

#include "ui_plugin.h"

Color_Plugin::Color_Plugin()
{
    // Insert initialization codes here ...
}

Color_Plugin::~Color_Plugin()
{
    // Insert cleanup codes here ...
}

QString Color_Plugin::title()
{
    return this->metaObject()->className();
}

QString Color_Plugin::version()
{
    return "1.0.0";
}

QString Color_Plugin::description()
{
    return "";
}

QString Color_Plugin::help()
{
    return "";
}

void Color_Plugin::setupUi(QWidget *parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(parent);

    ui->colorMapCombo->addItems(QStringList()
                                << "COLORMAP_AUTUMN"
                                << "COLORMAP_BONE"
                                << "COLORMAP_JET"
                                << "COLORMAP_WINTER"
                                << "COLORMAP_RAINBOW"
                                << "COLORMAP_OCEAN"
                                << "COLORMAP_SUMMER"
                                << "COLORMAP_SPRING"
                                << "COLORMAP_COOL"
                                << "COLORMAP_HSV"
                                << "COLORMAP_PINK"
                                << "COLORMAP_HOT"
                                << "COLORMAP_PARULA");

    connect(ui->colorMapCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_colorMapCombo_currentIndexChanged(int)));
}

void Color_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    using namespace cv;
    applyColorMap(inputImage, outputImage, ui->colorMapCombo->currentIndex());
}

void Color_Plugin::on_colorMapCombo_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    emit updateNeeded();
}
