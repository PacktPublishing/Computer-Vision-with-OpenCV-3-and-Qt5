#ifndef QIMAGEPROCESSOR_H
#define QIMAGEPROCESSOR_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include "opencv2/opencv.hpp"

class QImageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit QImageProcessor(QObject *parent = nullptr);

    Q_INVOKABLE void processImage(const QString &path);

signals:
    void imageProcessed(const QImage &image);

public slots:

};

#endif // QIMAGEPROCESSOR_H
