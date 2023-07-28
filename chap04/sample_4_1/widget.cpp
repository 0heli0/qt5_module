#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCalcPrice_clicked()
{
    QString countStr = ui->editCount->text();
    int num = countStr.toInt();

    QString priceStr = ui->editPrice->text();
    float price = priceStr.toFloat();

    float total = num*price;

    QString str;
    str = str.setNum(total,'f',2);

    ui->editTotal->setText(str);


}

void Widget::on_btnDec_clicked()
{
    QString decStr = ui->editDec->text();
    int value = decStr.toInt();
    decStr = decStr.setNum(value,2);
    ui->editBinary->setText(decStr);

    decStr = decStr.setNum(value,16);
    ui->editHex->setText(decStr.toUpper());
}

void Widget::on_btnBinary_clicked()
{
    QString binStr = ui->editBinary->text();
    bool ok;
    int value = binStr.toInt(&ok,2);
    ui->editDec->setText(QString::number(value));
    ui->editHex->setText(QString::number(value,16).toUpper());
}
