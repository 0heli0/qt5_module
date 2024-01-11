#include "formdoc.h"
#include "ui_formdoc.h"
#include <QToolBar>
#include <QVBoxLayout>

FormDoc::FormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDoc)
{
    ui->setupUi(this);
    //使用UI设计的Actions设计工具栏
    QToolBar* locToolBar = new QToolBar(tr("文档"),this); //创建工具栏
    locToolBar->addAction(ui->actOpen);
    locToolBar->addAction(ui->actFont);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actCut);
    locToolBar->addAction(ui->actCopy);
    locToolBar->addAction(ui->actPaste);
    locToolBar->addAction(ui->actUndo);
    locToolBar->addAction(ui->actRedo);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actClose);

    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //    locToolBar->setAutoFillBackground(true);

    QVBoxLayout *Layout = new QVBoxLayout();
    Layout->addWidget(locToolBar); //设置工具栏和编辑器上下布局
    Layout->addWidget(ui->plainTextEdit);
    Layout->setContentsMargins(2,2,2,2); //减小边框的宽度
    Layout->setSpacing(2);
    this->setLayout(Layout); //设置布局
    //    this->setAutoFillBackground(true); //避免工具栏显示背景图片
}

FormDoc::~FormDoc()
{
    delete ui;
}
