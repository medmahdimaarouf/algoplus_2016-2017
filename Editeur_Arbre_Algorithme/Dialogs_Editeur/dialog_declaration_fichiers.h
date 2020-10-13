#ifndef DIALOG_DECLARATION_FICHIERS_H
#define DIALOG_DECLARATION_FICHIERS_H

#include <QDialog>
#include<QtXml>
#include<QtGui>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
#include<QCompleter>
namespace Ui {
class Dialog_Declaration_Fichiers;
}

class Dialog_Declaration_Fichiers : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Declaration_Fichiers(Gestion_Arbre_Algo *Arbre_Algo);
    ~Dialog_Declaration_Fichiers();
    Gestion_Arbre_Algo * ArbreAlgo;

    void metter_sous_modification();

private slots:
    void on_buttonBox_accepted();

    void on_nom_textChanged(const QString &arg1);

    void on_contenu_textChanged(const QString &arg1);

private:

    Ui::Dialog_Declaration_Fichiers *ui;
    bool sous_modification;
    QString Controle_NomType();
    QString controle_ContenuType();
    QString nomtype,contenuType,nom_Courant;
    QStringList listeTypes,listesContenuType;
    QCompleter * CompleterTypes,*CompleterContenuType;


};

#endif // DIALOG_DECLARATION_FICHIERS_H
