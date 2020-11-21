#include "basedbreader.h"
#include <QDataStream>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

BaseDBReader::BaseDBReader()
{
}
BaseDBReader::~BaseDBReader()
{
   if (db.isOpen()) db.close();
}

void BaseDBReader::loadBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./Tasks.db");

   if (!db.open())
   {
       qDebug() << db.lastError().text();
       return;
   }
   else
   {
        QSqlQuery query;

        auto a = query.exec("CREATE TABLE IF NOT EXISTS tasklist("
                                    "id INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,"
                                    "name varchar(50) NOT NULL,"
                                    "date varchar(50) NOT NULL,"
                                    "progress int(2) NOT NULL)"
                                    );
        if(!a)
            qDebug() << query.lastError().text();
   }

   emit initEnd(true);
}

void BaseDBReader::getRecords()
{
    QSqlQuery query;
    if(!query.exec("SELECT * FROM tasklist"))
    {
        qDebug() << query.lastError().text();
    }

    while(query.next()){
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString date = query.value("date").toString();
        QString progress = query.value("progress").toString();
        emit loadTask(id, name, date, progress);
    }
}

void BaseDBReader::writeNewInformation(QString name, QString date, QString progress) // Записываем
{
    QSqlQuery query;
    if(!query.exec("insert into tasklist ([name],[date],[progress]) VALUES('" +
               name + "','" +
               date + "','" +
               progress + "')"
               ))
    {
        qDebug() << query.lastError().text();
    }
}

bool BaseDBReader::removeRecord(int id)
{
    // Удаление строки из базы данных будет производитсья с помощью SQL-запроса
    QSqlQuery query;

    // Удаление производим по id записи, который передается в качестве аргумента функции
    query.prepare("DELETE FROM tasklist WHERE id= :ID ;");
    query.bindValue(":ID", id);

    // Выполняем удаление
    if(!query.exec()){
        qDebug() << "error delete row " << "tasklist";
        qDebug() << query.lastError().text();
        return false;
    } else {
        emit deleteTask();
        return true;
    }
    return false;
}
