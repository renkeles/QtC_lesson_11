#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>

#define TABLE "TableTask"
#define DATABASE_NAME "DataBase.db"
#define DATABASE_HOSTNAME "DataBaseHost"


class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    void connectToDataBase();
    bool inserIntoTable(const QVariantList &data);

private:
    QSqlDatabase db;

    bool openDataBase();
    bool restoreDataBase();
    bool createTable();
};

#endif // DATABASE_H
