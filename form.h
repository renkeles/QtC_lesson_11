#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QSqlTableModel>
#include "database.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

signals:
    void mainwindow();

private slots:
    void on_pushButton_clicked();
    void getForm(QString, QDate, int);
    void updateForm();

private:
    Ui::Form *ui;
    DataBase *db;
    QSqlTableModel *model;
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // FORM_H
