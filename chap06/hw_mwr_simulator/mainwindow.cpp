#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QtNetwork>
#include <QDebug>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);  //新建水平分割器
    this->setCentralWidget(splitter);
    QString style = QString("QSplitter::handle { background-color: rgb(179, 179, 179); }"); //分割线的颜色

    splitter->setStyleSheet(style);
    splitter->setHandleWidth(2);//分割线的宽度
    splitter->setChildrenCollapsible(false);//不允许把分割出的子窗口拖小到0，最小值被限定为sizeHint或maxSize/minSize

    splitter->addWidget(ui->groupBoxLeft);//把ui中拖出的各个控件拿走，放到分割器里面
    splitter->addWidget(ui->groupBoxRight);


    quint8 xt[8]={0xFD, 0xFD,0xFD,0xFD,
                  0x00,0x01,0x05,0x20};
    quint16 len = sizeof(xt);
    quint16 xxt=crc16Util.CRC16(xt,len);
    ui->textCommandInfo->append(QString::asprintf("启动成功:")+QString::number(xxt,10));

    initComboIp();//本机IP
    tcpServer=new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::initComboIp()
{//获取本机IPv4地址
    QString hostName=QHostInfo::localHostName();//本地主机名
    QHostInfo   hostInfo=QHostInfo::fromName(hostName);
    QString ip = "";
    QList<QHostAddress> addList=hostInfo.addresses();//

    if (!addList.isEmpty()){
        qDebug()<<QString::asprintf("size:")<<QString::number(addList.count(),10);
        for (int i=0;i<addList.count();i++)
        {
            QHostAddress aHost=addList.at(i);
            qDebug()<<aHost.toString();
            if (QAbstractSocket::IPv4Protocol==aHost.protocol())
            {
                ui->comboIp->addItem(aHost.toString());
            }

        }
    }

    return ip;
}

void MainWindow::onNewConnection()
{
    //    ui->plainTextEdit->appendPlainText("有新连接");
    qDebug()<<QString("开启端口号连接");
    tcpSocket = tcpServer->nextPendingConnection(); //创建socket

    connect(tcpSocket, SIGNAL(connected()),
            this, SLOT(onClientConnected()));

    onClientConnected();//
    qDebug()<<QString("客户端连接");
    connect(tcpSocket, SIGNAL(disconnected()),
            this, SLOT(onClientDisconnected()));

    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    onSocketStateChange(tcpSocket->state());

    connect(tcpSocket,SIGNAL(readyRead()),
            this,SLOT(onSocketReadyRead()));
}

void MainWindow::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    //socket状态变化时
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        ui->textCommandInfo->append("scoket状态：UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        ui->textCommandInfo->append("scoket状态：HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        ui->textCommandInfo->append("scoket状态：ConnectingState");
        break;

    case QAbstractSocket::ConnectedState:
        ui->textCommandInfo->append("scoket状态：ConnectedState");
        break;

    case QAbstractSocket::BoundState:
        ui->textCommandInfo->append("scoket状态：BoundState");
        break;

    case QAbstractSocket::ClosingState:
        ui->textCommandInfo->append("scoket状态：ClosingState");
        break;

    case QAbstractSocket::ListeningState:
        ui->textCommandInfo->append("scoket状态：ListeningState");
    }
}

void MainWindow::onClientConnected()
{
    //客户端接入时
    ui->textCommandInfo->append("**client socket connected");
    ui->textCommandInfo->append("**peer address:"+
                                tcpSocket->peerAddress().toString());
    ui->textCommandInfo->append("**peer port:"+
                                QString::number(tcpSocket->peerPort()));
}

void MainWindow::onClientDisconnected()
{
    //客户端断开连接时
    ui->textCommandInfo->append("**client socket disconnected");
    tcpSocket->deleteLater();
    //    deleteLater();//QObject::deleteLater();
}

void MainWindow::onSocketReadyRead()
{//读取缓冲区行文本
    //    QStringList   lines;
    //    while(tcpSocket->canReadLine())
    //        ui->textCommandInfo->append("[in] "+tcpSocket->readLine());
    //        lines.append(clientConnection->readLine());
    QByteArray data = tcpSocket->readAll();

    writeData(data,"D:/aa.txt");

    //    ui->textCommandInfo->append("[in] "+QString::fromUtf8(data));
}

void MainWindow::writeData(const QByteArray &qBa, const QString &fileName){
    QFile file(fileName);
    if (file.open(QIODevice::Append|QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_0); // 设置数据流版本
        //            out << data; // 将 QByteArray 写入数据流
        out.writeRawData(qBa.data(),qBa.size());
        file.close();
        //            ui->textCommandInfo->append(QString::asprintf("数据写入成功"));
    } else {
        // 处理文件打开失败的情况
        ui->textCommandInfo->append(QString::asprintf("数据写入失败"));
    }
}


void MainWindow::on_btnTcpListener_clicked(bool checked)
{
    QString isChecked = checked?"true":"false";
    qDebug()<<isChecked;
    if(checked){
        QString IP=ui->comboIp->currentText();//IP地址
        bool ok;
        quint16 port = ui->tpcPort->text().toInt(&ok,10);//端口
        QHostAddress addr(IP);
        tcpServer->listen(addr,port);
        ui->textCommandInfo->append("开启监听--->"+tcpServer->serverAddress().toString()+":"+QString::number(tcpServer->serverPort(),10));
        tcpServer->listen(addr,port);//

        ui->btnTcpListener->setText("停止监听");
        ui->btnTcpListener->setStyleSheet("color:red;");

    }else {
        if (tcpServer->isListening()) //tcpServer正在监听
        {
            tcpServer->close();//停止监听
            ui->textCommandInfo->append("监听状态：已停止监听");
        }
        ui->btnTcpListener->setText("开始监听");
        ui->btnTcpListener->setStyleSheet("color:black;");
    }
}
