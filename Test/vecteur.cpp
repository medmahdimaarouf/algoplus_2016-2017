#include "vecteur.h"
#include "ui_vecteur.h"

Vecteur::Vecteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vecteur)
{
    ui->setupUi(this);
}

Vecteur::~Vecteur()
{
    delete ui;
}
