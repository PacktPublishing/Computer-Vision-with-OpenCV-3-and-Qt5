#ifndef QENHANCEDGRAPHICSVIEW_H
#define QENHANCEDGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QtMath>
#include <QContextMenuEvent>
#include <QMenu>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsEffect>
#include "qcustomgraphicseffect.h"

class QEnhancedGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QEnhancedGraphicsView(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

private slots:
    void clearAll(bool);
    void clearSelected(bool);
    void noEffect(bool);
    void blurEffect(bool);
    void dropShadowEffect(bool);
    void colorizeEffect(bool);
    void customEffect(bool);

private:
    QPointF sceneMousePos;

};

#endif // QENHANCEDGRAPHICSVIEW_H
