class MyLineEdit : public QLineEdit {
    Q_OBJECT
public:
    MyLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

signals:
    void doubleClicked(); // 定义双击信号
};
