#ifndef TESTABLEFORM_H
#define TESTABLEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class TestableForm;
}

class TestableForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestableForm(QWidget *parent = 0);
    ~TestableForm();

    QPushButton *nextBtn;
    QLabel *infoLabel;

private slots:
    void on_nextBtn_pressed();

private:
    Ui::TestableForm *ui;
};

#endif // TESTABLEFORM_H
