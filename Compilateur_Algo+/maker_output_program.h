#ifndef MAKER_OUTPUT_PROGRAM_H
#define MAKER_OUTPUT_PROGRAM_H

#include <QObject>
#include<QtXml>
#include<QMessageBox>
#include<QFileDialog>
class Maker_Output_Program : public QObject
{
    Q_OBJECT
public:
    explicit Maker_Output_Program(QObject *parent = 0);

    QString get_output_program(QDomDocument document);

    QDomDocument document_to_convert;

    QString convert_champJs(QDomElement element);

private:

    QString get_condition_expression(QString attribut);

    QString convert_entetAlgoJs(QDomElement element_program);

    QString convert_constanteJs(QDomElement element);

    QString convert_enregistrementJs(QDomElement element);

    QString convert_tableauxJs(QDomElement element);

    QString convert_matricesJs(QDomElement element);

    QString convert_fichiersJs(QDomElement element);

    QString convert_fonctionJs(QDomElement element);

    QString convert_variableJs(QDomElement element);

    QString convert_procedureJs(QDomElement element);

    QString convert_instructionJs(QDomElement element);

    QString Appelle_Procedure(QDomElement element);

    QString convert_blok_algo(QDomElement element_program);

    int convert_instructionsJs(QDomNodeList list,QString * script);

    QString get_valtype(QString type);

    QString Convert_typeByName(QDomDocument document,QString type);

    QString get_typePassage(QDomElement function);

    QDomElement get_elementProcByName(QString nameproc);

    QString decript_message(QString message);

    QString decript_Variable(QString variable);

    QString fin_inst;

};

#endif // MAKER_OUTPUT_PROGRAM_H
