#ifndef WIDGET_H
#define WIDGET_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <menu.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);

    }
    bool connOpen() {
        // Close existing connection if it exists
        if (mydb.isOpen()) {
            mydb.close();
            mydb.removeDatabase(QSqlDatabase::defaultConnection);
        }

        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/hay/Desktop/projet/gestion_notes.db");

        if (!mydb.open()) {
            qDebug() << "Failed to open the database";
            return false;
        } else {
            qDebug() << "Connected...";
            return true;
        }
    }


    int sqlSize(QSqlQuery query)
    {
        int initialPos = query.at();
        // Very strange but for no records .at() returns -2
        int pos = 0;
        if (query.last())
            pos = query.at() + 1;
        else
            pos = 0;
        // Important to restore initial pos
        query.seek(initialPos);
        return pos;
    }

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
