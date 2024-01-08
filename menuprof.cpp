#include "menuprof.h"
#include "ui_menuprof.h"
#include "menu.h"
#include "ui_menu.h"
#include "widget.h"
#include <QMessageBox>
//#include <note_abs.h>
#include <QPixmap>


menuProf::menuProf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuProf)
{
    ui->setupUi(this);

}

menuProf::~menuProf()
{
    delete ui;
}

void menuProf::on_pushButton_ajouter_6_clicked()
{
    Widget conn;

    QString ID_Etud = ui->texte_CNE_Etudiant_2->text();
    QString ID_Matier = ui->texte_Id_Matier_2->text();
    QString Note = ui->texte_Note_2->text();
    QDate date = ui->Date->date();
    QString dateStr = date.toString();

    if (ID_Etud.isEmpty() || ID_Matier.isEmpty() || Note.isEmpty()) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please fill in all the fields."));
        return;
    }

    if (!conn.connOpen()) {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery checkQuery;

    // Check if the provided ID_Etud exists in Etudiant table
    checkQuery.prepare("SELECT CNE FROM Etudiant WHERE CNE = :id_etudiant");
    checkQuery.bindValue(":id_etudiant", ID_Etud);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::critical(this, tr("Error"), tr("ID_Etud not found in Etudiant table"));
        conn.connClose();
        return;
    }

    // Check if the provided ID_Matier exists in Matiere table
    checkQuery.prepare("SELECT id FROM Matiere WHERE id = :id_matiere");
    checkQuery.bindValue(":id_matiere", ID_Matier);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::critical(this, tr("Error"), tr("ID_Matier not found in Matiere table"));
        conn.connClose();
        return;
    }




    QSqlQuery query;

    //query.prepare("insert into Note (note , date,) values('" + Note + "','" + ID_Matier + "','" + Note + "');");

    query.prepare("insert into Note (note , date, id_etudiant, id_mattiere ) values('" + Note + "','" + dateStr + "','" + ID_Etud + "','" + ID_Matier + "');");

    qDebug() << query.lastQuery();

    if (query.exec()) {
        QMessageBox msgBox;
        msgBox.setText("The Note has been Saved.");
        msgBox.exec();
    } else {
        QMessageBox::critical(this, tr("ERROR::"), tr("Error saving Note"));
    }

    conn.connClose();
}


//-------------------------------------------------------------
void menuProf::on_pushButton_supprimer_6_clicked()
{
    Widget conn;

    // Assuming you have a QLineEdit for input
    QString ID_Etud = ui->texte_CNE_Etudiant_2->text();
    QString ID_Matr = ui->texte_Id_Matier_2->text();

    if (!conn.connOpen()){
        qDebug() << "Failed to open database";
        return;
    }

    conn.connOpen();
    QSqlQuery query;

    query.prepare("DELETE FROM Note WHERE id_etudiant = :ID_Etud  and id_mattiere = :ID_Matr  ");
    query.bindValue(":ID_Etud", ID_Etud);
    query.bindValue(":ID_Matr", ID_Matr);


    qDebug() << query.lastQuery();

    if (query.exec()) {
        QMessageBox msgBox;
        msgBox.setText("The Note has been deleted.");
        msgBox.exec();
    } else {
        QMessageBox::critical(this, tr("ERROR::"), tr("Error deleting Note"));
    }

    conn.connClose();
}


//-------------------------------------------------------------

void menuProf::on_pushButton_afficher_6_clicked()
{
    Widget conn;
    QSqlQueryModel *Modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *query = new QSqlQuery(conn.mydb);

    // Perform the join operation and select the required columns
    query->prepare("SELECT * FROM Note");

    if (query->exec()) {
        // Set the query result to the model
        Modal->setQuery(*query);
        // Set the model to the QTableView
        ui->tableView->setModel(Modal);
    }

    conn.connClose();
}


//-------------------------------------------------------------





//****************************************************************************

void menuProf::on_pushButton_All_Etudiant_8_clicked()
{
    Widget conn;
    QSqlQueryModel *Modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *query = new QSqlQuery(conn.mydb);
    query->prepare("SELECT * FROM Etudiant");
    query->exec();
    Modal->setQuery(*query);
    ui -> tableView_2->setModel(Modal);


    conn.connClose();

}
//-------------------------------------------------------------

void menuProf::on_pushButton_All_Matiers_8_clicked()
{
    Widget conn;
    QSqlQueryModel *Modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *query = new QSqlQuery(conn.mydb);
    query->prepare("SELECT * FROM Matiere");
    query->exec();
    Modal->setQuery(*query);
    ui -> tableView_2->setModel(Modal);
}

//-------------------------------------------------------------
















