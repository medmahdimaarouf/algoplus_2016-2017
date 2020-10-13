#include "dialog_affecation.h"
#include "ui_dialog_affecation.h"
#include<QPushButton>

Dialog_Affecation::Dialog_Affecation(Gestion_Arbre_Algo *Arbre_Algo) :
    ui(new Ui::Dialog_Affecation)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->Variable->setFocus();
    ArbreAlgo = Arbre_Algo;
    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    this->setWindowTitle("Ajouter une affectation");
    sous_modification = false;
    listeVariables = Arbre_Algo->liste_Variables_DE(Arbre_Algo->Programme_Courante());
    CompleterVariable = new QCompleter(listeVariables);
    ui->Variable->setCompleter(CompleterVariable);
}

Dialog_Affecation::~Dialog_Affecation()
{
    delete ui;
}

QString effacer_espaces(QString chaine)
{
    for(int i = 0; i < chaine.size() && chaine.at(i).isSpace();i++)
        chaine.remove(i,1);
    for(int i = chaine.count()-1; i >= 0 && chaine.at(i).isSpace();i--)
        chaine.remove(i,1);
}

void Dialog_Affecation::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier une affectation");
    ui->buttonBox->buttons().at(0)->setText("Modifier");

    ui->Variable->setText(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
    ui->valeur->setText(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(2));
}

void Dialog_Affecation::on_buttonBox_accepted()
{
    QString message_Controle = controle_de_saisieVariable();

    if(message_Controle.isEmpty())
        message_Controle = controle_de_saisieExression();

    if(!message_Controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_Controle,QMessageBox::Ok);
        return;
    }
    if(sous_modification)
    {
        ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setText(variable + "<--" + expression);
        ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription("1#" + variable + "#" + expression);
    }
    else
    {
        QStandardItem * Item_Algo = new QStandardItem(variable + "<--" + expression);
        Item_Algo->setAccessibleDescription("1#" + variable + "#" + expression);
        Item_Algo->setWhatsThis("item");
        Item_Algo->setEditable(false);
        ArbreAlgo->add_newItemAlgo(Item_Algo);

    }
}

QString Dialog_Affecation::controle_de_saisieVariable()
{
    variable = ArbreAlgo->PasEspaces(ui->Variable->text());
    return ArbreAlgo->Controle_Variable(variable);
}

QString Dialog_Affecation::controle_de_saisieExression()
{
    expression = ArbreAlgo->PasEspaces(ui->valeur->text());
    return ArbreAlgo->Controle_Expression(expression);
}

void Dialog_Affecation::on_Variable_textChanged(const QString &arg1)
{
    ui->commentaire->setText(controle_de_saisieVariable());
}

void Dialog_Affecation::on_valeur_textChanged(const QString &arg1)
{
    ui->commentaire->setText(controle_de_saisieExression());
}
