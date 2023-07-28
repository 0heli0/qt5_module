#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    ui->tBtnListIni->setDefaultAction(ui->actListIni);
    ui->tBtnListClear->setDefaultAction(ui->actListClear);
    ui->tBtnListAdd->setDefaultAction(ui->actListAppend);
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
    ui->tBtnListDel->setDefaultAction(ui->actListDelete);

    ui->tBtnSelAll->setDefaultAction(ui->actSelectAll);
    ui->tBtnSelNone->setDefaultAction(ui->actSelectNone);
    ui->tBtnSelItem->setDefaultAction(ui->actSelectMenu);
    ui->tBtnSelInv->setDefaultAction(ui->actSelInvs);

    QMenu *menu = new QMenu(this);

    menu->addAction(ui->actSelectAll);
    menu->addAction(ui->actSelectNone);
    menu->addAction(ui->actSelInvs);
    ui->actSelectMenu->setMenu(menu);

    ui->mainToolBar->addAction(ui->actSelectMenu);
    ui->tBtnSelItem->setDefaultAction(ui->actSelectMenu);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actQuit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::on_actListIni_triggered()
{
    ui->listWidget->clear();
    QListWidgetItem *aItem;
    QIcon icon(":/images/images/724.bmp");
    bool chk=ui->checkBox->isChecked();

    for(int i=0;i<20;i++){
        QString str = QString::asprintf("Item %d",i+1);
        aItem=new QListWidgetItem(str);
        aItem->setIcon(icon);
        aItem->setCheckState(Qt::Checked);
        if(chk){
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable
                            |Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }else {
            aItem->setFlags(Qt::ItemIsSelectable
                            |Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }
        ui->listWidget->addItem(aItem);

    }
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    int count = ui->listWidget->count();
    for(int i=0;i<count;i++){
        QListWidgetItem *aItem = ui->listWidget->item(i);
        if(checked){
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable
                            |Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }else {
            aItem->setFlags(Qt::ItemIsSelectable
                            |Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }
    }
}
