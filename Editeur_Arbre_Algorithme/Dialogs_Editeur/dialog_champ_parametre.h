#ifndef DIALOG_CHAMP_PARAMETRE_H
#define DIALOG_CHAMP_PARAMETRE_H

#include <QDialog>
#include<QCheckBox>
#include<QTreeWidget>
#include<QCompleter>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>

namespace Ui {
class Dialog_champ_parametre;
}

class Dialog_champ_parametre : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_champ_parametre(int operation, Gestion_Arbre_Algo * ArbreAlgo, QString typeCourant);
    ~Dialog_champ_parametre();
    QWidget *passe_var_Widget;
    QTreeWidget *liste_champs;
    QTreeWidget *liste_parametres;
    QList<QString> *types_var;

private slots:
    void on_buttonBox_accepted();

    void on_nom_textChanged(const QString &arg1);

    void on_Type_textChanged(const QString &arg1);

private:
    Ui::Dialog_champ_parametre *ui;
    bool sous_modification;
    QStringList listeTypes;
    QCompleter * CompleterTypes;
    QCompleter * Completer_TypesContenu;
    QString Controle_NomCP();
    QString Controle_TypeCP();
    QString nom,type,TypeCourant;
    int Operation;
    Gestion_Arbre_Algo * ArbreAlgo;
    QStringList listeNoms;
    QStringList listeTypesContenu;

};

#endif // DIALOG_CHAMP_PARAMETRE_H
