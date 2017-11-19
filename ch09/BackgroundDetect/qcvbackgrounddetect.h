#ifndef QCVBACKGROUNDDETECT_H
#define QCVBACKGROUNDDETECT_H

#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QMutex>
#include "opencv2/opencv.hpp"

class QCvBackgroundDetect : public QThread
{
    Q_OBJECT
public:
    explicit QCvBackgroundDetect(QObject *parent = nullptr);

signals:
    void newFrame(QPixmap pix);

public slots:

private:
    void run() override;

};

#endif // QCVBACKGROUNDDETECT_H
