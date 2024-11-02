#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include<QDebug>
#include<QTcpSocket>
#include<QFile>
#include <QDateTime>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetDevieStatus();
    void setDevicePixmp();
    void updateDeviceStatus(const QString &command); // 更新设备状态
    void Show_Text(QString humi, QString temp, QString val);
    void updateDate(QString humi, QString temp, QString val);
    void saveDataToFile(const QString& humi, const QString& temp, const QString& val);
private slots:
    void on_pushButton_clicked();
    void clientConnect();
    void Readyread();
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString,QString> deviceStatus;
    QTcpSocket *clientSocket;
    char BUF[2048];

};
#endif // MAINWINDOW_H
