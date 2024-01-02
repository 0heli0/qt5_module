#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
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


    //选择当前单元格变化时的信号与槽
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &old)
{
    if(!current.isValid()){
        return;
    }
    int row = current.row();
    int cloumn = current.column();
    LabCellPos->setText(QString::asprintf("当前单元格：%d行，%d列",row+1,cloumn+1));

    QStandardItem *item;
    item=theModel->itemFromIndex(current);
    LabCellText->setText("单元格内容:"+item->text());

    QFont font = item->font();
    ui->actFontBold->setChecked(font.bold());



}

void MainWindow::on_actOpen_triggered()
{
    QString curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径
    QString fileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,
                 "数据文件(*.txt);;所有文件(*.*)");
    if (fileName.isEmpty())
        return; //如果未选择文件，退出
}
