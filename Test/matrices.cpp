#include "matrices.h"
#include "ui_matrices.h"

Matrices::Matrices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrices)
{
    ui->setupUi(this);
}

Matrices::~Matrices()
{
    delete ui;
}
