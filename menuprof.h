#ifndef MENUPROF_H
#define MENUPROF_H

#include <QDialog>

namespace Ui {
class menuProf;
}

class menuProf : public QDialog
{
    Q_OBJECT

public:
    explicit menuProf(QWidget *parent = nullptr);
    ~menuProf();

private slots:
    void on_pushButton_ajouter_6_clicked();

    void on_pushButton_supprimer_6_clicked();

    void on_pushButton_afficher_6_clicked();

    void on_pushButton_All_Etudiant_8_clicked();

    void on_pushButton_All_Matiers_8_clicked();

private:
    Ui::menuProf *ui;
};

#endif // MENUPROF_H
