#include "commentaire.h"
#include "ui_commentaire.h"

Commentaire::Commentaire(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Commentaire)
{
    ui->setupUi(this);
}

Commentaire::~Commentaire()
{
    delete ui;
}
