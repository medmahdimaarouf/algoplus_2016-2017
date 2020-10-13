#include "tantequefaire.h"
#include "ui_tantequefaire.h"

TantequeFaire::TantequeFaire(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TantequeFaire)
{
    ui->setupUi(this);
}

TantequeFaire::~TantequeFaire()
{
    delete ui;
}
