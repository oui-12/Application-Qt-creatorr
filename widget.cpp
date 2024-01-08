#include "widget.h"
#include "menu.h"
#include "menuProf.h"
#include "ui_widget.h"
#include <QPixmap>

#include <QtSql>
#include <QDebug>
#include <QFileInfo>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap pix(":/Ressourses/Picture/1.png");

    if (!connOpen())
        ui->label->setText("Failed to open the database");
    else
        ui->label->setText("Conneted...");


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked() {
    QString username = ui->lineEdit_Username->text();
    QString password = ui->lineEdit_Password->text();

    if (!connOpen()) {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM ADMIN WHERE Username = :username AND Password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
    }

    int adminResultCount = 0;
    while (query.next()) {
        adminResultCount++;
    }

    QSqlQuery profQuery;
    profQuery.prepare("SELECT * FROM Professeur WHERE Username = :username AND Password = :password");
    profQuery.bindValue(":username", username);
    profQuery.bindValue(":password", password);

    if (!profQuery.exec()) {
        qDebug() << "Query execution error:" << profQuery.lastError().text();
    }

    int profResultCount = 0;
    while (profQuery.next()) {
        profResultCount++;
    }

    if (adminResultCount > 0) {
        qDebug() << "PASSWORD IS CORRECT - ADMIN";
        mydb.close();
        this->hide();
        Menu menu;
        menu.setModal(true);
        menu.exec();
    }
    else if (profResultCount > 0) {
        qDebug() << "PASSWORD IS CORRECT - PROFESSEUR";
        mydb.close();
        this->hide();
        menuProf menuprof;
        menuprof.setModal(true);
        menuprof.exec();
    } else {
        ui->label_Login->setText("The username or password is incorrect.");
    }
}



//"SELECT * FROM ADMIN WHERE Username = ''aa'' AND password = ''"
//"SELECT * FROM ADMIN WHERE Username = 'admin' AND password = 123456789"
//"SELECT * FROM ADMIN WHERE Username = 'admin' AND password = 123456789"
//"SELECT * FROM ADMIN WHERE Username = 'admin' AND password = '123456789'"
