#include "deletecomputer.h"
#include "ui_deletecomputer.h"


deleteComputer::deleteComputer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::deleteComputer)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [=]{//按下确认删除按键后发送back信号
        emit this->back();
    });


}

deleteComputer::~deleteComputer()
{
    delete ui;
}

void deleteComputer::closeEvent(QCloseEvent *e)//在删除计算机页面按下关闭窗口按键后发送back()信号
{
    emit this->back();
}

void deleteComputer::on_pushButton_clicked()
{
    host_ip_del = ui->lineEdit->text();

    QRegExp rx2("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
          if( !rx2.exactMatch(host_ip_del))
          {
              QMessageBox::critical(this, tr("删除失败"), tr("ip地址错误！"));
               //qDebug()<<"ip地址错误";
          }
          else
          {
             //qDebug()<<"ip地址正确";

             emit del_com();//发送删除信号到主窗口
          }
}
