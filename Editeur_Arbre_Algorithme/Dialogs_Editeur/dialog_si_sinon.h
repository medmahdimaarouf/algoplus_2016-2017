#ifndef DIALOG_SI_SINON_H
#define DIALOG_SI_SINON_H

#include <QDialog>
#include<QtXml>
#include<QtGui>
#include<QMessageBox>
#include"Editeur_Arbre_Algorithme/Gestionnaire_appercu/get_appercu.h"
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_SI_SINON;
}

class Dialog_SI_SINON : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_SI_SINON(Gestion_Arbre_Algo * Arbre_Algo);
    ~Dialog_SI_SINON();
    Gestion_Arbre_Algo * ArbreAlgo;
    void metter_sous_modification();

private slots:
    void on_buttonBox_accepted();

    void condition_Change();

private:
    Ui::Dialog_SI_SINON *ui;
    bool sous_modification;
    QString Controle_Condition();
    QString condition;

};

#endif // DIALOG_SI_SINON_H
