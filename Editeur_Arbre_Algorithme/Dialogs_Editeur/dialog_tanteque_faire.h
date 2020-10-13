#ifndef DIALOG_TANTEQUE_FAIRE_H
#define DIALOG_TANTEQUE_FAIRE_H

#include <QDialog>
#include<QtGui>
#include<QMessageBox>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_Tanteque_Faire;
}

class Dialog_Tanteque_Faire : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Tanteque_Faire(Gestion_Arbre_Algo * Arbre_Algo);
    ~Dialog_Tanteque_Faire();
    Gestion_Arbre_Algo * Arbre_Algo;
    void metter_sous_modification();

private slots:
    void on_buttonBox_accepted();

    void condition_Change();
    
private:
    Ui::Dialog_Tanteque_Faire *ui;
    bool sous_modification;
    QString condition;
    QString Controle_condition();

};

#endif // DIALOG_TANTEQUE_FAIRE_H
