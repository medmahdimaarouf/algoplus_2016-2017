#include "dialog_declaration_matrice.h"
#include "ui_dialog_declaration_matrice.h"
#include<QMessageBox>
#include<QPushButton>
Dialog_Declaration_Matrice::Dialog_Declaration_Matrice(Gestion_Arbre_Algo *arbreAlgo) :
    ui(new Ui::Dialog_Declaration_Matrice)
{
    ui->setupUi(this);
    ui->nom->setFocus();
    this->setModal(true);
    this->Arbre_Algo = arbreAlgo;
    sous_modification = false;
    ui->buttonBox->buttons().at(0)->setText("Déclarer");
    this->setWindowTitle("Déclarer une matrice");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    listeTypes = Arbre_Algo->listeTypes();
    CompleterTypes = new QCompleter(listeTypes);
    listeTpesContenu = Arbre_Algo->liste_TypeContenu("");
    CompleterTypesContenu = new QCompleter(listeTpesContenu);
    ui->nom->setCompleter(CompleterTypes);
    ui->Contenu->setCompleter(CompleterTypesContenu);
    nom_Courant = "";
}

Dialog_Declaration_Matrice::~Dialog_Declaration_Matrice()
{
    delete CompleterTypes,CompleterTypesContenu;
    delete ui;
}

void Dialog_Declaration_Matrice::metter_sous_modification()
{
    sous_modification = true;
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    this->setWindowTitle("Modifier une matrice");
    QStringList listeInfo = Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#");
    ui->nom->setText(listeInfo.at(1));
    ui->nbrligne->setValue(listeInfo.at(2).toInt());
    ui->nbrcolonne->setValue(listeInfo.at(3).toInt());
    nom_Courant = ui->nom->text();

    ui->Contenu->setText(listeInfo.at(4));
    listeTpesContenu = Arbre_Algo->liste_TypeContenu(Arbre_Algo->PasEspaces(ui->nom->text()));
    CompleterTypesContenu = new QCompleter(listeTpesContenu);
    listeTypes = Arbre_Algo->listeTypes();
    CompleterTypes = new QCompleter(listeTypes);
}

void Dialog_Declaration_Matrice::on_buttonBox_accepted()
{
    QString messageControle = Controle_NomType();
    if(messageControle.isEmpty())
        messageControle = Controle_TypeContenu();
    if(!messageControle.isEmpty())
    {
        QMessageBox::warning(this,"erreur de saisie ",messageControle,QMessageBox::Ok);
        return;
    }
    if(sous_modification)
    {
        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setAccessibleDescription("2#" + nom + "#" + QString::number(ui->nbrligne->value()) + "#" + QString::number(ui->nbrcolonne->value()) + "#" + contenu);
        Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText(nom + " = Tableau[1.." + QString::number(ui->nbrligne->value()) + "][1.." + QString::number(ui->nbrcolonne->value()) + "] Des " + contenu);

    }else
    {
        QStandardItem * std_matrice = new QStandardItem(nom + " = Tableau[1.." + QString::number(ui->nbrligne->value()) + "][1.." + QString::number(ui->nbrcolonne->value()) + "] Des " + contenu);
        std_matrice->setEditable(false);
        std_matrice->setAccessibleDescription("2#" + nom + "#" + QString::number(ui->nbrligne->value()) + "#" + QString::number(ui->nbrcolonne->value()) + "#" + contenu);
        std_matrice->setWhatsThis("mat");

        if(Arbre_Algo->modelViewAlgo->item(0)->hasChildren())
        {
            for(int  i = 0; i < Arbre_Algo->modelViewAlgo->item(0)->rowCount();i++)
                if(Arbre_Algo->modelViewAlgo->item(0)->child(i)->text() == "Types")
                {
                    Arbre_Algo->modelViewAlgo->item(0)->child(i)->appendRow(std_matrice);
                    return;
                }
            QStandardItem * std_rootmats = new QStandardItem("Types");
            std_rootmats->appendRow(std_matrice);
            std_rootmats->setEditable(false);
            std_rootmats->setWhatsThis("types");

            if(Arbre_Algo->modelViewAlgo->item(0)->child(0)->text() == "Constantes")
                Arbre_Algo->modelViewAlgo->item(0)->insertRow(1,std_rootmats);
            else
                Arbre_Algo->modelViewAlgo->item(0)->insertRow(0,std_rootmats);

        }
        else
        {
            QStandardItem * std_rootmats = new QStandardItem("Types");
            std_rootmats->setWhatsThis("types");
            std_rootmats->setEditable(false);
            std_rootmats->appendRow(std_matrice);
            Arbre_Algo->modelViewAlgo->item(0)->appendRow(std_rootmats);
        }
       Arbre_Algo->ArbreAlgo->setCurrentIndex(std_matrice->index());
    }

}

QString Dialog_Declaration_Matrice::Controle_NomType()
{
    nom = Arbre_Algo->PasEspaces(ui->nom->text());
    listeTpesContenu = Arbre_Algo->liste_TypeContenu(nom);
    CompleterTypesContenu = new QCompleter(listeTpesContenu);
    ui->Contenu->setCompleter(CompleterTypesContenu);
    return Arbre_Algo->Controle_NomType(nom,nom_Courant);
}

QString Dialog_Declaration_Matrice::Controle_TypeContenu()
{
    contenu = Arbre_Algo->PasEspaces(ui->Contenu->text());
    return Arbre_Algo->Controle_TypeContenu(0,Arbre_Algo->PasEspaces(ui->nom->text()),contenu);
}

void Dialog_Declaration_Matrice::on_nom_textChanged(const QString &arg1)
{
    listeTpesContenu = Arbre_Algo->liste_TypeContenu(Arbre_Algo->PasEspaces(ui->nom->text()));
    CompleterTypesContenu = new QCompleter(listeTpesContenu);
    ui->Contenu->setCompleter(CompleterTypesContenu);

    ui->commentaire->setText(Controle_NomType());
}

void Dialog_Declaration_Matrice::on_Contenu_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_TypeContenu());
}
