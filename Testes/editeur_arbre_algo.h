#ifndef EDITEUR_ARBRE_ALGO_H
#define EDITEUR_ARBRE_ALGO_H

#include<QTreeView>

#include "Gestion_appercu/gestion_arbre_algo.h"

#include<Gestion_appercu/gestion_arbre_algo.h>

class Editeur_Arbre_Algo : public QObject
{
public:
    Editeur_Arbre_Algo(QTreeView * View_Algo,QTreeView * View_menu);
    Gestion_Arbre_Algo * Arbre_Algo;
public slots:
    void gestion_des_commandes(const QModelIndex *index);
private:
    QStandardItemModel * model_View_menu,*model_View_Algo;
    void setup_menu(QTreeView *View_menu);
};

#endif // EDITEUR_ARBRE_ALGO_H
