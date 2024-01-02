#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    <QLabel>
#include    <QStandardItemModel>
#include    <QItemSelectionModel>

#define     FixedColumnCount    6       //文件固定6列

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //用于状态栏的信息显示
    QLabel  *LabCurFile;  //当前文件
    QLabel  *LabCellPos;    //当前单元格行列号
    QLabel  *LabCellText;   //当前单元格内容

    QStandardItemModel  *theModel;//数据模型
    QItemSelectionModel *theSelection;//Item选择模型

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &old);

    void on_actOpen_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
