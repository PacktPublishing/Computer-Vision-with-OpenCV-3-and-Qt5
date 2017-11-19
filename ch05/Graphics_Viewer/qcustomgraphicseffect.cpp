#include "qcustomgraphicseffect.h"

QCustomGraphicsEffect::QCustomGraphicsEffect(QObject *parent)
    : QGraphicsEffect(parent)
{

}

void QCustomGraphicsEffect::draw(QPainter *painter)
{
    QImage image;
    image = sourcePixmap().toImage();
    image = image.convertToFormat(
                QImage::Format_Grayscale8);
    for(int i=0; i<image.byteCount(); i++)
        image.bits()[i] =
                image.bits()[i] < 100 ?
                    0
                  :
                    255;
    painter->drawPixmap(0,0,QPixmap::fromImage(image));
}
