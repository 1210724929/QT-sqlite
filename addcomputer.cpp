#include "addcomputer.h"
#include "ui_addcomputer.h"

AddComputer::AddComputer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddComputer)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [=]{//按下确认添加按键后发送back_1信号
        emit this->back_1();
    });
}

AddComputer::~AddComputer()
{
    delete ui;
}


void AddComputer::closeEvent(QCloseEvent *e)//按下关闭窗口后发送back_1信号
{
    emit this->back_1();
}

void AddComputer::on_pushButton_clicked()
{
    host_ip_con = ui->lineEdit->text();
    QRegExp rx2("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
          if( !rx2.exactMatch(host_ip_con))
          {
              QMessageBox::critical(this, tr("添加失败"), tr("ip地址错误！"));
               //qDebug()<<"ip地址错误";
          }
          else
          {
             QMessageBox::about(this, tr("添加成功"), tr("欢迎使用MSMP进行病毒防护"));
             //qDebug()<<"ip地址正确";

             emit con_1();//发送连接信号到主窗口
          }




}
