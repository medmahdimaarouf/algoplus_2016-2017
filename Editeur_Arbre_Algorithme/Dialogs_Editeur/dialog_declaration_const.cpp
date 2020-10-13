#include "dialog_declaration_const.h"
#include "ui_dialog_declaration_const.h"
#include<QMessageBox>
#include<QPushButton>
Dialog_Declaration_Const::Dialog_Declaration_Const(Gestion_Arbre_Algo *Arbre_Algo) :
    //QDialog(parent),
    ui(new Ui::Dialog_Declaration_Const)
{
   ui->setupUi(this);
   ui->nom->setFocus();
   this->setModal(true);
   this->ArbreAlgo = Arbre_Algo;
   ui->buttonBox->buttons().at(0)->setText("Déclarer");
   ui->buttonBox->buttons().at(1)->setText("Annuler");
   this->setWindowTitle("Décalrer une constante");
   sous_modification = false;
}

Dialog_Declaration_Const::~Dialog_Declaration_Const()
{
    delete ui;
}

void Dialog_Declaration_Const::metter_sous_modification()
{
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    this->setWindowTitle("Modifier une constante");
    sous_modification = true;
    ui->nom->setText(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(0));
    ui->valeur->setText(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
}

void Dialog_Declaration_Const::on_buttonBox_accepted()
{
    QString message_Controle = Controle_Constante();
    if(message_Controle.isEmpty())
        message_Controle = Controle_Valeur();
    if(!message_Controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur ",message_Controle);
        return;
    }

    if(sous_modification)
    {
        ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setText(ui->nom->text() + " = " + ui->valeur->text());
        ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription(ui->nom->text() + "#" + ui->valeur->text());
    }
    else
    {
        QStandardItem  *std_constante = new QStandardItem(constante + " = " + valeur);
        std_constante->setAccessibleDescription(constante + "#" + valeur);
        std_constante->setWhatsThis("const");
        std_constante->setEditable(false);

        if(ArbreAlgo->Algo->hasChildren())
        {
            for(int i = 0;i < ArbreAlgo->Algo->rowCount();i++)
                if(ArbreAlgo->Algo->child(i)->text() == "Constantes")
                {
                    ArbreAlgo->Algo->child(i)->appendRow(std_constante);
                    return;
                }
            QStandardItem * std_rootconsts = new QStandardItem("Constantes");
            std_rootconsts->setEditable(false);
            std_rootconsts->setWhatsThis("constantes");
            std_rootconsts->appendRow(std_constante);
            ArbreAlgo->Algo->insertRow(0,std_rootconsts);
        }
        else
        {
            QStandardItem * std_rootconsts = new QStandardItem("Constantes");
            std_rootconsts->appendRow(std_constante);
            std_rootconsts->setEditable(false);
            std_rootconsts->setWhatsThis("constantes");
            ArbreAlgo->Algo->appendRow(std_rootconsts);
        }
        ArbreAlgo->ArbreAlgo->setCurrentIndex(std_constante->index());
    }

}

void Dialog_Declaration_Const::on_nom_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_Constante());
}

void Dialog_Declaration_Const::on_valeur_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_Valeur());
}

QString Dialog_Declaration_Const::Controle_Constante()
{
    constante = ArbreAlgo->PasEspaces(ui->nom->text());
    return ArbreAlgo->Controle_Constante(constante);
}

QString Dialog_Declaration_Const::Controle_Valeur()
{
    valeur = ArbreAlgo->PasEspaces(ui->valeur->text());
    if(valeur.isEmpty())
        return "Valeur de constante indeffinit";
    return "";
}

