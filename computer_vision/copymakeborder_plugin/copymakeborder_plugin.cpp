#include "copymakeborder_plugin.h"

#include "ui_plugin.h"

CopyMakeBorder_Plugin::CopyMakeBorder_Plugin()
{
    // Insert initialization codes here ...
}

CopyMakeBorder_Plugin::~CopyMakeBorder_Plugin()
{
    // Insert cleanup codes here ...
}

QString CopyMakeBorder_Plugin::title()
{
    return this->metaObject()->className();
}

QString CopyMakeBorder_Plugin::version()
{
    return "1.0.0";
}

QString CopyMakeBorder_Plugin::description()
{
    return "";
}

QString CopyMakeBorder_Plugin::help()
{
    return "";
}

void CopyMakeBorder_Plugin::setupUi(QWidget *parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(parent);
    QStringList items;
    items.append("BORDER_CONSTANT");
    items.append("BORDER_REPLICATE");
    items.append("BORDER_REFLECT");
    items.append("BORDER_WRAP");
    items.append("BORDER_REFLECT_101");
    ui->borderTypeComboBox->addItems(items);
    connect(ui->borderTypeComboBox,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_borderTypeComboBox_currentIndexChanged(int)));
}

void CopyMakeBorder_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    int top, bot, left, right;
    top = bot = inputImage.rows/2;
    left = right = inputImage.cols/2;
    cv::copyMakeBorder(inputImage,
                   outputImage,
                   top,
                   bot,
                   left,
                   right,
                   ui->borderTypeComboBox->currentIndex());
}

void CopyMakeBorder_Plugin::on_borderTypeComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    emit updateNeeded();
}
