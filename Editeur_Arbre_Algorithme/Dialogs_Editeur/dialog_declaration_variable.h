#ifndef DIALOG_DECLARATION_VARIABLE_H
#define DIALOG_DECLARATION_VARIABLE_H

#include <QDialog>
#include<QtXml>
#include<QtGui>
#include<QCompleter>
#include"Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h"
typedef struct programs{
    QStandardItem * std_program;
    QDomElement elm_program;
}p;

namespace Ui {
class Dialog_Declaration_variable;
}

class Dialog_Declaration_variable : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Declaration_variable(Gestion_Arbre_Algo * ArbreAlgo);
    ~Dialog_Declaration_variable();

    Gestion_Arbre_Algo * Arbre_Algo;

    void metter_sous_modification();

private slots:

    void on_buttonBox_accepted();

    void on_nom_textChanged(const QString &arg1);

    void on_Type_textChanged(const QString &arg1);

    void on_program_currentTextChanged(const QString &arg1);

private:

    Ui::Dialog_Declaration_variable *ui;
    bool sous_modification;
    //QList<QStandardItem*> listSousProgram;
    QStringList listevars;
    QStringList listeTypesVar;
    QCompleter * completerTypes,*CompleterVariables;
    QString nom,type,nom_Courant;
    QString ControleVariable();
    QString Controle_Type();


};

#endif // DIALOG_DECLARATION_VARIABLE_H
