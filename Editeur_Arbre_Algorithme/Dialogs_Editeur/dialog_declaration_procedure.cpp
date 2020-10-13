#include "dialog_declaration_procedure.h"
#include "ui_dialog_declaration_procedure.h"
#include<QMessageBox>
QString crypt_passage(QString passage)
{
    if(passage == "Par adresse")
        return "1";
    else
        return "0";
}

Dialog_Declaration_Procedure::Dialog_Declaration_Procedure(bool estFonction, Gestion_Arbre_Algo *Arbre_Algo) :
    ui(new Ui::Dialog_Declaration_Procedure)
{
    ui->setupUi(this);
    ui->nom->setFocus();
    this->setModal(true);
    widget_return = ui->widget_return;

    ui->widget_return->setVisible(estFonction);

    if(estFonction)
        this->setWindowTitle("Declarer une fonction");
    else
        this->setWindowTitle("Declarer une procedure");

    isfunc = estFonction;
    ArbreAlgo = Arbre_Algo;
    sous_modification = false;
    ui->buttonBox->buttons().at(0)->setText("Déclarer");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    listeprgramme = Arbre_Algo->listeProgrammmes();
    ListeTypes = Arbre_Algo->listeTypes();
    if(isfunc)
    {
        ListeTypesContenu = Arbre_Algo->liste_TypeContenu("");
        CompleterTypesContenu  = new  QCompleter(ListeTypesContenu);
        ui->returntype->setCompleter(CompleterTypesContenu);
    }
    ui->Aide->setHtml("<h1 align='center'> Aide </h1> <p align = 'center'> Le contenu d'aide Algo+ est indisponible jusqu'a maintenant,Essayez d'avoir la dernier version de Algo+</p><h2 align='center'> Algo+.2016-2017 <h3>Email : medmahdi.maarouf@gmail.com</h3></h2>");
    ui->Aide->setReadOnly(true);
    nom_modif = "";

}

Dialog_Declaration_Procedure::~Dialog_Declaration_Procedure()
{
    delete ui;
}

void Dialog_Declaration_Procedure::metter_sous_modification()
{
    sous_modification = true;
    QStringList listeInfo = ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#");
    ui->buttonBox->buttons().at(0)->setText("Modifier");

    ui->nom->setText(listeInfo.at(1));

    if(!listeInfo.at(3).isEmpty())
      {
        QStringList listeparas = listeInfo.at(3).split("|");
        for(int i = 0; i < listeparas.size();i++)
        {
            QStringList infopara = listeparas.at(i).split(":");
            QTreeWidgetItem * itemPara = new QTreeWidgetItem(ui->listeparametre);
            itemPara->setText(0,infopara.at(0));
            itemPara->setText(1,infopara.at(1));
            if(infopara.at(2).toInt() == 1)
                itemPara->setText(2,"Par adresse");
            else
                itemPara->setText(2,"Par valeur");
            ui->listeparametre->addTopLevelItem(itemPara);
        }
      }

    if(isfunc)
    {
        this->setWindowTitle("Modifier une fonction");
        ui->returntype->setText(listeInfo.at(2));
    }
    else
        this->setWindowTitle("Modifier un procedure");
    nom_modif = ArbreAlgo->PasEspaces(ui->nom->text());
}

void Dialog_Declaration_Procedure::on_buttonBox_accepted()
{
    QString messageControle = Controle_nomProgram();
    if(messageControle.isEmpty() && isfunc)
        messageControle = Controle_RetourneProgram();
    if(!messageControle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur ",messageControle,QMessageBox::Ok);
        return;
    }
    QStandardItem  * std_debut = new QStandardItem("Debut");
    std_debut->setEditable(false);
    std_debut->setWhatsThis("Debut");

    QStandardItem * std_fin = new QStandardItem("Fin " + ui->nom->text());
    std_fin->setEditable(false);
    std_fin->setAccessibleDescription("0#");
    std_fin->setWhatsThis("fin");
    QString view_paras = "",liste_paras = "";
    if(isfunc)
       {

            for(int i = 0;i<ui->listeparametre->topLevelItemCount();i++)
            {
                view_paras += ui->listeparametre->topLevelItem(i)->text(0) + ":" + ui->listeparametre->topLevelItem(i)->text(1) + ",";
                liste_paras += ui->listeparametre->topLevelItem(i)->text(0) + ":" + ui->listeparametre->topLevelItem(i)->text(1) + ":0|";
            }

            QStandardItem * std_fonction = new QStandardItem("Fonction " + ui->nom->text() + "(" + view_paras.remove(view_paras.length()-1,1) + ") :" + ui->returntype->text());
            std_fonction->setAccessibleDescription("0#" + ui->nom->text()+ "#" + ui->returntype->text() + "#" + liste_paras.remove(liste_paras.length()-1,1));
            std_fonction->setWhatsThis("fct");

            std_fonction->setEditable(false);
            std_fonction->appendRow(std_debut);
            std_fonction->appendRow(std_fin);
            // SETTING IN THE TREE
            if(sous_modification)
            {
                ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setText("Fonction " + ui->nom->text() + "(" + view_paras.remove(view_paras.length()-1,1) + ") :" + ui->returntype->text());
                ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription("0#" + ui->nom->text()+ "#" + ui->returntype->text() + "#" + liste_paras.remove(liste_paras.length()-1,1));
                ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->child(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->rowCount()-1)->setText("Fin " + ui->nom->text());
            }
            else
            {
                if(ArbreAlgo->Algo->hasChildren())
                {
                    if(ArbreAlgo->Algo->rowCount() < 3)
                        ArbreAlgo->Algo->insertRow(ArbreAlgo->modelViewAlgo->item(0)->rowCount(),std_fonction);
                    else
                        ArbreAlgo->Algo->insertRow(3,std_fonction);
                }else
                        ArbreAlgo->Algo->appendRow(std_fonction);
            }
       }
        else
        {
        QString liste_paras  = "";
            for(int i = 0;i<ui->listeparametre->topLevelItemCount();i++)
            {
                if(ui->listeparametre->topLevelItem(i)->text(2) == "Par adresse")
                {
                    view_paras +="var " + ui->listeparametre->topLevelItem(i)->text(0) + ":" + ui->listeparametre->topLevelItem(i)->text(1) + ",";
                    liste_paras += ui->listeparametre->topLevelItem(i)->text(0) + ":" + ui->listeparametre->topLevelItem(i)->text(1) + ":1|";
                }
                else
                {
                    view_paras += ui->listeparametre->topLevelItem(i)->text(0) + ":" + ui->listeparametre->topLevelItem(i)->text(1) + ",";
                    liste_paras += ui->listeparametre->topLevelItem(i)->text(0) + ":" + ui->listeparametre->topLevelItem(i)->text(1) + ":0|";
                }

            }

            QStandardItem * std_procedure = new QStandardItem("Procedure " + ui->nom->text() + "(" + view_paras.remove(view_paras.length()-1,1) + ")");
            std_procedure->setAccessibleDescription("1#" + ui->nom->text() + "##" + liste_paras.remove(liste_paras.length()-1,1));
            std_procedure->setWhatsThis("proc");
            std_procedure->setEditable(false);
            std_procedure->appendRow(std_debut);
            std_procedure->appendRow(std_fin);
            if(sous_modification)
            {
                ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setText("Procedure " + ui->nom->text() + "(" + view_paras.remove(view_paras.length()-1,1) + ")");
                ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription("1#" + ui->nom->text() + "##" + liste_paras.remove(liste_paras.length()-1,1));
                ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->child(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->rowCount()-1)->setText("Fin " + ui->nom->text());
            }
            else
                ArbreAlgo->modelViewAlgo->item(0)->appendRow(std_procedure);

        }

}

QString Dialog_Declaration_Procedure::Controle_nomProgram()
{
    nom = ArbreAlgo->PasEspaces(ui->nom->text());
    return ArbreAlgo->controleNomProgrmme(isfunc,nom,nom_modif);
}

QString Dialog_Declaration_Procedure::Controle_RetourneProgram()
{
    if(isfunc)
    {
        retourne = ArbreAlgo->PasEspaces(ui->returntype->text());
        return ArbreAlgo->Controle_TypeContenu(5,nom,retourne);
    }
    else
        return "";
}


void Dialog_Declaration_Procedure::on_Ajouterparametre_clicked()
{
    if(isfunc)
        champ_parametre = new Dialog_champ_parametre(1,ArbreAlgo,"");
    else
        champ_parametre = new Dialog_champ_parametre(2,ArbreAlgo,"");

    champ_parametre->liste_parametres = ui->listeparametre;
    champ_parametre->show();
}


void Dialog_Declaration_Procedure::on_supprimerparametre_c_clicked()
{
    ui->listeparametre->model()->removeRow(ui->listeparametre->currentIndex().row());
}


void Dialog_Declaration_Procedure::on_supprimer_t_clicked()
{
    ui->listeparametre->clear();
}

void Dialog_Declaration_Procedure::on_nom_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_nomProgram());
}

void Dialog_Declaration_Procedure::on_returntype_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_RetourneProgram());
}
