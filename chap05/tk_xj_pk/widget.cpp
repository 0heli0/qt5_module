#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include "mylineedit.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString addr = ui->addr->text();
    if(!addr.isNull()&&!addr.isEmpty()){
        baseUrl ="http://"+addr+"/push/alarm/tk";
    }else{
        baseUrl ="http://127.0.0.1:9180/push/alarm/tk";
    }
    manager = new QNetworkAccessManager(this);
    initEventId();

    QGraphicsOpacityEffect *op1 = new QGraphicsOpacityEffect();
    op1->setOpacity(0);
    ui->btH1->setGraphicsEffect(op1);
    QGraphicsOpacityEffect *op2 = new QGraphicsOpacityEffect();
    op2->setOpacity(0);
    ui->btH2->setGraphicsEffect(op2);
    QGraphicsOpacityEffect *op3 = new QGraphicsOpacityEffect();
    op3->setOpacity(0);
    ui->btH3->setGraphicsEffect(op3);

    ui->addr->installEventFilter(this);
    QString initText;
    on_addr_textChanged(initText);
    ui->addr->setText(baseUrl);
    ui->addr->setReadOnly(true);

}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(qobject_cast<QLineEdit*>(watched) == ui->addr && event->type() == QEvent::MouseButtonDblClick){
        qDebug() << "Double click detected on QLineEdit";
        ui->addr->setReadOnly(false);
    }
}

void Widget::getRequest(const QUrl &requestedUrl)
{
    url = requestedUrl;
    QNetworkRequest request(url);
    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &Widget::onGetFinished);
}

void Widget::initEventId()
{
    ///-# 时间   时间戳 互相转化
    QDateTime time = QDateTime::currentDateTime();
    qDebug() << time.toString("yyyy-MM-dd hh:mm:ss.zzz");  ///< 时间
    qint64 time_t1 = QDateTime::currentSecsSinceEpoch();   ///< 精确到秒  时间戳10位
    qDebug() << time_t1;
    eventId = QString::number(time_t1);;
}


void Widget::onGetFinished()
{
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        qDebug() << "GET Response:" << response;
    } else {
        qDebug() << "GET Error:" << reply->errorString();
    }
    reply->deleteLater();
    reply = nullptr;
}

void Widget::onPostFinished()
{
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        qDebug() << "POST Response:" << response;
    } else {
        qDebug() << "POST Error:" << reply->errorString();
    }
    reply->deleteLater();
}

/*
 * 固定障碍物12
 */
void Widget::on_buttonGD12_clicked()
{
    QString a = baseUrl+"?isAlarm=1&obstacleType=1&distance=40&eventId="+eventId;
    qDebug() << "url:" << a;
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=1&distance=12&eventId="+eventId));
}

/*
 * 固定障碍物40
 */
void Widget::on_buttonGD40_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=1&distance=40&eventId="+eventId));
}

/*
 * 固定障碍物51
 */
void Widget::on_buttonGD51_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=1&distance=51&eventId="+eventId));

}

/*
 * 固定障碍物58
 */
void Widget::on_buttonGD58_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=1&distance=58&eventId="+eventId));

}

/*
 * 人12
 */
void Widget::on_buttonR12_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=2&distance=12&eventId="+eventId));

}

/*
 * 人40
 */
void Widget::on_buttonR40_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=2&distance=40&eventId="+eventId));
}

/*
 * 人51
 */
void Widget::on_buttonR51_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=2&distance=51&eventId="+eventId));
}

/*
 * 人58
 */
void Widget::on_buttonR58_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=2&distance=58&eventId="+eventId));
}

/*
 * 泥石流51
 */
void Widget::on_buttonNSL51_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=3&distance=51&eventId="+eventId));
}

/*
 * 取消报警12
 */
void Widget::on_btCancel12_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=2&obstacleType=0&distance=12&eventId="+eventId));
    initEventId();
}

/*
 * 取消报警40
 */
void Widget::on_btCancel40_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=2&obstacleType=0&distance=40&eventId="+eventId));
    initEventId();
}

/*
 * 取消报警51
 */
void Widget::on_btCancel51_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=2&obstacleType=0&distance=51&eventId="+eventId));
    initEventId();
}

/*
 * 取消报警58
 */
void Widget::on_btCancel58_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=2&obstacleType=0&distance=58&eventId="+eventId));
    initEventId();
}

void Widget::on_addr_textChanged(const QString &arg1)
{
    QString addr = arg1;
    if(!addr.isNull()&&!addr.isEmpty()){
        baseUrl ="http://"+addr+"/push/alarm/tk";
    }else{
        baseUrl ="http://127.0.0.1:9180/push/alarm/tk";
        ui->addr->setReadOnly(true);
    }

}

