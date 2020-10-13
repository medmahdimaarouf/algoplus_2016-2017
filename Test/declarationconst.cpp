#include "declarationconst.h"
#include "ui_declarationconst.h"

DeclarationConst::DeclarationConst(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeclarationConst)
{
    ui->setupUi(this);
}

DeclarationConst::~DeclarationConst()
{
    delete ui;
}
