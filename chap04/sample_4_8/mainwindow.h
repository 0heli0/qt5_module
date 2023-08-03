#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTreeWidgetItem>
#include <QPixmap>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum treeItemType{itTopItem=1001,itGroupItem,itImageItem};
    enum treeColNum{colItem=0,colItemType=1};
    QPixmap curPixmap;
    QLabel labelFileName;
    float pixRatio;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actVisible_toggled(bool arg1);

    void on_dockWidget_topLevelChanged(bool topLevel);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_actFloat_toggled(bool arg1);

    void on_actAddMenu_triggered();

    void on_actAddFiles_triggered();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actFitWidth_triggered();

    void resizeEvent(QResizeEvent *event);


    void on_actFitHigh_triggered();

    void on_actScanItem_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actRealSize_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
