#include "dialog_ecrire.h"
#include "ui_dialog_ecrire.h"
#include<QPushButton>

Dialog_Ecrire::Dialog_Ecrire(Gestion_Arbre_Algo * ArbreAlgo) :
    ui(new Ui::Dialog_Ecrire)
{
    ui->setupUi(this);
    ui->message->setFocus();
    setModal(true);
    Arbre_Algo = ArbreAlgo;

    sous_modification = false;
    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    this->setWindowTitle("Ajouter Ecrire variable");
    connect(ui->message,SIGNAL(textChanged(QString)),this,SLOT(message_change()));
}

Dialog_Ecrire::~Dialog_Ecrire()
{
    delete ui;
}

void Dialog_Ecrire::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier Ecrire variable");
    ui->buttonBox->buttons().at(0)->setText("Modifier");

    ui->message->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
}

void Dialog_Ecrire::on_buttonBox_accepted()
{
    QString message_controle = controle_saisie_msg();
    if(!message_controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_controle,QMessageBox::Ok);
        return;
    }
    if(sous_modification)
    {
        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText("Ecrire (" + message + ")");
        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setAccessibleDescription("3#" + message);
    }
    else
    {
        QStandardItem * std_Algo = new QStandardItem("Ecrire (" + message + ")");
        std_Algo->setWhatsThis("item");
        std_Algo->setAccessibleDescription("3#" + message);
        Arbre_Algo->add_newItemAlgo(std_Algo);
    }

}

void Dialog_Ecrire::message_change()
{
    ui->commentaire->setText(controle_saisie_msg());
}

QString Dialog_Ecrire::controle_saisie_msg()
{
    message = Arbre_Algo->PasEspaces(ui->message->text());
    return Arbre_Algo->Controle_Message(message);
}
