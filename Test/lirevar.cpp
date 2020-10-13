#include "lirevar.h"
#include "ui_lirevar.h"

LireVar::LireVar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LireVar)
{
    ui->setupUi(this);
}

LireVar::~LireVar()
{
    delete ui;
}
