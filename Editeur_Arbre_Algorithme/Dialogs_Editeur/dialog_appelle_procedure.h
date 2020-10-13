#ifndef DIALOG_APPELLE_PROCEDURE_H
#define DIALOG_APPELLE_PROCEDURE_H

#include <QDialog>
#include<QCompleter>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_appelle_procedure;
}

class Dialog_appelle_procedure : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_appelle_procedure(int index,Gestion_Arbre_Algo *ArbreAlgo);
    ~Dialog_appelle_procedure();

    QStringList listeProcs;
    void metter_sous_modification();


private slots:
    void on_buttonBox_accepted();

    void on_Parametres_textChanged(const QString &arg1);

    void on_nomproc_textChanged(const QString &arg1);

private:
    Ui::Dialog_appelle_procedure *ui;
    Gestion_Arbre_Algo * Arbre_Algo;
    int nbrParas,index;
    bool sous_modification;
    QString nomproc,defproc,parametres;
    void init_context(int index, QString titre);
    QString ControleSaise_Parametres();
    QString ControleSaisie_NomProc();
    QCompleter * Completer_Procs;

};

#endif // DIALOG_APPELLE_PROCEDURE_H
