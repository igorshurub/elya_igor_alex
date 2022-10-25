#include "functions.h"
#include "QString"
#include "dialog_login.h"
#include "editing.h"
#include "QString"
#include <QMessageBox>

QString authorize(std::string login,std::string password)
{   //edit = new Editing();
    QString result;
    if (login == "user" && password == "123"){

    }
    else if (login == "user2" && password == "124"){

    }
    else {
        result = "authorization error";
        return result;
    }
}
