#include "dialog_declaration_fichiers.h"
#include "ui_dialog_declaration_fichiers.h"

#include<QMessageBox>
#include<QPushButton>
Dialog_Declaration_Fichiers::Dialog_Declaration_Fichiers(Gestion_Arbre_Algo * Arbre_Algo) :
    ui(new Ui::Dialog_Declaration_Fichiers)
{
    ui->setupUi(this);
    ui->nom->setFocus();
    this->setModal(true);
    this->ArbreAlgo = Arbre_Algo;
    sous_modification = false;
    ui->buttonBox->buttons().at(0)->setText("Déclarer");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    this->setWindowTitle("Déclarer une fichier");
    listesContenuType = Arbre_Algo->liste_TypeContenu("");
    CompleterContenuType = new QCompleter(listesContenuType);
    listeTypes = Arbre_Algo->listeTypes();
    CompleterTypes = new QCompleter(listeTypes);

    ui->nom->setCompleter(CompleterTypes);
    ui->contenu->setCompleter(CompleterContenuType);
    nom_Courant = "";
}

Dialog_Declaration_Fichiers::~Dialog_Declaration_Fichiers()
{
    delete ui;
}

void Dialog_Declaration_Fichiers::metter_sous_modification()
{
    sous_modification = true;
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    QStringList listeInfo  = ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#");
    ui->nom->setText(listeInfo.at(1));
    ui->contenu->setText(listeInfo.at(2));
    nom_Courant = ui->nom->text();
}

void Dialog_Declaration_Fichiers::on_buttonBox_accepted()
{
    QString messageControle = Controle_NomType();
    if(messageControle.isEmpty())
        messageControle = controle_ContenuType();
    if(!messageControle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur ",messageControle,QMessageBox::Ok);
        return;
    }
    // PREPARTION STD ITEM ALGO
    if(sous_modification)
    {
        ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setText(ui->nom->text() + " = Fichier des " + ui->contenu->text());
        ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription("4#" + ui->nom->text() + "#" + ui->contenu->text());
    }
    else
    {
        QStandardItem * std_fichier = new QStandardItem(nomtype + " = Fichier des " + contenuType);
        std_fichier->setEditable(false);
        std_fichier->setAccessibleDescription("4#" + nomtype + "#" + contenuType);

        std_fichier->setWhatsThis("fich");
        // SETTING IN ARBRE VIEW ALGO

        if(ArbreAlgo->modelViewAlgo->item(0)->hasChildren())
        {
            for(int  i = 0; i < ArbreAlgo->modelViewAlgo->item(0)->rowCount();i++)
                if(ArbreAlgo->modelViewAlgo->item(0)->child(i)->text() == "Types")
                {
                    ArbreAlgo->modelViewAlgo->item(0)->child(i)->appendRow(std_fichier);
                    return;
                }
            QStandardItem * std_rootfichs = new QStandardItem("Types");
            std_rootfichs->appendRow(std_fichier);
            std_rootfichs->setEditable(false);
            std_rootfichs->setWhatsThis("types");

            if(ArbreAlgo->modelViewAlgo->item(0)->child(0)->text() == "Constantes")

                ArbreAlgo->modelViewAlgo->item(0)->insertRow(1,std_rootfichs);
            else
                ArbreAlgo->modelViewAlgo->item(0)->insertRow(0,std_rootfichs);

        }
        else
        {
            QStandardItem * std_rootfichs = new QStandardItem("Types");
            std_rootfichs->setWhatsThis("types");
            std_rootfichs->setEditable(false);
            std_rootfichs->appendRow(std_fichier);
            ArbreAlgo->modelViewAlgo->item(0)->appendRow(std_rootfichs);
        }
        ArbreAlgo->ArbreAlgo->setCurrentIndex(std_fichier->index());
    }

}

QString Dialog_Declaration_Fichiers::Controle_NomType()
{
    nomtype = ArbreAlgo->PasEspaces(ui->nom->text());
    return ArbreAlgo->Controle_NomType(nomtype,nom_Courant);
}

QString Dialog_Declaration_Fichiers::controle_ContenuType()
{
    contenuType = ArbreAlgo->PasEspaces(ui->contenu->text());
    return  ArbreAlgo->Controle_TypeContenu(0,ArbreAlgo->PasEspaces(ui->nom->text()),contenuType);
}

void Dialog_Declaration_Fichiers::on_nom_textChanged(const QString &arg1)
{
    listesContenuType = ArbreAlgo->liste_TypeContenu(ArbreAlgo->PasEspaces(ui->nom->text()));
    CompleterContenuType = new QCompleter(listesContenuType);
    ui->contenu->setCompleter(CompleterContenuType);

    ui->commentaire->setText(Controle_NomType());
}

void Dialog_Declaration_Fichiers::on_contenu_textChanged(const QString &arg1)
{
    ui->commentaire->setText(controle_ContenuType());
}
