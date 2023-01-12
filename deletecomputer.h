#ifndef DELETECOMPUTER_H
#define DELETECOMPUTER_H

#include <QMainWindow>
#include"QPushButton"
#include"QCloseEvent"
#include <QDebug>
#include<QMessageBox>
#include<QRegExp>

namespace Ui {
class deleteComputer;
}

class deleteComputer : public QMainWindow
{
    Q_OBJECT

public:
    explicit deleteComputer(QWidget *parent = 0);
    ~deleteComputer();

    QString host_ip_del;

    void closeEvent(QCloseEvent *);

private slots:
   // void on_pushButton_clicked();

    void on_pushButton_clicked();

signals:
    void back();//定义一个信号，用于发送关闭删除窗口信号
    void del_com();//发送删除计算机信号

private:
    Ui::deleteComputer *ui;

};

#endif // DELETECOMPUTER_H
