#include "pourfaire.h"
#include "ui_pourfaire.h"

Pourfaire::Pourfaire(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pourfaire)
{
    ui->setupUi(this);
}

Pourfaire::~Pourfaire()
{
    delete ui;
}
