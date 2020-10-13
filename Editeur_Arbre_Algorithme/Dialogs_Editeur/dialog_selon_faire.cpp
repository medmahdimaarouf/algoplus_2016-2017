#include "dialog_selon_faire.h"
#include "ui_dialog_selon_faire.h"

Dialog_Selon_faire::Dialog_Selon_faire(QString selecteur,Gestion_Arbre_Algo *Arbre_Algo) :
    ui(new Ui::Dialog_Selon_faire)
{
    ui->setupUi(this);
    ui->selecteur->setText(selecteur);
    this->Arbre_Algo = Arbre_Algo;
}

Dialog_Selon_faire::~Dialog_Selon_faire()
{
    delete ui;
}

void Dialog_Selon_faire::metter_sous_modification()
{
    sous_modification = true;
    this->setWindowTitle("Modifier Selon..Faire");
    ui->buttonBox->buttons().at(0)->setText("Modifier");
}

void Dialog_Selon_faire::on_Ajouter_clicked()
{
    ui->listchoix->addItem(ui->choix->text());
}

void Dialog_Selon_faire::on_supprimer_c_clicked()
{
    ui->listchoix->model()->removeRow(ui->listchoix->currentRow());
}

void Dialog_Selon_faire::on_supprimer_t_clicked()
{
    ui->listchoix->clear();
}

void Dialog_Selon_faire::on_buttonBox_accepted()
{
    QStandardItem * std_Algo = new QStandardItem("SELON ("+ui->selecteur->text()+") FAIRE");
    std_Algo->setAccessibleDescription("7#"+ui->selecteur->text());
    std_Algo->setWhatsThis("item");
    QStandardItem * std_fin = new QStandardItem("FIN SELON");
    std_fin->setAccessibleDescription("0#FIN SELON");
    std_fin->setWhatsThis("fin");
    std_Algo->appendRow(std_fin);
    Arbre_Algo->add_newItemAlgo(std_Algo);
}
