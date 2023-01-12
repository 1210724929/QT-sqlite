#ifndef ADDCOMPUTER_H
#define ADDCOMPUTER_H

#include <QMainWindow>
#include"QPushButton"
#include"QCloseEvent"
#include<QRegExp>
#include<QMessageBox>
#include<QString>

namespace Ui {
class AddComputer;
}

class AddComputer : public QMainWindow
{
    Q_OBJECT

signals:
    void back_1();//定义一个信号，用于发送关闭添加窗口信号
    void con_1();//发送连接信号

public:
    explicit AddComputer(QWidget *parent = 0);
    ~AddComputer();
    void closeEvent(QCloseEvent *);

    QString host_ip_con;//用户输入的IP地址，用于连接A端

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddComputer *ui;
};

#endif // ADDCOMPUTER_H
