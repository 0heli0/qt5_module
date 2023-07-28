#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QSpinBox>
#include <QFontComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *flabCurFile;
    QProgressBar *progressBar;
    QSpinBox *spinFontSize;
    QFontComboBox *comboFont;

    void initUI();

    void initSingalSlots();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actBlod_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

    void on_spinBoxFontSize_valueChanged(int fontSize);

    void on_comboFont_currentIndexChange(const QString &arg);

    void on_actItalic_triggered(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
