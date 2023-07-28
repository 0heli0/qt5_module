#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum treeItemType{itTopItem=1001,itGroupItem,itImageItem};
    enum treeColNum{colItem=0,colItemType=1};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actVisible_toggled(bool arg1);

    void on_dockWidget_topLevelChanged(bool topLevel);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_actFloat_toggled(bool arg1);

    void on_actAddMenu_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
