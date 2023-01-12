#include "database.h"

//构造方法
DataBase::DataBase(QString name)
{
    m_DataBase = QSqlDatabase::addDatabase("QSQLITE");
    m_DataBase.setDatabaseName(name);
    bool ok = m_DataBase.open();
    if (ok)
    {
        qDebug()<<"数据库打开成功";

    }
    else {
        qDebug()<<"数据库打开失败";
    }
}


DataBase::~DataBase()
{

}

//创建表
bool DataBase::createTable(QString table_name)
{
    if (!m_DataBase.open()) {
        qDebug()<<"没打开数据库";
        return false;
    }

    QSqlQuery query(m_DataBase);
    if (table_name == QString("host_manager")) {//创建计算机管理表

        bool success = query.exec("CREATE TABLE host_manager ("
                                    "host_ip VARCHAR(32) PRIMARY KEY, "
                                    "host_os VARCHAR(32) NOT NULL, "
                                    "host_connect_status VARCHAR(32) NOT NULL, "
                                    "host_fature_status VARCHAR(32) NOT NULL)");
        if (success) {
            qDebug()<<"新建host_manager数据表成功";
            return true;   //新建host_manager数据表成功
        }
        else {
            QSqlError lastError = query.lastError();
            QString err = lastError.driverText();
            qDebug()<<"host_manager数据表创建失败或者已经存在";
            return false;
        }
    }
    else if (table_name == QString("viruinfo")) {//创建计算机管理表
        bool success = query.exec("CREATE TABLE viruinfo ("
                                    "v_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "host_ip VARCHAR(32) NOT NULL, "
//                                   "v_mark VARCHAR(32) NOT NULL, "
                                    "file_address VARCHAR(60) NOT NULL,"
                                    "time VARCHAR(32) NOT NULL,"
                                    "scanning_way VARCHAR(32) NOT NULL)"
                                  );
        if (success) {
            qDebug()<<"新建viruinfo数据表成功";
            return true;   //新建viruinfo数据表成功
        }
        else {
            QSqlError lastError = query.lastError();
            QString err = lastError.driverText();
            qDebug()<<"viruinfo数据表创建失败或者已经存在";
            return false;
        }
    }

    else {
        return false;
    }
}


//删除表
void DataBase::deleteTabel(QString tabel_name)
{
    QSqlQuery query(m_DataBase);
    bool success = query.exec(QString("DROP TABLE %1").arg(tabel_name));
    if(success)
    {
        qDebug()<<"删除成功";
    }
    else {
        qDebug()<<"删除失败";
    }
}

bool DataBase::insertData(QString data, QString tabel_name)
{
    if (!m_DataBase.open()) {
        qDebug()<<"在插入数据时，无法打开数据库";
        return false;
    }
    QSqlQuery query(m_DataBase);
    if(tabel_name == QString("host_manager"))
    {
        QStringList data_list1 = data.split("+");
        qDebug()<<data_list1[0]<<data_list1[1]<<data_list1[2]<<data_list1[3];
        bool success = query.exec(QString("INSERT INTO host_manager(host_ip, host_os,host_connect_status ,host_fature_status) VALUES ('%1', '%2', '%3', '%4')").arg(data_list1[0]).arg(data_list1[1])
                                      .arg(data_list1[2]).arg(data_list1[3]));

          if (!success) {
            QSqlError lastError = query.lastError();
            QString err = lastError.driverText();
            qDebug()<<"host_manager插入数据失败"<<err;
            return false;
        }else{
            qDebug()<<"host_manager插入数据成功";
        }
        return true;
    }

    if(tabel_name == QString("viruinfo"))
        {
            QStringList data_list1 = data.split("+");
            qDebug()<<data_list1[0]<<data_list1[1]<<data_list1[2]<<data_list1[3];
            bool success = query.exec(QString("INSERT INTO viruinfo (host_ip,file_address,time,scanning_way) VALUES ('%1', '%2', '%3', '%4')").arg(data_list1[0]).arg(data_list1[1])
                                          .arg(data_list1[2]).arg(data_list1[3]));
            //bool success = query.exec(QString("INSERT INTO viruinfo (v_mark,host_ip,file_address,time,scanning_way) VALUES ('eicr', '192.168.136.34' ,'c:/bin/test' ,'2022-7-11 16:57' ,'手动')"));
              if (!success) {
                QSqlError lastError = query.lastError();
                QString err = lastError.driverText();
                qDebug()<<"viruinfo插入数据失败"<<err;
                return false;
            }else{
                qDebug()<<"viruinfo插入数据成功";
            }
            return true;
        }

}

//读取数据
QList<QString> DataBase::getDataList(QString tabel_name, QString host_ip)//读取病毒库数据，显示在事件栏
{
    if (!m_DataBase.open()) {
        qDebug()<<"从数据库读取数据失败，打开失败";
    }

    QSqlQuery query(m_DataBase);

    QList<QString> list;
    if(tabel_name == QString("host_manager"))
    {
        query.prepare(QString("SELECT * FROM host_manager"));
        query.exec();
        QSqlRecord rec = query.record();
        while (query.next())
        {
            for(int i=0;i<4;i++)
            {
                QString data = query.value(i).toString();
                list.append(data);
                qDebug()<<"从host_manager读取数据成功"<<query.value(i).toString();
            }
        }
        return list;
    }
    if(tabel_name == QString("viruinfo"))
    {

        qDebug()<<host_ip<<"=================================";
        query.prepare(QString("SELECT host_ip,file_address,time,scanning_way FROM viruinfo WHERE host_ip='%1'").arg(host_ip));
        query.exec();
        QSqlRecord rec = query.record();
        while (query.next())
        {
            for(int i=0;i<4;i++)
            {
                QString data = query.value(i).toString();
                list.append(data);
                qDebug()<<"从viruinfo读取数据成功"<<query.value(i).toString();
            }
        }
        return list;
    }
}


bool DataBase::deleteData(QString name)//删除对应字段的数据
{
    if (!m_DataBase.open()) {
        return false;
    }
    QSqlQuery query(m_DataBase);
    qDebug()<<name;
    query.prepare(QString("DELETE FROM host_manager WHERE host_ip = '%1'").arg(name));
    bool success = query.exec();
//    QSqlRecord rec = query.record();
    bool success_2 = query.next();
    if (!success || !success_2) {
            QSqlError lastError = query.lastError();
            QString err = lastError.driverText();
            return false;
        }
}
