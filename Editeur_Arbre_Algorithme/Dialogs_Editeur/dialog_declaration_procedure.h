#ifndef DIALOG_DECLARATION_PROCEDURE_H
#define DIALOG_DECLARATION_PROCEDURE_H

#include <QDialog>
#include<QtXml>
#include<QtGui>
#include<QWidget>
#include<QCompleter>
#include"Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h"
#include"dialog_champ_parametre.h"
namespace Ui {
class Dialog_Declaration_Procedure;
}

class Dialog_Declaration_Procedure : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Declaration_Procedure(bool estFonction,Gestion_Arbre_Algo * Arbre_Algo);
    ~Dialog_Declaration_Procedure();
    QDomDocument * documentAlgo;
    QWidget * widget_return;
    Gestion_Arbre_Algo * ArbreAlgo;
    Dialog_champ_parametre * champ_parametre;
    bool isfunc;
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();

    void on_Ajouterparametre_clicked();

    void on_supprimerparametre_c_clicked();

    void on_supprimer_t_clicked();

    void on_nom_textChanged(const QString &arg1);

    void on_returntype_textChanged(const QString &arg1);

private:
    Ui::Dialog_Declaration_Procedure *ui;
    QList<QStandardItem*> list__fct_programs;
    bool sous_modification;
    QString Controle_nomProgram();
    QString Controle_RetourneProgram();
    QStringList listeprgramme,ListeTypes,ListeTypesContenu;
    QCompleter * Competerprgrammes,*CompleterTypesContenu;
    QString nom,retourne,nom_modif;




};

#endif // DIALOG_DECLARATION_PROCEDURE_H
