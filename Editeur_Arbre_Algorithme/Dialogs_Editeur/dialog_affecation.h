#ifndef DIALOG_AFFECATION_H
#define DIALOG_AFFECATION_H

#include <QDialog>
#include<QtGui>
#include<QMessageBox>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
#include<QCompleter>

namespace Ui {
class Dialog_Affecation;
}

class Dialog_Affecation : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Affecation(Gestion_Arbre_Algo * Arbre_Algo);
    ~Dialog_Affecation();
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();

    void on_Variable_textChanged(const QString &arg1);

    void on_valeur_textChanged(const QString &arg1);

private:
    Gestion_Arbre_Algo * ArbreAlgo;
    Ui::Dialog_Affecation *ui;
    QString controle_de_saisieVariable();
    QString controle_de_saisieExression();
    bool sous_modification;
    QString variable,expression;
    QStringList listeVariables;
    QCompleter * CompleterExression;
    QCompleter * CompleterVariable;

};

#endif // DIALOG_AFFECATION_H
