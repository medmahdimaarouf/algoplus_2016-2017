#ifndef DIALOG_DECLARATION_VECTEUR_H
#define DIALOG_DECLARATION_VECTEUR_H

#include <QDialog>
#include<QtXml>
#include<QtGui>
#include<QCompleter>
#include"Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h"
namespace Ui {
class Dialog_Declaration_Vecteur;
}

class Dialog_Declaration_Vecteur : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Declaration_Vecteur(Gestion_Arbre_Algo * Arbre_Algo);
    ~Dialog_Declaration_Vecteur();
    Gestion_Arbre_Algo * ArbreAlgo;
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();

    void on_nom_textChanged(const QString &arg1);

    void on_Type_textChanged(const QString &arg1);

private:
    Ui::Dialog_Declaration_Vecteur *ui;
    bool sous_modification;
    QString nom,contenu,nom_Courant;
    QString ControleNomType();
    QString ControleTypeContenu();
    QStringList listeTypesContenu,listeTypes;
    QCompleter * CompleterTypes,* CompleterTypesContenu;


};

#endif // DIALOG_DECLARATION_VECTEUR_H
