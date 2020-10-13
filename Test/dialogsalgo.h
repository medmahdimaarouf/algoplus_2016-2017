#ifndef DIALOGSALGO_H
#define DIALOGSALGO_H

#include <QObject>
#include<QtXml>
#include<QtGui>
#include<QtCore>
////////////// BOITS DIALOGS //////////////////////////
#include "affectation.h"
#include"commentaire.h"
#include"declarationconst.h"
#include"lirevar.h"
#include"matrices.h"
#include"pourfaire.h"
#include"repeterjusqua.h"
#include"selonfaire.h"
#include"strsi_sinon.h"
#include"tantequefaire.h"
#include"vecteur.h"
////////////////////////////////////////////////////////////
class DialogsAlgo : public QObject
{
    Q_OBJECT
public:
    explicit DialogsAlgo(QObject *parent = 0);
    Affectation  D_affect;
    Commentaire  D_commentaire;
    DeclarationConst  D_const;
    LireVar  D_lecvar;
    Matrices  D_matrics;
    Pourfaire  D_pour;
    RepeterJusqua  D_repeter;
    SelonFaire  D_selon;
    StrSi_SInon  D_sisinon;
    TantequeFaire  D_tanteque;
    Vecteur  D_vecteur;
signals:

public slots:
////////////////////  DECLARATION /////////////////////////////////////
    void insert_dec_constAlgo(QDomDocument document);

    void insert_dec_tabAlgo(QDomDocument document);

    void insert_dec_matAlgo(QDomDocument document);

    void insert_dec_enregAlgo(QDomDocument document);

    void insert_dec_fileAlfo(QDomDocument document);

    void insert_dec_fonctionAlgo(QDomDocument document);

    void insert_dec_procAlgo(QDomDocument document);

    void insert_dec_Var(QDomDocument document);

///////////////////// STRUCTURE PROG ////////////////////////////////////////////////

    void insert_si_alorsAlgo(QDomDocument document);

    void insert_selon_faireAlgo(QDomDocument document);

    void insert_forAlgo(QDomDocument document);

    void insert_do_whileAlgo(QDomDocument document);

    void insert_whileAlgo(QDomDocument document);
/////////////////////////////////////////////////////////////////////////////////////////
    void insert_lireVarAlgo(QDomDocument document);

    void insert_EcrireVarAlgo(QDomDocument document);

    void insert_affectationAlgo(QDomDocument document);

    void insert_procAlgo(QDomDocument document);

    void insert_proc_defAlgo(QDomDocument document);
};

#endif // DIALOGSALGO_H
