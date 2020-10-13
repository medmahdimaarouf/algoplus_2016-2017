#include "dialog_declaration_enregistrement.h"
#include "ui_dialog_declaration_enregistrement.h"
#include<QMessageBox>

Dialog_Declaration_Enregistrement::Dialog_Declaration_Enregistrement(Gestion_Arbre_Algo *Arbre_Algo) :
    ui(new Ui::Dialog_Declaration_Enregistrement)
{
    ui->setupUi(this);
    ui->nom->setFocus();
    this->setModal(true);
    this->ArbreAlgo = Arbre_Algo;
    ui->buttonBox->buttons().at(0)->setText("Décalrer");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    this->setWindowTitle("Décalrer un enregistrement");
    sous_modification = false;
    listeTypes = Arbre_Algo->listeTypes();
    CompleterTypes = new QCompleter(listeTypes);
    ui->nom->setCompleter(CompleterTypes);
    ui->Aide->setHtml("<h1 align='center'> Aide </h1> <p align = 'center'> Le contenu d'aide Algo+ est indisponible jusqu'a maintenant,Essayez d'avoir la dernier version de Algo+</p><h2 align='center'> Algo+.2016-2017 <h3>Email : medmahdi.maarouf@gmail.com</h3></h2>");
    ui->Aide->setReadOnly(true);
    nom_Courant = "";
}

Dialog_Declaration_Enregistrement::~Dialog_Declaration_Enregistrement()
{
    delete ui;
}

void Dialog_Declaration_Enregistrement::metter_sous_modification()
{
    sous_modification = true;
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    this->setWindowTitle("Modifier un enregistrement");
    QStringList listeinfo = ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#");
    ui->nom->setText(listeinfo.at(1));

    if(!listeinfo.at(2).isEmpty())
    {
        for(int i = 0; i < listeinfo.at(2).split("|").size();i++)
        {
            QStringList champ = listeinfo.at(2).split("|").at(i).split(":");
            QTreeWidgetItem * itemchamp = new QTreeWidgetItem(ui->liste_champs);
            itemchamp->setText(0,champ.at(0));
            itemchamp->setText(1,champ.at(1));
            ui->liste_champs->addTopLevelItem(itemchamp);
        }
    }
    listeTypes = ArbreAlgo->listeTypes();
    CompleterTypes = new QCompleter(listeTypes);
    ui->nom->setCompleter(CompleterTypes);
    nom_Courant = ui->nom->text();

}

void Dialog_Declaration_Enregistrement::on_buttonBox_accepted()
{
    QString messageControle = Controle_NomType();
    if(!messageControle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur de saisie ",messageControle,QMessageBox::Ok);
        return;
    }
    // PREPARATION D UN APPERCU ITEM ALGORITHM

     QStandardItem * std_enregistrement = new QStandardItem(nomType + " = Enregistrement");
     std_enregistrement->setEditable(false);
     QString liste_Champs = "";
     for(int i = 0;i < ui->liste_champs->topLevelItemCount();i++)
     {
         QStandardItem * new_champ = new QStandardItem(ui->liste_champs->topLevelItem(i)->text(0) + " : " + ui->liste_champs->topLevelItem(i)->text(1));
         liste_Champs += ui->liste_champs->topLevelItem(i)->text(0) + ":" + ui->liste_champs->topLevelItem(i)->text(1) + "|";
         new_champ->setEditable(false);
         new_champ->setWhatsThis("champ");
         std_enregistrement->appendRow(new_champ);
     }
     QStandardItem * fin_enreg = new QStandardItem("fin "+nomType);
     fin_enreg->setAccessibleDescription("0#");
     fin_enreg->setWhatsThis("fin");
     fin_enreg->setEditable(false);
     std_enregistrement->appendRow(fin_enreg);
     std_enregistrement->setAccessibleDescription("3#" + nomType + "#" + liste_Champs.remove(liste_Champs.length()-1,1));
     std_enregistrement->setWhatsThis("enreg");

      if(sous_modification)
      {
          QStandardItem * enregCourant = ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex());
          int pos = enregCourant->row();
          QStandardItem * parent_item = enregCourant->parent();
          parent_item->removeRow(pos);
          parent_item->insertRow(pos,std_enregistrement);
          ArbreAlgo->ArbreAlgo->expand(parent_item->index());
          ArbreAlgo->ArbreAlgo->expand(std_enregistrement->index());

      }
        else
      {
        // LEUR INSERTION EN L ARBRE DE ALGORITHME
           if(ArbreAlgo->modelViewAlgo->item(0)->hasChildren())
             {
                 for(int  i = 0; i < ArbreAlgo->modelViewAlgo->item(0)->rowCount();i++)
                     if(ArbreAlgo->modelViewAlgo->item(0)->child(i)->text() == "Types")
                     {
                         ArbreAlgo->modelViewAlgo->item(0)->child(i)->appendRow(std_enregistrement);
                         return;
                     }
                 QStandardItem * std_rootenrg = new QStandardItem("Types");
                 std_rootenrg->appendRow(std_enregistrement);
                 std_rootenrg->setWhatsThis("types");
                 std_rootenrg->setEditable(false);

                 if(ArbreAlgo->modelViewAlgo->item(0)->child(0)->text() == "Constantes")

                     ArbreAlgo->modelViewAlgo->item(0)->insertRow(1,std_rootenrg);
                 else
                     ArbreAlgo->modelViewAlgo->item(0)->insertRow(0,std_rootenrg);

             }
             else
             {
                 QStandardItem * std_rootenrg = new QStandardItem("Types");
                 std_rootenrg->setWhatsThis("types");
                 std_rootenrg->appendRow(std_enregistrement);
                 ArbreAlgo->modelViewAlgo->item(0)->appendRow(std_rootenrg);
             }
    }
    ArbreAlgo->ArbreAlgo->setCurrentIndex(std_enregistrement->index());
}

void Dialog_Declaration_Enregistrement::on_Ajouterchamp_clicked()
{
    champ_parametre = new Dialog_champ_parametre(3,ArbreAlgo,ArbreAlgo->PasEspaces(ui->nom->text()));
    champ_parametre->liste_champs = ui->liste_champs;
    champ_parametre->setWindowTitle("Ajouter un champ");
    champ_parametre->show();
}

void Dialog_Declaration_Enregistrement::on_supprimerchams_c_clicked()
{
    ui->liste_champs->model()->removeRow(ui->liste_champs->currentIndex().row());
}

void Dialog_Declaration_Enregistrement::on_supprimer_t_clicked()
{
    ui->liste_champs->clear();
}

QString Dialog_Declaration_Enregistrement::Controle_NomType()
{
    nomType = ArbreAlgo->PasEspaces(ui->nom->text());
    return ArbreAlgo->Controle_NomType(nomType,nom_Courant);
}

void Dialog_Declaration_Enregistrement::on_nom_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_NomType());
}
