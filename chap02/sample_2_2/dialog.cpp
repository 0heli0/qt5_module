#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->radioButton_blue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    QObject::connect(ui->radioButton_red, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    QObject::connect(ui->radioButton_black, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_checkBox_Underline_clicked(bool checked)
{
    QFont font = ui -> plainTextEdit -> font();
    font.setUnderline(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::on_checkBox_Italic_clicked(bool checked)
{
    QFont font = ui -> plainTextEdit -> font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::on_checkBox_3_clicked(bool checked)
{
    QFont font = ui -> plainTextEdit -> font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette plet = ui->plainTextEdit->palette();
    if(ui->radioButton_blue->isChecked()){
        plet.setColor(QPalette::Text,Qt::blue);
    }else if(ui->radioButton_red->isChecked()){
         plet.setColor(QPalette::Text,Qt::red);
    }else{
       plet.setColor(QPalette::Text,Qt::black);
    }

    ui->plainTextEdit->setPalette(plet);
}
