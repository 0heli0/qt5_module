#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formdoc.h"
#include "formtable.h"
#include <QPainter>
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,ui->mainToolBar->height(),this->width(),
                       this->height()-ui->mainToolBar->height()-ui->statusBar->height(),
                       QPixmap(":/icon/images/back2.jpg"));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();//清除所有页面
    ui->tabWidget->tabsClosable(); //Page有关闭按钮，可被关闭
    this->setCentralWidget(ui->tabWidget);
    //    this->setWindowState(Qt::WindowFullScreen); //窗口最大化显示
    //        this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
    //    this->setWindowState(Qt::WindowMinimized); //窗口最大化显示
    this->setAutoFillBackground(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actWidgetInsite_triggered()
{
    FormDoc *formDoc = new FormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    int curIndex = ui->tabWidget->addTab(formDoc,QString::asprintf("Doc %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(curIndex);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (index<0)return;
    if(ui->tabWidget->count() == 1){
        ui->tabWidget->setVisible(false);
    }
    QWidget *tab = ui->tabWidget->widget(index);
    tab->close();
}

void MainWindow::on_actWindowInsite_triggered()
{
    FormTable *formTable = new FormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    int curIndex = ui->tabWidget->addTab(formTable,QString::asprintf("Table %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(curIndex);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_actWindow_triggered()
{
    FormTable* formTable = new FormTable(this);
    //    formChart = new QFormTable(); //无父窗体,在windows任务栏上有显示
    formTable->setAttribute(Qt::WA_DeleteOnClose); //对话框关闭时自动删除对话框对象,用于不需要读取返回值的对话框
    formTable->setWindowTitle("基于QMainWindow的窗口，指定父窗口，关闭时删除");
    //    formChart->setWindowTitle("多实例窗口，指定父窗口");
    formTable->show();
}
