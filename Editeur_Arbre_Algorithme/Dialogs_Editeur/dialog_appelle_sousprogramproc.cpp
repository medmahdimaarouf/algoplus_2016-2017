#include "dialog_appelle_sousprogramproc.h"
#include "ui_dialog_appelle_sousprogramproc.h"

Dialog_appelle_SousProgramProc::Dialog_appelle_SousProgramProc(QWidget *parent, QString nom, QString parametres, QStandardItem *RouteOfPrograms,Gestion_Arbre_Algo * Arbre_Algo) :
    QDialog(parent),
    ui(new Ui::Dialog_appelle_SousProgramProc)
{
    ui->setupUi(this);
    ArbreAlgo = Arbre_Algo;
    bool findproc = false;
    if(RouteOfPrograms->hasChildren())
        for(int i = 0; i < RouteOfPrograms->rowCount();i++)
        {
            if(RouteOfPrograms->child(i)->text() == "Constantes" || RouteOfPrograms->child(i)->text() == "Types" || RouteOfPrograms->child(i)->text() == "Variables")
                if(RouteOfPrograms->child(i)->accessibleDescription().split("#").at(2).toInt() == 1)
                    ui->Procedures->addItem(RouteOfPrograms->child(i)->accessibleDescription().split("#").at(0));
                         if(nom == RouteOfPrograms->child(i)->accessibleDescription().split("#").at(0))
                             findproc = true;
        }
    if(findproc)
    {
        ui->Procedures->setCurrentText(nom);
        ui->Parametres->setText(parametres);
    }
}

Dialog_appelle_SousProgramProc::~Dialog_appelle_SousProgramProc()
{
    delete ui;
}

void Dialog_appelle_SousProgramProc::on_buttonBox_accepted()
{
    QStandardItem *ItemAlgo = new QStandardItem(ui->Procedures->currentText() + "(" + ui->Parametres->text() + ")");
    ItemAlgo->setWhatsThis("item");
    ItemAlgo->setAccessibleDescription("12#" + ui->Procedures->currentText() + "#1#" + ui->Parametres->text() );
    ArbreAlgo->add_newItemAlgo(ItemAlgo);
}

QString Dialog_appelle_SousProgramProc::controle()
{
    if(ui->Procedures->currentText() == "")
        return "Nom de procedure invalide";

}
