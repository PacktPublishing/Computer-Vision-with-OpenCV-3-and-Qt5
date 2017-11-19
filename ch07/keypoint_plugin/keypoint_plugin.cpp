#include "keypoint_plugin.h"

#include "ui_plugin.h"

#include <QFileDialog>
#include <QDebug>

Keypoint_Plugin::Keypoint_Plugin()
{
    // Insert initialization codes here ...
}

Keypoint_Plugin::~Keypoint_Plugin()
{
    // Insert cleanup codes here ...
}

QString Keypoint_Plugin::title()
{
    return this->metaObject()->className();
}

QString Keypoint_Plugin::version()
{
    return "1.0.0";
}

QString Keypoint_Plugin::description()
{
    return "Feature Detection Plugin";
}

QString Keypoint_Plugin::help()
{
    return "Feature Detection Plugin";
}

void Keypoint_Plugin::setupUi(QWidget *parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(parent);

    ui->agastTypeCombo->addItems(QStringList()
                                 << "AGAST_5_8"
                                 << "AGAST_7_12d"
                                 << "AGAST_7_12s"
                                 << "OAST_9_16");

    ui->fastTypeCombo->addItems(QStringList()
                                << "TYPE_5_8"
                                << "TYPE_7_12"
                                << "TYPE_9_16");

    ui->akazeDescriptCombo->addItems(QStringList()
                                     << "DESCRIPTOR_KAZE_UPRIGHT"
                                     << "DESCRIPTOR_KAZE"
                                     << "DESCRIPTOR_MLDB_UPRIGHT"
                                     << "DESCRIPTOR_MLDB");

    ui->kazeDiffCombo->addItems(QStringList()
                                << "DIFF_PM_G1"
                                << "DIFF_PM_G2"
                                << "DIFF_WEICKERT"
                                << "DIFF_CHARBONNIER");

    ui->keypointCombo->addItems(QStringList()
                                << "AGAST"
                                << "KAZE"
                                << "BRISK"
                                << "FAST"
                                << "GFTT/Harris"
                                << "ORB");

    ui->descriptorCombo->addItems(QStringList()
                                  << "KAZE"
                                  << "BRISK"
                                  << "ORB");

    ui->matcherCombo->addItems(QStringList()
                               << "FLANNBASED"
                               << "BRUTEFORCE"
                               << "BRUTEFORCE_L1"
                               << "BRUTEFORCE_HAMMING"
                               << "BRUTEFORCE_HAMMINGLUT"
                               << "BRUTEFORCE_SL2");

    connect(ui->toolBox, SIGNAL(currentChanged(int)), this, SLOT(on_toolBox_currentChanged(int)));
    connect(ui->agastNonmaxCheck, SIGNAL(toggled(bool)), this, SLOT(on_agastNonmaxCheck_toggled(bool)));
    connect(ui->agastThreshSpin, SIGNAL(valueChanged(int)), this, SLOT(on_agastThreshSpin_valueChanged(int)));
    connect(ui->agastTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_agastTypeCombo_currentIndexChanged(int)));

    connect(ui->kazeAcceleratedCheck, SIGNAL(toggled(bool)), this, SLOT(on_kazeAcceleratedCheck_toggled(bool)));
    connect(ui->kazeExtendCheck, SIGNAL(toggled(bool)), this, SLOT(on_kazeExtendCheck_toggled(bool)));
    connect(ui->kazeUprightCheck, SIGNAL(toggled(bool)), this, SLOT(on_kazeUprightCheck_toggled(bool)));
    connect(ui->kazeLayerSpin, SIGNAL(valueChanged(int)), this, SLOT(on_kazeLayerSpin_valueChanged(int)));
    connect(ui->kazeOctaveSpin, SIGNAL(valueChanged(int)), this, SLOT(on_kazeOctaveSpin_valueChanged(int)));
    connect(ui->kazeThreshSpin, SIGNAL(valueChanged(double)), this, SLOT(on_kazeThreshSpin_valueChanged(double)));
    connect(ui->kazeDiffCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_kazeDiffCombo_currentIndexChanged(int)));
    connect(ui->akazeDescriptCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_akazeDescriptCombo_currentIndexChanged(int)));
    ui->kazeAcceleratedCheck->setChecked(true);

    connect(ui->briskOctaveSpin, SIGNAL(valueChanged(int)), this, SLOT(on_briskOctaveSpin_valueChanged(int)));
    connect(ui->briskScaleSpin, SIGNAL(valueChanged(double)), this, SLOT(on_briskScaleSpin_valueChanged(double)));
    connect(ui->briskThreshSpin, SIGNAL(valueChanged(int)), this, SLOT(on_briskThreshSpin_valueChanged(int)));

    connect(ui->fastNonmaxCheck, SIGNAL(toggled(bool)), this, SLOT(on_fastNonmaxCheck_toggled(bool)));
    connect(ui->fastThreshSpin, SIGNAL(valueChanged(int)), this, SLOT(on_fastThreshSpin_valueChanged(int)));
    connect(ui->fastTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_fastTypeCombo_currentIndexChanged(int)));

    connect(ui->harrisCheck, SIGNAL(toggled(bool)), this, SLOT(on_harrisCheck_toggled(bool)));
    connect(ui->harrisKSpin, SIGNAL(valueChanged(double)), this, SLOT(on_harrisKSpin_valueChanged(double)));
    connect(ui->gfttBlockSpin, SIGNAL(valueChanged(int)), this, SLOT(on_gfttBlockSpin_valueChanged(int)));
    connect(ui->gfttDistSpin, SIGNAL(valueChanged(double)), this, SLOT(on_gfttDistSpin_valueChanged(double)));
    connect(ui->gfttMaxSpin, SIGNAL(valueChanged(int)), this, SLOT(on_gfttMaxSpin_valueChanged(int)));
    connect(ui->gfttQualitySpin, SIGNAL(valueChanged(double)), this, SLOT(on_gfttQualitySpin_valueChanged(double)));

    connect(ui->orbFastCheck, SIGNAL(toggled(bool)), this, SLOT(on_orbFastCheck_toggled(bool)));
    connect(ui->orbFastSpin, SIGNAL(valueChanged(int)), this, SLOT(on_orbFastSpin_valueChanged(int)));
    connect(ui->orbFeaturesSpin, SIGNAL(valueChanged(int)), this, SLOT(on_orbFeaturesSpin_valueChanged(int)));
    connect(ui->orbLevelsSpin, SIGNAL(valueChanged(int)), this, SLOT(on_orbLevelsSpin_valueChanged(int)));
    connect(ui->orbPatchSpin, SIGNAL(valueChanged(int)), this, SLOT(on_orbPatchSpin_valueChanged(int)));
    connect(ui->orbWtaSpin, SIGNAL(valueChanged(int)), this, SLOT(on_orbWtaSpin_valueChanged(int)));
    connect(ui->orbScaleSpin, SIGNAL(valueChanged(double)), this, SLOT(on_orbScaleSpin_valueChanged(double)));

    connect(ui->browseBtn, SIGNAL(pressed()), this, SLOT(on_browseBtn_pressed()));
    connect(ui->keypointCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_keypointCombo_currentIndexChanged(int)));
    connect(ui->descriptorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_descriptorCombo_currentIndexChanged(int)));
    connect(ui->matcherCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_matcherCombo_currentIndexChanged(int)));
}

void Keypoint_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    if(secondImage.empty())
    {
        emit errorMessage("Select a secondary image first!");
        return;
    }

    using namespace cv;
    using namespace std;

    Ptr<Feature2D> keypDetector;
    Ptr<Feature2D> descExtractor;
    Ptr<DescriptorMatcher> descMather;

    fillFeature2D(ui->keypointCombo->currentText(), keypDetector);
    fillFeature2D(ui->descriptorCombo->currentText(), descExtractor);

    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptor1, descriptor2;
    vector<DMatch> matches;

    // fast and safe version
    if(ui->keypointCombo->currentText() == ui->descriptorCombo->currentText())
    {
        descExtractor->detectAndCompute(inputImage, Mat(), keypoints1, descriptor1);
        descExtractor->detectAndCompute(secondImage, Mat(), keypoints2, descriptor2);
    }
    else
    {
        // we need to check
        if(ui->keypointCombo->currentText() == "KAZE"
                || ui->keypointCombo->currentText() == "AKAZE"
                || ui->descriptorCombo->currentText() == "KAZE"
                || ui->descriptorCombo->currentText() == "AKAZE")
        {
            emit errorMessage("Use KAZE/AKAZE keypoints with KAZE/AKAZE descriptors only!");
            return;
        }

        keypDetector->detect(inputImage, keypoints1);
        descExtractor->compute(inputImage, keypoints1, descriptor1);
        keypDetector->detect(secondImage, keypoints2);
        descExtractor->compute(secondImage, keypoints2, descriptor2);
    }

    // Also check for the correct type of matching
    descMather = DescriptorMatcher::create(ui->matcherCombo->currentIndex()+1);
    descMather->match(descriptor1, descriptor2, matches);

    // Find good matches (AKAZE)
    vector<DMatch> goodMatches;
    double matchThresh = 0.1;
    for(int i=0; i<descriptor1.rows; i++)
    {
        if(matches[i].distance < matchThresh)
            goodMatches.push_back(matches[i]);
    }

    drawMatches(inputImage,
                keypoints1,
                secondImage,
                keypoints2,
                goodMatches,
                outputImage);

    vector<Point2f> goodP1, goodP2;
    for(size_t i=0; i<goodMatches.size(); i++)
    {
        goodP1.push_back(keypoints1[goodMatches[i].queryIdx].pt);
        goodP2.push_back(keypoints2[goodMatches[i].trainIdx].pt);
    }
    Mat homoChange = findHomography(goodP1, goodP2);

    vector<Point2f> corners1(4), corners2(4);
    corners1[0] = Point2f(0,0);
    corners1[1] = Point2f(inputImage.cols-1, 0);
    corners1[2] = Point2f(inputImage.cols-1, inputImage.rows-1);
    corners1[3] = Point2f(0, inputImage.rows-1);

    perspectiveTransform(corners1, corners2, homoChange);

    Point2f offset(inputImage.cols, 0);

    line(outputImage, corners2[0] + offset, corners2[1] + offset, Scalar::all(255), 2);
    line(outputImage, corners2[1] + offset, corners2[2] + offset, Scalar::all(255), 2);
    line(outputImage, corners2[2] + offset, corners2[3] + offset, Scalar::all(255), 2);
    line(outputImage, corners2[3] + offset, corners2[0] + offset, Scalar::all(255), 2);
}

void Keypoint_Plugin::fillFeature2D(QString algName, cv::Ptr<cv::Feature2D> &algorithm)
{
    using namespace cv;
    using namespace std;

    if(algName == "AGAST")
    {
        Ptr<AgastFeatureDetector> agast = AgastFeatureDetector::create();
        agast->setThreshold(ui->agastThreshSpin->value());
        agast->setNonmaxSuppression(ui->agastNonmaxCheck->isChecked());
        agast->setType(ui->agastTypeCombo->currentIndex());
        algorithm = agast;
    }
    else if(algName == "KAZE")
    {
        if(ui->kazeAcceleratedCheck->isChecked())
        {
            Ptr<AKAZE> akaze = AKAZE::create();
            akaze->setDescriptorChannels(3);
            akaze->setDescriptorSize(0);
            akaze->setDescriptorType(ui->akazeDescriptCombo->currentIndex() + 2);
            akaze->setDiffusivity(ui->kazeDiffCombo->currentIndex());
            akaze->setNOctaves(ui->kazeOctaveSpin->value());
            akaze->setNOctaveLayers(ui->kazeLayerSpin->value());
            akaze->setThreshold(ui->kazeThreshSpin->value());
            algorithm = akaze;
        }
        else
        {
            Ptr<KAZE> kaze = KAZE::create();
            kaze->setUpright(ui->kazeUprightCheck->isChecked());
            kaze->setExtended(ui->kazeExtendCheck->isChecked());
            kaze->setDiffusivity(ui->kazeDiffCombo->currentIndex());
            kaze->setNOctaves(ui->kazeOctaveSpin->value());
            kaze->setNOctaveLayers(ui->kazeLayerSpin->value());
            kaze->setThreshold(ui->kazeThreshSpin->value());
            algorithm = kaze;
        }

    }
    else if(algName == "BRISK")
    {
        Ptr<BRISK> brisk =
                BRISK::create(ui->briskThreshSpin->value(),
                              ui->briskOctaveSpin->value(),
                              ui->briskScaleSpin->value());
        algorithm = brisk;
    }
    else if(algName == "FAST")
    {
        Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();
        fast->setThreshold(ui->fastThreshSpin->value());
        fast->setNonmaxSuppression(ui->fastNonmaxCheck->isChecked());
        fast->setType(ui->fastTypeCombo->currentIndex());
        algorithm = fast;
    }
    else if(algName == "GFTT/Harris")
    {
        Ptr<GFTTDetector> gftt = GFTTDetector::create();
        gftt->setHarrisDetector(ui->harrisCheck->isChecked());
        gftt->setK(ui->harrisKSpin->value());
        gftt->setBlockSize(ui->gfttBlockSpin->value());
        gftt->setMaxFeatures(ui->gfttMaxSpin->value());
        gftt->setMinDistance(ui->gfttDistSpin->value());
        gftt->setQualityLevel(ui->gfttQualitySpin->value());
        algorithm = gftt;
    }
    else if(algName == "ORB")
    {
        Ptr<ORB> orb = ORB::create();
        orb->setMaxFeatures(ui->orbFeaturesSpin->value());
        orb->setScaleFactor(ui->orbScaleSpin->value());
        orb->setNLevels(ui->orbLevelsSpin->value());
        orb->setPatchSize(ui->orbPatchSpin->value());
        orb->setEdgeThreshold(ui->orbPatchSpin->value()); // same as patch size
        orb->setWTA_K(ui->orbWtaSpin->value());
        orb->setScoreType(ui->orbFastCheck->isChecked() ?
                              ORB::HARRIS_SCORE
                            :
                              ORB::FAST_SCORE);
        orb->setPatchSize(ui->orbPatchSpin->value());
        orb->setFastThreshold(ui->orbFastSpin->value());
        algorithm = orb;
    }
}

void Keypoint_Plugin::on_toolBox_currentChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_agastThreshSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_agastNonmaxCheck_toggled(bool)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_agastTypeCombo_currentIndexChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_kazeAcceleratedCheck_toggled(bool checked)
{
    ui->kazeExtendCheck->setVisible(!checked);
    ui->kazeUprightCheck->setVisible(!checked);
    ui->akazeDescriptCombo->setVisible(checked);
    emit updateNeeded();
}

void Keypoint_Plugin::on_kazeExtendCheck_toggled(bool)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_kazeUprightCheck_toggled(bool)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_akazeDescriptCombo_currentIndexChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_kazeThreshSpin_valueChanged(double)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_kazeOctaveSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_kazeLayerSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_kazeDiffCombo_currentIndexChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_briskThreshSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_briskOctaveSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_briskScaleSpin_valueChanged(double)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_fastThreshSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_fastNonmaxCheck_toggled(bool)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_fastTypeCombo_currentIndexChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_harrisCheck_toggled(bool)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_harrisKSpin_valueChanged(double)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_gfttBlockSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_gfttMaxSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_gfttDistSpin_valueChanged(double)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_gfttQualitySpin_valueChanged(double)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_orbFeaturesSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_orbScaleSpin_valueChanged(double)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_orbLevelsSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_orbPatchSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_orbWtaSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_orbFastCheck_toggled(bool)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_orbFastSpin_valueChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_browseBtn_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(ui->tabWidget,
                                                    tr("Open Input Image"),
                                                    QDir::currentPath(),
                                                    tr("Images") + " (*.jpg *.png *.bmp)");

    using namespace cv;
    secondImage = imread(fileName.toStdString());
    if(!secondImage.empty())
    {
        emit updateNeeded();
    }
}

void Keypoint_Plugin::on_keypointCombo_currentIndexChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_descriptorCombo_currentIndexChanged(int)
{
    emit updateNeeded();
}

void Keypoint_Plugin::on_matcherCombo_currentIndexChanged(int)
{
    emit updateNeeded();
}
