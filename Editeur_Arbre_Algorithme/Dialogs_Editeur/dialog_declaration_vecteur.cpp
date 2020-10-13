#include "dialog_declaration_vecteur.h"
#include "ui_dialog_declaration_vecteur.h"
#include<QMessageBox>
#include<QPushButton>
Dialog_Declaration_Vecteur::Dialog_Declaration_Vecteur(Gestion_Arbre_Algo *Arbre_Algo) :
    ui(new Ui::Dialog_Declaration_Vecteur)
{
    ui->setupUi(this);
    ui->nom->setFocus();
    this->setModal(true);
    this->ArbreAlgo = Arbre_Algo;
    sous_modification = false;
    ui->buttonBox->buttons().at(0)->setText("Déclarer");
    this->setWindowTitle("Déclarer un vecteur");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    listeTypes = Arbre_Algo->listeTypes();
    CompleterTypes = new QCompleter(listeTypes);

    listeTypesContenu = Arbre_Algo->liste_TypeContenu("");
    CompleterTypesContenu = new QCompleter(listeTypesContenu);

    ui->nom->setCompleter(CompleterTypes);
    ui->Type->setCompleter(CompleterTypesContenu);
    nom_Courant = "";

}

Dialog_Declaration_Vecteur::~Dialog_Declaration_Vecteur()
{
    delete ui;
}

void Dialog_Declaration_Vecteur::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifer un vecteur");
    ui->buttonBox->buttons().at(0)->setText("Modifer");
    QStringList listeInfo = ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#");
    ui->nom->setText(listeInfo.at(1));
    ui->taille->setValue(listeInfo.at(2).toInt());
    ui->Type->setText(listeInfo.at(3));
    nom_Courant = ui->nom->text();
}
void Dialog_Declaration_Vecteur::on_buttonBox_accepted()
{
    QString messageControle = ControleNomType();
    if(messageControle.isEmpty())
        messageControle = ControleTypeContenu();

    if(!messageControle.isEmpty())
    {
        QMessageBox::warning(this,"erreur de saisie ",messageControle,QMessageBox::Ok);
        return;
    }
        if(sous_modification)
        {
            ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setText(nom + " = Tableau[1.." + QString::number(ui->taille->value()) + "] Des " + contenu);
            ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription("1#" + nom + "#"+ QString::number(ui->taille->value()) + "#" + contenu);
        }
        else
         {
            QStandardItem * std_vecteur = new QStandardItem(nom + " = Tableau[1.." + QString::number(ui->taille->value()) + "] Des " + contenu);
            std_vecteur->setEditable(false);
            std_vecteur->setAccessibleDescription("1#" +nom + "#"+ QString::number(ui->taille->value()) + "#" + contenu);
            std_vecteur->setWhatsThis("tab");

            if(ArbreAlgo->Algo->hasChildren())
            {
                for(int  i = 0; i < ArbreAlgo->Algo->rowCount();i++)
                    if(ArbreAlgo->Algo->child(i)->text() == "Types")
                    {
                        ArbreAlgo->Algo->child(i)->appendRow(std_vecteur);
                        return;
                    }
                QStandardItem * std_rootvcts = new QStandardItem("Types");
                std_rootvcts->appendRow(std_vecteur);
                std_rootvcts->setWhatsThis("types");
                std_rootvcts->setEditable(false);

                if(ArbreAlgo->Algo->child(0)->text() == "Constantes")

                    ArbreAlgo->Algo->insertRow(1,std_rootvcts);
                else
                    ArbreAlgo->Algo->insertRow(0,std_rootvcts);

            }
            else
            {
                QStandardItem * std_rootvcts = new QStandardItem("Types");
                std_rootvcts->setEditable(false);
                std_rootvcts->setWhatsThis("types");
                std_rootvcts->appendRow(std_vecteur);
                ArbreAlgo->Algo->appendRow(std_rootvcts);
            }
          ArbreAlgo->ArbreAlgo->setCurrentIndex(std_vecteur->index());
        }
}

void Dialog_Declaration_Vecteur::on_nom_textChanged(const QString &arg1)
{
    listeTypesContenu = ArbreAlgo->liste_TypeContenu(ArbreAlgo->PasEspaces(arg1));
    CompleterTypesContenu = new QCompleter(listeTypesContenu);
    ui->Type->setCompleter(CompleterTypesContenu);
    ui->commentaire->setText(ControleNomType());
}

void Dialog_Declaration_Vecteur::on_Type_textChanged(const QString &arg1)
{
    ui->commentaire->setText(ControleTypeContenu());
}

QString Dialog_Declaration_Vecteur::ControleNomType()
{
    nom = ArbreAlgo->PasEspaces(ui->nom->text());
    return ArbreAlgo->Controle_NomType(nom,nom_Courant);
}

QString Dialog_Declaration_Vecteur::ControleTypeContenu()
{
    contenu = ArbreAlgo->PasEspaces(ui->Type->text());
    return ArbreAlgo->Controle_TypeContenu(0,ArbreAlgo->PasEspaces(ui->nom->text()),contenu);
}
