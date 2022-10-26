#include "viewing.h"
#include "ui_viewing.h"

Viewing::Viewing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Viewing)
{
    ui->setupUi(this);
    db = new DataBase();
    db->connectToDataBase();
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
void Viewing::setupModel(const QString &tableName, const QStringList &headers){
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    for (int i = 0,j = 0; i < model->columnCount();i++,j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    //Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void Viewing::createUI()
    {



    //Скрываем определенные поля из БД
    ui->tableView->setModel(model);
    QHeaderView *verticalHeader = ui->tableView->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(700);

    QHeaderView *horizontalHeader = ui->tableView->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
    horizontalHeader->setDefaultSectionSize(250);

    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(2, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    /* Подключаем сигнал об изменении выбора текущей строки в таблицу
         * к СЛОТу для установки изображения в picLabel
         * */
    connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
               this, SLOT(slotCurrentPic(QModelIndex)));

    model->select();


    }

Viewing::~Viewing()
{
    delete ui;
}

void Viewing::slotCurrentPic(QModelIndex index)
{
    // установка фона приложения
    QPixmap pix("/home/sis201331/medhelper_new/biba/fon.jpg");
    int w = ui->label_2->width();
    int h = ui->label_2->height();
    ui->label_2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    QPixmap outPixmap = QPixmap(); // Создаём QPixmap, который будет помещаться в picLabel
    /* Забираем данные об изображении из таблицы в качестве QByteArray
     * и помещаем их в QPixmap
     * */
    outPixmap.loadFromData(model->data(model->index(index.row(), 2)).toByteArray());
    // Устанавливаем изображение в picLabel
    ui->picLabel->setPixmap(outPixmap.scaled(500,400));
}

void Viewing::on_back_clicked()
{
    this->close();
    emit ShowMW();
}

