#include "dialog_tanteque_faire.h"
#include "ui_dialog_tanteque_faire.h"
#include<QPushButton>

Dialog_Tanteque_Faire::Dialog_Tanteque_Faire(Gestion_Arbre_Algo *Arbre_Algo) :
    ui(new Ui::Dialog_Tanteque_Faire)
{
    ui->setupUi(this);
    this->setModal(true);
    this->Arbre_Algo = Arbre_Algo;
    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    this->setWindowTitle("Ajouter Tanteque..Faire");
    sous_modification = false;
    connect(ui->condition,SIGNAL(textChanged(QString)),this,SLOT(condition_Change()));
}

Dialog_Tanteque_Faire::~Dialog_Tanteque_Faire()
{
    delete ui;
}

void Dialog_Tanteque_Faire::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier Tantque..Faire");
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    ui->condition->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
}

void Dialog_Tanteque_Faire::on_buttonBox_accepted()
{
    QString message_controle = Controle_condition();
    if(!message_controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_controle,QMessageBox::Ok);
        return;
    }
    if(sous_modification)
    {
        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText("TANTE QUE (" + condition + ")FAIRE");
        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setAccessibleDescription("10#" + condition);
    }
    else
    {
        QStandardItem * std_Algo = new QStandardItem("TANTE QUE (" + condition + ")FAIRE");
        std_Algo->setAccessibleDescription("10#" + condition);
        std_Algo->setWhatsThis("item");
        QStandardItem * fin = new QStandardItem("FIN TANTE QUE");
        fin->setAccessibleDescription("0#FIN TANTE QUE");
        fin->setWhatsThis("fin");
        QStandardItem * std_ins = new QStandardItem("");
        std_Algo->appendRow(std_ins);
        std_Algo->appendRow(fin);
        Arbre_Algo->add_newItemAlgo(std_Algo);
        Arbre_Algo->ArbreAlgo->setCurrentIndex(std_ins->index());
    }

}

void Dialog_Tanteque_Faire::condition_Change()
{
    ui->commentaire->setText(Controle_condition());
}

QString Dialog_Tanteque_Faire::Controle_condition()
{
    condition = Arbre_Algo->PasEspaces(ui->condition->text());
    return Arbre_Algo->Controle_condition(condition);
}
