#include "appercualgorithmewidget.h"
#include "ui_appercualgorithmewidget.h"

AppercuAlgorithmeWidget::AppercuAlgorithmeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppercuAlgorithmeWidget)
{
    ui->setupUi(this);
    //this->window()->setStyleSheet("background-color :rgb(115, 115, 115);");
    TreeViewCodeAlgo = ui->treeViewCodeAlgo;
    ui->treeViewCodeAlgo->setHeaderHidden(true);
    TextEditDescAlgo = ui->textEditDescription;
    labComCode = ui->labelCodeAlgo;
    labComDesc = ui->labelCommentaireCodeAlgo;
    ArbreAlgo = new Gestion_Arbre_Algo(ui->treeViewCodeAlgo,ui->textEditDescription);
}

AppercuAlgorithmeWidget::~AppercuAlgorithmeWidget()
{
    delete ArbreAlgo;
    delete ui;
}
