#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{
}

void DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/server/"  DATABASE_NAME);
    if (db.open()) {qDebug()<<"database is open";} else {qDebug()<<"database not open";}
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/*Функция запроса в БД*/
QString DataBase::bdquery(QString temp){

    QSqlQuery query(db);
    query.exec(temp);
    query.next();
    if (query.value(0).toString().length() > 0)
    {
        return "query done";
    }
    else {
        return "query error";
    }
}
