#include "dialog_champ_parametre.h"
#include "ui_dialog_champ_parametre.h"
#include<QMessageBox>

QString decrype_passage(bool passage)
{
    if(passage)
        return "Par adresse";
    else
        return "Par valeur";
}

Dialog_champ_parametre::Dialog_champ_parametre(int operation,Gestion_Arbre_Algo *ArbreAlgo, QString typeCourant) :
    ui(new Ui::Dialog_champ_parametre)
{
    ui->setupUi(this);
    ui->nom->setFocus();
    this->setModal(true);
    this->ArbreAlgo = ArbreAlgo;
    passe_var_Widget = ui->Passage_widget;
    types_var = new QList<QString>;
    ui->passage_par_valeur->setChecked(true);

    listeTypesContenu = ArbreAlgo->liste_TypeContenu(typeCourant);
    Completer_TypesContenu = new QCompleter(listeTypesContenu);
    ui->Type->setCompleter(Completer_TypesContenu);
    TypeCourant = typeCourant;
    Operation = operation;
    if(operation == 1)
    {
        ui->Passage_widget->setVisible(false);
        ui->line_2->setVisible(false);
        setWindowTitle("Ajouter un parametre du fonction");
    }
    else
            if(operation == 2)
                setWindowTitle("Ajouter un parametre du procedure");
            else
            {
                setWindowTitle("Ajouter un champ");
                ui->Passage_widget->setVisible(false);
            }
    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");

}

Dialog_champ_parametre::~Dialog_champ_parametre()
{
    delete CompleterTypes;
    delete ui;
}

void Dialog_champ_parametre::on_buttonBox_accepted()
{
    QString message_Controle = Controle_NomCP();
    if(message_Controle.isEmpty())
        message_Controle = Controle_TypeCP();
    if(!message_Controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_Controle,QMessageBox::Ok);
        return;
    }

    if(Operation == 1)
    {
        QTreeWidgetItem * parametre = new QTreeWidgetItem(liste_parametres);
        parametre->setText(0,nom);
        parametre->setText(1,type);
        parametre->setText(2,"Par valeur");
        liste_parametres->addTopLevelItem(parametre);
     }
     else if(Operation == 2)
        {
            QTreeWidgetItem * parametre = new QTreeWidgetItem(liste_parametres);
            parametre->setText(0,nom);
            parametre->setText(1,type);
            parametre->setText(2,decrype_passage(ui->passage_par_adresse->isChecked()));
            liste_parametres->addTopLevelItem(parametre);
        }
            else
            {
                QTreeWidgetItem * champ = new QTreeWidgetItem(liste_champs);
                champ->setText(0,nom);
                champ->setText(1,type);
                liste_champs->addTopLevelItem(champ);
    }
}

QString Dialog_champ_parametre::Controle_NomCP()
{
    nom = ArbreAlgo->PasEspaces(ui->nom->text());
    if(Operation > 2)
        return ArbreAlgo->ControleNomCP(Operation,liste_champs,nom);
    else
        return ArbreAlgo->ControleNomCP(Operation,liste_parametres,nom);

}


QString Dialog_champ_parametre::Controle_TypeCP()
{
    type = ArbreAlgo->PasEspaces(ui->Type->text());
    return ArbreAlgo->Controle_TypeContenu(Operation,TypeCourant,type);
}


void Dialog_champ_parametre::on_nom_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_NomCP());
}

void Dialog_champ_parametre::on_Type_textChanged(const QString &arg1)
{
    ui->commentaire->setText(Controle_TypeCP());
}


/*     QString messageControle = ArbreAlgo->Controle_NomVariable(nom,"");

    QString prefix;
    if(Operation > 2)
        prefix = "Champ";
    else
        prefix = "Parametre";

    if(!messageControle.isEmpty())
        return prefix + messageControle.remove("Nom de variable");

    if(nomVariable.isEmpty())
        return "Nom de variable n'est pas déffinit";
    if(!nomVariable.at(0).isLetter())
        return "Nom de variable doit commncé par une lettre";
    for(int i = 0; i < nomVariable.size();i++)
        if(nomVariable.at(i).isSpace())
            return "Nom de variable contient un espace";
        else
            if(!nomVariable.at(i).isLetterOrNumber() && nomVariable.at(i) != '_')
                return QString("Nom de variable contient un symbole interdit '").append(nomVariable.at(i)) + "'";



    if(prefix == "Champ" && nom == "id")
        return "Champ interdit";

    listeNoms.clear();

    if(Operation == 3)
    {
        if(liste_champs->topLevelItemCount())
            for(int i = 0; i < liste_champs->topLevelItemCount();i++)
                listeNoms<<liste_champs->topLevelItem(i)->text(0);
        if(listeNoms.contains(nom))
            return "Champ existe déja";

    }else
    {
        if(liste_parametres->topLevelItemCount())
            for(int i = 0; i < liste_parametres->topLevelItemCount();i++)
                listeNoms<<liste_parametres->topLevelItem(i)->text(0);
        if(listeNoms.contains(nom))
            return "Parametre existe déja";
    }
    return "";
*/
