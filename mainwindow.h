#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStringList>
#include"deletecomputer.h"//删除计算机头文件
#include"addcomputer.h"//添加计算机头文件
#include"computer_manager.h"//计算机管理界面头文件
#include"database.h"
#include <QtcpSocket>
#include<QMessageBox>


#endif // MAINWINDOW_H
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DataBase *db;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

    //socket的信号
//    void to_connect();
    void su_connect();
    void recv_env();
    void connect_error();

    void su_connect_flag1();
    void recv_env_flag1();


private:
    Ui::MainWindow *ui;
    deleteComputer *del = NULL;//删除计算机窗口，野指针不可操作
    AddComputer *add = NULL;//添加计算机窗口
    Computer_Manager *manager = NULL;

    QTcpSocket *sockfd;  //与A端进行通信需要的套接字
    QString ip_head,ip_body;


public:
    QString host_ip;//获取双击主界面后对应的ip地址
    bool get_ALL_Computer_Data();
//    bool sockt_Send(QString ip_address, QString information);
};


