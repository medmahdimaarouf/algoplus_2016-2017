#ifndef DIALOG_RETOURNEFN_H
#define DIALOG_RETOURNEFN_H

#include <QDialog>
#include<QCompleter>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_RetourneFN;
}

class Dialog_RetourneFN : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_RetourneFN(Gestion_Arbre_Algo * ArbreAlgo);
    ~Dialog_RetourneFN();
    QStringList listefcts;
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();

    void retourne_Change();

    void fonction_Change();

private:
    Ui::Dialog_RetourneFN *ui;
    Gestion_Arbre_Algo * Arbre_Algo;
    bool sous_modification;
    QString Controle_retourne();
    QStringList ListeVariables;
    QCompleter * CompleterVars;
    QString retourne;

};

#endif // DIALOG_RETOURNEFN_H
