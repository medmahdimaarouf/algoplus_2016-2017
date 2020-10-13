#ifndef DIALOG_DECLARATION_ENREGISTREMENT_H
#define DIALOG_DECLARATION_ENREGISTREMENT_H

#include <QDialog>
#include<QtXml>
#include<QtGui>
#include"Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h"
#include"dialog_champ_parametre.h"
#include<QCompleter>
namespace Ui {
class Dialog_Declaration_Enregistrement;
}

class Dialog_Declaration_Enregistrement : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Declaration_Enregistrement(Gestion_Arbre_Algo  *Arbre_Algo);
    ~Dialog_Declaration_Enregistrement();
    Gestion_Arbre_Algo * ArbreAlgo;
    Dialog_champ_parametre * champ_parametre;
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();

    void on_Ajouterchamp_clicked();

    void on_supprimerchams_c_clicked();

    void on_supprimer_t_clicked();
    void on_nom_textChanged(const QString &arg1);

private:
    Ui::Dialog_Declaration_Enregistrement *ui;
    bool sous_modification;
    QStringList listeTypes;
    QCompleter * CompleterTypes;
    QString nomType,nom_Courant;
    QString Controle_NomType();


};

#endif // DIALOG_DECLARATION_ENREGISTREMENT_H
