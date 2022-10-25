#include "doctor_call.h"
#include "ui_doctor_call.h"
//#include "dialog_login.h"
#include <QBuffer>
#include <QScreen>
#include <QApplication>
#include <QFileDialog>
#include <QDialog>
#include <QSqlQueryModel>
#include <QImage>
#include <QFile>
#include <QPixmap>
#include <QColor>
#include <QSqlRecord>


doctor_call::doctor_call(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::doctor_call)
{
    ui->setupUi(this);

    // установка фона приложения
    QPixmap pix("/home/sis201331/medhelper_new/biba/fon.jpg");
    int w = ui->label_2->width();
    int h = ui->label_2->height();
    ui->label_2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    db = new DataBase();
    db->connectToDataBase();

    //отображение столбцов БД в следующем виде
    this->setupModel(TABLE_2,
                    QStringList() << trUtf8("Пациент")
                                  << trUtf8("Врач")
                                  << trUtf8("Дата вызова")
                                  << trUtf8("Адрес вызова")
                                  << trUtf8("Симптомы")
                                  << trUtf8("Диагноз")
                                  << trUtf8("Предписания")
                                  << trUtf8("Лекарства"));
    this->createUI();
}

//получение таблицы из БД
void doctor_call::setupModel(const QString &tableName, const QStringList &headers){
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    for (int i = 1,j = 0; i < model->columnCount();i++,j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    //Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void doctor_call::createUI()
    {
     ui->tableView3->setModel(model);

     QHeaderView *verticalHeader = ui->tableView3->verticalHeader();
     verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
     verticalHeader->setDefaultSectionSize(700);

     QHeaderView *horizontalHeader = ui->tableView3->horizontalHeader();
     horizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
     horizontalHeader->setDefaultSectionSize(250);

     //Скрываем определенные поля из БД

     ui->tableView3->setColumnHidden(0, true);
     //ui->tableView3->setColumnHidden(0, true);
     //ui->tableView3->setColumnHidden(1, true);
     //ui->tableView3->setColumnHidden(2, true);
     //ui->tableView3->setColumnHidden(3, true);
     //ui->tableView3->setColumnHidden(4, true);
     //ui->tableView3->setColumnHidden(5, true);
     //ui->tableView3->setColumnHidden(6, true);
     //ui->tableView3->setColumnHidden(7, true);

     ui->tableView3->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView3->horizontalHeader()->setStretchLastSection(true);
     //model->setEditStrategy(QSqlTableModel::OnManualSubmit); //редактирование строк

     model->select();
    }

doctor_call::~doctor_call()
{
    delete ui;
}


void doctor_call::on_add_call_clicked()
{
    QString patient_name = ui->patient_name->text();
    QString doctor_name = ui->doctor_name->text();
    QString date = ui->date->text();
    QString address = ui->address->text();
    QString symptoms = ui->symptoms->text();
    QString diagnosis = ui->diagnosis->text();
    QString prescription = ui->prescription->text();
    QString medecine_id = ui->name_cure->text();

    QString descripriom = ui->description_cure->text();
    QString effects = ui->effects_cure->text();
    QPixmap inPixmap(QPixmap("D:/Qt/medhelper_new/biba/cure.jpg")); // Сохраняем его в изображение объекта QPixmap;
    QByteArray inByteArray; // Создаём объект QByteArray для сохранения изображения QBuffer
    QBuffer inBuffer( &inByteArray );
    inPixmap.save( &inBuffer, "JPG" );

    db->insertIntoTable2(patient_name, doctor_name, date, address, symptoms, diagnosis, prescription, medecine_id);
    //model->select();
    db->insertIntoTable(medecine_id, inByteArray, descripriom, effects);
    model->select();
}


void doctor_call::on_delete_call_clicked()
{
    QModelIndex current = ui->tableView3->currentIndex();
    int id = current.sibling(current.row(), 0).data ().toInt ();
    QSqlQuery query;
    query.prepare("delete from calls where (ID = "+QString::number(id)+")");
    query.exec();
    model->select();
}


void doctor_call::on_enter_patient_clicked()
{
    QSqlQuery query2;
    query2.exec("SELECT * FROM calls WHERE diagnosis LIKE '"+ui->search_patient->text()+"'");
    int i = 0;
    while (query2.next()) {
        if (query2.value(0).toInt() != 0){
            i++;
        }
    }
    ui->label_text1->setNum(i);
}


void doctor_call::on_enter_call_clicked()
{
    QSqlQuery query2;
    query2.exec("SELECT * FROM calls WHERE date LIKE '"+ui->search_call->text()+"'");
    int i = 0;
    while (query2.next()) {
        if (query2.value(0).toInt() != 0){
            i++;
        }
    }
    ui->label_text1_2->setNum(i);

}


void doctor_call::on_back_clicked()
{
    this->close();
    emit ShowDoc();
}

