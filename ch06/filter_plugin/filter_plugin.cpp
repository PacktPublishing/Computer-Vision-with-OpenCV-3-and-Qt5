#include "filter_plugin.h"

#include "ui_plugin.h"

#define BILATERAL_FILTER_PAGE           0
#define BLUR_FILTER_PAGE                1
#define BOX_FILTER_PAGE                 2
#define GAUSSIAN_FILTER_PAGE            3
#define MEDIAN_FILTER_PAGE              4
#define FILTER2D_PAGE                   5
#define DERIVATIVES_PAGE                6
#define MORPH_PAGE                      7

Filter_Plugin::Filter_Plugin()
{
    // Insert initialization codes here ...
}

Filter_Plugin::~Filter_Plugin()
{
    // Insert cleanup codes here ...
}

QString Filter_Plugin::title()
{
    return this->metaObject()->className();
}

QString Filter_Plugin::version()
{
    return "1.0.0";
}

QString Filter_Plugin::description()
{
    return "Performs different filters available in OpenCV";
}

QString Filter_Plugin::help()
{
    return "This is a plugin that performs different filters available in OpenCV";
}

void Filter_Plugin::setupUi(QWidget *parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(parent);

    ui->mainTabs->setCurrentIndex(0);

    connect(ui->mainTabs, SIGNAL(currentChanged(int)), this, SLOT(on_mainTabs_currentChanged(int)));

    connect(ui->bilateralDiaSpin, SIGNAL(valueChanged(int)), this, SLOT(on_bilateralDiaSpin_valueChanged(int)));
    connect(ui->bilateralSigmaColorSpin, SIGNAL(valueChanged(double)), this, SLOT(on_bilateralSigmaColorSpin_valueChanged(double)));
    connect(ui->bilateralSigmaSpaceSpin, SIGNAL(valueChanged(double)), this, SLOT(on_bilateralSigmaSpaceSpin_valueChanged(double)));

    connect(ui->blurKernelSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_blurKernelSizeSpinBox_valueChanged(int)));
    connect(ui->blurAnchoXSpin, SIGNAL(valueChanged(int)), this, SLOT(on_blurAnchoXSpin_valueChanged(int)));
    connect(ui->blurAnchoYSpin, SIGNAL(valueChanged(int)), this, SLOT(on_blurAnchoYSpin_valueChanged(int)));

    connect(ui->boxKernelSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_boxKernelSizeSpinBox_valueChanged(int)));
    connect(ui->boxDepthSpin, SIGNAL(valueChanged(int)), this, SLOT(on_boxDepthSpin_valueChanged(int)));
    connect(ui->boxAnchoXSpin, SIGNAL(valueChanged(int)), this, SLOT(on_boxAnchoXSpin_valueChanged(int)));
    connect(ui->boxAnchoYSpin, SIGNAL(valueChanged(int)), this, SLOT(on_boxAnchoYSpin_valueChanged(int)));
    connect(ui->boxNormalCheck, SIGNAL(toggled(bool)), this, SLOT(on_boxNormalCheck_toggled(bool)));

    connect(ui->gaussKernelSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_gaussKernelSizeSpinBox_valueChanged(int)));
    connect(ui->gaussSigmaXSpin, SIGNAL(valueChanged(double)), this, SLOT(on_gaussSigmaXSpin_valueChanged(double)));
    connect(ui->gaussSigmaYSpin, SIGNAL(valueChanged(double)), this, SLOT(on_gaussSigmaYSpin_valueChanged(double)));

    connect(ui->medianApertureSpin, SIGNAL(valueChanged(int)), this, SLOT(on_medianApertureSpin_valueChanged(int)));

    connect(ui->derivSobelRadio, SIGNAL(toggled(bool)), this, SLOT(on_derivSobelRadio_toggled(bool)));
    connect(ui->derivScharrRadio, SIGNAL(toggled(bool)), this, SLOT(on_derivScharrRadio_toggled(bool)));
    connect(ui->derivLaplacRadio, SIGNAL(toggled(bool)), this, SLOT(on_derivLaplacRadio_toggled(bool)));
    connect(ui->derivDeltaSpin, SIGNAL(valueChanged(double)), this, SLOT(on_derivDeltaSpin_valueChanged(double)));
    connect(ui->derivScaleSpin, SIGNAL(valueChanged(double)), this, SLOT(on_derivScaleSpin_valueChanged(double)));

    ui->morphShapesCombo->addItems(
                QStringList() << "MORPH_RECT" << "MORPH_CROSS" << "MORPH_ELLIPSE");
    ui->morphTypesCombo->addItems(
                QStringList() << "MORPH_ERODE" << "MORPH_DILATE" << "MORPH_OPEN" << "MORPH_CLOSE"
                << "MORPH_GRADIENT" << "MORPH_TOPHAT" << "MORPH_BLACKHAT");
    connect(ui->morphDilateRadio, SIGNAL(toggled(bool)), this, SLOT(on_morphDilateRadio_toggled(bool)));
    connect(ui->morphErodeRadio, SIGNAL(toggled(bool)), this, SLOT(on_morphErodeRadio_toggled(bool)));
    connect(ui->morphMorphRadio, SIGNAL(toggled(bool)), this, SLOT(on_morphMorphRadio_toggled(bool)));
    connect(ui->morphIterSpin, SIGNAL(valueChanged(int)), this, SLOT(on_morphIterSpin_valueChanged(int)));
    connect(ui->morphShapesCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_morphShapesCombo_currentIndexChanged(int)));
    connect(ui->morphTypesCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_morphTypesCombo_currentIndexChanged(int)));
}

void Filter_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    using namespace cv;
    Matx33f f2dkernel;

    switch(ui->mainTabs->currentIndex())
    {

    case BILATERAL_FILTER_PAGE:
        bilateralFilter(inputImage,
                        outputImage,
                        ui->bilateralDiaSpin->value(),
                        ui->bilateralSigmaColorSpin->value(),
                        ui->bilateralSigmaSpaceSpin->value());
        break;

    case BLUR_FILTER_PAGE:
        blur(inputImage,
             outputImage,
             Size(ui->blurKernelSizeSpinBox->value(),
                  ui->blurKernelSizeSpinBox->value()),
             Point(ui->blurAnchoXSpin->value(),
                   ui->blurAnchoYSpin->value()));
        break;

    case BOX_FILTER_PAGE:
        boxFilter(inputImage,
                  outputImage,
                  ui->boxDepthSpin->value(),
                  Size(ui->boxKernelSizeSpinBox->value(),
                       ui->boxKernelSizeSpinBox->value()),
                  Point(ui->boxAnchoXSpin->value(),
                        ui->boxAnchoYSpin->value()),
                  ui->boxNormalCheck->isChecked());

        // replace with sqrBoxFilter
        break;

    case GAUSSIAN_FILTER_PAGE:
        GaussianBlur(inputImage,
                     outputImage,
                     Size(ui->gaussKernelSizeSpinBox->value(),
                          ui->gaussKernelSizeSpinBox->value()),
                     ui->gaussSigmaXSpin->value(),
                     ui->gaussSigmaYSpin->value());
        break;

    case MEDIAN_FILTER_PAGE:
        medianBlur(inputImage,
                   outputImage,
                   ui->medianApertureSpin->value());
        break;

    case FILTER2D_PAGE:
        f2dkernel = Matx33f(0, +1.5, 0,
                            +1.5, -6, +1.5,
                            0, +1.5, 0);

        filter2D(inputImage,
                 outputImage,
                 -1, // Output should have same depth as source
                 f2dkernel,
                 Point(-1,-1));
        break;

    case DERIVATIVES_PAGE:
        if(ui->derivSobelRadio->isChecked())
            Sobel(inputImage, outputImage, -1, 1, 1, 3, ui->derivScaleSpin->value(), ui->derivDeltaSpin->value());
        else if(ui->derivScharrRadio->isChecked())
            Scharr(inputImage, outputImage, -1, 1, 0, ui->derivScaleSpin->value(), ui->derivDeltaSpin->value());
        else if(ui->derivLaplacRadio->isChecked())
            Laplacian(inputImage, outputImage, -1, 3, ui->derivScaleSpin->value(), ui->derivDeltaSpin->value());
        break;

    case MORPH_PAGE:
        if(ui->morphErodeRadio->isChecked())
        {
            erode(inputImage,
                  outputImage,
                  getStructuringElement(ui->morphShapesCombo->currentIndex(),
                                        Size(5,5)),
                  Point(-1,-1),
                  ui->morphIterSpin->value());
        }
        else if(ui->morphDilateRadio->isChecked())
        {
            dilate(inputImage,
                   outputImage,
                   getStructuringElement(ui->morphShapesCombo->currentIndex(),
                                         Size(5,5)),
                   Point(-1,-1),
                   ui->morphIterSpin->value());
        }
        else if(ui->morphMorphRadio->isChecked())
        {
            morphologyEx(inputImage,
                         outputImage,
                         ui->morphTypesCombo->currentIndex(),
                         getStructuringElement(ui->morphShapesCombo->currentIndex(),
                                               Size(5,5)),
                         Point(-1,-1),
                         ui->morphIterSpin->value());
        }
        break;

    }
}

void Filter_Plugin::on_bilateralDiaSpin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_bilateralSigmaColorSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_bilateralSigmaSpaceSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_blurKernelSizeSpinBox_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_blurAnchoXSpin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_blurAnchoYSpin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_boxKernelSizeSpinBox_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_boxDepthSpin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_boxAnchoXSpin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_boxAnchoYSpin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_boxNormalCheck_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit updateNeeded();
}

void Filter_Plugin::on_gaussKernelSizeSpinBox_valueChanged(int arg1)
{
    if(arg1 % 2 == 1) // Must be odd
        emit updateNeeded();
}

void Filter_Plugin::on_gaussSigmaXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_gaussSigmaYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_medianApertureSpin_valueChanged(int arg1)
{
    if(arg1 % 2 == 1) // Must be odd
        emit updateNeeded();
}

void Filter_Plugin::on_mainTabs_currentChanged(int index)
{
    Q_UNUSED(index);
    emit updateNeeded();
}

void Filter_Plugin::on_derivSobelRadio_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit updateNeeded();
}

void Filter_Plugin::on_derivScharrRadio_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit updateNeeded();
}

void Filter_Plugin::on_derivLaplacRadio_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit updateNeeded();
}

void Filter_Plugin::on_derivScaleSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_derivDeltaSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_morphErodeRadio_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit updateNeeded();
}

void Filter_Plugin::on_morphDilateRadio_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit updateNeeded();
}

void Filter_Plugin::on_morphMorphRadio_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit updateNeeded();
}

void Filter_Plugin::on_morphIterSpin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit updateNeeded();
}

void Filter_Plugin::on_morphTypesCombo_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    emit updateNeeded();
}

void Filter_Plugin::on_morphShapesCombo_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    emit updateNeeded();
}
