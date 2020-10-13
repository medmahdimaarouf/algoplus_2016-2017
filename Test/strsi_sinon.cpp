#include "strsi_sinon.h"
#include "ui_strsi_sinon.h"

StrSi_SInon::StrSi_SInon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StrSi_SInon)
{
    ui->setupUi(this);
}

StrSi_SInon::~StrSi_SInon()
{
    delete ui;
}
