#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QPlainTextEdit>

class Dialog : public QDialog
{
    Q_OBJECT

private:
    QCheckBox *ckBoxUnderline;
    QCheckBox *ckBoxItalic;
    QCheckBox *ckBoxBold;

    QRadioButton *rBtnRed;
    QRadioButton *rBtnBlue;
    QRadioButton *rBtnBlack;

    QPushButton *btnConfirm;
    QPushButton *btnCancel;
    QPushButton *btnClose;

    QPlainTextEdit *plainTextEdit;

    void initUI();

    void initSinalSlots();

private slots:
    void on_checkUnderline(bool checked);
    void on_checkItalic(bool checked);
    void on_checkBlob(bool checked);

    void setTextFontcolor();

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
};

#endif // DIALOG_H
