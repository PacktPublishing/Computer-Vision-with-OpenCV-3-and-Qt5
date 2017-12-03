#include "qimageviewer.h"

QImageViewer::QImageViewer(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

void QImageViewer::setImage(const QImage &img)
{
    currentImage = img.copy(); // perform a copy
    update();
}

void QImageViewer::paint(QPainter *painter)
{
    QSizeF scaled = QSizeF(currentImage.width(),
                           currentImage.height())
            .scaled(boundingRect().size(), Qt::KeepAspectRatio);
    QRect centerRect(qAbs(scaled.width() - width()) / 2.0f,
                     qAbs(scaled.height() - height()) / 2.0f,
                     scaled.width(),
                     scaled.height());
    painter->drawImage(centerRect,
                       currentImage);
}
