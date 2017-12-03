#ifndef QIMAGEVIEWER_H
#define QIMAGEVIEWER_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

class QImageViewer : public QQuickPaintedItem
{
    Q_OBJECT
public:
    QImageViewer(QQuickItem *parent = Q_NULLPTR);
    Q_INVOKABLE void setImage(const QImage &img);

private:
    QImage currentImage;
    void paint(QPainter *painter);

};

#endif // QIMAGEVIEWER_H
