#ifndef DIALOG_ECRIRE_H
#define DIALOG_ECRIRE_H

#include <QDialog>
#include<QMessageBox>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_Ecrire;
}

class Dialog_Ecrire : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Ecrire(Gestion_Arbre_Algo * ArbreAlgo);
    ~Dialog_Ecrire();
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();
    void message_change();

private:
    Ui::Dialog_Ecrire *ui;
    Gestion_Arbre_Algo * Arbre_Algo;
    bool sous_modification;
    QString controle_saisie_msg();
    QString message;
};

#endif // DIALOG_ECRIRE_H
