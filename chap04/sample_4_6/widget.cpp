#include "widget.h"
#include "ui_widget.h"

#include <QTextBlock>

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

void Widget::on_btnInitCb_clicked()
{
    QIcon icon(":/icons/images/3.ico");
    ui->comboBoxData->clear();
    for(int i=0;i<20;i++){
        ui->comboBoxData->addItem(icon,QString::asprintf("Item %d",i));
    }
}

void Widget::on_btnInit_clicked()
{
    ui->comboBoxInit->clear();
    QIcon icon(":/icons/images/2.ico");
    QMap<QString,int> cityZone;
    cityZone.insert("上海",10);
    cityZone.insert("北京",20);
    cityZone.insert("成都",30);

    foreach (auto str, cityZone.keys()) {
        ui->comboBoxInit->addItem(icon,str,cityZone.value(str));
    }
}


void Widget::on_btnAppend_clicked()
{
    QTextDocument *doc = ui->plainTextEdit->document();
    QIcon icon(":/icons/images/2.ico");
    int num = doc->blockCount();
    for(int i=0;i<num;i++){
//        doc->findBlockByNumber(i);
         ui->comboBoxData->addItem(icon,doc->findBlockByNumber(i).text());
    }

}
