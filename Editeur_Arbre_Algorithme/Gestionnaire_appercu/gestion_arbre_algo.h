#ifndef GESTION_ARBRE_ALGO_H
#define GESTION_ARBRE_ALGO_H

#include <QStandardItemModel>

#include<QtXml>
#include<QObject>
#include<QTreeView>
#include<QTreeWidget>
#include"get_appercu.h"
#include<QTextEdit>

class Gestion_Arbre_Algo : public QObject
{
    Q_OBJECT
public:

    explicit Gestion_Arbre_Algo(QTreeView *ViewAlgo,QTextEdit * TextDescription);

    QStandardItem *Algo,*DebutAlgo,*finAlgo;
    QString nameAlgo;
    QStandardItemModel * modelViewAlgo;
    QTreeView * ArbreAlgo;
    QTextEdit * Text_Description;
    void seletionner(int ligne);
    QStringList listeProgrammmes();
    QStringList listeTypes();
    QStringList liste_TypeContenu(QString TypeCourant);
    QStringList listeProcedures();
    QStringList ListeToutVariables();
    QStringList liste_Variables_DE(QString programme);
    QStringList listeFonctions();

    QStandardItem * std_sousProgramme(QString sousProgramme);
    QString programmeInstruction(QStandardItem * std_instruction);
    QStringList parametresProgrammes(QStandardItem * programme);
    QString PasEspaces(QString chaine);
    QString ControleNomCP(int operation, QTreeWidget *Viewliste_CP, QString nom);
    QString Controle_NomVariable(QString nomVariable, QString programme, QString nom_Courant);
    QString Controle_Variable(QString variable);
    QString Controle_NomType(QString nomType, QString nom_Courant);
    QString Controle_Expression(QString Expression);
    QString Controle_Parametres(QString parametres);
    QString Controle_Constante(QString constante);
    QString Controle_TypeContenu(int opertaion, QString Type, QString contenu);
    QString controleNomProgrmme(bool operation, QString nomProgram, QString nom_modif);
    QString Controle_Message(QString message);
    QString Controle_condition(QString condition);
    QString Programme_Courante();

public slots:

    void afficher_Algorithme(QDomDocument document);

    void add_newItemAlgo(QStandardItem * newItemAlgo);

    void Couper_ligne();

    void Copier_ligne();

    void Coller_ligne();

    void supprimer_ligne();
private slots:

    void changement_index_courant(const QModelIndex index);


private:
    Get_Appercu * get_appercuOf;

    QStandardItem * std_Copie;

    QStandardItem *CopierL(QStandardItem *Source);
    void coller2L(QStandardItem * itemSource,QStandardItem * itemDestinataire);
    void couperL(QStandardItem * std_item);
    void supprimerL(QStandardItem * std_item);

    void affiche_entetAlgo(QDomElement element_program, QStandardItem *std_program);

    void affiche_BlokAlgo(QDomElement element_program, QStandardItem *std_debut);

    int affiche_instructions(QDomNodeList list, QStandardItem *stditm);

    QString Appercu_Instruction(QDomElement instruction,QStandardItem * Item_Algo);

    void vider(QStandardItem * item);
    QStandardItem *itemAlgoligne(int ligne);

    //QString Programme_Courante();

};
#endif // GESTION_ARBRE_ALGO_H
