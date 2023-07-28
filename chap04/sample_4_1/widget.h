#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnCalcPrice_clicked();

    void on_btnDec_clicked();

    void on_btnBinary_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
