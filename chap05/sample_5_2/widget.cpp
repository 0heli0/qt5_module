#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    theModel=new QStringListModel(this);
    QStringList strList;
    strList<<"北京"<<"上海"<<"成都"<<"深圳"<<"杭州"<<"广州";
    theModel->setStringList(strList);
    ui->listView->setModel(theModel); //为listView设置数据模型
}

Widget::~Widget()
{
    delete ui;
}
