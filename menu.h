// menu.h
#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_afficher_clicked();
    void on_pushButton_ajouter_2_clicked();
    void on_pushButton_supprimer_2_clicked();
    void on_pushButton_afficher_2_clicked();

    //void on_pushButton_ajouter_6_clicked();

  //  void on_pushButton_supprimer_6_clicked();

  //  void on_pushButton_afficher_6_clicked();

    void on_pushButton_ajouter_3_clicked();

    void on_pushButton_supprimer_3_clicked();

    void on_pushButton_afficher_3_clicked();

private:
    Ui::Menu *ui;
    void displayErrorMessage(const QString& message);
};

#endif // MENU_H
