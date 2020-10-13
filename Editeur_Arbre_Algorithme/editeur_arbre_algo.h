#ifndef EDITEUR_ARBRE_ALGO_H
#define EDITEUR_ARBRE_ALGO_H

#include <QWidget>
#include<QTreeView>
#include<QFileInfo>
#include<QFileIconProvider>
#include<QDebug>
#include<QtCore>
#include<QFileDialog>

#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
//////////////////////////////DIALOG DECLARATION/////////////
#include"Dialogs_Editeur/dialog_declaration_const.h"
#include"Dialogs_Editeur/dialog_declaration_fichiers.h"
#include"Dialogs_Editeur/dialog_declaration_variable.h"
#include"Dialogs_Editeur/dialog_declaration_matrice.h"
#include"Dialogs_Editeur/dialog_declaration_vecteur.h"
#include"Dialogs_Editeur/dialog_declaration_enregistrement.h"
#include"Dialogs_Editeur/dialog_declaration_procedure.h"
///////////////////////////////DIALOG INSTRUCTION///////////////
#include"Dialogs_Editeur/dialog_si_sinon.h"
#include"Dialogs_Editeur/dialog_selon_faire.h"
#include"Dialogs_Editeur/dialog_pour_faire.h"
#include"Dialogs_Editeur/dialog_repeter_jusqua.h"
#include"Dialogs_Editeur/dialog_tanteque_faire.h"
#include"Dialogs_Editeur/dialog_affecation.h"
#include"Dialogs_Editeur/dialog_lire_variable.h"
#include"Dialogs_Editeur/dialog_ecrire.h"
#include"Dialogs_Editeur/dialog_appelle_procedure.h"
#include"Dialogs_Editeur/dialog_retournefn.h"
#include"Editeur_Arbre_Algorithme/Gestionnaire_appercu/get_appercu.h"
#include<QWidgetItem>
#include<appercualgorithmewidget.h>

typedef struct Algorithm{
    AppercuAlgorithmeWidget * tabAlgorithme;
    QString chemainFichier;
    QWidget * tabSource;
}Algorithme;

class Editeur_Arbre_Algo : public QWidget
{
    Q_OBJECT
public:
    explicit Editeur_Arbre_Algo(QWidget *parent, QTabWidget * tab_Algorithmes, QTreeView * View_menu);

    QStandardItemModel * model_View_menu;
    QDomDocument CreerXMLDocument();
    QTabWidget * tabAlgorithmes;
    void AfficherAlgorithm(QDomDocument documentAlgo, QString nomFichier);
    AppercuAlgorithmeWidget * AlgorithmeCourant;
    QString CouranteNomFichier;
public slots:
    void NouveauAlgorithm(QString sourceAlgo);

    void Supprimer();
    void modifier_ligne();
    void Copier();
    void Coller();
    void Couper();
    void Annuler();
    void Retablir();
    void Enregistrer_Algorithme();
    void Enregistrer_Sous_Algorithme();

private slots:
    void gestion_des_commandes(const QModelIndex &index);
    void Item_Change(QStandardItem *item);
    void CouranteAlogrithmeChange(int index);
    void FermerAlgorithm(int index);
    void cliquer(int index);
private:

    void setup_menu(QTreeView *View_menu);

    void CreerXMLCorpProgramAlgo(QStandardItem * std_Debut, QDomElement *elem_Debut,QDomDocument * DocumentAlgo);

    void EditerXMLItem(QDomElement * item, QStringList liste_infoInst);


        QList<QDomElement> Entete;

        Dialog_Declaration_Const * D_dec_const;
        Dialog_Declaration_Fichiers * D_dec_fichiers;
        Dialog_Declaration_variable * D_dec_varibles;
        Dialog_Declaration_Matrice * D_dec_matrice;
        Dialog_Declaration_Vecteur * D_dec_vecteur;
        Dialog_Declaration_Enregistrement * D_dec_enregitrement;
        Dialog_Declaration_Procedure * D_dec_procedure;

        Dialog_SI_SINON * D_si_sinon;
        Dialog_Selon_faire * D_selon_faire;
        Dialog_Pour_Faire * D_pour_faire;
        Dialog_Repeter_jusqua * D_repeter_jusqua;
        Dialog_Tanteque_Faire * D_tantque_faire;
        Dialog_Lire_Variable * D_lire_var;
        Dialog_Affecation  * D_affectation;
        Dialog_Ecrire * D_Ecrire;
        Dialog_appelle_procedure * D_Appelle;
        Dialog_RetourneFN * D_retournFN;
        QList<Algorithm> listeAlgorithmes;
        int CouranteAlgorithm(QWidget * WidgetCourant);

        bool ControleFichiersAlgorithm(QDomDocument documentAlgo);

        int estDejaOuvert(QString nomFichier);

};

#endif // EDITEUR_ARBRE_ALGO_H
