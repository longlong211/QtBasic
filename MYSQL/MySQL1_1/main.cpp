#include <QCoreApplication>
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QString>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //从Mysql驱动程序中获取一个mysql数据库
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString driver,drivers)
        qDebug()<<driver;
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("123456");

    //打开数据库链接
    if(db.open()){  //注意不要写成isopen
        qDebug()<<"database is established!";
          }
        else{
            qDebug()<<"build error!";
            return a.exec();

    }
    QSqlQuery query;
    query.exec("create table test(sno varchar(10) not null primary key,sname varchar(20) not null,sclass varchar(10) not null)");
    query.exec("insert into test (sno,sname,sclass)values('2009001','lilei','0901')");
     query.exec("insert into test (sno,sname,sclass)values('2009002','lucy','0902')");
      query.exec("insert into test (sno,sname,sclass)values('2009003','mike','0903')");
       query.exec("insert into test (sno,sname,sclass)values('2009004','lifei','0904')");

       query.exec("select * from test");
       QSqlRecord rec=query.record();//返回查询执行的结果
       int count=rec.count();//获取查询到的列数
       qDebug()<<"Number of coloum : "<<count;

       //获取查询到的记录，并输出到控制台
       while(query.next()){
           rec=query.record();
           int snocol=rec.indexOf("sno");
           int snamecol=rec.indexOf("sname");
           int sclasscol=rec.indexOf("sclass");

           QString v1=query.value(snocol).toString();
             QString v2=query.value(snamecol).toString();
               QString v3=query.value(sclasscol).toString();
           qDebug()<<"son : "<<v1<<"\t"<<"sname :"<<v2<<"\t"<<"sclass :"<<v3;

       }
       query.clear();//清空查询语句并释放内存
       db.close();//关闭数据库

    return a.exec();
}
