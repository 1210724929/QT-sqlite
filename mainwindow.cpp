#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//创建主窗口
    sockfd=NULL;  //初始化 与A端进行通信需要的套接字
    del = new deleteComputer();//创建删除计算机窗口，注意空括号，该窗口不是mainwindow的子控件
    add = new AddComputer();//创建添加计算机窗口
    manager = new Computer_Manager();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"计算机IP"<<"系统版本"<<"连接状态"<<"防病毒状态");//设置表头
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许修改单元格信息
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式

    //创建数据库并创建表
    QString dataBasePath = QCoreApplication::applicationDirPath()+"//"+ "database.db";
    db = new DataBase(dataBasePath);
      db->deleteTabel("host_manager");
    db->createTable("host_manager");//创建host_manager
      db->deleteTabel("viruinfo");
    db->createTable("viruinfo");//创建viruinfo
//    db->insertData("192.168.136.67+C:/kafokokpf/afijaijfaiojf/auafsoiujfj+2022-6-5 10:21+实时","viruinfo");
//    db->insertData("192.168.136.34+C:/kafokokpf/afijjf/auafsoiujfj+2022-6-5 10:33+实时","viruinfo");
//    db->insertData("192.168.136.36+C:/kafokokpf/afifaiojf/auafsoiujfj+2022-6-5 10:31+手动","viruinfo");
//    db->insertData("192.168.136.67+C:/kafokokpf/afijaijfaiojf/auafsoiujfj+2022-6-5 10:21+实时","viruinfo");
//    db->insertData("192.168.136.34+C:/kafokokpf/ijfaiojf/auafsoiujfj+2022-6-5 10:11+实时","viruinfo");
//    db->insertData("192.168.136.36+C:/kafokokpf/afijaiojf/auafsoiujfj+2022-6-5 10:21+手动","viruinfo");
//    db->insertData("10.22.13.190+C:/kafokokpf/ijfaiojf/auafsoiujfj+2022-6-5 10:41+手动","viruinfo");
//    db->insertData("192.168.136.67+C:/kafokokpf/afijiojf/auafsoiujfj+2022-6-5 10:21+实时","viruinfo");
//    db->insertData("192.168.136.34+C:/kafokokpf/jfaiojf/auafsoiujfj+2022-6-5 10:21+实时","viruinfo");
//    db->insertData("192.168.136.36+C:/kafokokpf/ijf/auafsoiujfj+2022-6-5 10:21+手动","viruinfo");
//    db->insertData("192.168.136.67+centos7+连接+手动","host_manager");
//    db->insertData("192.168.136.34+centos7+连接+手动","host_manager");
    //将表中数据拿出来并输入到主界面tabelwidgt中
    QString data  = "192.168.136.36+cent0S7+连接+关闭";
    QStringList data_list1 = data.split("+");
    qDebug()<<data_list1[0]<<data_list1[1]<<data_list1[2]<<data_list1[3];
//    bool success = query.exec(QString("INSERT INTO host_manager(host_ip, host_os,host_connect_status ,host_fature_status) VALUES ('%1', '%2', '%3', '%4')").arg(data_list1[0]).arg(data_list1[1])
//                                  .arg(data_list1[2]).arg(data_list1[3]));
//    db->insertData(data, "host_manager");
//    db->insertData(QString("'%1'+cent0S7+连接+关闭").arg(QString(add->host_ip_con)),"host_manager");
    get_ALL_Computer_Data();

    //判断计算机管理界面的实时扫描和手动扫描,用信号来判定，flag_1()开启手动扫// flag_2()开启实时扫描// void flag_3()实时+手动//void flag_4()关闭
    connect(manager, &Computer_Manager::flag_1, [=]{
        QString cmomode = "1";
        QByteArray sendMessage = cmomode.toLocal8Bit();
        sockfd->write(sendMessage);
        sockfd->flush();
        qDebug()<<"开启手动扫描成功";

        char req_buf[1500] = {0};
        int ret=sockfd->read(req_buf, sizeof(req_buf) - 1);
        qDebug()<<"接受的文件大小:"<<ret<<endl;
        ret = strlen(req_buf);
        req_buf[ret] = '\0';
        QString testss = QString(req_buf);
        qDebug()<<"手动模式数据"<<req_buf<<testss;
//        db->insertData("192.168.136.67+C:/kafokokpf/afijaijfaiojf/auafsoiujfj+2022：3333：3233：3323+SHISHI","viruinfo");
//        db->insertData(add->host_ip_con+"+"+testss.split('+')[1]+"+"+testss.split('+')[2]+"+"+"实时", "viruinfo");
//        qDebug()<<"手动录入数据成功";
        qDebug()<<"手动模式数据录入成功";



    });
    connect(manager, &Computer_Manager::flag_2, [=]{
        QString cmomode = "2";
        QByteArray sendMessage = cmomode.toLocal8Bit();
        sockfd->write(sendMessage);
        sockfd->flush();
        qDebug()<<"开启实时扫描成功";

        char req_buf[1500] = {0};
        int ret=sockfd->read(req_buf, sizeof(req_buf));
        qDebug()<<"实时模式接受的文件大小:"<<ret<<endl;
        QString testss = QString(req_buf);
        qDebug()<<"实时模式数据"<<testss;


    });
    connect(manager, &Computer_Manager::flag_3, [=]{
        QString cmomode = "3";
        QByteArray sendMessage = cmomode.toLocal8Bit();
        sockfd->write(sendMessage);
        sockfd->flush();
        qDebug()<<"开启实时+手动成功";

        char req_buf[1500] = {0};
        int ret=sockfd->read(req_buf, sizeof(req_buf));
        qDebug()<<"实时+手动模式接受的文件大小:"<<ret<<endl;
        QString testss = QString(req_buf);
        qDebug()<<"实时+手动模式数据"<<testss;
    });
    connect(manager, &Computer_Manager::flag_4, [=]{
        QString cmomode = "4";
        QByteArray sendMessage = cmomode.toLocal8Bit();
        sockfd->write(sendMessage);
        sockfd->flush();
        qDebug()<<"实时+手动关闭";


    });


    connect(del, &deleteComputer::back, [=]{//接受删除计算机窗口中按钮信号back，关闭删除计算机窗口，打开主窗口
        del->hide();
        this->show();
    });

    connect(add, &AddComputer::back_1, [=]{//接受添加计算机窗口中按钮信号back_1，关闭删除计算机窗口，打开主窗口
        add->hide();
        this->show();
    });

    connect(manager, &Computer_Manager::back_2, [=]{
        manager->hide();
        this->show();
    });

    connect(add, &AddComputer::con_1, [=]{//接收到发送信号，获取IP地址，socket连接，刷新计算机页面
        // 连接后，接受校验码，确定host_ip是A端
        QString ip=add->host_ip_con;
        int port=8888;
        if(sockfd==NULL)
        {
            sockfd=new QTcpSocket();
            sockfd->connectToHost(ip,port);//连接到网址
            connect(sockfd,SIGNAL(connected()),this,SLOT(su_connect()));//连接成功后
            connect(sockfd,SIGNAL(readyRead()),this,SLOT(recv_env()));//准备读取套接字
            connect(sockfd, SIGNAL(disconnected()),this,SLOT(connect_error()));//断开连接
            qDebug()<<"===============连接成功，准备接受数据";
        }
        qDebug()<<"数据就收成功，准备写入数据库===================";
        ui->tableWidget->clearContents();
        get_ALL_Computer_Data();
    });


    //删除计算机信号
    connect(del, &deleteComputer::del_com, [=]{
        bool success = db->deleteData(del->host_ip_del);
        if (success)
        {
            QMessageBox::about(this, tr("删除成功"), tr("删除成功"));
        }
        else {
            QMessageBox::about(this, tr("删除失败"), tr("没有该IP地址的计算机"));
        }
        ui->tableWidget->clearContents();
        get_ALL_Computer_Data();
    });




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//点击删除计算机按钮
{
    this->hide();//隐藏主窗口
    del->show();//显示删除计算机窗口


}

void MainWindow::on_pushButton_2_clicked()//点击添加计算机按钮
{
    this->hide();//隐藏主窗口
    add->show();//显示添加计算机窗口
}

bool MainWindow::get_ALL_Computer_Data()
{
    if(!db->m_DataBase.open())
    {
        qDebug()<<"在获得计算机管理信息时，无法打开数据库。";
        return false;
    }
    else
    {
         QSqlQuery query(db->m_DataBase);
         query.prepare(QString("SELECT * FROM host_manager"));
         query.exec();
         QSqlRecord rec = query.record();
         ui->tableWidget->clear();
         ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"计算机IP"<<"系统版本"<<"连接状态"<<"防病毒状态");
         ui->tableWidget->setRowCount(0);
         int RowCont = 0;
         while(query.next())
         {
             QString host_ip = query.value(0).toString();
             QString host_os = query.value(1).toString();
             QString host_connect_status = query.value(2).toString();
             QString host_fature_status = query.value(3).toString();
//             RowCont=ui->tableWidget->rowCount();
             ui->tableWidget->insertRow(RowCont);//增加一行
             //插入元素
             ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(host_ip));
             ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(host_os));
             ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(host_connect_status));
             ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem(host_fature_status));
             RowCont += 1;

         }
         return true;
    }
}


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)//双击控制台界面列表跳转到对应计算机管理页面
{



    host_ip = ui->tableWidget->item(row,0)->text();

    QFile file;
        file.setFileName(QCoreApplication::applicationDirPath()+"//"+ "host_ip.txt");
    // 追加写入
        if(file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate))
        {
            QTextStream in(&file);
            in<<host_ip<<endl;
        }
        file.close();

    this->hide();
    manager->show();
}

//socket对应信号的处理函数
void MainWindow::su_connect()
{
    qDebug()<<"与A端连接成功";
#if 0
    int ret = 0;
    char req_buf[10] = {0};
    QThread::sleep(3);
 //   memset(req_buf,0,sizeof(req_buf));
    ret=sockfd->read(req_buf, sizeof(req_buf) - 1);
    qDebug()<<"aaaaa:"<<ret;
    ret = strlen(req_buf);
    req_buf[ret] = '\0';
    char *p=req_buf;
    qDebug()<<"数据"<<req_buf;
    if(strstr(req_buf,"0")!=NULL) //校验码核对成功的话,写如数据库
    {
        sscanf(p,"0%s+%s",&ip_head,&ip_body);
        char ip_body_buf[7] = "";
        sprintf(ip_body_buf,"%s",ip_body);
        if(ip_body_buf == "0x45678"){
            qDebug()<<"得到校验码";
        }
        qDebug()<<"写入数据库";
    }
    sockfd->flush();   // 写的时候调用，就直接把缓冲的发送
 #endif

}
void MainWindow::connect_error(){
    QMessageBox::critical(this, tr("连接失败"), tr("网络问题！"));
}

#if 1
void MainWindow::recv_env()
{
    qDebug()<<"接受客户端数据"<<endl;
    int ret = 0;
    char req_buf[1500] = {0};
 //   memset(req_buf,0,sizeof(req_buf));
    ret=sockfd->read(req_buf, sizeof(req_buf) - 1);
    qDebug()<<"接受的文件大小:"<<ret<<endl;
    ret = strlen(req_buf);
    req_buf[ret] = '\0';

    QString testss = QString(req_buf);
    qDebug()<<"校验码数据："<<req_buf<<testss;
    if(testss.split('+')[1] == "0x45678"){
        qDebug()<<"检验通过";
        QMessageBox::about(this, tr("检验通过"), tr("检验通过！"));
        QString cmomode = "5";
        QByteArray sendMessage = cmomode.toLocal8Bit();
        sockfd->write(sendMessage);
        sockfd->flush();
        qDebug()<<add->host_ip_con<<"============453";
        db->insertData(add->host_ip_con +"+cent0S7+连接+关闭","host_manager");
        get_ALL_Computer_Data();
    }
    else if(testss.split('+')[0] == "5"){
        qDebug()<<"接受手动扫描的病毒事件"<<testss.split('+')[1];
        db->insertData(add->host_ip_con+"+"+testss.split('+')[1]+"+"+testss.split('+')[2]+"+"+"实时", "viruinfo");

    }
    else {
        QMessageBox::critical(this, tr("连接失败"), tr("连接失败！"));
    }


    sockfd->flush();   // 写的时候调用，就直接把缓冲的发送

}

#else
void MainWindow::recv_env()
{
  /*  int ret = 0;
    char recv_buf[10] = "";

    memset(recv_buf,0,sizeof(recv_buf));
    ret=sockfd->read(recv_buf,sizeof(recv_buf));
    ret = strlen(recv_buf);
    qDebug()<<"====从A端读取数据======数量"<<ret<<recv_buf;
    recv_buf[ret] = '\0';

    ui->label_2->setText(recv_buf);
    //ui->label_2->setText(QString::number(ret));
    //对接收到的字符串进行判断处理， 5+病毒内容,写入数据库
    char *p=recv_buf;
    //数据解析
    if(strstr(recv_buf,"5")!=NULL)
    {
       //往数据库写入数据

    }

     sockfd->flush();
     */
}
#endif
void MainWindow::su_connect_flag1(){
    QString cmomode = "1";
    QByteArray sendMessage = cmomode.toLocal8Bit();
    sockfd->write(sendMessage);
    sockfd->flush();
}
void MainWindow::recv_env_flag1(){
    QString cmomode = "1";
    QByteArray sendMessage = cmomode.toLocal8Bit();
    sockfd->write(sendMessage);
    sockfd->flush();
}

//bool MainWindow :: sockt_Send(QString information)
//{

//}


