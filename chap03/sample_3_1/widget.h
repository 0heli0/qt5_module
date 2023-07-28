#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qperson.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPerson *boy;
    QPerson *girl;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    void on_ageChanged(unsigned age);

private slots:
    void on_btnBoyAdd_clicked();
    void on_btnGrilAdd_clicked();
    void on_btnMeta_clicked();
    void on_spin_valueChanged(int value);
};

#endif // WIDGET_H
