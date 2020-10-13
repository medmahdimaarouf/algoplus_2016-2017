#include "dialog_lire_variable.h"
#include "ui_dialog_lire_variable.h"
#include<QPushButton>
Dialog_Lire_Variable::Dialog_Lire_Variable(Gestion_Arbre_Algo *ArbreAlgo) :
    ui(new Ui::Dialog_Lire_Variable)
{
    ui->setupUi(this);
    ui->Variable->setFocus();
    this->setModal(true);
    Arbre_Algo = ArbreAlgo;

    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    this->setWindowTitle("Ajouter Lire variable");
    sous_modification = false;
    listeVras = ArbreAlgo->liste_Variables_DE(ArbreAlgo->Programme_Courante());
    CompleterVars = new QCompleter(listeVras);
    ui->Variable->setCompleter(CompleterVars);
    connect(ui->message,SIGNAL(textChanged(QString)),this,SLOT(message_change()));
    connect(ui->Variable,SIGNAL(textChanged(QString)),this,SLOT(variable_change()));

}

Dialog_Lire_Variable::~Dialog_Lire_Variable()
{
    delete ui;
}

void Dialog_Lire_Variable::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier Lire variable");
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    ui->Variable->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
    ui->message->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(2));
}

void Dialog_Lire_Variable::on_buttonBox_accepted()
{
    QString message_controle = Controlevariable();
    if(message_controle.isEmpty())
        message_controle = Controlemessage();
    if(!message_controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_controle,QMessageBox::Ok);
        return;
    }

    if(sous_modification)
    {
        if(message.isEmpty())
            Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText("Lire( " + variable + ")");
        else
            Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText("Ecrire(" + message + "),Lire( " + variable + ")");

        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())-> setAccessibleDescription("2#" + variable+"#" + message);
    }
    else
    {
        QStandardItem * std_Algo;
        if(message.isEmpty())
            std_Algo = new QStandardItem("Lire( " + variable + ")");
        else
            std_Algo = new QStandardItem("Ecrire(" + message + "),Lire( " + variable + ")");

        std_Algo->setEditable(false);
        std_Algo->setAccessibleDescription("2#" + variable + "#" + message);
        std_Algo->setWhatsThis("item");
        Arbre_Algo->add_newItemAlgo(std_Algo);
    }
}

void Dialog_Lire_Variable::message_change()
{
    ui->Commantaire->setText(Controlemessage());
}

void Dialog_Lire_Variable::variable_change()
{
    ui->Commantaire->setText(Controlevariable());
}

QString Dialog_Lire_Variable::Controlemessage()
{
    message = Arbre_Algo->PasEspaces(ui->message->text());
    if(message.isEmpty())
        return "message n'est pas deffinit";

    return Arbre_Algo->Controle_Message(message);

}

QString Dialog_Lire_Variable::Controlevariable()
{
    variable = Arbre_Algo->PasEspaces(ui->Variable->text());
    return Arbre_Algo->Controle_Variable(variable);

}
