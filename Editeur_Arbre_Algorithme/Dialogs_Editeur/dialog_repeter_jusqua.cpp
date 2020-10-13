#include "dialog_repeter_jusqua.h"
#include "ui_dialog_repeter_jusqua.h"
#include<QPushButton>
Dialog_Repeter_jusqua::Dialog_Repeter_jusqua(Gestion_Arbre_Algo *Arbre_Algo) :
    ui(new Ui::Dialog_Repeter_jusqua)
{
    ui->setupUi(this);
    ui->condition->setFocus();
    this->Arbre_Algo = Arbre_Algo;
    sous_modification = false;
    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    setWindowTitle("Ajouter Repeter..Jusqu'a(condition d'arret)");
    connect(ui->condition,SIGNAL(textChanged(QString)),this,SLOT(condition_Change()));
}

Dialog_Repeter_jusqua::~Dialog_Repeter_jusqua()
{
    delete ui;
}

void Dialog_Repeter_jusqua::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier Repeter..Jusqu'a(condition d'arret)");
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    if(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(0).toInt() == -1)
    {
      ui->condition->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->child(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->rowCount()-1)->accessibleDescription().split("#").at(1));
    }
     else
    {
       ui->condition->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
    }
}

void Dialog_Repeter_jusqua::on_buttonBox_accepted()
{
    QString message_controle = Controle_Condition();
    if(!message_controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_controle,QMessageBox::Ok);
        return;
    }
    if(sous_modification)
    {
        if(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(0).toInt() == -1)
        {
          Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->child(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->rowCount()-1)->setAccessibleDescription("11#" + condition);
           Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->child(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->rowCount()-1)->setText("JUSQU'A (" + condition + ")");
        }
         else
        {
           Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setAccessibleDescription("11#" + condition);
           Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText("JUSQU'A (" + condition + ")");
        }
    }
    else
    {
        QStandardItem * std_Algo = new QStandardItem("REPETER");
        std_Algo->setEditable(false);
        std_Algo->setAccessibleDescription("-1#REPETER");
        std_Algo->setWhatsThis("item");
        QStandardItem * std_ins = new QStandardItem("");
        std_ins->setEditable(false);
        QStandardItem * std_jusq = new QStandardItem("JUSQU'A (" + condition + ")");
        std_jusq->setEditable(false);
        std_jusq->setAccessibleDescription("11#" + condition );
        std_jusq->setWhatsThis("fin");
        std_Algo->appendRow(std_ins);
        std_Algo->appendRow(std_jusq);
        Arbre_Algo->add_newItemAlgo(std_Algo);
        Arbre_Algo->ArbreAlgo->setCurrentIndex(std_ins->index());
    }
}

void Dialog_Repeter_jusqua::condition_Change()
{
  ui->commentaire->setText(Controle_Condition());
}

QString Dialog_Repeter_jusqua::Controle_Condition()
{
  condition = Arbre_Algo->PasEspaces(ui->condition->text());
  return Arbre_Algo->Controle_condition(condition);
}
