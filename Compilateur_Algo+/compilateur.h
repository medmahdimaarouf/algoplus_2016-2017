#ifndef COMPILATEUR_H
#define COMPILATEUR_H

#include <QObject>
#include<QtXml>

#include"executer.h"
#include"maker_output_program.h"
#include<Console/consolewidget.h>

class Compilateur : public QWidget
{
    Q_OBJECT
public:
    explicit Compilateur(QWidget * parent, QDomDocument Source_program, ConsoleWidget *Console);

    void execute();

//private:
   Maker_Output_Program * maker_output_program;
   Executer * executer;
   ConsoleWidget * Console;

};

#endif // COMPILATEUR_H
