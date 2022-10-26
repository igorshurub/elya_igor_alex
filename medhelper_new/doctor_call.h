#ifndef doctor_call_H
#define doctor_call_H

#include <QImage>
#include <QPixmap> //для получения изображения из БД и работы с ним
#include <QColor> //для изменения характеристик фото
#include <QDialog>
#include <QSqlTableModel>
#include "database.h"


namespace Ui {
class doctor_call;
}

class doctor_call : public QDialog
{
    Q_OBJECT

public:
    explicit doctor_call(QWidget *parent = nullptr);
    ~doctor_call();


signals:
    void ShowDoc();//функция для возврата на окно Editing

private slots:
    void on_add_call_clicked();
    void on_delete_call_clicked();
    void on_enter_patient_clicked();
    void on_enter_call_clicked();
    void on_back_clicked();

private:
    Ui::doctor_call *ui;
    DataBase *db;
    QSqlTableModel *model;

private:
    void setupModel(const QString &tableName, const QStringList &headers);//получение таблицы из БД
    void createUI();
};
#endif // doctor_call_H
