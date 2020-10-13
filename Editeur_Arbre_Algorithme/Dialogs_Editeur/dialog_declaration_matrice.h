#ifndef DIALOG_DECLARATION_MATRICE_H
#define DIALOG_DECLARATION_MATRICE_H

#include <QDialog>
#include<QtXml>
#include<QtGui>
#include<QCompleter>
#include"Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h"
namespace Ui {
class Dialog_Declaration_Matrice;
}

class Dialog_Declaration_Matrice : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Declaration_Matrice(Gestion_Arbre_Algo * arbreAlgo);
    ~Dialog_Declaration_Matrice();
    Gestion_Arbre_Algo * Arbre_Algo;
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();
    void on_nom_textChanged(const QString &arg1);

    void on_Contenu_textChanged(const QString &arg1);

private:
    Ui::Dialog_Declaration_Matrice *ui;
    QString nom,contenu,nom_Courant;
    int ligne,colonne;
    bool sous_modification;
    QString Controle_NomType();
    QString Controle_TypeContenu();
    QStringList listeTypes,listeTpesContenu;
    QCompleter * CompleterTypes,* CompleterTypesContenu;



};

#endif // DIALOG_DECLARATION_MATRICE_H
