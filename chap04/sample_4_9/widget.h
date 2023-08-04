#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private:
    void creatItemsARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isParty, int score);
    enum CellType{ctName = 1000,ctSex,ctBirth,ctNation,ctIsParty,ctScore};
    enum FileColNum{colName = 0,colSex,colBirth,colNation,colScore,colIsParty};

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_btnSetTableHeader_clicked();

    void on_btnSetRowNum_clicked();

    void on_chkColer_clicked(bool checked);

    void on_btnInitTableData_clicked();

    void on_btnAutoRow_clicked();

    void on_btnAutoCol_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
