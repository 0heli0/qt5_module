#include "widget.h"
#include "ui_widget.h"

#include <QMetaProperty>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->boxBoy->setProperty("isBoy",true);
    ui->boxGril->setProperty("isGirl",true);

    boy=new QPerson("王小明");
    boy->setProperty("score",95);
    boy->setProperty("age",10);
    boy->setProperty("sex","boy");
    connect(boy,&QPerson::ageChanged,this,&Widget::on_ageChanged);

    girl=new QPerson("李翠花");
    girl->setProperty("score",80);
    girl->setProperty("age",11);
    girl->setProperty("sex","gilr");
    connect(girl,&QPerson::ageChanged,this,&Widget::on_ageChanged);

    connect(ui->boxBoy,SIGNAL(valueChanged(int)),this,SLOT(on_spin_valueChanged(int)));
    connect(ui->boxGril,SIGNAL(valueChanged(int)),this,SLOT(on_spin_valueChanged(int)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_spin_valueChanged(int value)
{
    Q_UNUSED(value);
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if(spinBox->property("isBoy").toBool()){
        boy->setAge(spinBox->value());
    }
    if(spinBox->property("isGirl").toBool()){
        girl->setAge(spinBox->value());
    }

}

void Widget::on_ageChanged(unsigned age)
{
    Q_UNUSED(age);
    QPerson *aPerson=qobject_cast<QPerson *>(sender());
    QString aName = aPerson->property("name").toString();
    QString aSex = aPerson->property("sex").toString();
    unsigned aAge = aPerson->age();
    ui->plainTextEdit->appendPlainText(aName+","+aSex+QString::asprintf(",年龄=%d",aAge));
}

void Widget::on_btnBoyAdd_clicked()
{
    boy->increaseAge();
}

void Widget::on_btnGrilAdd_clicked()
{
    girl->increaseAge();
}

void Widget::on_btnMeta_clicked()
{
    const QMetaObject *meta = girl->metaObject();
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("==元对象信息==\n");
    ui->plainTextEdit->appendPlainText(QString("类命名：%1\n").arg(meta->className()));
    ui->plainTextEdit->appendPlainText("property");
    for(int i=meta->propertyOffset();i<meta->propertyCount();i++){
        QMetaProperty prop = meta->property(i);
        const char* propName=prop.name();
        QString propValue = boy->property(propName).toString();
        ui->plainTextEdit->appendPlainText(QString("属性名称: %1, 属性值: %2").arg(propName).arg(propValue));

    }

    ui->plainTextEdit->appendPlainText("");
    ui->plainTextEdit->appendPlainText("classInfo");
    for(int i=meta->classInfoOffset();i<meta->classInfoCount();i++){
        QMetaClassInfo calssInfo= meta->classInfo(i);
        ui->plainTextEdit->appendPlainText(QString("name: %1, value: %2").arg(calssInfo.name()).arg(calssInfo.value()));

    }

}
