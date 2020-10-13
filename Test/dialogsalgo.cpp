#include "dialogsalgo.h"

DialogsAlgo::DialogsAlgo(QObject *parent) :
    QObject(parent)
{
}
///////////////////// Declaration PROG ////////////////////////////////////////////////

void DialogsAlgo::insert_dec_constAlgo(QDomDocument document)
{

}

void DialogsAlgo::insert_dec_tabAlgo(QDomDocument document)
{
    qDebug()<<"dec tab" ;
}

void DialogsAlgo::insert_dec_matAlgo(QDomDocument document)
{
    qDebug()<< "dec mat";
}

void DialogsAlgo::insert_dec_enregAlgo(QDomDocument document)
{
    qDebug()<< "dec eng";
}

void DialogsAlgo::insert_dec_fileAlfo(QDomDocument document)
{
    qDebug()<<"dec file" ;
}

void DialogsAlgo::insert_dec_fonctionAlgo(QDomDocument document)
{
    qDebug()<<"dec fct" ;
}

void DialogsAlgo::insert_dec_procAlgo(QDomDocument document)
{
    qDebug()<<"dec proc " ;
}

void DialogsAlgo::insert_dec_Var(QDomDocument document)
{
    qDebug()<<"dec var";
}

void DialogsAlgo::insert_si_alorsAlgo(QDomDocument document)
{
    qDebug()<<"si alors" ;
}

void DialogsAlgo::insert_selon_faireAlgo(QDomDocument document)
{
    qDebug()<<"selon faire" ;
}

void DialogsAlgo::insert_forAlgo(QDomDocument document)
{
    qDebug()<<"pour" ;
}

void DialogsAlgo::insert_do_whileAlgo(QDomDocument document)
{
    qDebug()<< "do while";
}

void DialogsAlgo::insert_whileAlgo(QDomDocument document)
{
    qDebug()<<"while" ;
}
///////////////////// STRUCTURE PROG ////////////////////////////////////////////////

void DialogsAlgo::insert_lireVarAlgo(QDomDocument document)
{
    qDebug()<<"lire" ;
}

void DialogsAlgo::insert_EcrireVarAlgo(QDomDocument document)
{
 qDebug()<<"ecrire var algo";
}

void DialogsAlgo::insert_affectationAlgo(QDomDocument document)
{
    qDebug()<< "affectation";
}

void DialogsAlgo::insert_procAlgo(QDomDocument document)
{
    qDebug()<<"procedure predfinit" ;
}

void DialogsAlgo::insert_proc_defAlgo(QDomDocument document)
{
    qDebug()<<"proc definit";
}
