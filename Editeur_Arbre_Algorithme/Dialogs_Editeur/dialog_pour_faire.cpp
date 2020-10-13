#include "dialog_pour_faire.h"
#include "ui_dialog_pour_faire.h"
#include<QPushButton>
Dialog_Pour_Faire::Dialog_Pour_Faire(Gestion_Arbre_Algo * ArbreAlgo) :
    ui(new Ui::Dialog_Pour_Faire)
{
    ui->setupUi(this);
    ui->cmp->setFocus();
    this->ArbreAlgo = ArbreAlgo;
    sous_modification = false;

    ui->buttonBox->buttons().at(0)->setText("Ajouter");
    ui->buttonBox->buttons().at(1)->setText("Annuler");
    setWindowTitle("Ajouter Pour..Faire");
    listevariables = ArbreAlgo->liste_Variables_DE(ArbreAlgo->Programme_Courante());
    CompleterCMP = new QCompleter(listevariables);
    ui->cmp->setCompleter(CompleterCMP);
}

Dialog_Pour_Faire::~Dialog_Pour_Faire()
{
    delete ui;
}

void Dialog_Pour_Faire::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier Pour..Faire");
    ui->buttonBox->buttons().at(0)->setText("Modifier");
    ui->cmp->setText(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(1));
    ui->vi->setText(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(2));
    ui->vf->setText(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(3));
    ui->pas->setValue(ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(4).toInt());
}

void Dialog_Pour_Faire::on_buttonBox_accepted()
{
    vi = ArbreAlgo->PasEspaces(ui->vi->text());
    vf = ArbreAlgo->PasEspaces(ui->vf->text());
    QString message_controle = Controle_Compteur();
    if(message_controle.isEmpty())
    {
        if(vi.isEmpty())
            message_controle = "Valeur initiale indeffinit";
        else
            if(vf.isEmpty())
                message_controle = "Valeur finale indeffinit";
    }
    if(!message_controle.isEmpty())
    {
        QMessageBox::warning(this,"Erreur",message_controle,QMessageBox::Ok);
        return;
    }
    if(sous_modification)
    {
        ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setText("POUR" + cmp + " DE " + vi + " A " + vf + " FAIRE");
        ArbreAlgo->modelViewAlgo->itemFromIndex(ArbreAlgo->ArbreAlgo->currentIndex())->setAccessibleDescription("9#" + cmp + "#" + vi + "#" + vf + "#" + QString::number(ui->pas->value()));
    }
    else
    {
        QStandardItem * std_Algo = new QStandardItem("POUR" + cmp + " DE " + vi + " A " + vf + " FAIRE");
        std_Algo->setAccessibleDescription("9#" + cmp + "#" + vi + "#" + vf + "#" + QString::number(ui->pas->value()));
        std_Algo->setWhatsThis("item");
        QStandardItem * std_inst = new QStandardItem("");
        std_Algo->appendRow(std_inst);
        QStandardItem * fin = new QStandardItem("FIN POUR");
         fin->setAccessibleDescription("0#FIN POUR");
         fin->setWhatsThis("fin");
        std_Algo->appendRow(fin);
        ArbreAlgo->add_newItemAlgo(std_Algo);
        ArbreAlgo->ArbreAlgo->setCurrentIndex(std_inst->index());
    }
}

void Dialog_Pour_Faire::Comteur_Change()
{
    ui->Commantaire->setText(Controle_Compteur());
}

QString Dialog_Pour_Faire::Controle_Compteur()
{
    cmp = ArbreAlgo->PasEspaces(ui->cmp->text());
    return ArbreAlgo->Controle_Variable(cmp);
}
