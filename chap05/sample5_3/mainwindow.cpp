#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
void MainWindow::iniModelFromStringList(QStringList& strList)
{
    int row = strList.count();
    theModel->setRowCount(row-1);
    // 写入表头
    QString headerStr = strList.at(0);
    QStringList headerList=headerStr.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList); //设置表头文字
    QStandardItem *item;
    //写入内容
    for(int i=1;i<row;i++){
        QString rowStr = strList.at(i);
        QStringList rowList = rowStr.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for(int j=0;j<FixedColumnCount;j++){
            item = new QStandardItem(rowList.at(j));
            if(j==FixedColumnCount-1){
                item->setCheckable(true);
                item->setCheckState(Qt::Checked);
                if(rowList.at(j)=="0")item->setCheckState(Qt::Unchecked);
            }
            theModel->setItem(i-1,j,item);
        }


    }
}

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
                                                  "#数据文件(*.txt);;所有文件(*.*)");
    if (fileName.isEmpty())
        return; //如果未选择文件，退出
    // 获取文件内容
    QStringList fileContentList;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream textStream(&file);
        ui->plainTextEdit->clear();
        while (!textStream.atEnd()) {
            QString lineStr = textStream.readLine();
            fileContentList.append(lineStr);
            ui->plainTextEdit->appendPlainText(lineStr);
        }
    }

    file.close();
    this->LabCurFile->setText("当前文件："+fileName);
    ui->actAppend->setEnabled(true); //更新Actions的enable属性
    ui->actInsert->setEnabled(true);
    ui->actDelete->setEnabled(true);
    ui->actSave->setEnabled(true);
    iniModelFromStringList(fileContentList);

}

void MainWindow::on_actSave_triggered()
{

}
