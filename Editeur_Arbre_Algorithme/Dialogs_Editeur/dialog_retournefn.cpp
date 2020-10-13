#include "dialog_retournefn.h"
#include "ui_dialog_retournefn.h"
#include<QMessageBox>
#include<QPushButton>

Dialog_RetourneFN::Dialog_RetourneFN(Gestion_Arbre_Algo *ArbreAlgo) :

    ui(new Ui::Dialog_RetourneFN)
{
    ui->setupUi(this);
    ui->retourne->setFocus();
    Arbre_Algo = ArbreAlgo;
    /*if(ArbreAlgo->modelViewAlgo->item(0)->hasChildren())
        for(int i = 0; i < ArbreAlgo->modelViewAlgo->item(0)->rowCount();i++)
            if(ArbreAlgo->modelViewAlgo->item(0)->child(i)->text() != "Constantes" && ArbreAlgo->modelViewAlgo->item(0)->child(i)->text() != "Types" && ArbreAlgo->modelViewAlgo->item(0)->child(i)->text() != "Variables" && ArbreAlgo->modelViewAlgo->item(0)->child(i)->accessibleDescription().split("#").at(0).toInt() == 0)
            {
                listefcts<< ArbreAlgo->modelViewAlgo->item(0)->child(i)->accessibleDescription().split("#").at(1);
                listeindex<<i;
            }*/
    listefcts = ArbreAlgo->listeFonctions();

    if(listefcts.isEmpty())
    {
        QMessageBox::information(this,"Information Editeur Algo+","Aucune fonction a ete declaraer",QMessageBox::Ok);
    }
    ui->nomfonction->addItems(listefcts);

    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    this->setWindowTitle("Ajouter Retourne Fonction");
    connect(ui->retourne,SIGNAL(textChanged(QString)),this,SLOT(retourne_Change()));
    fonction_Change();
    sous_modification = false;


}

Dialog_RetourneFN::~Dialog_RetourneFN()
{
    delete ui;
}

void Dialog_RetourneFN::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier une Retourne de fonction");
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    ui->nomfonction->setEnabled(false);
    ui->retourne->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(2));

}

void Dialog_RetourneFN::on_buttonBox_accepted()
{
    QString message_controle = Controle_retourne();

    if(!message_controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_controle,QMessageBox::Ok);
        return;
    }
    if(sous_modification)
    {
        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText(ui->nomfonction->currentText() + "<--" + retourne);
        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setAccessibleDescription("13#" + ui->nomfonction->currentText() + "#" + retourne);
    }
    else
    {
        QStandardItem * std_item = new QStandardItem(ui->nomfonction->currentText() + "<--" + retourne);
        std_item->setEditable(false);
        std_item->setAccessibleDescription("13#" + ui->nomfonction->currentText() + "#" + retourne);
        std_item->setWhatsThis("item");
        //Arbre_Algo->modelViewAlgo->item(0)->child(listeindex.at(ui->nomfonction->currentIndex()))->child(Arbre_Algo->modelViewAlgo->item(0)->child(listeindex.at(ui->nomfonction->currentIndex()))->rowCount() -2)->appendRow(std_item);
        QStandardItem * std_fonction = Arbre_Algo->std_sousProgramme(ui->nomfonction->currentText());
        if(std_fonction)
            std_fonction->child(std_fonction->rowCount() -2)->appendRow(std_item);
        else
            QMessageBox::warning(this,"Erreur Algo+","Un erreur se produis trait -> recherche std_fct ");
    }

}

void Dialog_RetourneFN::retourne_Change()
{
    ui->commentaire->setText(Controle_retourne());
}

void Dialog_RetourneFN::fonction_Change()
{
    ListeVariables = Arbre_Algo->liste_Variables_DE(ui->nomfonction->currentText());
    CompleterVars = new QCompleter(ListeVariables);
    ui->retourne->setCompleter(CompleterVars);
}

QString Dialog_RetourneFN::Controle_retourne()
{
    retourne = Arbre_Algo->PasEspaces(ui->retourne->text());
    if(retourne.isEmpty())
        return "retourne de fonction indeffinit";
    return "";
}
