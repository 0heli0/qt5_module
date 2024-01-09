#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QWidget>

#endif // MYLINEEDIT_H

class MyLineEdit : public QLineEdit {
    Q_OBJECT
public:
    MyLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

signals:
    void doubleClicked(); // 定义双击信号
};
