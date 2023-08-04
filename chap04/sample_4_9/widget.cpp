#include "widget.h"
#include "ui_widget.h"

#include <QDate>

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

void Widget::creatItemsARow(int rowNo, QString name, QString sex, QDate birth, QString nation,  bool isParty, int score)
{
    unsigned StudId = 2000;
    QTableWidgetItem *item;
    item = new QTableWidgetItem(name,ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    item->setData(Qt::UserRole,StudId++);
    ui->tableWidget->setItem(rowNo,colName,item);

    item = new QTableWidgetItem(sex,ctSex);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    QIcon icon;
    if(sex=="男"){
        icon.addFile(":icon/images/728.bmp");
    }else {
     icon.addFile(":icon/images/718.bmp");
    }
    item->setIcon(icon);
    ui->tableWidget->setItem(rowNo,colSex,item);

    item = new QTableWidgetItem(birth.toString("yyyy-MM-dd"),ctBirth);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,colBirth,item);

    item = new QTableWidgetItem(nation,ctNation);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,colNation,item);

    item = new QTableWidgetItem("党员",ctIsParty);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    item->setBackgroundColor(Qt::yellow);
    if(isParty){
        item->setCheckState(Qt::Checked);
    }else {
        item->setCheckState(Qt::Unchecked);
    }

    ui->tableWidget->setItem(rowNo,colIsParty,item);

    item = new QTableWidgetItem(QString::number(score),ctScore);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,colScore,item);
}

void Widget::on_btnSetTableHeader_clicked()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"姓 名"<<"性 别"<<"出生日期"<<"民 族"<<"分 数"<<"是否党员";
    ui->tableWidget->setColumnCount(headerText.count());

    for(int i=0;i< ui->tableWidget->columnCount();i++){
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = ui->tableWidget->font();
        font.setBold(true);
        font.setPointSize(12);
        headerItem->setFont(font);
        headerItem->setTextColor(Qt::red);
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }
}

void Widget::on_btnSetRowNum_clicked()
{
    ui->tableWidget->setRowCount(ui->sBRowNum->value());
    ui->tableWidget->setAlternatingRowColors(ui->chkColer->isChecked());
}

void Widget::on_chkColer_clicked(bool checked)
{
    ui->tableWidget->setAlternatingRowColors(checked);
}

void Widget::on_btnInitTableData_clicked()
{
    ui->tableWidget->clearContents();

    QString name,sex;
    bool isParty = false;
    QDate brith;
    brith.setDate(1991,2,22);
     for(int i=0;i< ui->tableWidget->rowCount();i++){
        name = QString::asprintf("学生%d",i);
        sex = i%2==0?"男":"女";
        isParty = !isParty;
        creatItemsARow(i,name, sex, brith,"汉族",isParty,80+i);
     }
}

void Widget::on_btnAutoRow_clicked()
{
    ui->tableWidget->resizeRowsToContents();
}

void Widget::on_btnAutoCol_clicked()
{
    ui->tableWidget->resizeColumnsToContents();
}
