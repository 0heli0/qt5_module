#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "crc16util.h"
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnTcpListener_clicked(bool checked);

//自定义槽函数
    void    onNewConnection();//监听端口号，开启服务
    void    onSocketStateChange(QAbstractSocket::SocketState socketState);
    void    onClientConnected(); //Client Socket connected
    void    onClientDisconnected();//Client Socket disconnected
    void    onSocketReadyRead();//读取socket传入的数据

private:
    Ui::MainWindow *ui;

    CRC16Util crc16Util;
    QTcpServer *tcpServer; //TCP服务器
    QTcpSocket *tcpSocket;//TCP通讯的Socket

    QString initComboIp();//获取本机IP地址
    void writeData(const QByteArray &data, const QString &fileName);


};

#endif // MAINWINDOW_H
