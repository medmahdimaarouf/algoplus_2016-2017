#ifndef DIALOG_REPETER_JUSQUA_H
#define DIALOG_REPETER_JUSQUA_H

#include <QDialog>
#include<QtGui>
#include<QMessageBox>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_Repeter_jusqua;
}

class Dialog_Repeter_jusqua : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Repeter_jusqua(Gestion_Arbre_Algo * Arbre_Algo);
    ~Dialog_Repeter_jusqua();
    Gestion_Arbre_Algo * Arbre_Algo;
    void metter_sous_modification();

private slots:
    void on_buttonBox_accepted();
    
    void condition_Change();

private:
    Ui::Dialog_Repeter_jusqua *ui;
    bool sous_modification;
    QString Controle_Condition();
    QString condition;

};

#endif // DIALOG_REPETER_JUSQUA_H
