#ifndef DIALOG_LIRE_VARIABLE_H
#define DIALOG_LIRE_VARIABLE_H

#include <QDialog>
#include<QMessageBox>
#include<QCompleter>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_Lire_Variable;
}

class Dialog_Lire_Variable : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Lire_Variable(Gestion_Arbre_Algo * ArbreAlgo);
    ~Dialog_Lire_Variable();
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();

    void message_change();

    void variable_change();

private:
    Ui::Dialog_Lire_Variable *ui;
    Gestion_Arbre_Algo * Arbre_Algo;
    bool sous_modification;
    QStringList listeVras;
    QCompleter * CompleterVars;
    QString variable,message;
    QString Controlemessage();
    QString Controlevariable();

};

#endif // DIALOG_LIRE_VARIABLE_H
