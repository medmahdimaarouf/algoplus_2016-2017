#ifndef DIALOG_APPELLE_SOUSPROGRAMPROC_H
#define DIALOG_APPELLE_SOUSPROGRAMPROC_H

#include <QDialog>
#include<QStandardItem>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class Dialog_appelle_SousProgramProc;
}

class Dialog_appelle_SousProgramProc : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_appelle_SousProgramProc(QWidget *parent, QString nom, QString parametres, QStandardItem * RouteOfPrograms, Gestion_Arbre_Algo *Arbre_Algo);
    ~Dialog_appelle_SousProgramProc();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_appelle_SousProgramProc *ui;
    Gestion_Arbre_Algo * ArbreAlgo;
    QString controle();
};

#endif // DIALOG_APPELLE_SOUSPROGRAMPROC_H
