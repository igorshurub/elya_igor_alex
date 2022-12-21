#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define HOSTNAME            "192.168.31.27"
#define DATABASE_NAME       "photolife"
#define USER                "postgres"
#define PASSWORD            "12345678"
#define TABLE                "authoriz"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

public:
    /* Внутренние методы для работы с базой данных
     * */
    void openDataBase();
    void closeDataBase();
    QString bdquery(QString temp); //запрос В БД для сравнения логина и пароля
};

#endif // DATABASE_H
