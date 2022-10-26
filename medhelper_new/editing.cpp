#include "editing.h"
#include "ui_editing.h"
//#include "dialog_login.h"
#include <QBuffer>
#include <QScreen>
#include <QApplication>
#include <QFileDialog>
#include <QDialog>
#include <QSqlQueryModel>
#include <QImage>
#include <QPixmap>
#include <QColor>


void Editing::on_extra_functions_clicked()
{
    this->close();
    doc->show();
}


Editing::Editing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editing)
{
    ui->setupUi(this);

    // установка фона приложения
    QPixmap pix("/home/sis201331/medhelper_new/biba/fon.jpg");
    int w = ui->label_2->width();
    int h = ui->label_2->height();
    ui->label_2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    db = new DataBase();
    db->connectToDataBase();
    doc = new doctor_call;
    connect(doc, &doctor_call::ShowDoc,this,&Editing::show);
    //отображение столбцов БД в следующем виде
    this->setupModel(TABLE_1,
                    QStringList() << trUtf8("Номер лекарства")
                                  << trUtf8("Название лекарства")
                                  << trUtf8("Фото")
                                  << trUtf8("Описание")
                                  << trUtf8("Побочные эффекты"));
    this->createUI();
}

//получение таблицы из БД
void Editing::setupModel(const QString &tableName, const QStringList &headers){
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    for (int i = 1,j = 0; i < model->columnCount();i++,j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    //Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void Editing::createUI()
    {
     ui->tableView2->setModel(model);

     QHeaderView *verticalHeader = ui->tableView2->verticalHeader();
     verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
     verticalHeader->setDefaultSectionSize(700);

     QHeaderView *horizontalHeader = ui->tableView2->horizontalHeader();
     horizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
     horizontalHeader->setDefaultSectionSize(250);

     //Скрываем определенные поля из БД

     // ui->tableView2->setColumnHidden(0, true);
     ui->tableView2->setColumnHidden(0, true);
     //ui->tableView2->setColumnHidden(1, true);
     //ui->tableView2->setColumnHidden(3, true);
     //ui->tableView2->setColumnHidden(4, true);
     ui->tableView2->setColumnHidden(2, true);
     //ui->tableView2->setColumnHidden(6, true);

     ui->tableView2->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView2->horizontalHeader()->setStretchLastSection(true);
     model->setEditStrategy(QSqlTableModel::OnManualSubmit); //редактирование строк

     /* Подключаем сигнал об изменении выбора текущей строки в таблицу
          * к СЛОТу для установки изображения в picLabel
          * */
     connect(ui->tableView2->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                 this, SLOT(slotCurrentPic(QModelIndex)));

     model->select();
    }

Editing::~Editing()
{
    delete ui;
}

void Editing::slotCurrentPic(QModelIndex index)
{
    QPixmap outPixmap = QPixmap(); // Создаём QPixmap, который будет помещаться в picLabel
    /* Забираем данные об изображении из таблицы в качестве QByteArray
     * и помещаем их в QPixmap
     * */
     outPixmap.loadFromData(model->data(model->index(index.row(), 2)).toByteArray());
    // Устанавливаем изображение в picLabel
    image.loadFromData(model->data(model->index(index.row(), 2)).toByteArray());
    ui->picLabel2->setPixmap(outPixmap.scaled(500,400));
    ui->picLabel2->setPixmap(QPixmap::fromImage(image));
}


void Editing::on_download_photo_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Select one or more files to open",
                                                    "/home",
                                                    "Images (*.png *.xpm *.jpg)");
    QPixmap inPixmap(fileName); // Сохраняем его в изображение объекта QPixmap;
    QByteArray inByteArray; // Создаём объект QByteArray для сохранения изображения QBuffer
    QBuffer inBuffer( &inByteArray );
    inPixmap.save( &inBuffer, "PNG" );
    QString name_photo = ui->name_cure->text();
    QString descripriom = ui->description_cure->text();
    QString effects = ui->effects_cure->text();
    db->insertIntoTable(name_photo, inByteArray, descripriom, effects);
}


void Editing::on_add_cure_clicked()
{
    model->select();
}


void Editing::on_delete_cure_clicked()
{
    QModelIndex current = ui->tableView2->currentIndex();
    int id = current.sibling(current.row(), 0).data ().toInt ();
    QSqlQuery query;
    query.prepare("delete from medicine where (ID = "+QString::number(id)+")");
    query.exec();
    model->select();
}


void Editing::on_save_cure_clicked()
{
    if(model->submitAll())
        model->database().commit();
    else
        model->database().rollback();
}




