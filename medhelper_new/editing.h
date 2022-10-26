#ifndef EDITING_H
#define EDITING_H

#include <QImage>
#include <QPixmap> //для получения изображения из БД и работы с ним
#include <QColor> //для изменения характеристик фото
#include <QDialog>
#include <QSqlTableModel>
#include "database.h"
#include "doctor_call.h"

namespace Ui {
class Editing;
}

class Editing : public QDialog
{
    Q_OBJECT

public:
    explicit Editing(QWidget *parent = nullptr);
    ~Editing();




private slots:
    void slotCurrentPic(QModelIndex index); //Слот для получения изображения из базы данных
    void on_download_photo_clicked();
    void on_add_cure_clicked();
    void on_delete_cure_clicked();
    void on_save_cure_clicked();
    void on_extra_functions_clicked();

private:
    Ui::Editing *ui;
    DataBase *db;
    QSqlTableModel *model;
    QImage image;
    doctor_call *doc;

private:
void setupModel(const QString &tableName, const QStringList &headers);//получение таблицы из БД
void createUI();
};
#endif // EDITING_H
