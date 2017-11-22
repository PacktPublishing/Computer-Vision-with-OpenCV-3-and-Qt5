#ifndef PIXELCOUNTER_H
#define PIXELCOUNTER_H

#include <QObject>
#include <QFile>

#include "opencv2/opencv.hpp"

class PixelCounter : public QObject
{
    Q_OBJECT
public:
    explicit PixelCounter(QObject *parent = nullptr);

    int countPixels(QString fname);

signals:

public slots:
};

#endif // PIXELCOUNTER_H
