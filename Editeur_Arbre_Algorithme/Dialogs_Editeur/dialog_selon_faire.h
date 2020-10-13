#ifndef DIALOG_SELON_FAIRE_H
#define DIALOG_SELON_FAIRE_H
#include<QtGui>
#include <QDialog>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_Selon_faire;
}

class Dialog_Selon_faire : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Selon_faire(QString selecteur,Gestion_Arbre_Algo * Arbre_Algo);
    ~Dialog_Selon_faire();
    Gestion_Arbre_Algo *Arbre_Algo;
    QList<QStandardItem *> list_choix;
    void metter_sous_modification();

private slots:
    void on_Ajouter_clicked();

    void on_supprimer_c_clicked();

    void on_supprimer_t_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_Selon_faire *ui;
    bool sous_modification;

};

#endif // DIALOG_SELON_FAIRE_H
