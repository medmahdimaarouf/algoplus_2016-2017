#include "repeterjusqua.h"
#include "ui_repeterjusqua.h"

RepeterJusqua::RepeterJusqua(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RepeterJusqua)
{
    ui->setupUi(this);
}

RepeterJusqua::~RepeterJusqua()
{
    delete ui;
}
