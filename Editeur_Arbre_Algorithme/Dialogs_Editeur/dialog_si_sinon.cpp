#include "dialog_si_sinon.h"
#include "ui_dialog_si_sinon.h"

Dialog_SI_SINON::Dialog_SI_SINON(Gestion_Arbre_Algo * Arbre_Algo) :
    ui(new Ui::Dialog_SI_SINON)
{
    ui->setupUi(this);
    this->setModal(true);
    ArbreAlgo = Arbre_Algo;
    sous_modification = false;
    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    setWindowTitle("Ajouter SI (...) Alors");
    connect(ui->condition,SIGNAL(textChanged(QString)),this,SLOT(condition_Change()));
}

Dialog_SI_SINON::~Dialog_SI_SINON()
{
    delete ui;
}

void Dialog_SI_SINON::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier Si..Non");
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    ui->condition->setText(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
    ui->sinon->setChecked(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(2).toInt() == 1);
    ui->sinon->setEnabled(false);
}

void Dialog_SI_SINON::on_buttonBox_accepted()
{

    QString message_controle = Controle_Condition();
    if(!message_controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_controle,QMessageBox::Ok);
        return;
    }
    if(sous_modification)
    {
       ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setText("SI (" + condition + ") ALORS");
       if(ui->sinon->isChecked())
           ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription("5#" + condition + "#1");
        else
           ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription("5#" + condition + "#0");
    }
    else
    {
        QStandardItem *itemAlgo = new QStandardItem("SI (" + condition + ") ALORS");

        QStandardItem * std_fin = new QStandardItem("FIN SI");
        std_fin->setAccessibleDescription("0#FIN SI");
        std_fin->setWhatsThis("fin");

        QStandardItem * std_ins = new QStandardItem("");
        itemAlgo->appendRow(std_ins);

        if(ui->sinon->isChecked())
        {
            QStandardItem * std_sinon = new QStandardItem("SI NON");
            std_sinon->setAccessibleDescription("6#");
            std_sinon->setWhatsThis("item");
            QStandardItem * std_ins_sinon = new QStandardItem("");
            itemAlgo->appendRow(std_sinon);
            std_sinon->appendRow(std_ins_sinon);
            itemAlgo->appendRow(std_fin);
            itemAlgo->setAccessibleDescription("5#" + condition + "#1");
            itemAlgo->setWhatsThis("item");
        }else
        {
            itemAlgo->appendRow(std_fin);
            itemAlgo->setAccessibleDescription("5#" + condition + "#0");
            itemAlgo->setWhatsThis("item");
        }
        ArbreAlgo->add_newItemAlgo(itemAlgo);
        ArbreAlgo->ArbreAlgo->setCurrentIndex(std_ins->index());
    }

}

void Dialog_SI_SINON::condition_Change()
{
    ui->commentaire->setText(Controle_Condition());
}

QString Dialog_SI_SINON::Controle_Condition()
{
    condition = ArbreAlgo->PasEspaces(ui->condition->text());
    return ArbreAlgo->Controle_condition(condition);

}
