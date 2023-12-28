#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建状态栏组件
    LabCurFile = new QLabel("当前文件：",this);
    LabCurFile->setMinimumWidth(200);

    LabCellPos = new QLabel("当前单元格：",this);
    LabCellPos->setMinimumWidth(180);
//    LabCellPos->setAlignment(Qt::AlignHCenter);

    LabCellText = new QLabel("单元格内容：",this);
    LabCellText->setMinimumWidth(150);

    theModel = new QStandardItemModel(10,FixedColumnCount,this); //数据模型
    theSelection = new QItemSelectionModel(theModel);// Item选择模型
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->statusBar->addWidget(LabCurFile);
    ui->statusBar->addWidget(LabCellPos);
    ui->statusBar->addWidget(LabCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}
