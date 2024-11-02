#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetDevieStatus();
    clientSocket = new QTcpSocket;//创建套接字
    clientSocket->connectToHost("192.168.4.1",8888);//连接服务器
    connect(clientSocket,SIGNAL(connected()),this,SLOT(clientConnect()));
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(Readyread()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clientConnect()
{
    qDebug()<<"连接服务器成功";
}

void MainWindow::Readyread()
{
    while (clientSocket->bytesAvailable() > 0) {
        QByteArray ret = clientSocket->readAll(); // 读取所有可用字节
        qDebug() << "收到信息" << ret;

        QByteArray retCStr = ret.trimmed(); // 去除多余空格
        QString str = QString::fromUtf8(retCStr);
        QStringList token = str.split(":");

        if(token.size() >=3)
        {
            QString humi = token.at(0);
            QString temp = token.at(1);
            QString val = token.at(2);
            qDebug() << "湿度:" << humi << "温度:" << temp << "光照强度:" << val;
            updateDate(humi,temp,val);
            Show_Text(humi,temp,val);
            saveDataToFile(humi,temp,val);
        }


    }

}

void MainWindow::SetDevieStatus()
{
    deviceStatus.insert("电灯","关闭");
    deviceStatus.insert("警报","关闭");
    deviceStatus.insert("风扇","关闭");
}

void MainWindow::setDevicePixmp()//更新设备图片
{
    // 更新电灯图标
    if (deviceStatus["电灯"] == "打开") {
        ui->label_4->setStyleSheet("border-image: url(:/tu/灯光全开.png);");
        ui->pushButton->setStyleSheet("border-image: url(:/tu/开关按钮 (1).png);");
    } else {
        ui->label_4->setStyleSheet("border-image: url(:/tu/关灯.png);");
        ui->pushButton->setStyleSheet("border-image: url(:/tu/开关按钮.png);");
    }
    //更新风扇图片
    if (deviceStatus["风扇"] == "打开") {
        ui->label_7->setStyleSheet("border-image: url(:/tu/排风机-开.png);");
        ui->pushButton_3->setStyleSheet("border-image: url(:/tu/开关按钮 (1).png);");
    } else {
        ui->label_7->setStyleSheet("border-image: url(:/tu/排风机.png);");
        ui->pushButton_3->setStyleSheet("border-image: url(:/tu/开关按钮.png);");
    }
    //更新警报
    if (deviceStatus["警报"] == "打开") {
        ui->label_6->setStyleSheet("border-image: url(:/tu/报警1.png);");
        ui->pushButton_2->setStyleSheet("border-image: url(:/tu/开关按钮 (1).png);");
    } else {
        ui->label_6->setStyleSheet("border-image: url(:/tu/报警.png);");
        ui->pushButton_2->setStyleSheet("border-image: url(:/tu/开关按钮.png);");
    }
}

void MainWindow::updateDeviceStatus(const QString &command)
{
    static const QMap<QString, QString> commandToDevice = {
        {"打开警报", "警报"},
        {"关闭警报", "警报"},
        {"打开电灯", "电灯"},
        {"关闭电灯", "电灯"},
        {"打开风扇", "风扇"},
        {"关闭风扇", "风扇"}
    };

    if (commandToDevice.contains(command)) {
        QString device = commandToDevice[command];
        QString action = command.startsWith("打开") ? "打开" : "关闭"; // 根据命令决定动作
        deviceStatus[device] = action; // 更新设备状态
        qDebug() << device << action; // 打印结果
    } else {
        qDebug() << "未知命令：" << command; // 处理未知命令
    }
    setDevicePixmp();
}

void MainWindow::Show_Text(QString humi, QString temp, QString val)
{
    QString styleSheet = "QLabel {"
                         "font-size: 20px;"           // 字体大小
                         "font-weight: bold;"         // 字体加粗
                         "color: #FF0000;"            // 字体颜色，红色
                         "}";

    QStringList labelTextList; // 用于存储所有提示信息

    // 检查温度
    if (temp.toInt() >= 30) {
        labelTextList << "当前温度过高，请及时降温";
    }

    // 检查湿度
    if (humi.toInt() >= 80) {
        labelTextList << "当前湿度过高，请及时降低湿度";
    }

    if (temp.toInt() < 30) {
        labelTextList.removeAll("当前温度过高，请及时降温");
    }

    if (humi.toInt() < 80) {
        labelTextList.removeAll("当前湿度过高，请及时降低湿度");
    }

    if(val.toInt() >=3000){
        labelTextList<<"当前光照太低，请加大照明";
        ui->label_3->setStyleSheet("border-image: url(:/tu/光照.png);");
    }
    if(val.toInt() <3000)
    {
        labelTextList.removeAll("当前光照太低，请加大照明");
        ui->label_3->setStyleSheet("border-image: url(:/tu/光照 (2).png);");
        if(val.toInt()<1000)
        {
            ui->label_3->setStyleSheet("border-image: url(:/tu/光照 (1).png);");
        }
    }
    ui->label_5->setText(labelTextList.join("\n"));
    ui->label_5->setStyleSheet(styleSheet);
}

void MainWindow::updateDate(QString humi, QString temp, QString val)
{
    ui->label_wd_sj->setText(temp);
    ui->label_sd_sj->setText(humi);
    ui->label_gz_sj->setText(val);

    // 设置样式
    QString styleSheet = "QLabel {"
                         "font-size: 20px;"           // 字体大小
                         "font-weight: bold;"         // 字体加粗
                         "color: #2E8BC0;"            // 字体颜色，使用16进制颜色值
                         "background-color: #F0F8FF;" // 背景颜色
                         "border: 1px solid #2E8BC0;" // 边框
                         "padding: 5px;"              // 内边距
                         "border-radius: 5px;"        // 圆角边框
                         "}";

    // 应用样式
    ui->label_wd_sj->setStyleSheet(styleSheet);
    ui->label_sd_sj->setStyleSheet(styleSheet);
    ui->label_gz_sj->setStyleSheet(styleSheet);
}

void MainWindow::saveDataToFile(const QString& humi, const QString& temp, const QString& val)
{
    QFile file("data_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        out.setCodec("UTF-8");
        QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss -");
        out <<currentTime<< tr("湿度: ") << humi << tr(", 温度: ") << temp << tr(", 光照强度: ") << val << "\n";
        file.close(); // 关闭文件
    } else {
        qDebug() << "无法打开文件以保存数据.";
    }
}




void MainWindow::on_pushButton_clicked()//开关灯按钮
{
    if(deviceStatus["电灯"] == "打开")
    {
        qDebug()<<"关闭电灯";
        updateDeviceStatus("关闭电灯");
        clientSocket->write("2");
    }else{
        qDebug()<<"打开电灯";
        updateDeviceStatus("打开电灯");
        clientSocket->write("7");
    }
}

void MainWindow::on_pushButton_3_clicked()//风扇按钮
{
    if(deviceStatus["风扇"] == "打开")
    {
        qDebug()<<"关闭风扇";
        updateDeviceStatus("关闭风扇");
        clientSocket->write("4");
    }else{
        qDebug()<<"打开风扇";
        updateDeviceStatus("打开风扇");
        clientSocket->write("3");
    }
}

void MainWindow::on_pushButton_2_clicked()//警报按钮
{
    if(deviceStatus["警报"] == "打开")
    {
        qDebug()<<"关闭警报";
        updateDeviceStatus("关闭警报");
        clientSocket->write("6");
    }else{
        qDebug()<<"打开警报";
        updateDeviceStatus("打开警报");
        clientSocket->write("5");
    }
}
