#ifndef MEMOIRE_H
#define MEMOIRE_H
#include<QtXml>
#include <QDomDocument>
#include<QObject>
#include<QtScript>
#include"maker_output_program.h"

typedef struct FichierAlgoPlus{
    int location;
    QFile *fichier;
}FichierAlgoPlus;


class Memoire : public QObject
{
    Q_OBJECT
public:
    explicit Memoire(QDomDocument Source_program);
    QString setLocation(QString namevar, QString typevar);
    QString setpointer(QString namePointer,QString typePointer);
    bool remouve_var(int location);
    QString get_type_ofvar(int location);
    QString get_name_ofvar(int location);
    QString get_script_location(int location);
    bool islocatedAsFile(int location);
    QFile * getFileByLocation(int location);
    QScriptEngine * engine;
//private:
    QDomDocument memoire;
    QList<FichierAlgoPlus> ListFichiers;
    QDomElement root_algo;
    int get_new_location();
    Maker_Output_Program * maker_out_put;
    bool islocated(int location);
    void get_std_tabs(QDomElement root, QDomElement variable, QDomElement elemtype, QDomElement * elm_new_var);
    void get_std_mats(QDomElement root, QDomElement variable, QDomElement elemtype, QDomElement * elm_new_var);
    void get_std_engres(QDomElement root, QDomElement variable, QDomElement elemtype, QDomElement * elm_new_var);
    void go_to_simplevar(QDomElement root, QDomElement variable, QDomElement *element_new_var);

    QString get_script_dec_var(QString nom,QString type,QString location);
    QDomElement getvariableElemByLoc(int location);
};

#endif // MEMOIRE_H
