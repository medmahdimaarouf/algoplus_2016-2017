#ifndef DIALOG_POUR_FAIRE_H
#define DIALOG_POUR_FAIRE_H

#include <QDialog>
#include<QtGui>
#include<QMessageBox>
#include<QCompleter>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_Pour_Faire;
}

class Dialog_Pour_Faire : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Pour_Faire(Gestion_Arbre_Algo * ArbreAlgo);
    ~Dialog_Pour_Faire();
    Gestion_Arbre_Algo * ArbreAlgo;
    void metter_sous_modification();

private slots:
    void on_buttonBox_accepted();
    void Comteur_Change();
    
private:
    Ui::Dialog_Pour_Faire *ui;
    bool sous_modification;
    QString cmp,vi,vf;
    QString Controle_Compteur();
    QCompleter * CompleterCMP;
    QStringList listevariables;

};

#endif // DIALOG_POUR_FAIRE_H
