#include "computer_manager.h"
#include "ui_computer_manager.h"

Computer_Manager::Computer_Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Computer_Manager)
{
    ui->setupUi(this);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"计算机IP"<<"病毒路径"<<"时间"<<"扫描方式");//设置表头
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许修改单元格信息
    ui->tableWidget->setColumnWidth(0, 130);
    ui->tableWidget->setColumnWidth(1, 250);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 100);//调整列宽

    ui->tableWidget->setRowCount(10);                   // 设置表格行数
    ui->tableWidget->setColumnCount(4);

    path_1 = ui->lineEdit->text();//获取手动扫描路径
}
Computer_Manager::~Computer_Manager()
{
    delete ui;
}

void Computer_Manager::closeEvent(QCloseEvent *event)
{
    emit back_2();
}



void Computer_Manager::on_pushButton_clicked()
{
    bool bool_1 = ui->shishi_check->isChecked();
    bool bool_2 = ui->shoudong_check->isChecked();

    if(bool_1&&bool_2)//如果实时+手动
    {
        emit flag_3();
        return;
    }
    if(bool_2)//如果手动扫描
    {
        emit flag_1();
        return;
    }
    if(bool_1)//如果实时扫描
    {
        emit flag_2();
        return;
    }
    else {//如果都关闭
       emit flag_4();
    }
}


//功能和事件tab变换，功能是0，事件是1
void Computer_Manager::on_tabWidget_tabBarClicked(int index)
{

    qDebug()<<index;
        if(index == 1) //功能是0，事件是1
        {
            qDebug()<<"从viruinfo读取数据";
            //从数据库读取数据
            QString dataBasePath = QCoreApplication::applicationDirPath()+"//"+ "database.db";
            DataBase db(dataBasePath);
            QFile file( QCoreApplication::applicationDirPath()+"//"+ "host_ip.txt");
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug()<<"Can't open the file!"<<endl;
            }
            QByteArray line = file.readLine();
            QString host_ip(line);
            host_ip = host_ip.trimmed();
            QList<QString> testlist =  db.getDataList("viruinfo", host_ip);
            if (testlist.size() == 0)
            {
                ui->tableWidget->clearContents();
                return;
            }
            for (int i = 0; i < testlist.size(); i++)
            {
                qDebug() << testlist[i];
                ui->tableWidget->setItem(i/4,i%4,new QTableWidgetItem(testlist[i]));


            }

        }

}
