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
    baseUrl ="http://127.0.0.1:9180/push/alarm/tk";
    manager = new QNetworkAccessManager(this);
    initEventId();
    obsTypeStr = "无";

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

void Widget::labelAlarmStateChange(const QString &alarmStateStr)
{
    ui->label_alarm->setText(alarmStateStr);
}

void Widget::getObsTypeStr(const QString &obsType)
{
    if(alarmObstacleType=="1"){
        obsTypeStr="固定障碍物";
    }else if(alarmObstacleType=="2"){
        obsTypeStr="人";
    }else if(alarmObstacleType=="3"){
        obsTypeStr="泥石流";
    }
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
    QString a = baseUrl+"?isAlarm=1&obstacleType=1&distance=12&position=1&eventId="+eventId;
    qDebug() << "url:" << a;
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=1&distance=12&position=1&eventId="+eventId));
    alarmDistance = "12";
    alarmObstacleType = "1";
    pos = "1";
    position = "左固定障碍物";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 固定障碍物40
 */
void Widget::on_buttonGD40_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=1&distance=40&position=1&eventId="+eventId));
    alarmDistance = "40";
    alarmObstacleType = "1";
    getObsTypeStr(alarmObstacleType);
    position = "左固定障碍物";
    pos = "1";
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 固定障碍物52
 */
void Widget::on_buttonGD51_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=1&distance=52&position=1&eventId="+eventId));
    alarmDistance = "52";
    alarmObstacleType = "1";
    position = "左固定障碍物";
    pos = "1";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);

}

/*
 * 固定障碍物58
 */
void Widget::on_buttonGD58_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=1&distance=58&position=1&eventId="+eventId));
    alarmDistance = "58";
    alarmObstacleType = "1";
    position = "左固定障碍物";
    pos = "1";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 人12
 */
void Widget::on_buttonR12_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=2&distance=12&position=1&eventId="+eventId));
    alarmDistance = "12";
    alarmObstacleType = "2";
    pos = "1";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型：人";
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 人40
 */
void Widget::on_buttonR40_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=2&distance=40&position=1&eventId="+eventId));
    alarmDistance = "40";
    alarmObstacleType = "2";
    pos = "1";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型：人";
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 人52
 */
void Widget::on_buttonR51_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=2&distance=52&position=1&eventId="+eventId));
    alarmDistance = "52";
    alarmObstacleType = "2";
    pos = "1";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型：人";
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 人58
 */
void Widget::on_buttonR58_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=2&distance=58&position=1&eventId="+eventId));
    alarmDistance = "58";
    alarmObstacleType = "2";
    pos = "1";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型：人";
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 泥石流52
 */
void Widget::on_buttonNSL51_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType=3&distance=52&position=1&eventId="+eventId));
    alarmDistance = "52";
    alarmObstacleType = "3";
    pos = "1";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型：泥石流";
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 取消报警12
 */
void Widget::on_btCancel12_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=2&obstacleType="+alarmObstacleType+"&distance=12&position="+pos+"&eventId="+eventId));
    initEventId();
    alarmDistance = "12";
    QString alarmStateStr = "报警状态：报警取消, 报警距离："+alarmDistance+"米, 障碍物类型："+obsTypeStr;
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 取消报警40
 */
void Widget::on_btCancel40_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=2&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    initEventId();
    alarmDistance = "40";
    QString alarmStateStr = "报警状态：报警取消, 报警距离："+alarmDistance+"米, 障碍物类型："+obsTypeStr;
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 取消报警51
 */
void Widget::on_btCancel51_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=2&obstacleType="+alarmObstacleType+"&distance=52&position="+pos+"&eventId="+eventId));
    initEventId();
    alarmDistance = "52";
    QString alarmStateStr = "报警状态：报警取消, 报警距离："+alarmDistance+"米, 障碍物类型："+obsTypeStr;
    labelAlarmStateChange(alarmStateStr);
}

/*
 * 取消报警58
 */
void Widget::on_btCancel58_clicked()
{
    getRequest(QUrl(baseUrl+"?isAlarm=2&obstacleType="+alarmObstacleType+"&distance=58&position="+pos+"&eventId="+eventId));
    initEventId();
    alarmDistance = "58";
    QString alarmStateStr = "报警状态：报警取消, 报警距离："+alarmDistance+"米, 障碍物类型："+obsTypeStr;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_addr_textChanged(const QString &arg1)
{
    QString addr = arg1;
    if(!addr.isNull()&&!addr.isEmpty()){
        baseUrl =addr;
    }else{
        baseUrl ="http://127.0.0.1:9180/push/alarm/tk";
        ui->addr->setReadOnly(true);
    }

}
// 固定障碍物
void Widget::on_buttonGD12_2_clicked()
{
    alarmDistance = "12";
    alarmObstacleType = "1";
    position = "中固定障碍物";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));    alarmDistance = "40";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonGD12_3_clicked()
{
    alarmDistance = "12";
    alarmObstacleType = "1";
    position = "右固定障碍物";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));    alarmDistance = "40";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonGD40_2_clicked()
{
    alarmDistance = "40";
    alarmObstacleType = "1";
    position = "中固定障碍物";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));    alarmDistance = "40";
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonGD40_3_clicked()
{

    alarmDistance = "40";
    alarmObstacleType = "1";
    position = "右固定障碍物";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonGD51_2_clicked()
{
    alarmDistance = "52";
    alarmObstacleType = "1";
    position = "中固定障碍物";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonGD51_3_clicked()
{
    alarmDistance = "52";
    alarmObstacleType = "1";
    position = "右固定障碍物";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonGD58_2_clicked()
{
    alarmDistance = "58";
    alarmObstacleType = "1";
    position = "中固定障碍物";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonGD58_3_clicked()
{
    alarmDistance = "58";
    alarmObstacleType = "1";
    position = "右固定障碍物";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

// 人
void Widget::on_buttonR12_2_clicked()
{
    alarmDistance = "12";
    alarmObstacleType = "2";
    position = "中人";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonR12_3_clicked()
{
    alarmDistance = "12";
    alarmObstacleType = "2";
    position = "右人";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonR40_2_clicked()
{
    alarmDistance = "40";
    alarmObstacleType = "2";
    position = "中人";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonR40_3_clicked()
{
    alarmDistance = "40";
    alarmObstacleType = "2";
    position = "右人";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonR51_2_clicked()
{
    alarmDistance = "52";
    alarmObstacleType = "2";
    position = "中人";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonR51_3_clicked()
{
    alarmDistance = "52";
    alarmObstacleType = "2";
    position = "右人";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonR58_2_clicked()
{
    alarmDistance = "58";
    alarmObstacleType = "2";
    position = "中人";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonR58_3_clicked()
{
    alarmDistance = "58";
    alarmObstacleType = "2";
    position = "右人";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

// 泥石流

void Widget::on_buttonNSL51_2_clicked()
{
    alarmDistance = "52";
    alarmObstacleType = "3";
    position = "中间泥石流";
    pos = "2";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}

void Widget::on_buttonNSL51_3_clicked()
{
    alarmDistance = "52";
    alarmObstacleType = "3";
    position = "右泥石流";
    pos = "3";
    getRequest(QUrl(baseUrl+"?isAlarm=1&obstacleType="+alarmObstacleType+"&distance="+alarmDistance+"&position="+pos+"&eventId="+eventId));
    getObsTypeStr(alarmObstacleType);
    QString alarmStateStr = "报警状态：报警, 报警距离："+alarmDistance+"米, 障碍物类型："+position;
    labelAlarmStateChange(alarmStateStr);
}
