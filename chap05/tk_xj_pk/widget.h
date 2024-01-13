#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool eventFilter(QObject *watched, QEvent *event);
private:
    void getRequest(const QUrl &requestedUrl);
    void initEventId();
    void labelAlarmStateChange(const QString &alarmStateStr);
    void getObsTypeStr(const QString &obsType);

private slots:
    void on_buttonGD12_clicked();
    void onGetFinished();
    void onPostFinished();

    void on_buttonGD40_clicked();

    void on_buttonGD51_clicked();

    void on_buttonGD58_clicked();

    void on_buttonR12_clicked();

    void on_buttonR40_clicked();

    void on_buttonR51_clicked();

    void on_buttonR58_clicked();

    void on_buttonNSL51_clicked();

    void on_btCancel12_clicked();

    void on_btCancel40_clicked();

    void on_btCancel51_clicked();

    void on_btCancel58_clicked();

    void on_addr_textChanged(const QString &arg1);

    void on_buttonGD12_2_clicked();

    void on_buttonGD12_3_clicked();

    void on_buttonGD40_2_clicked();

    void on_buttonGD40_3_clicked();

    void on_buttonGD51_2_clicked();

    void on_buttonGD51_3_clicked();

    void on_buttonGD58_2_clicked();

    void on_buttonGD58_3_clicked();

    void on_buttonR12_2_clicked();

    void on_buttonR12_3_clicked();

    void on_buttonR40_2_clicked();

    void on_buttonR40_3_clicked();

    void on_buttonR51_2_clicked();

    void on_buttonR51_3_clicked();

    void on_buttonR58_2_clicked();

    void on_buttonR58_3_clicked();

    void on_buttonNSL51_2_clicked();

    void on_buttonNSL51_3_clicked();

private:
    Ui::Widget *ui;
    QString baseUrl;
    QUrl url;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QMap<QString,QString> eventIdMap;
    QString eventId;
    QString alarmDistance;
    QString alarmObstacleType;
    QString obsTypeStr;
    QString position;
    QString pos;
};

#endif // WIDGET_H
