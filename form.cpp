#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();
    Form::updateForm();

}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    this->close();
    emit mainwindow();
}

void Form::getForm(QString task, QDate date, int priority)
{
    QVariantList data;
    data.append(task);
    data.append(date);
    data.append(priority);


    model->clear();
    db->inserIntoTable(data);
    Form::updateForm();

}

void Form::updateForm()
{
    this->setupModel(TABLE, QStringList() << trUtf8("id")
                                          << trUtf8("Задача")
                                          << trUtf8("Дата завершения")
                                          << trUtf8("Приоритет")
                     );
    this->createUI();
}

void Form::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); ++i, ++j)
    {
        model->setHeaderData(i, Qt::Horizontal, headers[j]);
    }

    model->setSort(0, Qt::AscendingOrder);
}

void Form::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select();

}

