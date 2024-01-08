#include "menu.h"
#include "ui_menu.h"
#include "widget.h"
#include <QMessageBox>
//#include <note_abs.h>
#include <QPixmap>

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    QPixmap pix(":/Ressourses/Picture/");
    ui->label_Picture->setPixmap(pix);
    Widget conn;
    if (!conn.connOpen())
        ui->label_menu->setText("Failed to open the database");
    else
        ui->label_menu->setText("Conneted...");

}

Menu::~Menu()
{
    delete ui;
}



void Menu::on_pushButton_ajouter_clicked()
{
    Widget conn;
    QString CNE = ui->texte_CNE->text();
    QString Nom = ui->texte_Nom->text();
    QString Prenom = ui->texte_prenom->text();
    QDate DN = ui->DN->date();
    QString Birthday = DN.toString();

    // Check if any of the input fields is empty
    if (CNE.isEmpty() || Nom.isEmpty() || Prenom.isEmpty() || Birthday.isEmpty()) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please fill in all the fields."));
        return;
    }

    if (!conn.connOpen()) {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery query;

    query.prepare("insert into Etudiant (CNE , Nom, Prénom, Date_de_naissance) values('" + CNE + "','" + Nom + "','" + Prenom + "','" + Birthday + "');");

    qDebug() << query.lastQuery();

    if (query.exec()) {
        QMessageBox msgBox;
        msgBox.setText("L'étudiant a bien été enregistré!");
        msgBox.exec();
    } else {
        QMessageBox::critical(this, tr("Database Error"), tr("Error inserting student into the database"));
    }

    conn.connClose();
}



//--------------------------------------------------------------------------
void Menu::on_pushButton_modifier_clicked()
{
    Widget conn;
    QString CNE = ui  -> texte_CNE -> text();
    QString Nom = ui  ->  texte_Nom-> text();
    QString Prenom = ui  ->  texte_prenom-> text();
    QDate DN = ui  ->  DN -> date();
    QString Birthday=DN.toString();

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

    conn.connOpen();
    QSqlQuery query;


    query.prepare("UPDATE Etudiant SET CNE ='"+CNE+"',Nom='"+Nom+"',Prénom='"+Prenom+"',Date_de_naissance='"+Birthday+"' WHERE CNE ='"+CNE+"';");
    qDebug() << query.lastQuery();


    if (query.exec()){
        QMessageBox msgBox;
        msgBox.setText("L'étudiant a bien été modifier!");
        msgBox.exec();
        conn.connClose();}

    else
        QMessageBox::critical(this,tr("ERROR::"),tr("ERRORRRRRRRR"));


}
//-----------------------------------------------------------------
void Menu::on_pushButton_supprimer_clicked()
{
    Widget conn;
    QString CNE = ui  -> texte_CNE -> text();
    QString Nom = ui  ->  texte_Nom-> text();
    QString Prenom = ui  ->  texte_prenom-> text();
    QDate DN = ui  ->  DN -> date();
    QString Birthday=DN.toString();

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;
//query.exec("create table Student(CNE int primary key, "
//       "Nom varchar(20), Prénom varchar(20),Date_de_naissance int)");

//query.exec("SELECT CNE,Nom,Prénom,Date_de_naissance FROM Student WHERE CNE="+CNE+";");
//qDebug() << query.lastQuery();

query.prepare("DELETE FROM Etudiant WHERE CNE ='"+CNE+"';");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("The student has been deleted.");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("ERRORRRRRRRR"));

}
//-------------------------------------------------------------
void Menu::on_pushButton_afficher_clicked()
{
     Widget conn;
     QSqlQueryModel *Modal = new QSqlQueryModel();

     conn.connOpen();
     QSqlQuery *query = new QSqlQuery(conn.mydb);
     query->prepare("SELECT * FROM Etudiant");
     query->exec();
     Modal->setQuery(*query);
     ui -> tableView->setModel(Modal);


     conn.connClose();

}

//*******************************************************************

void Menu::on_pushButton_ajouter_2_clicked()
{
    Widget conn;

    QString Id = ui->texte_Id->text();
    QString name = ui->texte_NameMatiere_2->text();

    // Check if any of the input fields is empty
    if (Id.isEmpty() || name.isEmpty()) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please fill in all the fields."));
        return;
    }

    if (!conn.connOpen()) {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery query;

    query.prepare("insert into Matiere values('" + Id + "','" + name + "');");
    qDebug() << query.lastQuery();

    if (query.exec()) {
        QMessageBox msgBox;
        msgBox.setText("The Matiere has been Saved.");
        msgBox.exec();
    } else {
        QMessageBox::critical(this, tr("ERROR::"), tr("Error saving Matiere"));
    }

    conn.connClose();
}




//-------------------------------------------------------------

void Menu::on_pushButton_supprimer_2_clicked()
{
    Widget conn;

    // Assuming you have a QLineEdit for input
    QString matiereToDelete = ui->texte_NameMatiere_2->text();

    if (!conn.connOpen()){
        qDebug() << "Failed to open database";
        return;
    }

    conn.connOpen();
    QSqlQuery query;

    query.prepare("DELETE FROM Matiere WHERE Name = :matiereToDelete");
    query.bindValue(":matiereToDelete", matiereToDelete);

    qDebug() << query.lastQuery();

    if (query.exec()) {
        QMessageBox msgBox;
        msgBox.setText("The Matiere has been deleted.");
        msgBox.exec();
    } else {
        QMessageBox::critical(this, tr("ERROR::"), tr("Error deleting Matiere"));
    }

    conn.connClose();
}




void Menu::on_pushButton_afficher_2_clicked()
{
    Widget conn;
    QSqlQueryModel *Modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *query = new QSqlQuery(conn.mydb);
    query->prepare("SELECT * FROM Matiere");
    query->exec();
    Modal->setQuery(*query);
    ui -> tableView->setModel(Modal);

}

//*****************************************************************************




//*****************************************************************************

void Menu::on_pushButton_ajouter_3_clicked()
{
    Widget conn;
    QString idProf = ui->texte_Id_Prof_2->text();
    QString UsrNameProf = ui->texte_userName_prof_3->text();
    QString PasswordProf = ui->texte_Password_Prof_5->text();

    if (idProf.isEmpty() || UsrNameProf.isEmpty() || PasswordProf.isEmpty()) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please fill in all the fields."));
        return;
    }

    if (!conn.connOpen()) {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery query(conn.mydb);

    query.prepare("INSERT INTO Professeur (id, Username, password) "
                  "VALUES (:idProf, :UsrNameProf, :PasswordProf)");
    query.bindValue(":idProf", idProf);
    query.bindValue(":UsrNameProf", UsrNameProf);
    query.bindValue(":PasswordProf", PasswordProf);

    qDebug() << query.lastQuery();

    if (query.exec()) {
        QMessageBox msgBox;
        msgBox.setText("Professeur a bien été enregistré!");
        msgBox.exec();
    } else {
        QMessageBox::critical(this, tr("Database Error"), tr("Error inserting Professeur into the database: ") + query.lastError().text());
    }

    conn.connClose();
}
//-------------------------------------------------------------

void Menu::on_pushButton_supprimer_3_clicked()
{
    Widget conn;

    QString idProf = ui->texte_Id_Prof_2->text();

    if (!conn.connOpen()){
        qDebug() << "Failed to open database";
        return;
    }

    conn.connOpen();
    QSqlQuery query;

    query.prepare("DELETE FROM Professeur WHERE id = :IdProf");
    query.bindValue(":IdProf", idProf);

    qDebug() << query.lastQuery();

    if (query.exec()) {
        QMessageBox msgBox;
        msgBox.setText("The Professeur has been deleted.");
        msgBox.exec();
    } else {
        QMessageBox::critical(this, tr("ERROR::"), tr("Error deleting Matiere"));
    }

    conn.connClose();
}



//-------------------------------------------------------------



void Menu::on_pushButton_afficher_3_clicked()
{
    Widget conn;
    QSqlQueryModel *Modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *query = new QSqlQuery(conn.mydb);

    query->prepare("SELECT * FROM Professeur");

    if (query->exec()) {

        Modal->setQuery(*query);
        ui->tableView->setModel(Modal);
    }

    conn.connClose();
}

//*****************************************************************************


