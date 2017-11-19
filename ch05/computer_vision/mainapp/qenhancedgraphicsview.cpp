#include "qenhancedgraphicsview.h"

QEnhancedGraphicsView::QEnhancedGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{

}

void QEnhancedGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->orientation() == Qt::Vertical)
    {
        double angleDeltaY = event->angleDelta().y();
        double zoomFactor = qPow(1.0015, angleDeltaY);
        scale(zoomFactor, zoomFactor);
        if(angleDeltaY > 0)
        {
            this->centerOn(sceneMousePos);
            sceneMousePos = this->mapToScene(event->pos());
        }
        this->viewport()->update();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void QEnhancedGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QMenu menu;
        QAction *clearAllAction = menu.addAction("Clear All");
        connect(clearAllAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(clearAll(bool)));

        QAction *clearSelectedAction = menu.addAction("Clear Selected");
        connect(clearSelectedAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(clearSelected(bool)));

        QAction *noEffectAction = menu.addAction("No Effect");
        connect(noEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(noEffect(bool)));

        QAction *blurEffectAction = menu.addAction("Blur Effect");
        connect(blurEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(blurEffect(bool)));

        QAction *dropShadEffectAction = menu.addAction("Drop Shadow Effect");
        connect(dropShadEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(dropShadowEffect(bool)));

        QAction *colorizeEffectAction = menu.addAction("Colorize Effect");
        connect(colorizeEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(colorizeEffect(bool)));

        QAction *customEffectAction = menu.addAction("Custom Effect");
        connect(customEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(customEffect(bool)));

        menu.exec(event->globalPos());
        event->accept();
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}
