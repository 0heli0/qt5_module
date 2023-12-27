#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    theModel=new QStringListModel(this);
    strList<<"北京"<<"上海"<<"成都"<<"深圳"<<"杭州"<<"广州";
    theModel->setStringList(strList);
    ui->listView->setModel(theModel); //为listView设置数据模型
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnTextImport_clicked()
{
    ui->plainTextEdit->clear();
    QStringList strList = theModel->stringList();
    foreach (auto str, strList) {
     ui->plainTextEdit->appendPlainText(str);
    }
}

void Widget::on_btnTextClear_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_btnListClear_clicked()
{
    strList.clear();
    theModel->removeRows(0,theModel->rowCount());
}

void Widget::on_btnIniList_clicked()
{
    strList.clear();
    strList<<"北京"<<"上海"<<"成都"<<"深圳"<<"杭州"<<"广州";
    theModel->setStringList(strList);
}

void Widget::on_btnListAppend_clicked()
{
    strList.append("newItem");
    theModel->setStringList(strList);
    QModelIndex index = theModel->index(strList.size()-1);
    ui->listView->setCurrentIndex(index);
}

void Widget::on_btnListInsert_clicked()
{
    int rowCount = ui->listView->currentIndex().row();
    QModelIndex index = theModel->index(rowCount);
    qDebug("int: %d",rowCount);
    strList.insert(rowCount,"newItem");
    theModel->setStringList(strList);
    ui->listView->setCurrentIndex(index);

}

void Widget::on_btnListDelete_clicked()
{
    int rowCount = ui->listView->currentIndex().row();
    qDebug("int: %d",rowCount);
    strList.removeAt(rowCount);
    theModel->setStringList(strList);
}

void Widget::on_listView_clicked(const QModelIndex &index)
{
    ui->label->setText(QString::asprintf("行: %d, 列: %d",index.row(),index.column()));
}
