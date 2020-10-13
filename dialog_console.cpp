#include "dialog_console.h"
#include "ui_dialog_console.h"

Dialog_Console::Dialog_Console(QWidget *parent,QDomDocument Source_ProgramAlgo) :
    QDialog(parent),
    ui(new Ui::Dialog_Console)
{
    ui->setupUi(this);
    this->setModal(true);
    setWindowTitle("Console d'execution Algo+");
    compilateur = new Compilateur(this,Source_ProgramAlgo,new ConsoleWidget(ui->Console,new QLineEdit(this)));
}

Dialog_Console::~Dialog_Console()
{
    delete compilateur;
    delete ui;
}

void Dialog_Console::on_actionaffichage_d_triggered()
{
    QTextEdit * textd = new QTextEdit();
    textd->setText(compilateur->executer->Input_program);
    textd->show();
}
