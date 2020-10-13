#include "dialog_declaration_variable.h"
#include "ui_dialog_declaration_variable.h"
#include<QMessageBox>
#include<QPushButton>

Dialog_Declaration_variable::Dialog_Declaration_variable(Gestion_Arbre_Algo *ArbreAlgo ) :
    ui(new Ui::Dialog_Declaration_variable)
{
    ui->setupUi(this);
    ui->nom->setFocus();
    this->setModal(true);
    Arbre_Algo = ArbreAlgo;
    /*for(int i = 0; i < Arbre_Algo->modelViewAlgo->item(0)->rowCount();i++)
        if(!Arbre_Algo->modelViewAlgo->item(0)->child(i)->accessibleDescription().isEmpty())
        {
            listSousProgram.append(ArbreAlgo->modelViewAlgo->item(0)->child(i));
            ui->program->addItem(ArbreAlgo->modelViewAlgo->item(0)->child(i)->accessibleDescription().split("#").at(1));
        }
    */

    ui->program->addItems(ArbreAlgo->listeProgrammmes());
    ui->program->setCurrentIndex(0);

    this->setWindowTitle("Déclarer un variable");
    ui->buttonBox->buttons().at(0)->setText("Déclarer");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    sous_modification = false;

    listevars = Arbre_Algo->liste_Variables_DE(ui->program->currentText());
    CompleterVariables = new QCompleter(listevars);
    ui->nom->setCompleter(CompleterVariables);

    listeTypesVar = Arbre_Algo->liste_TypeContenu("");
    completerTypes = new QCompleter(listeTypesVar);
    ui->Type->setCompleter(completerTypes);
    connect(ui->program,SIGNAL(currentTextChanged(QString)),this,SLOT(on_program_currentTextChanged(QString)));
    nom_Courant = "";
}

Dialog_Declaration_variable::~Dialog_Declaration_variable()
{
    delete completerTypes,CompleterVariables;
    delete ui;
}

void Dialog_Declaration_variable::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier un variable");
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    QStringList listeInfo = Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#");
    ui->nom->setText(listeInfo.at(0));
    ui->Type->setText(listeInfo.at(1));
    ui->program->setEditable(false);
    nom_Courant = ui->nom->text();
}

QString Dialog_Declaration_variable::ControleVariable()
{
    nom = Arbre_Algo->PasEspaces(ui->nom->text());
    return Arbre_Algo->Controle_NomVariable(nom,ui->program->currentText(),nom_Courant);
}

QString Dialog_Declaration_variable::Controle_Type()
{
    type = Arbre_Algo->PasEspaces(ui->Type->text());
    return Arbre_Algo->Controle_TypeContenu(-1,nom,type);
}


void Dialog_Declaration_variable::on_buttonBox_accepted()
{
    QString message_Controle = ControleVariable();
    if(message_Controle.isEmpty())
        message_Controle = Controle_Type();
    if(!message_Controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur ",message_Controle,QMessageBox::Ok);
        return;
    }

     if(sous_modification)
     {
         Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText(nom + ":" + type);
         Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setAccessibleDescription(nom + "#" + type);
     }
      else
     {
         QStandardItem * std_variable = new QStandardItem(nom + ":" + type);
         std_variable->setEditable(false);
         std_variable->setAccessibleDescription(nom + "#" + type);
         std_variable->setWhatsThis("var");

        if(ui->program->currentIndex() == 0)
        {// CAS OU LE DECLARATION EN PROGRAME PRINCIPALE
            if(Arbre_Algo->modelViewAlgo->item(0)->hasChildren())
            {
                for(int i = 0; i < Arbre_Algo->modelViewAlgo->item(0)->rowCount();i++)
                    if(Arbre_Algo->modelViewAlgo->item(0)->child(i)->text() == "Variables")
                    {
                        Arbre_Algo->modelViewAlgo->item(0)->child(i)->appendRow(std_variable);
                        return;
                    }
                QStandardItem * rootvars = new QStandardItem("Variables");
                rootvars->setEditable(false);
                rootvars->setWhatsThis("variables");
                rootvars->appendRow(std_variable);

                if(Arbre_Algo->modelViewAlgo->item(0)->rowCount() == 1)
                    Arbre_Algo->modelViewAlgo->item(0)->insertRow(1,rootvars);
                else
                    if(Arbre_Algo->modelViewAlgo->item(0)->rowCount() >= 2)
                        Arbre_Algo->modelViewAlgo->item(0)->insertRow(2,rootvars);
            }
            else
            {
                QStandardItem * rootvars = new QStandardItem("Variables");
                rootvars->setEditable(false);
                rootvars->setWhatsThis("variables");
                rootvars->appendRow(std_variable);
                Arbre_Algo->modelViewAlgo->item(0)->appendRow(rootvars);
            }
        }
        else
        {
            QStandardItem * std_program = Arbre_Algo->std_sousProgramme(ui->program->currentText());

           if(std_program->rowCount() == 3)
               std_program->child(0)->appendRow(std_variable);
           else
           {
               QStandardItem * std_RacineVars = new QStandardItem("Variables");
               std_RacineVars->setWhatsThis("variables");
               std_RacineVars->appendRow(std_variable);
               if(std_program)
                   std_program->insertRow(0,std_RacineVars);
           }
        }
        Arbre_Algo->ArbreAlgo->setCurrentIndex(std_variable->index());
     }
}

void Dialog_Declaration_variable::on_nom_textChanged(const QString &arg1)
{
    ui->commentaire->setText(ControleVariable());
}

void Dialog_Declaration_variable::on_Type_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_Type());
}

void Dialog_Declaration_variable::on_program_currentTextChanged(const QString &arg1)
{
    listevars = Arbre_Algo->liste_Variables_DE(arg1);
    CompleterVariables = new QCompleter(listevars);
    ui->nom->setCompleter(CompleterVariables);
    on_nom_textChanged(ui->nom->text());
}
