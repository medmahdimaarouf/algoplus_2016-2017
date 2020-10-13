#ifndef DIALOG_DECLARATION_CONST_H
#define DIALOG_DECLARATION_CONST_H

#include <QDialog>
#include<QtXml>
#include<QtGui>
#include"Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h"
namespace Ui {
class Dialog_Declaration_Const;
}

class Dialog_Declaration_Const : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Declaration_Const(Gestion_Arbre_Algo * Arbre_Algo);
    ~Dialog_Declaration_Const();
    QStandardItemModel * modelViewAlgo;
    void metter_sous_modification();
private slots:
    void on_buttonBox_accepted();
    void on_nom_textChanged(const QString &arg1);

    void on_valeur_textChanged(const QString &arg1);

private:
    Ui::Dialog_Declaration_Const *ui;
    Gestion_Arbre_Algo * ArbreAlgo;
    bool sous_modification;
    QString constante;
    QString valeur;
    QString Controle_Constante();
    QString Controle_Valeur();


};

#endif // DIALOG_DECLARATION_CONST_H
