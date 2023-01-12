#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QCoreApplication>
#include <QDebug>
#include <QSqlRecord>
#include<QFileInfo>
#include<QString>
#include <QList>
//#include<mainwindow.h>

class DataBase : public QObject
{
    Q_OBJECT
public:
    DataBase(QString name);
    ~DataBase();

    QSqlDatabase m_DataBase;
    bool createTable(QString table);
    bool isExistTable(QString table);
    void deleteTabel(QString tabel_name);
    bool insertData(QString data, QString tabel_name);
    bool deleteData(QString name);

    QList<QString> getDataList(QString tabel_name, QString host_ip); //从host_manager/viruinfo读取数据

};

#endif // DATABASE_H

