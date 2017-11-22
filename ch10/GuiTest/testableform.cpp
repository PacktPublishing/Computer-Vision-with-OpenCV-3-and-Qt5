#include "testableform.h"
#include "ui_testableform.h"

TestableForm::TestableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestableForm)
{
    ui->setupUi(this);

    this->nextBtn = ui->nextBtn;
    this->infoLabel = ui->infoLabel;
}

TestableForm::~TestableForm()
{
    delete ui;
}

void TestableForm::on_nextBtn_pressed()
{
    if(ui->infoLabel->text().trimmed().isEmpty())
    {
        ui->infoLabel->setText("1");
    }
    else
    {
        int n = ui->infoLabel->text().toInt();
        ui->infoLabel->setText(QString::number(n*2));
    }
}
