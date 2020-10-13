#include "editeur_arbre_algo.h"



Editeur_Arbre_Algo::Editeur_Arbre_Algo(QTreeView *View_Algo, QTreeView *View_menu)
{
    model_View_Algo = new QStandardItemModel(this);
    model_View_menu = new QStandardItemModel(this);
    View_Algo->setModel(model_View_Algo);
    View_menu->setModel(model_View_menu);
    Arbre_Algo = new Gestion_Arbre_Algo(model_View_Algo);
    setup_menu(View_menu);
    connect(View_menu,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(gestion_des_commandes(QModelIndex)));
}

void Editeur_Arbre_Algo::gestion_des_commandes(const QModelIndex *index)
{
    qDebug()<<"ici";
}

void Editeur_Arbre_Algo::setup_menu(QTreeView *View_menu)
{
    QFile source_outils(":/Fichiers/Fichiers/Outils Algo+.xml");
    source_outils.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument doc_outils;
    doc_outils.setContent(&source_outils);
    QDomElement elm =  doc_outils.firstChildElement();
    QDomNodeList list_Titre_outils = elm.elementsByTagName("item");
    QFont Style1;
    Style1.setUnderline(true);
    for(int i=0;i< list_Titre_outils.count();i++)
    {QStandardItem * stdtitre_outils = new QStandardItem(list_Titre_outils.at(i).toElement().attribute("outils"));
        stdtitre_outils->setWhatsThis("-1");
        stdtitre_outils->setIcon(QIcon(":/Icons/Icon/Oxygen-Icons.org-Oxygen-Categories-applications-education-mathematics.ico"));
        stdtitre_outils->setFont(Style1);
        stdtitre_outils->setEditable(false);
        stdtitre_outils->setWhatsThis(list_Titre_outils.at(i).toElement().attribute("index"));
        int j;
        for(j=0;j < list_Titre_outils.at(i).toElement().elementsByTagName("item").count();j++)
        {
            QDomElement outils = list_Titre_outils.at(i).toElement().elementsByTagName("item").at(j).toElement();
            QStandardItem * std_outils = new QStandardItem(outils.attribute("outils"));
            std_outils->setIcon(QIcon(":/Icons/Icon/Benjigarner-Summer-Collection-Software-Photoshop.ico"));
            std_outils->setEditable(false);
            std_outils->setWhatsThis(outils.attribute("index"));
            if(outils.hasChildNodes())
            {int h;
                QDomNodeList lis = outils.elementsByTagName("item");
                for(h=0;h<lis.count();h++)
                {
                QStandardItem * item = new QStandardItem(lis.at(h).toElement().attribute("outils"));
                item->setWhatsThis(lis.at(h).toElement().attribute("index"));
                item->setEditable(false);
                std_outils->appendRow(item);
                }
                j+=h;
            }
            stdtitre_outils->appendRow(std_outils);
        }
        i+=j;
       model_View_menu->appendRow(stdtitre_outils);
    }

View_menu->setModel(model_View_menu);
View_menu->expandAll();
View_menu->setAnimated(true);

}
