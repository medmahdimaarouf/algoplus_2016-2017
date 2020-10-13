#include "editeur_arbre_algo.h"
#include<QPushButton>

Editeur_Arbre_Algo::Editeur_Arbre_Algo(QWidget *parent, QTabWidget *tab_Algorithmes, QTreeView *View_menu):
    QWidget(parent)
{
       model_View_menu = new QStandardItemModel(this);
       View_menu->setModel(model_View_menu);
       View_menu->setHeaderHidden(true);
       tabAlgorithmes = tab_Algorithmes;
       connect(tab_Algorithmes,SIGNAL(currentChanged(int)),this,SLOT(CouranteAlogrithmeChange(int)));
       connect(tab_Algorithmes,SIGNAL(tabCloseRequested(int)),this,SLOT(FermerAlgorithm(int)));
       connect(tabAlgorithmes,SIGNAL(tabBarClicked(int)),this,SLOT(cliquer(int)));
       tabAlgorithmes->clear();
       //****************************************
       NouveauAlgorithm(NULL);
       setup_menu(View_menu);
       connect(AlgorithmeCourant->ArbreAlgo->modelViewAlgo,SIGNAL(rowsInserted(QModelIndex,int,int)),AlgorithmeCourant->TreeViewCodeAlgo,SLOT(expand(QModelIndex)));
       connect(View_menu,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(gestion_des_commandes(QModelIndex)));
       //connect(model_View_Algo,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(Item_Change(QStandardItem*)));
}

QDomDocument Editeur_Arbre_Algo::CreerXMLDocument()
{
    QDomDocument DocumentAlgo;
    QDomElement rootProcs = DocumentAlgo.createElement("procedures");
    QDomElement rootfcts = DocumentAlgo.createElement("fonctions");
    QDomElement DomRacineAlgo = DocumentAlgo.createElement("Algo");
     DomRacineAlgo.setAttribute("name",AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->accessibleDescription().split("#").at(0));
     DomRacineAlgo.setAttribute("desc",AlgorithmeCourant->TextEditDescAlgo->toPlainText());
     DocumentAlgo.appendChild(DomRacineAlgo);

    if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->hasChildren())
    {
        for(int i = 0;i < AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->rowCount();i++)// ROUTES ELEMENT DECLARATION
        {
            if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->text() == "Constantes")// DECLARATION CONSTANTES
            {
                if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->hasChildren()) // IF HAS SOME DECLARATION CONSTES
                {
                    QDomElement rootConsts = DocumentAlgo.createElement("constantes");

                    for(int j = 0;j < AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->rowCount();j++)// TRAITEMENT DECLARATION CONSTES
                      {
                        QStringList listeinfo = AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(j)->accessibleDescription().split("#");
                        QDomElement elmconst = DocumentAlgo.createElement("const");
                        elmconst.setAttribute("name",listeinfo.at(0));
                        elmconst.setAttribute("valeur",listeinfo.at(1));
                        rootConsts.appendChild(elmconst);

                      }
                    DomRacineAlgo.appendChild(rootConsts);
                }

            }else
                if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->text() == "Types")
                {
                    if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->hasChildren())
                    {
                        QDomElement rootTypes = DocumentAlgo.createElement("types");
                        for(int j = 0; j < AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->rowCount();j++)
                        {
                            QStringList listeinfo = AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(j)->accessibleDescription().split("#");
                            QDomElement elmType;
                            switch (listeinfo.at(0).toInt()) {
                            case 1:
                            {
                                elmType = DocumentAlgo.createElement("tab");
                                elmType.setAttribute("name",listeinfo.at(1));
                                elmType.setAttribute("taille",listeinfo.at(2));
                                elmType.setAttribute("contenu",listeinfo.at(3));
                            }
                                break;
                            case 2:
                            {
                                elmType = DocumentAlgo.createElement("mat");
                                elmType.setAttribute("name",listeinfo.at(1));
                                elmType.setAttribute("ligne",listeinfo.at(2));
                                elmType.setAttribute("colonne",listeinfo.at(3));
                                elmType.setAttribute("contenu",listeinfo.at(4));
                            }
                                break;
                            case 3:
                            {
                                elmType = DocumentAlgo.createElement("enreg");
                                elmType.setAttribute("name",listeinfo.at(1));
                                if(listeinfo.at(2) != "")
                                {
                                    QStringList listChamps = listeinfo.at(2).split("|");
                                    for(int c = 0; c < listChamps.count();c++)
                                    {
                                        QStringList infoChamp = listChamps.at(c).split(":");
                                        QDomElement elmChamp = DocumentAlgo.createElement("champ");
                                        elmChamp.setAttribute("name",infoChamp.at(0));
                                        elmChamp.setAttribute("type",infoChamp.at(1));
                                        elmType.appendChild(elmChamp);
                                    }
                                }

                            }
                                break;
                            case 4:
                            {
                                elmType = DocumentAlgo.createElement("fich");
                                elmType.setAttribute("name",listeinfo.at(1));
                                elmType.setAttribute("contenu",listeinfo.at(2));
                            }
                                break;
                            default:
                                break;
                            }
                            rootTypes.appendChild(elmType);
                        }
                        DomRacineAlgo.appendChild(rootTypes);
                    }
                }
                else
                     if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->text() == "Variables")
                     {
                         if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->hasChildren())
                         {
                             QDomElement rootvars = DocumentAlgo.createElement("variables");
                             for(int v = 0; v < AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->rowCount();v++)
                             {
                                 QStringList listeinfovar = AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(v)->accessibleDescription().split("#");
                                 QDomElement elmvar = DocumentAlgo.createElement("var");
                                 elmvar.setAttribute("name",listeinfovar.at(0));
                                 elmvar.setAttribute("type",listeinfovar.at(1));
                                 rootvars.appendChild(elmvar);
                             }
                             DomRacineAlgo.appendChild(rootvars);
                         }
                     }
                else
                     {// **************************FUNCTIONS OR PROCEDURES****************
                         QStringList listeInfoProcFunc = AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->accessibleDescription().split("#");

                            QDomElement elmprocFunc ;
                            // IDENTIFICATION FUNC OR PROC AND INITIATION
                             if(listeInfoProcFunc.at(0).toInt())// IS PROCEDURE
                                {
                                     elmprocFunc = DocumentAlgo.createElement("proc");
                                     elmprocFunc.setAttribute("name",listeInfoProcFunc.at(1));
                                     rootProcs.appendChild(elmprocFunc);
                                 }
                              else
                                {
                                     elmprocFunc = DocumentAlgo.createElement("fct");
                                     elmprocFunc.setAttribute("name",listeInfoProcFunc.at(1));
                                     elmprocFunc.setAttribute("type",listeInfoProcFunc.at(2));
                                     rootfcts.appendChild(elmprocFunc);
                                }
                             // PREPARATION PARAMERES SOUS PROGRAMMES
                                    if(listeInfoProcFunc.at(3) != "")
                                     {
                                         QStringList listeParas = listeInfoProcFunc.at(3).split("|");
                                         for(int p = 0; p < listeParas.count();p++)
                                         {
                                             QStringList infoPara = listeParas.at(p).split(":");
                                             QDomElement elmpara = DocumentAlgo.createElement("para");
                                             elmpara.setAttribute("name",infoPara.at(0));
                                             elmpara.setAttribute("type",infoPara.at(1));
                                             elmpara.setAttribute("passage",infoPara.at(2));
                                             elmprocFunc.appendChild(elmpara);
                                         }
                                     }

                             // VARIABLES SOUS PROGRAMS
                             if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(0)->text() == "Variables")
                             {
                                 if(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(0)->hasChildren())
                                 {
                                     QDomElement elmRoutVarsSousProgram = DocumentAlgo.createElement("variables");
                                     for(int v = 0; v < AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(0)->rowCount();v++)
                                     {
                                         QDomElement elmVarSousProgram = DocumentAlgo.createElement("var");
                                         elmVarSousProgram.setAttribute("name",AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(0)->child(v)->accessibleDescription().split("#").at(0));
                                         elmVarSousProgram.setAttribute("type",AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(0)->child(v)->accessibleDescription().split("#").at(1));
                                        elmRoutVarsSousProgram.appendChild(elmVarSousProgram);
                                     }
                                     elmprocFunc.appendChild(elmRoutVarsSousProgram);
                                 }
                                 // INITAIATION DEBUT SOUS PROGRAM

                                QDomElement elmDebutSousProgram = DocumentAlgo.createElement("Debut");
                                CreerXMLCorpProgramAlgo(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(1),&elmDebutSousProgram,&DocumentAlgo);
                                elmprocFunc.appendChild(elmDebutSousProgram);
                             }
                             else
                             {
                                 QDomElement elmDebutSousProgram = DocumentAlgo.createElement("Debut");
                                 CreerXMLCorpProgramAlgo(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(0)->child(i)->child(0),&elmDebutSousProgram,&DocumentAlgo);
                                 elmprocFunc.appendChild(elmDebutSousProgram);
                             }

                     }
        }
        if(rootfcts.hasChildNodes())
            DomRacineAlgo.appendChild(rootfcts);
        if(rootProcs.hasChildNodes())
            DomRacineAlgo.appendChild(rootProcs);
    }
    QDomElement elmDebutPrincipalProgram = DocumentAlgo.createElement("Debut");
    CreerXMLCorpProgramAlgo(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->item(1),&elmDebutPrincipalProgram,&DocumentAlgo);
    DomRacineAlgo.appendChild(elmDebutPrincipalProgram);
    return DocumentAlgo;

}

void Editeur_Arbre_Algo::AfficherAlgorithm(QDomDocument documentAlgo,QString nomFichier)
{
    if(!ControleFichiersAlgorithm(documentAlgo))
    {
        QMessageBox::warning(this,"Erreur ","Ce fichier ne correspand pas a un algorithme","Ok","Annuler");
        //return;
    }
    NouveauAlgorithm(nomFichier);
    AlgorithmeCourant->ArbreAlgo->afficher_Algorithme(documentAlgo);
}

void Editeur_Arbre_Algo::NouveauAlgorithm(QString sourceAlgo)
{
    QString nomAlgo = "",suffix = "";
    QDateTime der_modification,derLecture,Creation;

    if(sourceAlgo.isEmpty())
      {
          nomAlgo = "Sans-Titre";
          suffix = "";
          Creation = QDateTime::currentDateTime();
          derLecture = der_modification = Creation;
      }
      else
      {
          QFileInfo infoFichierAlgo;

          infoFichierAlgo.setFile(sourceAlgo);
          nomAlgo = infoFichierAlgo.completeBaseName();
          suffix = infoFichierAlgo.suffix();
          Creation = infoFichierAlgo.created();
          derLecture = infoFichierAlgo.lastRead();
          der_modification = infoFichierAlgo.lastModified();
          int pos = estDejaOuvert(sourceAlgo);

           if(pos != -1)
              {
                  AlgorithmeCourant = listeAlgorithmes.at(pos).tabAlgorithme;
                  tabAlgorithmes->setCurrentWidget(listeAlgorithmes.at(pos).tabSource);
                  CouranteNomFichier = sourceAlgo;
                  return;
              }

      }

    AppercuAlgorithmeWidget * tabAlgorithme = new AppercuAlgorithmeWidget();
    Algorithme algorithm;
    algorithm.tabAlgorithme = tabAlgorithme;
    algorithm.chemainFichier = sourceAlgo;
    CouranteNomFichier = sourceAlgo;
    int indexNouveauTab = tabAlgorithmes->addTab(tabAlgorithme,nomAlgo);
    algorithm.tabSource = tabAlgorithmes->widget(indexNouveauTab);
    tabAlgorithmes->setCurrentWidget(tabAlgorithme);
    tabAlgorithmes->setTabToolTip(indexNouveauTab,"Nom : " + nomAlgo + "\n Chemain : " + sourceAlgo + "\n Date de dernier lecture : " + derLecture.toString() + "\n Date de dernier modification : " + der_modification.toString() + "\n Date de création : " + Creation.toString());
    tabAlgorithmes->setToolTipDuration(3000);
    tabAlgorithmes->setCurrentIndex(indexNouveauTab);
    AlgorithmeCourant = tabAlgorithme;
    listeAlgorithmes.append(algorithm);

}

void Editeur_Arbre_Algo::Supprimer()
{
    if(!AlgorithmeCourant->TreeViewCodeAlgo->currentIndex().isValid())
        return;
  AlgorithmeCourant->ArbreAlgo->supprimer_ligne();
}

void Editeur_Arbre_Algo::modifier_ligne()
{
  QModelIndex index = AlgorithmeCourant->TreeViewCodeAlgo->currentIndex();
  if(!index.isValid())
      return;
  QString whatsThis = AlgorithmeCourant->ArbreAlgo->modelViewAlgo->itemFromIndex(index)->whatsThis();
  if(whatsThis == "const")
  {
      D_dec_const = new Dialog_Declaration_Const(AlgorithmeCourant->ArbreAlgo);
      D_dec_const->metter_sous_modification();
      D_dec_const->show();
  }else
      if(whatsThis == "enreg")
      {
        D_dec_enregitrement = new Dialog_Declaration_Enregistrement(AlgorithmeCourant->ArbreAlgo);
        D_dec_enregitrement->metter_sous_modification();
        D_dec_enregitrement->show();
      }
      else
          if(whatsThis == "tab")
          {
           D_dec_vecteur = new Dialog_Declaration_Vecteur(AlgorithmeCourant->ArbreAlgo);
           D_dec_vecteur->metter_sous_modification();
           D_dec_vecteur->show();
          }
          else
              if(whatsThis == "mat")
              {
               D_dec_matrice = new Dialog_Declaration_Matrice(AlgorithmeCourant->ArbreAlgo);
               D_dec_matrice->metter_sous_modification();
               D_dec_matrice->show();
              }
                else
                   if(whatsThis == "fich")
                   {
                     D_dec_fichiers = new Dialog_Declaration_Fichiers(AlgorithmeCourant->ArbreAlgo);
                     D_dec_fichiers->metter_sous_modification();
                     D_dec_fichiers->show();
                   }
                   else
                       if(whatsThis == "var")
                       {
                        D_dec_varibles = new Dialog_Declaration_variable(AlgorithmeCourant->ArbreAlgo);
                        D_dec_varibles->metter_sous_modification();
                        D_dec_varibles->show();
                       }
                       else
                           if(whatsThis == "fct")
                           {
                             D_dec_procedure = new Dialog_Declaration_Procedure(true,AlgorithmeCourant->ArbreAlgo);
                             D_dec_procedure->metter_sous_modification();
                             D_dec_procedure->show();
                           }
                           else
                               if(whatsThis == "proc")
                               {
                                   D_dec_procedure = new Dialog_Declaration_Procedure(false,AlgorithmeCourant->ArbreAlgo);
                                   D_dec_procedure->metter_sous_modification();
                                   D_dec_procedure->show();
                               }
                               else
                                    if(whatsThis == "item")
                                    {
                                            int op = AlgorithmeCourant->ArbreAlgo->modelViewAlgo->itemFromIndex(index)->accessibleDescription().split("#").at(0).toInt();
                                        switch (op)
                                        {
                                        case -1 :
                                        {
                                           D_repeter_jusqua = new Dialog_Repeter_jusqua(AlgorithmeCourant->ArbreAlgo);
                                           D_repeter_jusqua->metter_sous_modification();
                                           D_repeter_jusqua->show();
                                        }break;
                                        case 1 :
                                        {
                                           D_affectation = new Dialog_Affecation(AlgorithmeCourant->ArbreAlgo);
                                           D_affectation->metter_sous_modification();
                                           D_affectation->show();

                                        }break;
                                        case 2 :
                                        {
                                            D_lire_var = new Dialog_Lire_Variable(AlgorithmeCourant->ArbreAlgo);
                                            D_lire_var->metter_sous_modification();
                                            D_lire_var->show();

                                        }break;
                                        case 3 :
                                        {
                                             D_Ecrire = new Dialog_Ecrire(AlgorithmeCourant->ArbreAlgo);
                                             D_Ecrire->metter_sous_modification();
                                             D_Ecrire->show();
                                        }break;
                                        //case 4 : break;
                                        case 5 :
                                        {
                                             D_si_sinon = new Dialog_SI_SINON(AlgorithmeCourant->ArbreAlgo);
                                             D_si_sinon->metter_sous_modification();
                                             D_si_sinon->show();
                                        }break;
                                        //case 7 :{ }break;
                                        //case 8 : break;
                                        case 9 :
                                        {
                                          D_pour_faire = new Dialog_Pour_Faire(AlgorithmeCourant->ArbreAlgo);
                                          D_pour_faire->metter_sous_modification();
                                          D_pour_faire->show();
                                        }break;
                                        case 10:
                                        {
                                            D_tantque_faire = new Dialog_Tanteque_Faire(AlgorithmeCourant->ArbreAlgo);
                                            D_tantque_faire->metter_sous_modification();
                                            D_tantque_faire->show();
                                        }break;
                                        case 12:
                                        {
                                            D_Appelle = new Dialog_appelle_procedure(AlgorithmeCourant->ArbreAlgo->modelViewAlgo->itemFromIndex(AlgorithmeCourant->ArbreAlgo->ArbreAlgo->currentIndex())->accessibleDescription().split("#").at(2).toInt(),AlgorithmeCourant->ArbreAlgo);
                                            D_Appelle->metter_sous_modification();
                                            D_Appelle->show();

                                        }break;
                                        case 13:
                                        {
                                            D_retournFN = new Dialog_RetourneFN(AlgorithmeCourant->ArbreAlgo);
                                            D_retournFN->metter_sous_modification();
                                            D_retournFN->show();
                                        }break;
                                    default:
                                        break;

                                        }
                                    }else
                                    {
                                        qDebug()<<"modification impossible";
                                    }

}

void Editeur_Arbre_Algo::Copier()
{
    AlgorithmeCourant->ArbreAlgo->Copier_ligne();
}

void Editeur_Arbre_Algo::Coller()
{
    AlgorithmeCourant->ArbreAlgo->Coller_ligne();
}

void Editeur_Arbre_Algo::Couper()
{
    AlgorithmeCourant->ArbreAlgo->Couper_ligne();
}

void Editeur_Arbre_Algo::Annuler()
{

}

void Editeur_Arbre_Algo::Retablir()
{

}

void Editeur_Arbre_Algo::Enregistrer_Sous_Algorithme()
{
       QString chemain = QFileDialog::getSaveFileName(this,"Enregistrer sous","C:/Users/Med_Mahdi_Maarouf/Desktop/Algo+");
       if(!chemain.isEmpty())
       {
           CouranteNomFichier = chemain;

           int pos = CouranteAlgorithm(tabAlgorithmes->currentWidget());
           if(pos != -1)
           {
               Algorithm algorithme = listeAlgorithmes.at(pos);
               algorithme.chemainFichier = CouranteNomFichier;
               listeAlgorithmes.replace(pos,algorithme);
           }

           QFile fichierAlgorithme(chemain);
           if(!fichierAlgorithme.open(QIODevice::WriteOnly | QIODevice::Text))
           {
               QMessageBox::warning(this,"Enregistrement impossible","Un erreur s'est produis lord d'ouverture de fichier",QMessageBox::Ok);
               return;
           }
           QTextStream dans(&fichierAlgorithme);
           dans<< CreerXMLDocument().toString(0);
           QFileInfo infoFichierAlgorithme(fichierAlgorithme);
           tabAlgorithmes->setTabToolTip(tabAlgorithmes->currentIndex(),"Nom : " + infoFichierAlgorithme.completeBaseName() + "\n Chemain : " + chemain + "\n Date de dernier lecture : " + infoFichierAlgorithme.created().toString() + "\n Date de dernier modification : " + infoFichierAlgorithme.lastModified().toString() + "\n Date de création : " + infoFichierAlgorithme.created().toString());
           tabAlgorithmes->setTabText(tabAlgorithmes->currentIndex(),infoFichierAlgorithme.completeBaseName());
           fichierAlgorithme.close();
       }
       else
           QMessageBox::warning(this,"Enregistrement impossible","Invalide chemain d'enregistrement",QMessageBox::Ok);


}

void Editeur_Arbre_Algo::Enregistrer_Algorithme()
{
    if(CouranteNomFichier.isEmpty())
        Enregistrer_Sous_Algorithme();
    else
    {
        int pos = CouranteAlgorithm(tabAlgorithmes->currentWidget());
        if(pos != -1)
        {
            Algorithm algorithme = listeAlgorithmes.at(pos);
            algorithme.chemainFichier = CouranteNomFichier;
            listeAlgorithmes.replace(pos,algorithme);
        }

        QFile fichierAlgorithme(CouranteNomFichier);
        if(!fichierAlgorithme.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Enregistrement impossible","Un erreur s'est produis lord d'ouverture de fichier",QMessageBox::Ok);
            return;
        }
        QTextStream dans(&fichierAlgorithme);
        dans<< CreerXMLDocument().toString(0);
        QFileInfo infoFichierAlgorithme(fichierAlgorithme);
        tabAlgorithmes->setTabToolTip(tabAlgorithmes->currentIndex(),"Nom : " + infoFichierAlgorithme.completeBaseName() + "\n Chemain : " + CouranteNomFichier + "\n Date de dernier lecture : " + infoFichierAlgorithme.created().toString() + "\n Date de dernier modification : " + infoFichierAlgorithme.lastModified().toString() + "\n Date de création : " + infoFichierAlgorithme.created().toString());
        fichierAlgorithme.close();
    }

}

void Editeur_Arbre_Algo::gestion_des_commandes(const QModelIndex &index)
{
    if(!index.isValid())
        return;
    if(model_View_menu->itemFromIndex(index)->hasChildren() || model_View_menu->itemFromIndex(index)->text() == "Procedures Algo+")
        return;
    int operation_index = model_View_menu->itemFromIndex(index)->accessibleDescription().split("#").at(0).toInt();

    if(AlgorithmeCourant->TreeViewCodeAlgo->currentIndex().isValid())
    {
        QString textInsAlgo = AlgorithmeCourant->ArbreAlgo->modelViewAlgo->itemFromIndex(AlgorithmeCourant->TreeViewCodeAlgo->currentIndex())->accessibleDescription();
        if( textInsAlgo.mid(0,textInsAlgo.indexOf("#")).toInt() == -1 || textInsAlgo.mid(0,textInsAlgo.indexOf("#")).toInt() == 11 && operation_index > 7 )
        return;
    }

    switch (operation_index)
    {
    case 0:{
        D_dec_const  = new Dialog_Declaration_Const(AlgorithmeCourant->ArbreAlgo);
        D_dec_const->show();
    }break;
    case 1:{
        D_dec_vecteur = new Dialog_Declaration_Vecteur(AlgorithmeCourant->ArbreAlgo);
        D_dec_vecteur->show();
    }break;
    case 2:{
        D_dec_matrice = new Dialog_Declaration_Matrice(AlgorithmeCourant->ArbreAlgo);
        D_dec_matrice->show();
    } break;
    case 3:{
        D_dec_enregitrement = new Dialog_Declaration_Enregistrement(AlgorithmeCourant->ArbreAlgo);
        D_dec_enregitrement->show();
    }break;
    case 4:{
        D_dec_fichiers = new Dialog_Declaration_Fichiers(AlgorithmeCourant->ArbreAlgo);
        D_dec_fichiers->show();
    } break;
    case 5:{
        D_dec_varibles = new Dialog_Declaration_variable(AlgorithmeCourant->ArbreAlgo);
        D_dec_varibles->show();
    }break;
    case 6:{
        D_dec_procedure = new Dialog_Declaration_Procedure(true,AlgorithmeCourant->ArbreAlgo);
        D_dec_procedure->show();
    }break;
    case 7:{
        D_dec_procedure = new Dialog_Declaration_Procedure(false,AlgorithmeCourant->ArbreAlgo);
        D_dec_procedure->show();
    }break;
    case 8:{
       D_si_sinon = new Dialog_SI_SINON(AlgorithmeCourant->ArbreAlgo);
       D_si_sinon->show();
    }break;
    case 9:{
        D_selon_faire = new Dialog_Selon_faire("",AlgorithmeCourant->ArbreAlgo);
        D_selon_faire->show();
    }break;
    case 10:{
        D_pour_faire = new Dialog_Pour_Faire(AlgorithmeCourant->ArbreAlgo);
        D_pour_faire->show();
    }break;
    case 11:{
        D_tantque_faire = new Dialog_Tanteque_Faire(AlgorithmeCourant->ArbreAlgo);
        D_tantque_faire->show();
    }break;
    case 12:{
        D_repeter_jusqua = new Dialog_Repeter_jusqua(AlgorithmeCourant->ArbreAlgo);
        D_repeter_jusqua->show();
    }break;
    case 13:{
        D_lire_var = new Dialog_Lire_Variable(AlgorithmeCourant->ArbreAlgo);
        D_lire_var->show();
    }break;
    case 14:{
        D_Ecrire = new Dialog_Ecrire(AlgorithmeCourant->ArbreAlgo);
        D_Ecrire->show();
    }break;
    case 15:{
        D_affectation = new Dialog_Affecation(AlgorithmeCourant->ArbreAlgo);
        D_affectation->show();
             }break;
    case 16:{
        D_Appelle = new Dialog_appelle_procedure(0,AlgorithmeCourant->ArbreAlgo);
        if(!D_Appelle->listeProcs.isEmpty())
            D_Appelle->show();
    }break;
    case 17:{
        D_retournFN = new Dialog_RetourneFN(AlgorithmeCourant->ArbreAlgo);
        if(!D_retournFN->listefcts.isEmpty())
            D_retournFN->show();
    }break;
    case 18:{
        switch (model_View_menu->itemFromIndex(index)->accessibleDescription().split("#").at(1).toInt())
        {
        case 1:
        {
            D_Appelle = new Dialog_appelle_procedure(1,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 2:
        {
            D_Appelle = new Dialog_appelle_procedure(2,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 3:
        {
            D_Appelle = new Dialog_appelle_procedure(3,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 4:
        {
            D_Appelle = new Dialog_appelle_procedure(4,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 5:
        {
            D_Appelle = new Dialog_appelle_procedure(5,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 6:
        {
            D_Appelle = new Dialog_appelle_procedure(6,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 7:
        {
            D_Appelle = new Dialog_appelle_procedure(7,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 8:
        {
            D_Appelle = new Dialog_appelle_procedure(8,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 9:
        {
            D_Appelle = new Dialog_appelle_procedure(9,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 10:
        {
            D_Appelle = new Dialog_appelle_procedure(10,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 11:
        {
            D_Appelle = new Dialog_appelle_procedure(11,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 12:
        {
            D_Appelle = new Dialog_appelle_procedure(12,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 13:
        {
            D_Appelle = new Dialog_appelle_procedure(13,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }
            break;
        case 14:
        {
            D_Appelle = new Dialog_appelle_procedure(14,AlgorithmeCourant->ArbreAlgo);
            D_Appelle->show();
        }

            break;
        }
    }break;
    default:{
        throw "commande invalide";
             }break;
    }

}

void Editeur_Arbre_Algo::Item_Change(QStandardItem *item)
{

}

void Editeur_Arbre_Algo::CouranteAlogrithmeChange(int index)
{
   int pos =  CouranteAlgorithm(tabAlgorithmes->widget(index));
   if(pos != -1)
   {
        AppercuAlgorithmeWidget * TabAlgo = listeAlgorithmes.at(pos).tabAlgorithme;
        CouranteNomFichier = listeAlgorithmes.at(pos).chemainFichier;
        AlgorithmeCourant = TabAlgo;
   }
}

void Editeur_Arbre_Algo::FermerAlgorithm(int index)
{
    QMessageBox *boiteMessage = new QMessageBox(this);

    int rep = boiteMessage->question(this,"Enregistrer le changement","Voulez-vous entregistrer les modifications de ce algorithme","Enregistrer","Ne pas enregistrer","Annuler",0,2);

    switch (rep)
    {
    case 0:
         Enregistrer_Algorithme();
        break;
    case 2:
        return;
        break;
    default:
        {// FERMETURE DE L ALGORITHM SEULEMENT
            int pos = CouranteAlgorithm(tabAlgorithmes->widget(index));

            if(pos != -1)
            {
                listeAlgorithmes.removeAt(pos);
                tabAlgorithmes->removeTab(index);

            }
            if(tabAlgorithmes->currentIndex() == -1)
                NouveauAlgorithm("");
        }break;
    }

}

void Editeur_Arbre_Algo::cliquer(int index)
{

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
        stdtitre_outils->setAccessibleDescription("-1");
        stdtitre_outils->setIcon(QIcon(":/Icons/Icon/Oxygen-Icons.org-Oxygen-Categories-applications-education-mathematics.ico"));
        stdtitre_outils->setFont(Style1);
        stdtitre_outils->setEditable(false);
        stdtitre_outils->setAccessibleDescription(list_Titre_outils.at(i).toElement().attribute("index"));
        int j;
        for(j=0;j < list_Titre_outils.at(i).toElement().elementsByTagName("item").count();j++)
        {
            QDomElement outils = list_Titre_outils.at(i).toElement().elementsByTagName("item").at(j).toElement();
            QStandardItem * std_outils = new QStandardItem(outils.attribute("outils"));
            std_outils->setIcon(QIcon(":/Icons/Icon/Benjigarner-Summer-Collection-Software-Photoshop.ico"));
            std_outils->setEditable(false);
            std_outils->setAccessibleDescription(outils.attribute("index"));
            if(outils.hasChildNodes())
            {int h;
                QDomNodeList lis = outils.elementsByTagName("item");
                for(h=0;h<lis.count();h++)
                {
                QStandardItem * item = new QStandardItem(lis.at(h).toElement().attribute("outils"));
                item->setAccessibleDescription(lis.at(h).toElement().attribute("index"));
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

void Editeur_Arbre_Algo::CreerXMLCorpProgramAlgo(QStandardItem *std_Debut,QDomElement * elem_Debut,QDomDocument * DocumentAlgo)
{
    if(std_Debut->hasChildren())
       for(int i = 0;i < std_Debut->rowCount();i++)
        {
           if(std_Debut->child(i)->text() != "")
           {
               QDomElement ItemAlgo = DocumentAlgo->createElement("item");
               EditerXMLItem(&ItemAlgo,std_Debut->child(i)->accessibleDescription().split("#"));
               elem_Debut->appendChild(ItemAlgo);
               CreerXMLCorpProgramAlgo(std_Debut->child(i),&ItemAlgo,DocumentAlgo);
           }
       }


}

void Editeur_Arbre_Algo::EditerXMLItem(QDomElement *item,QStringList liste_infoInst)
{
    switch (liste_infoInst.at(0).toInt()) {
    case -1:
    {
        item->setAttribute("index",liste_infoInst.at(0));
    }
        break;
    case 0:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("app",liste_infoInst.at(1));
    }
        break;
    case 1:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("var",liste_infoInst.at(1));
        item->setAttribute("exp",liste_infoInst.at(2));

    }
        break;
    case 2:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("var",liste_infoInst.at(1));
        item->setAttribute("msg",liste_infoInst.at(2));
    }
        break;
    case 3:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("msg",liste_infoInst.at(1));
    }
        break;
    case 4:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("com",liste_infoInst.at(1));
    }
        break;
    case 5:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("condition",liste_infoInst.at(1));
    }
        break;
    case 6:
    {
        item->setAttribute("index",liste_infoInst.at(0));
    }
        break;
    case 7:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("selecteur",liste_infoInst.at(1));
    }
        break;
    case 8:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("choix",liste_infoInst.at(1));
    }
        break;
    case 9:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("cmp",liste_infoInst.at(1));
        item->setAttribute("vi",liste_infoInst.at(2));
        item->setAttribute("vf",liste_infoInst.at(3));
        item->setAttribute("pas",liste_infoInst.at(4));
    }
        break;
    case 10:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("condition",liste_infoInst.at(1));
    }
        break;
    case 11:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("condition",liste_infoInst.at(1));
    }
        break;
    case 12:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("proc",liste_infoInst.at(1));
        item->setAttribute("isPred",liste_infoInst.at(2));
        item->setAttribute("para",liste_infoInst.at(3));
    }
        break;
    case 13:
    {
        item->setAttribute("index",liste_infoInst.at(0));
        item->setAttribute("name",liste_infoInst.at(1));
        item->setAttribute("retour",liste_infoInst.at(2));

    }
        break;
    default:
        qDebug()<<"operation inconnu";
        break;
    }
}

int Editeur_Arbre_Algo::CouranteAlgorithm(QWidget *WidgetCourant)
{
    for(int i = 0; i < listeAlgorithmes.size();i++)
        if(listeAlgorithmes.at(i).tabSource == WidgetCourant)
            return i;
    return -1;
}

bool controleItemAlgo(QDomNode instruction)
{
        if(!instruction.isElement())
        {qDebug()<<"ctr itm alg inst !Elem";
            return false;
        }
        if(instruction.toElement().tagName() != "item")
        {qDebug()<<"ctr itm alg !item";
            return false;
        }
        if(!instruction.toElement().hasAttributes())
        {qDebug()<<"ctr itm alg item !att";
            return false;
        }
        if(!instruction.toElement().hasAttribute("index"))
        {qDebug()<<"ctr itm alg !index";
            return false;
        }
        bool ok = true;
        int index;
        index =  instruction.toElement().attribute("index").toInt(&ok);
        if(!ok)
        {qDebug()<<"index ! N";
            return false;
        }

        switch (index)
            {
             case -1:
                 // AUCUN CHOSE ICI;
                 break;
             case 0:
                       return instruction.toElement().hasAttribute("app");
                break;
             case 1:
                     return instruction.toElement().hasAttribute("var") && instruction.toElement().hasAttribute("exp");
                 break;
             case 2:
                      return instruction.toElement().hasAttribute("msg") && instruction.toElement().hasAttribute("var");
                break;
             case 3:
                     return instruction.toElement().hasAttribute("msg");
                break;
             case 4:
                 qDebug()<<"pas de controle sur les commentaire jusqu'a maintenant";
                 break;
             case 5:
                     return instruction.toElement().hasAttribute("condition");
                 break;
             case 6:
                 // AUCUN CHOSE ICI.
                 break;
             case 7:
                     return instruction.toElement().hasAttribute("selecteur");
                 break;
             case 8:
                     return instruction.toElement().hasAttribute("choix");
                 break;
             case 9:
                     return instruction.toElement().hasAttribute("cmp") && instruction.toElement().hasAttribute("vi") && instruction.toElement().hasAttribute("vf") && instruction.toElement().hasAttribute("pas");
                 break;
             case 10:
                     return instruction.toElement().hasAttribute("condition");
                 break;
             case 11:
                     return instruction.toElement().hasAttribute("condition");
                 break;
             case 12:
                     return instruction.toElement().hasAttribute("proc") && instruction.toElement().hasAttribute("isPred") && instruction.toElement().hasAttribute("para") && instruction.toElement().hasAttribute("isPred");
                 break;
             case 13:
                     return instruction.toElement().hasAttribute("name") && instruction.toElement().hasAttribute("retour");
            break;
                default:
                     {
                        qDebug()<<"index out range"<<index;
                         return false;
                     }
             break;
            }

        return true;
}

bool ControleDebutProgrammme(QDomElement itemAlgo)
{
    if(itemAlgo.hasChildNodes())
    {
        for(int i = 0; i < itemAlgo.childNodes().size();i++)
        {
            QDomNode inst = itemAlgo.childNodes().at(i);
            if(!controleItemAlgo(inst))
            {
                qDebug()<<"item erreur ctr deb prog";
                return false;
            }
            if(!ControleDebutProgrammme(inst.toElement()))
            {qDebug()<<"cont deb erruer";
                return false;
            }
        }
    }
    else
        if(!controleItemAlgo(itemAlgo))
            return false;
    return true;
}




bool Editeur_Arbre_Algo::ControleFichiersAlgorithm(QDomDocument documentAlgo)
{

 // ---------------------- CONTROLE Element Racine (Algo) ----------------------------


    if(!documentAlgo.hasChildNodes())
    {
        qDebug()<<"document vide";
        return false;
    }
    if(!documentAlgo.firstChild().isElement())
    {
        qDebug()<<"Algo n est une element";
        return false;
    }
    if(documentAlgo.firstChild().toElement().tagName() != "Algo")
    {
        qDebug()<<"tag Algo undefined";
        return false;
    }
    if(!documentAlgo.firstChild().toElement().hasAttribute("name") || !documentAlgo.firstChild().toElement().hasAttribute("desc"))
    {
        qDebug()<<"Algo attribs erreur";
        return false;
    }
    if(!documentAlgo.firstChild().toElement().hasChildNodes())
    {
        qDebug()<<"Algo vide";
        return false;
    }

    QDomElement RacineAlgo = documentAlgo.firstChild().toElement();

        for(int i = 0; i < RacineAlgo.childNodes().count();i++)
        {
            if(!RacineAlgo.childNodes().at(i).isElement())
            {
                qDebug()<<"child racine "<<i<<" !element";
                return false;
            }
            QString tagName = RacineAlgo.childNodes().at(i).toElement().tagName();

            if( tagName == "constantes") // ***** CONSTANTES **************
            {
                QDomNode Constantes = RacineAlgo.childNodes().at(i);

                if(Constantes.hasChildNodes())
                {
                    for(int i = 0; i < Constantes.childNodes().size();i++)
                    {
                        QDomNode constante = Constantes.childNodes().at(i);

                        if(!constante.isElement() || constante.hasChildNodes())
                            return false;
                        if(constante.toElement().tagName() != "const" || !constante.toElement().hasAttribute("name") || !constante.toElement().hasAttribute("valeur"));
                            return false;
                    }
                }

            }else
                if(tagName == "types")
                {

                }else
                    if(tagName == "variables")
                    {
                        QDomNode variables = RacineAlgo.childNodes().at(i);

                        if(variables.hasChildNodes())
                        {
                            for(int i = 0; i < variables.childNodes().size();i++)
                            {
                                QDomNode variable = variables.childNodes().at(i);

                                if(!variable.isElement())
                                    return false;
                                if(variable.hasChildNodes())
                                    return false;
                                if(variable.toElement().tagName() != "var")
                                    return false;
                                if(!variable.toElement().hasAttribute("name") || !variable.toElement().hasAttribute("type"))
                                    return false;
                            }
                        }

                    }else
                        if(tagName == "fonctions")
                        {
                            QDomNode fonctions = RacineAlgo.childNodes().at(i);

                            if(fonctions.hasChildNodes())
                            {
                                for(int i = 0; i < fonctions.childNodes().size();i++)
                                {
                                    QDomNode fonction = fonctions.childNodes().at(i);

                                    if(!fonction.isElement())
                                        return false;
                                    if(fonction.toElement().tagName() != "fct")
                                        return false;
                                    if(!fonction.toElement().hasAttribute("name") || !fonction.toElement().hasAttribute("type"))
                                        return false;

                                    if(fonction.hasChildNodes())
                                    {
                                        for(int i = 0; i < fonction.childNodes().size();i++)
                                        {
                                            QDomNode NdFct = fonction.childNodes().at(i);

                                            if(!NdFct.isElement())
                                                return false;
                                            QString tagNdfct = NdFct.toElement().tagName();
                                            if(tagNdfct == "para")
                                            {
                                                if(!NdFct.toElement().hasAttribute("name") || !NdFct.toElement().hasAttribute("type") || !NdFct.toElement().hasAttribute("passage"))
                                                    return false;
                                                bool ok = true;
                                                NdFct.toElement().attribute("passage").toInt(&ok);
                                                 if(!ok)
                                                     return false;

                                            }else
                                                if(tagNdfct == "variables")
                                                {

                                                    if(NdFct.hasChildNodes())
                                                    {
                                                        for(int i = 0; i < NdFct.childNodes().size();i++)
                                                        {
                                                            QDomNode variable = NdFct.childNodes().at(i);

                                                            if(!variable.isElement())
                                                                return false;
                                                            if(variable.hasChildNodes())
                                                                return false;
                                                            if(variable.toElement().tagName() != "var")
                                                                return false;
                                                            if(!variable.toElement().hasAttribute("name") || !variable.toElement().hasAttribute("type"))
                                                                return false;
                                                        }
                                                    }
                                                }else
                                                    if(tagNdfct == "Debut")
                                                    {
                                                        /*if(NdFct.toElement().hasAttributes());
                                                        {qDebug()<<"ici";
                                                            return false;
                                                        }*/
                                                        if(NdFct.hasChildNodes())
                                                        {
                                                            if(!ControleDebutProgrammme(NdFct.toElement()))
                                                            {
                                                                qDebug()<<"contr de fct deb Erreur ici";
                                                                return false;
                                                            }
                                                        }
                                                    }else
                                                    {
                                                        qDebug()<<"nfct ?";
                                                        return false;
                                                    }
                                        }

                                    }else
                                    {
                                        qDebug()<<"child fct ?";
                                        return false;
                                    }

                                }
                            }
                        }else
                            if(tagName == "procedures")
                            {
                                QDomNode procedures = RacineAlgo.childNodes().at(i);

                                if(procedures.hasChildNodes())
                                {
                                    for(int i = 0; i < procedures.childNodes().size();i++)
                                    {
                                        QDomNode procedure = procedures.childNodes().at(i);

                                        if(!procedure.isElement())
                                            return false;
                                        if(procedure.toElement().tagName() != "proc")
                                            return false;
                                        if(!procedure.toElement().hasAttribute("name"))
                                            return false;

                                        if(procedure.hasChildNodes())
                                        {
                                            for(int i = 0; i < procedure.childNodes().size();i++)
                                            {
                                                QDomNode NdProc = procedure.childNodes().at(i);

                                                if(!NdProc.isElement())
                                                    return false;
                                                QString tagNdProc = NdProc.toElement().tagName();
                                                if(tagNdProc == "para")
                                                {
                                                    if(!NdProc.toElement().hasAttribute("name") || !NdProc.toElement().hasAttribute("type") || !NdProc.toElement().hasAttribute("passage"))
                                                        return false;
                                                    bool ok = true;
                                                    NdProc.toElement().attribute("passage").toInt(&ok);
                                                     if(!ok)
                                                         return false;

                                                }else
                                                    if(tagNdProc == "variables")
                                                    {

                                                        if(NdProc.hasChildNodes())
                                                        {
                                                            for(int i = 0; i < NdProc.childNodes().size();i++)
                                                            {
                                                                QDomNode variable = NdProc.childNodes().at(i);

                                                                if(!variable.isElement())
                                                                    return false;
                                                                if(variable.hasChildNodes())
                                                                    return false;
                                                                if(variable.toElement().tagName() != "var")
                                                                    return false;
                                                                if(!variable.toElement().hasAttribute("name") || !variable.toElement().hasAttribute("type"))
                                                                    return false;
                                                            }
                                                        }
                                                    }else
                                                        if(tagNdProc == "Debut")
                                                        {
                                                            /*if(NdProc.toElement().hasAttributes());
                                                                return false;*/
                                                                if(NdProc.hasChildNodes())
                                                                    if(!ControleDebutProgrammme(NdProc.toElement()))
                                                                        return false;
                                                        }else
                                                            return false;
                                              }

                                        }else
                                            return false;
                                    }
                                }

                            }else
                                if(tagName == "Debut")
                                {//qDebug()<<"deb aldo";
                                    /*if(RacineAlgo.childNodes().at(i).hasAttributes());
                                        return false;*/
                                        if(RacineAlgo.hasChildNodes())
                                            if(!ControleDebutProgrammme(RacineAlgo.childNodes().at(i).toElement()))
                                                return false;

                                }else
                                    return false;
        }

  return true;
}

int Editeur_Arbre_Algo::estDejaOuvert(QString nomFichier)
{
   for(int i = 0; i < listeAlgorithmes.size();i++)
       if(listeAlgorithmes.at(i).chemainFichier == nomFichier)
           return i;
   return -1;
}

