#include "qblinkingwidget.h"

QBlinkingWidget::QBlinkingWidget(QWidget *parent) : QWidget(parent)
{
    blink  = false;
    connect(&blinkTimer,
            SIGNAL(timeout()),
            this,
            SLOT(onBlink()));
    blinkTimer.start(500);
}

void QBlinkingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if(blink)
        painter.fillRect(this->rect(),
                         QBrush(Qt::red));
    else
        painter.fillRect(this->rect(),
                         QBrush(Qt::white));
}

void QBlinkingWidget::onBlink()
{
    blink = !blink;
    this->update();
}
