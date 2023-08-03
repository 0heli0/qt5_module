#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addWidget(&labelFileName);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actVisible_toggled(bool arg1)
{
    ui->dockWidget->setVisible(arg1);
}

void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actFloat->setChecked(topLevel);
}

void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actVisible->setChecked(visible);
}

void MainWindow::on_actFloat_toggled(bool arg1)
{
    bool isFloating = ui->dockWidget->isFloating();
    if(isFloating != arg1){
        ui->dockWidget->setFloating(arg1);
    }
}

void MainWindow::on_actAddMenu_triggered()
{
    QString fullname = QFileDialog::getExistingDirectory();
    if(fullname.isEmpty()) return;

    QString dirName = fullname.right(fullname.length()-fullname.lastIndexOf("/")-1);

    if(!ui->treeWidget->currentIndex().isValid()){
        QMessageBox::information(NULL, "提示", "请选择一个目录");
        return;
    }

    QTreeWidgetItem *parItem = ui->treeWidget->currentItem();
    QTreeWidgetItem *item = new QTreeWidgetItem(itGroupItem);

    QIcon icon(":/images/images/122.bmp");
    item->setIcon(colItem, icon);
    item->setText(colItem,dirName);
    item->setText(colItemType,"type:group");
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsAutoTristate|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);

    parItem->addChild(item);
}

void MainWindow::on_actAddFiles_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"选择一个或多个文件","","Images(*.jpg;*.png)");
    if(files.isEmpty()){
        QMessageBox::information(NULL, "提示", "请选择图片");
        return;
    }
    if(!ui->treeWidget->currentIndex().isValid()){
        QMessageBox::information(NULL, "提示", "请选择一个目录");
        return;
    }
    QTreeWidgetItem *parItem;
    QTreeWidgetItem *currentItem = ui->treeWidget->currentItem();

    if(currentItem->type() == itImageItem){
        parItem = currentItem->parent();
    }else{
        parItem = currentItem;
    }

    foreach (auto file, files) {
        QTreeWidgetItem *item = new QTreeWidgetItem(itImageItem);
        QString fileName = file.right(file.length()-file.lastIndexOf("/")-1);
        QIcon icon(":/images/images/804.bmp");
        item->setIcon(colItem, icon);
        item->setText(colItem,fileName);
        item->setText(colItemType,"type:image");
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsAutoTristate|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
        item->setCheckState(colItem,Qt::Checked);
        item->setData(colItem,Qt::UserRole,file);

        parItem->addChild(item);

    }
}



void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(current == NULL) return;
    int type = current->type();

    switch (type) {
    ui->actFitHigh->setEnabled(false);
    ui->actFitWidth->setEnabled(false);
    case itTopItem:
        ui->actAddFiles->setEnabled(true);
        ui->actAddMenu->setEnabled(true);
        ui->actDelItem->setEnabled(false);
        break;
    case itGroupItem:
        ui->actAddFiles->setEnabled(true);
        ui->actAddMenu->setEnabled(true);
        ui->actDelItem->setEnabled(true);
        break;
    case itImageItem:
        ui->actAddFiles->setEnabled(true);
        ui->actAddMenu->setEnabled(false);
        ui->actDelItem->setEnabled(true);
        ui->actFitHigh->setEnabled(true);
        ui->actFitWidth->setEnabled(true);
        ui->actRealSize->setEnabled(true);
        ui->actZoomIn->setEnabled(true);
        ui->actZoomOut->setEnabled(true);
        labelFileName.setText(current->data(colItem,Qt::UserRole).toString());
        curPixmap.load(current->data(colItem,Qt::UserRole).toString());
        on_actFitHigh_triggered();
        break;
    }

}

void MainWindow::on_actFitWidth_triggered()
{
    int width = ui->scrollArea->width();
    int realWidth = curPixmap.width();
    pixRatio = (float)width/realWidth;
    qDebug("p:%f,width:%d realWidth:%d",pixRatio,width,realWidth);
    QPixmap pix = curPixmap.scaledToWidth(width - 30);
    ui->label->setPixmap(pix);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
}


void MainWindow::on_actFitHigh_triggered()
{
    int height = ui->scrollArea->height();
    int realHeight = curPixmap.height();
    pixRatio = (float)height/realHeight;
    qDebug("p:%f,height:%d realHeight:%d",pixRatio,height,realHeight);
    QPixmap pix = curPixmap.scaledToHeight(height - 50);
    ui->label->setPixmap(pix);
}

void MainWindow::on_actScanItem_triggered()
{
    for(int i=0;i<ui->treeWidget->topLevelItemCount();i++){
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        QString str = "*"+item->text(colItem);
        item->setText(colItem,str);
    }

}

void MainWindow::on_actZoomIn_triggered()
{
    pixRatio*=1.2;
    int w = pixRatio*curPixmap.width();
    int h = pixRatio*curPixmap.height();
    qDebug("p:%f,w:%d h:%d",pixRatio,w,h);
    QPixmap pix = curPixmap.scaled(w,h);
    ui->label->setPixmap(pix);
}

void MainWindow::on_actZoomOut_triggered()
{
    pixRatio*=0.8;
    int w = pixRatio*curPixmap.width();
    int h = pixRatio*curPixmap.height();
    qDebug("p:%f,w:%d h:%d",pixRatio,w,h);
    QPixmap pix = curPixmap.scaled(w,h);
    ui->label->setPixmap(pix);
}

void MainWindow::on_actRealSize_triggered()
{
    pixRatio = 1;
    int realHeight = curPixmap.height();
    int realWidth = curPixmap.width();
    qDebug("realHeight:%f,realWidth:%d",realHeight,realWidth);
    ui->label->setPixmap(curPixmap);
}
