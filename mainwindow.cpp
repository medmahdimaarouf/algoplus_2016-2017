#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QXmlStreamWriter>
#include<QComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    //ui->dockWidget_2->close();
    //ui->webView_3->setHtml("<h1 align='center'> Aide </h1> <p align = 'center'> Le contenu d'aide Algo+ est indisponible jusqu'a maintenant,Essayez d'avoir la dernier version de Algo+</p><h2 align='center'><font color='red'>Algo+.2016-2017</font> <h3>Email : <font>medmahdi.maarouf@gmail.com</font></h3></h2>");
    EDT_Arbre_Algo = new Editeur_Arbre_Algo(this,ui->tabWidget,ui->List_Outils);
    this->on_actionAide_triggered();
    QMessageBox::information(this,"Information","application en cour d'évaluation , certains erreurs peuvent se produisent, essayez-vous d'obtenir la version complète d'Algo+ ",QMessageBox::Ok);

}

void MainWindow::closeEvent(QCloseEvent *e)
{

}

MainWindow::~MainWindow()
{
    //on_actionEnregistrer_triggered();
    delete ui;

}

void MainWindow::on_actionEnregistrer_triggered()
{
    EDT_Arbre_Algo->Enregistrer_Algorithme();
}

void MainWindow::on_actionSupprimer_triggered()
{
    EDT_Arbre_Algo->Supprimer();
}

void MainWindow::on_actionEnregistrer_sous_triggered()
{
    EDT_Arbre_Algo->Enregistrer_Sous_Algorithme();
}

void MainWindow::on_actionOuvrir_triggered()
{
    nomFichier = QFileDialog::getOpenFileName(this,"Ouvrir un Algorithm","C:/Users/Med_Mahdi_Maarouf/Desktop/Algo+");
    QFile fichierAlgo(nomFichier);
    if(!fichierAlgo.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<" Fichier en ouverture ne peux pas ouverir";
        return;
    }
QComboBox * box = new QComboBox(this);

    QDomDocument documentAlgo;
    documentAlgo.setContent(&fichierAlgo);

    EDT_Arbre_Algo->AfficherAlgorithm(documentAlgo,nomFichier);
    fichierAlgo.close();
    //ui->statusBar->showMessage(" Fichier courant : " + nomFichier);
}

void MainWindow::on_actionNouveau_triggered()
{
    EDT_Arbre_Algo->NouveauAlgorithm("");
}

void MainWindow::on_actionQuitter_triggered()
{
    if(QMessageBox::question(this,"Quitter","Voulez vous quitter","Annuler","Quitter"))
        close();
}

void MainWindow::on_actionAide_triggered()
{
    /*if(EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->ArbreAlgo->currentIndex().isValid())
    {
        qDebug()<<"whatsThis"<<EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->modelViewAlgo->itemFromIndex(EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->ArbreAlgo->currentIndex())->whatsThis();
        qDebug()<<"Description"<<EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->modelViewAlgo->itemFromIndex(EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription();
        qDebug()<<"index"<<EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->modelViewAlgo->itemFromIndex(EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->ArbreAlgo->currentIndex())->index();
    }*/
    //qDebug()<<EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->Programme_Courante()<<"what"<<EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->modelViewAlgo->itemFromIndex(EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->ArbreAlgo->currentIndex())->whatsThis();


    ui->dockWidget_2->setVisible(true);
}

void MainWindow::on_actionExecuter_triggered()
{
    Console = new Dialog_Console(this,EDT_Arbre_Algo->CreerXMLDocument());
    Console->show();
    Console->compilateur->execute();
}

void MainWindow::on_actionModifier_triggered()
{
    EDT_Arbre_Algo->modifier_ligne();
}

void MainWindow::on_actionCopier_triggered()
{
    EDT_Arbre_Algo->Copier();
}

void MainWindow::on_actionColler_triggered()
{
    EDT_Arbre_Algo->Coller();
}

void MainWindow::on_actionCouper_triggered()
{
    EDT_Arbre_Algo->Couper();
}

void MainWindow::on_actionInserer_triggered()
{
    QStandardItem * newitem = new QStandardItem();
    newitem->setEditable(false);
    EDT_Arbre_Algo->AlgorithmeCourant->ArbreAlgo->add_newItemAlgo(newitem);
}

void MainWindow::on_actionAnnuler_triggered()
{
    EDT_Arbre_Algo->Annuler();
}

void MainWindow::on_actionA_propot_Algo_triggered()
{
    /*QTextEdit * deb = new QTextEdit();
    deb->setText(EDT_Arbre_Algo->CreerXMLDocument().toString());
    deb->show();*/
    if(!ui->dockWidget_2->isVisible())
    {

        if(QMessageBox::question(this,"Information Algo+","Tout les informations concernent Algo+ se trouvent dans l'aide Algo+ \n Voulez-vous ouvrir ce lui ?","Ouvrir","Annuler") == 0)
            on_actionAide_triggered();
    }else
        QMessageBox::information(this,"Information Algo+","Tout les informations concernent Algo+ se trouvent dans l'aide Algo+ ",QMessageBox::Ok);

}

void MainWindow::on_actionOuvrir_un_exemple_triggered()
{
    QString nomFichier = QFileDialog::getOpenFileName(this,"Ouvrir un exemple","Exemples/");
    QFile fichierAlgo(nomFichier);
    if(fichierAlgo.open(QIODevice::ReadOnly))
    {
        QDomDocument documentAlgo;
        documentAlgo.setContent(&fichierAlgo);
        EDT_Arbre_Algo->AfficherAlgorithm(documentAlgo,nomFichier);
        fichierAlgo.close();
        //ui->statusBar->showMessage(" Fichier courant : " + nomFichier);
    }
}
