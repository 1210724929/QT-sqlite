#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include<Qstring>
#include"database.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QString dataBasePath = QCoreApplication::applicationDirPath()+"//"+ "database.db";
//    DataBase db(dataBasePath);
//    db.createTable("host_manager");//创建host_manager
//    db.createTable("viruinfo");//创建viruinfo
//    db.deleteTabel("host_manager");
//    db.deleteTabel("viruinfo");
//    db.insertData("192.168.136.99+CentOS7+连接+关闭","host_manager");
    MainWindow w;
    w.show();
    return a.exec();
}
