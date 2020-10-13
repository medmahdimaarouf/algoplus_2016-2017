#include "dialog_appelle_procedure.h"
#include "ui_dialog_appelle_procedure.h"
#include<QMessageBox>
#include<QPushButton>

Dialog_appelle_procedure::Dialog_appelle_procedure(int index, Gestion_Arbre_Algo *ArbreAlgo) :
    ui(new Ui::Dialog_appelle_procedure)
{
    ui->setupUi(this);
    ui->nomproc->setFocus();
    Arbre_Algo = ArbreAlgo;
    this->index = index;
    sous_modification =  false;

    if(index == 0)
    {

        listeProcs = ArbreAlgo->listeProcedures();

        if(listeProcs.isEmpty())
        {
            QMessageBox::information(this,"Information","Aucune procedure a éte declarer",QMessageBox::Ok);
        }
        nbrParas = 0;
        Completer_Procs = new QCompleter(listeProcs);
        ui->nomproc->setCompleter(Completer_Procs);
        qDebug()<<listeProcs;
        this->setWindowTitle("Ajouter une Procedure");
    }
    else
    {
        init_context(index,"Ajouter " + defproc);
    }


    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
}

Dialog_appelle_procedure::~Dialog_appelle_procedure()
{
    delete ui;
}

void Dialog_appelle_procedure::metter_sous_modification()
{
    sous_modification = true;
    ui->buttonBox->buttons().at(0)->setText("Modifier");

    if(index == 0)
    {
        this->setWindowTitle("Modifier une appelle de procedure");
        ui->nomproc->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
        ui->nomproc->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));

    }else
    {
        init_context(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(2).toInt(),"Modifier les parametres de la procedure : " + defproc );
    }

    ui->Parametres->setText(Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(3));
    ui->buttonBox->buttons().at(0)->setText("Modifier");
}

void Dialog_appelle_procedure::on_buttonBox_accepted()
{
    QString message_Controle = ControleSaisie_NomProc();
    if(message_Controle.isEmpty())
        message_Controle = ControleSaise_Parametres();
    if(!message_Controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_Controle,QMessageBox::Ok);
        return;
    }

        if(sous_modification)
        {
            Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setText(nomproc + "(" + parametres + ")");
            Arbre_Algo->modelViewAlgo->itemFromIndex(Arbre_Algo->ArbreAlgo->currentIndex())->setAccessibleDescription("12#" + nomproc + "#" + QString::number(index) + "#" + parametres);
        }
        else
        {
            QStandardItem * itemAlgo = new QStandardItem(nomproc + "(" + parametres + ")");
            itemAlgo->setAccessibleDescription("12#" + nomproc + "#" + QString::number(index) + "#" + parametres);
            itemAlgo->setWhatsThis("item");
            itemAlgo->setEditable(false);
            Arbre_Algo->add_newItemAlgo(itemAlgo);
        }
}

void Dialog_appelle_procedure::on_Parametres_textChanged(const QString &arg1)
{
  ui->Commentaire->setText(ControleSaise_Parametres());
}

QString Dialog_appelle_procedure::ControleSaise_Parametres()
{
    parametres = Arbre_Algo->PasEspaces(ui->Parametres->text());
    return Arbre_Algo->Controle_Parametres(parametres);
}

QString Dialog_appelle_procedure::ControleSaisie_NomProc()
{
   if(!index)
   {
       nomproc = Arbre_Algo->PasEspaces(ui->nomproc->text());
       if(!listeProcs.contains(nomproc))
          return "Nom procedure saisie n'est pas déclarer";
   }
   return "";
}

void Dialog_appelle_procedure::init_context(int index,QString titre)
{
    if(index == 0)
    {
        nbrParas = 0;
        nomproc = "";
        defproc = "";

    }else
     {

        switch (index) {
        case 1:
        {
            nomproc = "Allouer";
            defproc = "Allouer(var P : Pointeur)";
            nbrParas = 1;
        }break;
        case 2:
        {
            nomproc = "Liberer";
            defproc = "Liberer(var P : Pointeur)";
            nbrParas = 1;
        }break;
        case 3:
        {
            nomproc = "Associer";
            defproc = "Associer(var F : Fichier,ch : chaine)";
            nbrParas = 2;
        }break;
        case 4:
        {
            nomproc = "Ouvrir";
            defproc = "Ouvrir(var F : Fichier)";
            nbrParas = 1;
        }break;
        case 5:
        {
            nomproc = "Fermer";
            defproc = "Fermer(var F : Fichier)";
            nbrParas = 1;
        }break;
        case 6:
        {
            nomproc = "Recree";
            defproc = "Recree(var F : Fichier)";
            nbrParas = 1;
        }break;
        case 7:
        {
            nomproc = "Pointer";
            defproc = "Pointer(var F : Fichier, P : entier)";
            nbrParas = 2;
        }break;
        case 8:
        {
            nomproc = "Lire";
            defproc = "Lire(var F : Fichier,var V : variable)";
            nbrParas = 2;
        }break;
        case 9:
        {
            nomproc = "Valeur";
            defproc = "Valeur(ch : chaine,N : entier,e : booleen)";
            nbrParas = 2;
        }break;
        case 10:
        {
            nomproc = "Convch";
            defproc = "Convch(N : entier,var ch : chaine)";
            nbrParas = 2;
        }break;
        case 11:
        {
            nomproc = "Efface";
            defproc = "Efface(var ch : chaine, pi,pf : entier)";
            nbrParas = 3;
        }break;
        case 12:
        {
            nomproc = "Inserer";
            defproc = "Inserer(ch1 : chaine, var ch2 : chaine,p : entier)";
            nbrParas = 1;
        }break;
        case 13:
        {
            nomproc = "Concat";
            defproc = "Concat(var ch1 : chaine, ch2 : chaine)";
            nbrParas = 2;
        }break;
        default:
            break;
        }
        ui->nomproc->setText(nomproc);
        ui->nomproc->setEnabled(false);
        setWindowTitle(titre);

    }

}

void Dialog_appelle_procedure::on_nomproc_textChanged(const QString &arg1)
{
    if(!index)
        ui->Commentaire->setText(ControleSaisie_NomProc());
}
