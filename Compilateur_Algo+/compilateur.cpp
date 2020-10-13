#include "compilateur.h"

Compilateur::Compilateur(QWidget *parent, QDomDocument Source_program,ConsoleWidget * Console):
    QWidget(parent)

{
    maker_output_program = new Maker_Output_Program(this);
    this->Console = Console;
    executer = new Executer(Source_program,maker_output_program->get_output_program(Source_program));
    connect(executer,SIGNAL(GetInput(QString,bool)),Console,SLOT(Lire(QString,bool)));

    connect(Console,SIGNAL(sentInput(QString)),executer,SLOT(change_input(QString)));
    connect(executer,SIGNAL(SentMessage(QString,bool,QColor)),Console,SLOT(Ecrire(QString,bool,QColor)));

}

void Compilateur::execute()
{
    Console->Clear();
    executer->start();
}
