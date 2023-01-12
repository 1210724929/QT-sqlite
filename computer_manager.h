#ifndef COMPUTER_MANAGER_H
#define COMPUTER_MANAGER_H

#include <QMainWindow>
#include<QHeaderView>
#include"QCloseEvent"
#include <database.h>
//#include<mainwindow.h>

namespace Ui {
class Computer_Manager;
}

class Computer_Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Computer_Manager(QWidget *parent = 0);
    ~Computer_Manager();
    void closeEvent(QCloseEvent *event);

    QString path_1;
signals:
    void back_2();//关闭信号
    void flag_1();//开启手动扫描
    void flag_2();//开启实时扫描
    void flag_3();//实时+手动
    void flag_4();//关闭

private slots:

    void on_pushButton_clicked();

    void on_tabWidget_tabBarClicked(int index); //功能和事件tab变换

public:
    Ui::Computer_Manager *ui;
};

#endif // COMPUTER_MANAGER_H
