#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    form = new Form;
    connect(form, &Form::mainwindow, this, &MainWindow::show);
    connect(this, SIGNAL(sendForm(QString, QDate, int)), form, SLOT(getForm(QString, QDate, int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    task = ui->lineEdit->text();
    date = ui->dateEdit->date();
    priority = ui->spinBox->value();
    sendForm(task, date, priority);
}


void MainWindow::on_pushButton_2_clicked()
{
    form->show();
    this->close();
}

