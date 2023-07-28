#include "dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

void Dialog::initUI()
{
    // 添加横向
    ckBoxUnderline = new QCheckBox(tr("Underline"));
    ckBoxItalic = new QCheckBox(tr("Italic"));
    ckBoxBold = new QCheckBox(tr("Bold"));
    QHBoxLayout *HLayout1 = new QHBoxLayout;
    HLayout1->addWidget(ckBoxUnderline);
    HLayout1->addWidget(ckBoxItalic);
    HLayout1->addWidget(ckBoxBold);

    rBtnRed = new QRadioButton(tr("red"));
    rBtnBlue = new QRadioButton(tr("blue"));
    rBtnBlack = new QRadioButton(tr("black"));
    QHBoxLayout *HLayout2 = new QHBoxLayout;
    HLayout2->addWidget(rBtnRed);
    HLayout2->addWidget(rBtnBlue);
    HLayout2->addWidget(rBtnBlack);

     plainTextEdit = new QPlainTextEdit();
     QFont font = plainTextEdit->font();
     font.setPointSize(20);
     plainTextEdit->setFont(font);
     plainTextEdit->setPlainText("Hello World \n\nThis is Arxibye!");

    btnConfirm = new QPushButton(tr("确定"));
    btnCancel = new QPushButton(tr("取消"));
    btnClose = new QPushButton(tr("退出"));
    QHBoxLayout *HLayout3 = new QHBoxLayout;
    HLayout3->addStretch();
    HLayout3->addWidget(btnConfirm);
    HLayout3->addWidget(btnCancel);
    HLayout3->addStretch();
    HLayout3->addWidget(btnClose);

    // 添加纵向
    QVBoxLayout *VLayout = new QVBoxLayout();
    VLayout ->addLayout(HLayout1);
    VLayout ->addLayout(HLayout2);
    VLayout ->addWidget(plainTextEdit);
    VLayout ->addLayout(HLayout3);
    setLayout(VLayout);
}

void Dialog::initSinalSlots()
{
    connect(btnConfirm, SIGNAL(clicked()),this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()),this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()),this, SLOT(close()));
    connect(ckBoxUnderline, SIGNAL(clicked(bool)),this, SLOT(on_checkUnderline(bool)));
    connect(ckBoxItalic, SIGNAL(clicked(bool)),this, SLOT(on_checkItalic(bool)));
    connect(ckBoxBold, SIGNAL(clicked(bool)),this, SLOT(on_checkBlob(bool)));
    connect(rBtnRed, SIGNAL(clicked()),this, SLOT(setTextFontcolor()));
    connect(rBtnBlue, SIGNAL(clicked()),this, SLOT(setTextFontcolor()));
    connect(rBtnBlack, SIGNAL(clicked()),this, SLOT(setTextFontcolor()));
}

void Dialog::on_checkUnderline(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setUnderline(checked);
    plainTextEdit->setFont(font);
}

void Dialog::on_checkItalic(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setItalic(checked);
    plainTextEdit->setFont(font);
}

void Dialog::on_checkBlob(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setBold(checked);
    plainTextEdit->setFont(font);
}

void Dialog::setTextFontcolor()
{
    QPalette palet = plainTextEdit->palette();
    if(rBtnRed->isChecked()){
        palet.setColor(QPalette::Text,Qt::red);
    }else if(rBtnBlue ->isChecked()){
         palet.setColor(QPalette::Text,Qt::blue);
    }else if(rBtnBlack->isChecked()){
         palet.setColor(QPalette::Text,Qt::black);
    } else{
         palet.setColor(QPalette::Text,Qt::black);
    }
    plainTextEdit->setPalette(palet);

}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    initUI();
    initSinalSlots();
}

Dialog::~Dialog()
{

}
