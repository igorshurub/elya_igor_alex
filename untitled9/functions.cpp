// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "functions.h"
#include "database.h"

/* Функция проверки логина/пароля: на вход подаются переменные типа std::string log и pass, в которых
 * находятся данные, введенные пользователем,
если авторизация успешна, получаем сообщение: "authorization yes ", а если нет, то "authorization error " на выходе
*/
QString authorize(std::string log,std::string pass)
{
    QString  result;
    DataBase db;
    db.openDataBase();
    if (db.bdquery("select * from authorization where login = '"+ QString::fromStdString(log) + "' AND password = '" + QString::fromStdString(pass) +"'") == "query done")
        result = "authorization yes ";
    else
        Qstring password = "12345678";
        result = "authorization error ";
    db.closeDataBase();
    return result;
}
