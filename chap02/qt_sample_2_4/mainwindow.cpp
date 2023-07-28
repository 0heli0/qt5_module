#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initUI()
{
    flabCurFile = new QLabel();
    flabCurFile->setMidLineWidth(150);
    flabCurFile->setText("当前文件: ");
    ui->statusBar->addWidget(flabCurFile);

    progressBar = new QProgressBar;
    progressBar->setMinimum(5);
    progressBar->setMaximum(30);
    progressBar->setValue(ui->textEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar);

    spinFontSize = new QSpinBox;
    ui->mainToolBar->addWidget(new QLabel("字体大小"));
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(30);
    ui->mainToolBar->addWidget(spinFontSize);

    comboFont = new QFontComboBox;
    ui->mainToolBar->addWidget(new QLabel("字体"));
    ui->mainToolBar->addWidget(comboFont);
}

void MainWindow::initSingalSlots()
{
    connect(spinFontSize,SIGNAL(valueChanged(int)), this,SLOT(on_spinBoxFontSize_valueChanged(int)));
    connect(comboFont,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(on_comboFont_currentIndexChange(const QString&)));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    setCentralWidget(ui->textEdit);
    initSingalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actBlod_triggered(bool checked)
{
    QTextCharFormat fmt;
    //fmt=ui->textEdit->currentCharFormat();
    if(checked){
        fmt.setFontWeight(QFont::Bold);
    }else {
        fmt.setFontWeight(QFont::Normal);
    }
    ui->textEdit->mergeCurrentCharFormat(fmt);

}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    fmt=ui->textEdit->currentCharFormat();
    ui->actUnderLine->setChecked(fmt.font().underline());
    ui->actBlod->setChecked(fmt.font().bold());
    ui->actItalic->setChecked(fmt.font().italic());
}

void MainWindow::on_spinBoxFontSize_valueChanged(int fontSize)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(fontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar->setValue(fontSize);
}

void MainWindow::on_comboFont_currentIndexChange(const QString &arg)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(arg);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actItalic_triggered(bool checked)
{
    QTextCharFormat fmt;
    //fmt=ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}
