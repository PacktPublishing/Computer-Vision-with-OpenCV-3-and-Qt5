#ifndef QBLINKINGWIDGET_H
#define QBLINKINGWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

class QBlinkingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QBlinkingWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

signals:

private slots:
    void onBlink();

private:
    QTimer blinkTimer;
    bool blink;

};

#endif // QBLINKINGWIDGET_H
