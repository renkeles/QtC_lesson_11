#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{
    db.close();
}

void DataBase::connectToDataBase()
{
    if(!QFile("./" DATABASE_NAME).exists())
    {
        this->restoreDataBase();
    }else
    {
        this->openDataBase();
    }
}

bool DataBase::inserIntoTable(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " (Task , Deadline , Priority) VALUES (:Task, :Deadline, :Priority)");
    query.bindValue(":Task",        data[0].toString());
    query.bindValue(":Deadline",    data[1].toDate());
    query.bindValue(":Priority",    data[2].toInt());

    if(!query.exec())
    {
        qDebug() << "Error insert into" << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }else
    {
        return true;
    }
    return false;
}

bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("./" DATABASE_NAME);
    if(db.open())
    {
        return true;
    }else
    {
        return false;
    }
}

bool DataBase::restoreDataBase()
{
    if(this->openDataBase())
    {
        if(!this->createTable())
        {
            return false;
        }else
        {
            return true;
        }
    }else
    {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBase::createTable()
{
    QSqlQuery query;
    if(!query.exec("CREATE TABLE " TABLE " (id INTEGER PRIMARY KEY AUTOINCREMENT, Task VARCHAR(255) NOT NULL, Deadline DATE NOT NULL, Priority INTEGER NOT NULL)"))
    {
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }else
    {
        return true;
    }
    return false;
}
