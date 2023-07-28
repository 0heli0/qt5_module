#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
