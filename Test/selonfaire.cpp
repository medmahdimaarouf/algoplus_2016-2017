#include "selonfaire.h"
#include "ui_selonfaire.h"

SelonFaire::SelonFaire(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelonFaire)
{
    ui->setupUi(this);
}

SelonFaire::~SelonFaire()
{
    delete ui;
}
