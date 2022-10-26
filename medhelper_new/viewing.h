#ifndef VIEWING_H
#define VIEWING_H

#include <QDialog>
#include <QSqlTableModel>
#include "database.h"



namespace Ui {
class Viewing;
}

class Viewing : public QDialog
{
    Q_OBJECT

public:
    explicit Viewing(QWidget *parent = nullptr);
    ~Viewing();

private slots:
    // Слот для получения изображения из базы данных
    void slotCurrentPic(QModelIndex index);

    void on_back_clicked();

signals:
    void ShowMW();//функция для возврата на окно MW

private:
    Ui::Viewing *ui;
    DataBase *db;
    QSqlTableModel *model;

private:
void setupModel(const QString &tableName, const QStringList &headers);//получение таблицы из БД
void createUI();
void    setWordWrap ( bool on );
};

#endif // VIEWING_H
