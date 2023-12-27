#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    QStringListModel   *theModel; //数据模型
    QStringList strList;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnTextImport_clicked();

    void on_btnTextClear_clicked();

    void on_btnListClear_clicked();

    void on_btnIniList_clicked();

    void on_btnListAppend_clicked();

    void on_btnListInsert_clicked();

    void on_btnListDelete_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
