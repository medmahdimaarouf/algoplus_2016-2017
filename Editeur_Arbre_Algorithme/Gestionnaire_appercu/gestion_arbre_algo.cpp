#include "gestion_arbre_algo.h"
int NBOccurence(QChar car,QString chaine)
{
    if(chaine.isEmpty())
        return 0;
    int occ = 0;
    for(int i = 0; i < chaine.size();i++)
        if(chaine.at(i) == car)
            occ++;
    return occ;
}


Gestion_Arbre_Algo::Gestion_Arbre_Algo(QTreeView *ViewAlgo, QTextEdit *TextDescription)
{
    modelViewAlgo = new QStandardItemModel(this);
    Text_Description = TextDescription;
    ViewAlgo->setModel(modelViewAlgo);
    get_appercuOf = new Get_Appercu;
    nameAlgo = "Sans titre";
    Algo = new QStandardItem("Algoritme:"+nameAlgo);
    Algo->setAccessibleDescription(nameAlgo + "# Any Think to describe");
    Algo->setWhatsThis("Algo");
    Algo->setEditable(false);
    modelViewAlgo->appendRow(Algo);
    DebutAlgo = new QStandardItem("Debut");
    DebutAlgo->setWhatsThis("Debut");
    DebutAlgo->setEditable(false);
    modelViewAlgo->appendRow(DebutAlgo);
    finAlgo = new QStandardItem("Fin : "+nameAlgo);
    finAlgo->setEditable(false);
    finAlgo->setWhatsThis("fin");
    modelViewAlgo->appendRow(finAlgo);
    ArbreAlgo = ViewAlgo;
    std_Copie = NULL;
    connect(ViewAlgo,SIGNAL(clicked(QModelIndex)),this,SLOT(changement_index_courant(QModelIndex)));


}

void Gestion_Arbre_Algo::seletionner(int ligne)
{

}

QStringList Gestion_Arbre_Algo::listeProgrammmes()
{
    QStringList liste_Programmes;
    if(Algo->rowCount() > 0)
        for(int i = 0; i < Algo->rowCount();i++)
            if(!Algo->child(i)->accessibleDescription().isEmpty())
                liste_Programmes.append(Algo->child(i)->accessibleDescription().split("#").at(1));
    return liste_Programmes;

}

QStringList Gestion_Arbre_Algo::listeTypes()
{
    QStringList liste_Types;
    liste_Types<<"entier"<<"reel"<<"chaine"<<"caractere"<<"booleen";
    QStandardItem * std_types = NULL;
    if(Algo->rowCount() > 0)
        for(int i = 0;i < Algo->rowCount();i++)
            if(Algo->child(i)->whatsThis() == "types")
            {
                std_types = Algo->child(i);
                break;
            }

    if(std_types)
         if(std_types->rowCount() > 0)
              for(int i = 0;  i < std_types->rowCount();i++)
                  liste_Types<<std_types->child(i)->accessibleDescription().split("#").at(1);
    return liste_Types;
}

QStringList Gestion_Arbre_Algo::liste_TypeContenu(QString TypeCourant)
{
    QStringList liste_TypesContenu;
    liste_TypesContenu<<"entier"<<"reel"<<"chaine"<<"caractere"<<"booleen"<<"@entier"<<"@reel"<<"@chaine"<<"@caractere"<<"@booleen";
    QStandardItem * std_types = NULL;
    if(Algo->hasChildren())
        for(int i = 0;i < Algo->rowCount();i++)
            if(Algo->child(i)->whatsThis() == "types")
            {
                std_types = Algo->child(i);
                break;
            }

    if(std_types)
         if(std_types->hasChildren())
              for(int i = 0;  i < std_types->rowCount();i++)
              {
                  liste_TypesContenu<<std_types->child(i)->accessibleDescription().split("#").at(1);
                  liste_TypesContenu<<"@" + std_types->child(i)->accessibleDescription().split("#").at(1);
              }
    if(!PasEspaces(TypeCourant).isEmpty())
       liste_TypesContenu<< "@" + PasEspaces(TypeCourant);
    return liste_TypesContenu;
}

QStringList Gestion_Arbre_Algo::listeProcedures()
{
    QStringList listeProcs;
    if(modelViewAlgo->item(0)->hasChildren())
        for(int i = 0; i < modelViewAlgo->item(0)->rowCount();i++)
        {
            if(modelViewAlgo->item(0)->child(i)->text() != "Constantes" && modelViewAlgo->item(0)->child(i)->text() != "Types" && modelViewAlgo->item(0)->child(i)->text() != "Variables" && modelViewAlgo->item(0)->child(i)->accessibleDescription().split("#").at(0).toInt() == 1)
                    listeProcs<<modelViewAlgo->item(0)->child(i)->accessibleDescription().split("#").at(1);
        }
    return listeProcs;
}

QStringList Gestion_Arbre_Algo::ListeToutVariables()
{
    if(!Algo->hasChildren())
        return QStringList();
    QStringList listetoutvars = liste_Variables_DE("Programme principale"),listeprogs = listeProgrammmes();
    if(!listeprogs.isEmpty())
        for(int i = 0; i < listeprogs.size();i++)
            listetoutvars.append(liste_Variables_DE(listeprogs.at(i)));
    return listetoutvars;
}

QStringList Gestion_Arbre_Algo::liste_Variables_DE(QString programme)
{
   QStringList listevariables ;

   if(programme.isEmpty())
       return listevariables;
   if(programme == "Programme principale")
     {
       if(!Algo->hasChildren())
           return listevariables;
       QStandardItem * std_variables = NULL;

           if(Algo->child(0)->whatsThis() == "variables")
              std_variables = Algo->child(0);
           else
               if(Algo->child(1))
               {
                   if(Algo->child(1)->whatsThis() == "variables")
                       std_variables = Algo->child(1);
                   else
                       if(Algo->child(2))
                       {
                           if(Algo->child(2)->whatsThis() == "variables")
                               std_variables = Algo->child(2);
                       }
               }

           if(std_variables)
               for(int i = 0; i < std_variables->rowCount();i++)
                   listevariables.append(std_variables->child(i)->accessibleDescription().split("#").at(0));
     }
       else
       {
           QStandardItem * std_programme = std_sousProgramme(programme);
              if(std_programme)
                  if(std_programme->child(0)->whatsThis() == "variables")
                      for(int i = 0; i < std_programme->child(0)->rowCount();i++)
                          listevariables<<std_programme->child(0)->child(i)->accessibleDescription().split("#").at(0);
       }
   return listevariables;

}

QStringList Gestion_Arbre_Algo::listeFonctions()
{
    QStringList listefcts;
    if(modelViewAlgo->item(0)->hasChildren())
        for(int i = 0; i < modelViewAlgo->item(0)->rowCount();i++)
            if(modelViewAlgo->item(0)->child(i)->text() != "Constantes" && modelViewAlgo->item(0)->child(i)->text() != "Types" && modelViewAlgo->item(0)->child(i)->text() != "Variables" && modelViewAlgo->item(0)->child(i)->accessibleDescription().split("#").at(0).toInt() == 0)
                listefcts<< modelViewAlgo->item(0)->child(i)->accessibleDescription().split("#").at(1);
 return listefcts;
}

QStandardItem *Gestion_Arbre_Algo::std_sousProgramme(QString sousProgramme)
{
    if(sousProgramme == "Programme principale")
        return Algo;
    else
        if(Algo->rowCount() > 0)
            for(int i = 0; i < Algo->rowCount();i++)
                if(!Algo->child(i)->accessibleDescription().isEmpty())
                    if(Algo->child(i)->accessibleDescription().split("#").at(1) == sousProgramme)
                        return Algo->child(i);
    return NULL;
}

QString Gestion_Arbre_Algo::programmeInstruction(QStandardItem *std_instruction)
{
   while(std_instruction->whatsThis() == "item") {
        std_instruction = std_instruction->parent();
        if(!std_instruction)
            return "";
     }

   if(std_instruction->whatsThis() == "Debut")
       std_instruction = std_instruction->parent();
   if(std_instruction)
       if(std_instruction->whatsThis() == "Algo")
           return "Programme principale";
        else
           if(std_instruction->whatsThis() == "fct" || std_instruction->whatsThis() == "proc")
               return std_instruction->accessibleDescription().split("#").at(1);
            else
               return "";
}


QStringList Gestion_Arbre_Algo::parametresProgrammes(QStandardItem *programme)
{
    QStringList listeParas;
    if(programme)
        if(programme->accessibleDescription().split("#").size() >= 4)
        {
            QStringList listeinfoParas = programme->accessibleDescription().split("#").at(3).split("|");
            if(!listeinfoParas.isEmpty())
                for(int i = 0; i < listeinfoParas.size();i++)
                    listeParas.append(listeinfoParas.at(i).split(":").at(0));
        }
    return listeParas;

}


QString Gestion_Arbre_Algo::PasEspaces(QString chaine)
{
    if(!chaine.isEmpty())
    {
        while (chaine.at(0).isSpace()) {
            chaine.remove(0,1);
        }
        while (chaine.at(chaine.size()-1).isSpace()) {
            chaine.remove(chaine.at(chaine.size()-1));
        }
    }
    return chaine;

}

QString Gestion_Arbre_Algo::ControleNomCP(int operation,QTreeWidget * Viewliste_CP,QString nom)
{
    nom = PasEspaces(nom);

    QString prefix;
    if(operation > 2)
        prefix = "Champ";
    else
        prefix = "Parametre";

    if(nom.isEmpty())
        return prefix + " n'est pas déffinit";
    if(!nom.at(0).isLetter())
        return prefix + " doit commncé par une lettre";
    for(int i = 0; i < nom.size();i++)
        if(nom.at(i).isSpace())
            return prefix + " contient un espace";
        else
            if(!nom.at(i).isLetterOrNumber() && nom.at(i) != '_')
                return QString(prefix + "contient un symbole interdit '").append(nom.at(i)) + "'";


    if(prefix == "Champ" && nom == "id")
        return "Champ interdit";

    QStringList listeNoms;

    if(operation == 3)
    {
        if(Viewliste_CP->topLevelItemCount())
            for(int i = 0; i < Viewliste_CP->topLevelItemCount();i++)
                listeNoms<<Viewliste_CP->topLevelItem(i)->text(0);
        if(listeNoms.contains(nom))
            return "Champ existe déja";

    }else
    {
        if(Viewliste_CP->topLevelItemCount())
            for(int i = 0; i < Viewliste_CP->topLevelItemCount();i++)
                listeNoms<<Viewliste_CP->topLevelItem(i)->text(0);
        if(listeNoms.contains(nom))
            return "Parametre existe déja";
    }
    return "";

}


QString Gestion_Arbre_Algo::Controle_NomVariable(QString nomVariable,QString programme,QString nom_Courant)
{
    nomVariable = PasEspaces(nomVariable);
    if(nomVariable.isEmpty())
        return "Nom de variable n'est pas déffinit";
    if(!nomVariable.at(0).isLetter())
        return "Nom de variable doit commncé par une lettre";
    for(int i = 0; i < nomVariable.size();i++)
        if(nomVariable.at(i).isSpace())
            return "Nom de variable contient un espace";
        else
            if(!nomVariable.at(i).isLetterOrNumber() && nomVariable.at(i) != '_')
                return QString("Nom de variable contient un symbole interdit '").append(nomVariable.at(i)) + "'";
// ********** NIEW ****************
    if(listeTypes().contains(nomVariable))
        return "Nom de variable est déja utlilisé comme un nom de type";
    if(listeProgrammmes().contains(nomVariable))
        return "Nom de variable est déja utlilisé comme un nom d'un sous programme";
    QStringList listeVariables = liste_Variables_DE(programme);
    if(!nom_Courant.isEmpty())
        listeVariables.removeOne(nom_Courant);
    if(listeVariables.contains(nomVariable))
        return "Variable déja déclarer dans ce programme";

    return "";
}


QString Gestion_Arbre_Algo::Controle_Variable(QString variable)
{
    variable = PasEspaces(variable);
    if(variable.isEmpty())
        return "Variable n'est pas déffinit";
    if(!variable.at(0).isLetter())
        return "Variable doit commncé par une lettre";
    QString symboles = "@[]._";
    for(int i = 0; i < variable.size();i++)
        if(variable.at(i).isSpace())
            return "Variable contient un espace";
            else
                if(!variable.at(i).isLetterOrNumber() && !symboles.contains(variable.at(i)))
                    return QString("Variable contient un symbole interdit '").append(variable.at(i)) + "'";
    return "";
}


QString Gestion_Arbre_Algo::Controle_NomType(QString nomType,QString nom_Courant)
{
    nomType = PasEspaces(nomType);

    if(nomType.isEmpty())
        return "Nom de type n'est pas deffinit";
    if(!nomType.at(0).isLetter())
        return "Nom de type doit commencé par une lettre";
    for(int i = 0; i < nomType.size();i++)
        if(!nomType.at(i).isLetterOrNumber() && nomType.at(i) != '_')
            return QString("Nom de type contient un symbole interdit '").append(nomType.at(i)) + "'";
    QStringList liste_Types = listeTypes();
    if(!nom_Courant.isEmpty())
        liste_Types.removeOne(nom_Courant);
    if(liste_Types.contains(nomType))
        return "Nom type déja déclarer";
    // ************* NIEW ****************

    if(ListeToutVariables().contains(nomType))
        return "Nom de type est déja déclaré comme un nom de variable";
    if(listeProgrammmes().contains(nomType))
        return "Nom de type est déja déclarer comme un nom d'un sous programme";

    return "";
}


QString Gestion_Arbre_Algo::Controle_Expression(QString Expression)
{
    if(Expression.isEmpty())
        return "Expression n'est pas déffinit";
    Expression = PasEspaces(Expression);

    if(NBOccurence('(',Expression) > NBOccurence(')',Expression))
        return "Expression manque une fermeture de ')'";
    if(NBOccurence('[',Expression) > NBOccurence(']',Expression))
        return "Expression manque une fermeture de ']'";

    if(NBOccurence('(',Expression) < NBOccurence(')',Expression))
        return "Expression manque une ouverture de '('";
    if(NBOccurence('[',Expression) < NBOccurence(']',Expression))
        return "Expression manque une ouverture de '['";
    QStringList operateurs = QString("+#-#*#/# MOD # DIV # NON # ET # OU #<#>#<=#>=#=").split("#");

    for(int i = 0; i < operateurs.size();i++)
        if(Expression.endsWith(operateurs.at(i)))
            return "Expression de valeur n'est pas compléte .";
    return "";
}


QString Gestion_Arbre_Algo::Controle_Parametres(QString parametres)
{
    parametres = PasEspaces(parametres);

    if(parametres.isEmpty())
        return "Parametre(s) indeffinit";
    QStringList listeParas = parametres.split(",");
    for(int i = 0; i < listeParas.size();i++)
    {
        /*QString message_ControlePara = Controle_Variable(listeParas.at(i));
        if(!message_ControlePara.isEmpty())
            return "Parametre " + QString::number(i+1) + " " + message_ControlePara.remove("Variable");
            */
        if(listeParas.at(i).isEmpty())
            return "Parametre " + QString::number(i+1) + " est indeffinit";
    }
    return "";

}


QString Gestion_Arbre_Algo::Controle_Constante(QString constante)
{
    constante = PasEspaces(constante);
    if(constante.isEmpty())
        return "Nom de constante n'est pas déffinit";
    if(!constante.at(0).isLetter())
        return "Nom de constante doit commncé par une lettre";
    for(int i = 0; i < constante.size();i++)
        if(constante.at(i).isSpace())
            return "Nom de constante contient un espace";
        else
            if(!constante.at(i).isLetterOrNumber() && constante.at(i) != '_')
                return QString("Nom de constante contient un symbole interdit '").append(constante.at(i)) + "'";
    return "";
}


QString Gestion_Arbre_Algo::Controle_TypeContenu(int opertaion,QString Type, QString contenu)
{
    contenu = PasEspaces(contenu);

    if(contenu.isEmpty())
        return "Type de contenu indeffinit";

    QString prefix;

    if(opertaion == 3)
        prefix = "Champ ";
    else
       if(opertaion == 2 || opertaion == 1)
            prefix = "Parametre ";
            else
                if(opertaion == 0)
                       prefix = "Type de contenu ";
                    else
                      prefix = "Type ";

    if(!contenu.at(0).isLetterOrNumber() && contenu.at(0) != '@')
        return prefix + QString("contient un symbole interdit '").append(contenu.at(0)) + "'";
    if(contenu.size() == 1 && contenu.at(0) == '@')
        return prefix + QString("contient un symbole interdit '").append(contenu.at(0)) + "'";
    for(int i = 1; i < contenu.size();i++)
        if(contenu.at(i).isSpace())
            return prefix + " contient un espace";
        else
            if(!contenu.at(i).isLetterOrNumber() && contenu.at(i) != '_' )
                return prefix + QString("contient un symbole interdit '").append(contenu.at(i)) + "'";

    Type = PasEspaces(Type);
    if(contenu == Type)
        return "Déclation évoque un erreur d'execution";

    return "";
}


QString Gestion_Arbre_Algo::controleNomProgrmme(bool operation,QString nomProgram,QString nom_modif)
{
    nomProgram  =PasEspaces(nomProgram);
    QString prefix;
    if(operation)
        prefix = "Nom de fonction ";
    else
        prefix = "Nom de procedure ";
    if(nomProgram.isEmpty())
        return prefix + " indeffinit";
    if(nomProgram.at(0) == '_')
        return prefix + "contient un symbole interdit '_'";
    for(int i = 0; i < nomProgram.size();i++)
        if(nomProgram.at(i).isSpace())
            return prefix + "contient un espace";
        else
            if(!nomProgram.at(i).isLetterOrNumber() && nomProgram.at(i) != '_' )
                return prefix + QString("contient un symbole interdit '").append(nomProgram.at(i)) + "'";
    //****** NIEWS *********************
    QStringList listePrpogrammes = listeProgrammmes();
    if(!nom_modif.isEmpty())
        listePrpogrammes.removeOne(nom_modif);
    if(listePrpogrammes.contains(nomProgram))
        return prefix + "est déja déclaré";
    if(listeTypes().contains(nomProgram))
        return prefix + "est déja déclaré comme un type";
    if(ListeToutVariables().contains(nomProgram))
        return prefix + "est déja déclaré comme un nom de variable";

    return "";
}

QString Gestion_Arbre_Algo::Controle_Message(QString message)
{
    message = PasEspaces(message);
    if(message.isEmpty())
        return "message indeffinit";
    return "";
}

QString Gestion_Arbre_Algo::Controle_condition(QString condition)
{
    condition = PasEspaces(condition);
    if(condition.isEmpty())
        return "Condition indeffinit";
    return "";
}


void Gestion_Arbre_Algo::Couper_ligne()
{
    if(ArbreAlgo->currentIndex().isValid())
    {
        if(modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex())->whatsThis() == "item")// VALIDATION DE L ITEM DE L OPERATION
        {
            Copier_ligne();
            supprimer_ligne();
        }
    }
    else
        qDebug()<<"Couper invalide index";
}


void Gestion_Arbre_Algo::Copier_ligne()
{
    if(ArbreAlgo->currentIndex().isValid())// VALIDATION DU INDEX
     {
        if(modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex())->whatsThis() == "item")// VALIDATION DE L ITEM DE L OPERATION
        {
            std_Copie = CopierL(modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex()));
        }
    }
     else
        qDebug()<<"Copier invalide index";
}


void Gestion_Arbre_Algo::Coller_ligne()
{
    if(ArbreAlgo->currentIndex().isValid())
    {
        if(std_Copie != NULL)
        {
            if(std_Copie->whatsThis() == modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex())->whatsThis() || modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex())->text() == "")
            {
                coller2L(std_Copie,modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex()));
            }
            else
                qDebug()<<"coller impossible car ne sont pas compatible";
        }
        else
            qDebug()<<"std copie null";
    }else
        qDebug()<<"index invalide de collage";

}


void Gestion_Arbre_Algo::supprimer_ligne()
{
    if(ArbreAlgo->currentIndex() != Algo->index() && modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex())->text() != "Debut" && modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex())->whatsThis() != "fin" && modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex())->whatsThis() != "champ")// && model_View_Algo->itemFromIndex(index)->accecibledesc().split("#").at(0).toInt() != -1)
        supprimerL(modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex()));
}


void Gestion_Arbre_Algo::afficher_Algorithme(QDomDocument document)
{
    Algo->removeRows(0,Algo->rowCount());
    DebutAlgo->removeRows(0,DebutAlgo->rowCount());
    nameAlgo = document.firstChildElement().attribute("name");

           Algo->setText("Algoritme:" + nameAlgo);
           Text_Description->setPlainText(document.firstChildElement().attribute("desc"));
           affiche_entetAlgo(document.firstChildElement(),Algo);
           affiche_BlokAlgo(document.firstChildElement(),DebutAlgo);
           finAlgo->setText("Fin :"+nameAlgo);

   ArbreAlgo->expandAll();
}


void Gestion_Arbre_Algo::add_newItemAlgo(QStandardItem *newItemAlgo)
{

    if(!ArbreAlgo->currentIndex().isValid())// Index est invalide -> Ajout a la fin de Debut
    {//qDebug()<<"not valid index ->ajout a la fin";
        DebutAlgo->insertRow(0,newItemAlgo);
    }
    else
    {
        QStandardItem * CurrentItem = modelViewAlgo->itemFromIndex(ArbreAlgo->currentIndex());
        QString whatsThis = CurrentItem->whatsThis();
        if(whatsThis == "Debut")
            CurrentItem->insertRow(0,newItemAlgo);
        else
            if(whatsThis == "" && CurrentItem->text() == "")
            {
                coller2L(newItemAlgo,CurrentItem);

            }
             else
                if(whatsThis == "item" && CurrentItem->hasChildren())
                {
                    if(CurrentItem->accessibleDescription().split("#").at(0).toInt() == 5 && CurrentItem->accessibleDescription().split("#").at(2).toInt()  == 1)
                    {
                        if(CurrentItem->child(0)->text() == "")
                        {
                            /*CurrentItem->removeRow(0);
                            CurrentItem->insertRow(0,newItemAlgo);*/
                            coller2L(newItemAlgo,CurrentItem->child(0));
                        }
                        else
                        //CurrentItem->insertRow( CurrentItem->rowCount()-2,newItemAlgo);
                            CurrentItem->insertRow(0,newItemAlgo);
                    }
                    else
                        if(CurrentItem->accessibleDescription().split("#").at(0).toInt() == 6)
                        {
                            if(CurrentItem->child(0)->text() == "")
                            {
                                /*CurrentItem->removeRow(0);
                                CurrentItem->insertRow(0,newItemAlgo);*/
                                coller2L(newItemAlgo,CurrentItem->child(0));

                            }
                            else
                           // CurrentItem->appendRow(newItemAlgo);
                                CurrentItem->insertRow(0,newItemAlgo);
                        }
                        else
                        {
                            if(CurrentItem->child(0)->text() == "")
                            {
                                /*CurrentItem->removeRow(0);
                                CurrentItem->insertRow(0,newItemAlgo);*/
                                coller2L(newItemAlgo,CurrentItem->child(0));

                            }
                            else
                                //CurrentItem->insertRow(CurrentItem->rowCount()-1,newItemAlgo);
                                CurrentItem->insertRow(0,newItemAlgo);
                        }
                }
                else
                    if(whatsThis == "item" && !CurrentItem->hasChildren())
                        CurrentItem->parent()->insertRow(CurrentItem->row()+1,newItemAlgo);
                        else
                           if(whatsThis == "fct" || whatsThis == "proc")
                               CurrentItem->child(CurrentItem->rowCount()-2)->insertRow(0,newItemAlgo);
                               else
                                    if(CurrentItem->whatsThis() == "fin" && CurrentItem->index() != finAlgo->index())
                                    {
                                        CurrentItem->parent()->parent()->insertRow(CurrentItem->parent()->row()+1,newItemAlgo);
                                    }
                                   else
                                       DebutAlgo->insertRow(0,newItemAlgo);
    }
    ArbreAlgo->setCurrentIndex(newItemAlgo->index());
}


int Gestion_Arbre_Algo::affiche_instructions(QDomNodeList list, QStandardItem *stditm)
{
    int i;
    for(i=0;i< list.count();i++)
    {
        QDomElement instruction = list.at(i).toElement();
        QStandardItem * std_instruction = new QStandardItem();
        std_instruction->setText(Appercu_Instruction(instruction,std_instruction));
        std_instruction->setEditable(false);
        if(instruction.hasChildNodes())
        {
            i+= affiche_instructions(instruction.elementsByTagName("item"),std_instruction);
        }
      stditm->appendRow(std_instruction);
    }
    return list.count();
}


QString Gestion_Arbre_Algo::Appercu_Instruction(QDomElement instruction, QStandardItem *Item_Algo)
{
    switch (instruction.attribute("index").toInt())
    {
        case -1 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("-1#REPETER");
                    return "Repeter";

                }
        break;
        case 0 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("0#" + instruction.attribute("app"));
                    return instruction.attribute("app");
                }
        break;
        case 1 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("1#" + instruction.attribute("var") + "#" + instruction.attribute("exp"));
                    return instruction.attribute("var")+" <--- "+instruction.attribute("exp");
                }
        break;
        case 2 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("2#" + instruction.attribute("var") + "#" + instruction.attribute("msg"));
                    if(instruction.attribute("msg").isEmpty())
                        return "Lire("+instruction.attribute("var")+")";
                    else
                        return "Ecrire('" + instruction.attribute("msg") + "')Lire("+instruction.attribute("var")+")";
                }
        break;
        case 3 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("3#" + instruction.attribute("msg"));
                    return "Ecrire("+instruction.attribute("msg")+")";
                }
        break;
        case 4 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("4#" + instruction.attribute("com"));
                    return "{* "+instruction.attribute("com")+" *}";
                }
        break;
        case 5 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("5#" + instruction.attribute("condition"));
                    return "SI("+instruction.attribute("condition")+")Alors";
                }
        break;
        case 6 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("6#SI NON");
                    return "SI NON";
                }
        break;
        case 7 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("7" + instruction.attribute("selectore"));
                    return "SELON("+instruction.attribute("selectore")+")FAIRE";
                }
        break;

       case 8 :
                {
                Item_Algo->setWhatsThis("item");
                Item_Algo->setAccessibleDescription("8#" + instruction.attribute("choix"));
                return instruction.attribute("choix")+" : ";
                }
        break;
        case 9 :
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("9#" + instruction.attribute("cmp") + "#" + instruction.attribute("vi") + "#" + instruction.attribute("vf") + "#" + instruction.attribute("pas"));
                    return "POUR "+instruction.attribute("cmp")+" DE "+instruction.attribute("vi")+" A "+instruction.attribute("vf")+" FAIRE";
                }
        break;
        case 10:
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("10#" + instruction.attribute("condition"));
                    return "TANTE_QUE("+instruction.attribute("condition")+")FAIRE";
                  }
        break;
        case 11:
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("11#" + instruction.attribute("condition"));
                    return "JUSQU'A(" + instruction.attribute("condition") + ")";
                }
        break;
        case 12:
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("12#" + instruction.attribute("proc") + "#" + instruction.attribute("isPred") + "#" + instruction.attribute("para"));
                    return instruction.attribute("proc")+"("+instruction.attribute("para")+")";
                }
        break;
        case 13:
                {
                    Item_Algo->setWhatsThis("item");
                    Item_Algo->setAccessibleDescription("13#" + instruction.attribute("name") + "#" + instruction.attribute("retour"));
                    return instruction.attribute("name") + " <-- " + instruction.attribute("retour");
                }
        break;
    default:
        qDebug()<<"instruction indefinie pour l afficher";
        break;
    }

}



void Gestion_Arbre_Algo::coller2L(QStandardItem *itemSource, QStandardItem *itemDestinataire)
{
    vider(itemDestinataire);

    itemDestinataire->setText(itemSource->text());
    itemDestinataire->setAccessibleDescription(itemSource->accessibleDescription());
    itemDestinataire->setWhatsThis(itemSource->whatsThis());
    if(itemSource->hasChildren())
    {
       for(int i = 0; i < itemSource->rowCount();i++)
       {
           QStandardItem * item = new QStandardItem();
           item->setEditable(false);
           coller2L(itemSource->child(i),item);
           itemDestinataire->appendRow(item);
       }
    qDebug()<<"endl";
    }
}



QStandardItem * Gestion_Arbre_Algo::CopierL(QStandardItem * Source)
{
    QStandardItem * copie = new QStandardItem();
    copie->setText(Source->text());
    copie->setWhatsThis(Source->whatsThis());
    copie->setAccessibleDescription(Source->accessibleDescription());
    if(Source->hasChildren())
    {
        for(int i = 0; i < Source->rowCount();i++)
            copie->appendRow(CopierL(Source->child(i)));
    }
    return copie;

}



void Gestion_Arbre_Algo::supprimerL(QStandardItem * std_item)
{
    std_item->parent()->removeRow(std_item->row());
}


void Gestion_Arbre_Algo::vider(QStandardItem *item)
{
 item->setText("");
 item->setAccessibleDescription("");
 item->setWhatsThis("");
 item->removeRows(0,item->rowCount());
}


QStandardItem *Gestion_Arbre_Algo::itemAlgoligne(int ligne)
{

}

QString Gestion_Arbre_Algo::Programme_Courante()
{
   QModelIndex indexCourante = ArbreAlgo->currentIndex();
   if(!indexCourante.isValid())
       return "Programme principale";

   QStandardItem * std_Courant = modelViewAlgo->itemFromIndex(indexCourante);

   if(std_Courant->whatsThis() == "Algo")
       return "Programme principale";

   QStringList listemots;
   listemots<<"constantes"<<"const"<<"types"<<"mat"<<"tab"<<"enreg"<<"champ"<<"fich";
   if(listemots.contains(std_Courant->whatsThis()))
       return "Programme principale";

   if(std_Courant->whatsThis() == "variables")
   {
       if(std_Courant->parent()->whatsThis() == "Algo")
           return "Programme principale";
       if(std_Courant->parent()->whatsThis() == "fct" || std_Courant->parent()->whatsThis() == "proc")
           return std_Courant->parent()->accessibleDescription().split("#").at(1);
   }

   if(std_Courant->whatsThis() == "var")
   {
       if(!std_Courant->parent()->parent()->parent())
           return "Programme principale";
        if(std_Courant->parent()->parent()->whatsThis() == "fct" || std_Courant->parent()->parent()->whatsThis() == "proc")
           return std_Courant->parent()->parent()->accessibleDescription().split("#").at(1);
   }


   if(std_Courant->whatsThis() == "fct" || std_Courant->whatsThis() == "proc")
       return std_Courant->accessibleDescription().split("#").at(1);

   if(std_Courant->whatsThis() == "Debut")
   {
       if(!std_Courant->parent())
           return "Programme principale";
       if(std_Courant->parent()->whatsThis() == "fct" || std_Courant->parent()->whatsThis() == "proc")
           return std_Courant->parent()->accessibleDescription().split("#").at(1);
   }
   if(std_Courant->whatsThis() == "item")
   {
       while (std_Courant->whatsThis() == "item") {
           std_Courant = std_Courant->parent();
       }
       if(std_Courant->whatsThis() == "Debut")
       {
           if(!std_Courant->parent())
               return "Programme principale";
           if(std_Courant->parent()->whatsThis() == "fct" || std_Courant->parent()->whatsThis() == "proc")
               return std_Courant->parent()->accessibleDescription().split("#").at(1);

       }

   }
   if(std_Courant->whatsThis() == "fin")
   {
       if(!std_Courant->parent())
           return "Programme principale";
       if(std_Courant->parent()->whatsThis() == "enreg")
           return "Programme principale";
       if(std_Courant->parent()->whatsThis() == "fct" || std_Courant->parent()->whatsThis() == "proc")
           return std_Courant->parent()->accessibleDescription().split("#").at(1);
       if(std_Courant->parent()->whatsThis() == "item")
       {
           std_Courant = std_Courant->parent();
           while (std_Courant->whatsThis() == "item") {
               std_Courant = std_Courant->parent();
           }
            if(std_Courant->whatsThis() == "Debut" && std_Courant->parent() == NULL)
                return "Programme principale";
            if(std_Courant->whatsThis() == "Debut" && std_Courant->parent())
                return std_Courant->parent()->accessibleDescription().split("#").at(1);
       }
   }
   //throw "Nom de programme courant introuvable";
   return "";
}


void Gestion_Arbre_Algo::changement_index_courant(const QModelIndex index)
{
    //qDebug()<<modelViewAlgo->itemFromIndex(index)->whatsThis();
}

void Gestion_Arbre_Algo::affiche_BlokAlgo(QDomElement element_program,QStandardItem * std_debut)
{
    QDomElement debut = element_program.firstChildElement("Debut");
    QDomNodeList instructions = debut.elementsByTagName("item");
    affiche_instructions(instructions,std_debut);
}




void Gestion_Arbre_Algo::affiche_entetAlgo(QDomElement element_program,QStandardItem * std_program)
{
    QDomNodeList constantes = element_program.firstChildElement("constants").elementsByTagName("const");
    QDomElement types = element_program.firstChildElement("types");
    QDomNodeList variables = element_program.firstChildElement("variables").elementsByTagName("var");
    QDomNodeList fonctions = element_program.firstChildElement("fonctions").elementsByTagName("fct");
    QDomNodeList procedures = element_program.firstChildElement("procedures").elementsByTagName("proc");
    if(constantes.count()>0)
    {
        QStandardItem * std_constantes = new QStandardItem("Constantes");
        std_constantes->setEditable(false);
        std_constantes->setWhatsThis("constantes");
        std_program->appendRow(std_constantes);
        for(int i=0;i<constantes.count();i++)
        {
            QStandardItem * std_const = new QStandardItem(get_appercuOf->constante(constantes.at(i).toElement()));
            std_const->setEditable(false);
            std_const->setWhatsThis("const");
            std_const->setAccessibleDescription(constantes.at(i).toElement().attribute("name") + "#" + constantes.at(i).toElement().attribute("valeur"));
            std_constantes->appendRow(std_const);

        }
    }
    if(types.hasChildNodes())
    {
        QStandardItem * std_types = new QStandardItem("Types");
        std_types->setEditable(false);
        std_types->setWhatsThis("types");
        for(int t = 0;t < types.childNodes().count();t++)
        {
            QDomElement type = types.childNodes().at(t).toElement();
            if(type.tagName()=="tab")
            {
              QStandardItem * std_tab = new QStandardItem(get_appercuOf->tableaux(type));
              std_tab->setWhatsThis("tab");
              std_tab->setAccessibleDescription("1#" + type.attribute("name") + "#" + type.attribute("taille") + "#" + type.attribute("contenu"));
              std_tab->setEditable(false);
              std_types->appendRow(std_tab);
            }
            else if(type.tagName()== "mat")
            {
               QStandardItem * std_mat = new QStandardItem(get_appercuOf->matrices(type));
               std_mat->setEditable(false);
               std_mat->setWhatsThis("mat");
               std_mat->setAccessibleDescription("2#" + type.attribute("name") + "#" + type.attribute("ligne") + "#" + type.attribute("colonne") + "#" + type.attribute("type"));
               std_types->appendRow(std_mat);

            }
            else if(type.tagName()== "enreg")
            {
                    QStandardItem * std_enreg = new QStandardItem(get_appercuOf->enregistrement(type));
                    std_enreg->setEditable(false);
                    std_enreg->setWhatsThis("enreg");
                    QDomNodeList champs = type.elementsByTagName("champ");
                    QString listechamp = "";
                    for(int j=0;j<champs.count();j++)
                    {
                        QStandardItem * std_champ = new QStandardItem(get_appercuOf->champ(champs.at(j).toElement()));
                        std_champ->setEditable(false);
                        std_champ->setWhatsThis("champ");
                        listechamp += std_champ->text() + "|";
                        std_enreg->appendRow(std_champ);
                    }
                    listechamp = listechamp.remove(listechamp.count()-1,1);
                    QStandardItem * finenreg = new QStandardItem("Fin_"+type.attribute("name"));
                    finenreg->setEditable(false);
                    finenreg->setWhatsThis("fin");
                    std_enreg->setAccessibleDescription("3#" + type.attribute("name") + "#" + listechamp);
                    std_enreg->appendRow(finenreg);
                    std_types->appendRow(std_enreg);
                }
            else if(type.tagName()== "fichier")
            {

                    QStandardItem * std_file = new QStandardItem(get_appercuOf->fichiers(type));
                    std_file->setEditable(false);
                    std_file->setWhatsThis("fich");
                    std_file->setAccessibleDescription("4#" + type.attribute("name") + "#" + type.attribute("type"));
                    std_types->appendRow(std_file);
            }
        }
        Algo->appendRow(std_types);
    }
    if(variables.count()>0)
    {
        QStandardItem * std_variables = new QStandardItem("Variables");
        std_variables->setWhatsThis("variables");
        std_variables->setEditable(false);

        std_program->appendRow(std_variables);
        for(int i=0;i<variables.count();i++)
        {
            QStandardItem * std_variable = new QStandardItem(get_appercuOf->variable(variables.at(i).toElement()));
            std_variable->setEditable(false);
            std_variable->setAccessibleDescription(variables.at(i).toElement().attribute("name") + "#" + variables.at(i).toElement().attribute("type"));
            std_variable->setWhatsThis("var");
            std_variables->appendRow(std_variable);
        }
    }
    if(fonctions.count()>0)
    {

        for(int i=0;i<fonctions.count();i++)
        {
            QString listeParas = "";
            QDomNodeList listeNodesParas = fonctions.at(i).toElement().elementsByTagName("para");
            for(int p = 0; p < listeNodesParas.count(); p++)
                listeParas += listeNodesParas.at(p).toElement().attribute("name") + ":" + listeNodesParas.at(p).toElement().attribute("type") + ":0|";
            listeParas = listeParas.remove(listeParas.count()-1,1);

            QStandardItem * std_entete = new QStandardItem(get_appercuOf->fonction(fonctions.at(i).toElement()));
            std_entete->setEditable(false);
            std_entete->setAccessibleDescription("0#" + fonctions.at(i).toElement().attribute("name") + "#" + fonctions.at(i).toElement().attribute("type") + "#" + listeParas);
            std_entete->setWhatsThis("fct");
            QStandardItem * std_debut = new QStandardItem("Debut");
            std_debut->setEditable(false);
            std_debut->setWhatsThis("Debut");
            affiche_entetAlgo(fonctions.at(i).toElement(),std_entete);
            affiche_BlokAlgo(fonctions.at(i).toElement(),std_debut);
            std_entete->appendRow(std_debut);
            QStandardItem * finfct = new QStandardItem("Fin_"+fonctions.at(i).toElement().attribute("name"));
            finfct->setEditable(false);
            finfct->setWhatsThis("fin");
            std_entete->appendRow(finfct);
            std_program->appendRow(std_entete);
        }

    }
    if(procedures.count()>0)
    {

        for(int i=0;i<procedures.count();i++)
        {
            QString listeParas = "";
            QDomNodeList listeNodesParas = procedures.at(i).toElement().elementsByTagName("para");
            for(int p = 0; p < listeNodesParas.count(); p++)
                listeParas += listeNodesParas.at(p).toElement().attribute("name") + ":" + listeNodesParas.at(p).toElement().attribute("type") + ":" + listeNodesParas.at(p).toElement().attribute("passage") + "|";
            listeParas = listeParas.remove(listeParas.count()-1,1);

            QStandardItem * std_entete = new QStandardItem(get_appercuOf->procedure(procedures.at(i).toElement()));
            std_entete->setEditable(false);
            std_entete->setWhatsThis("proc");
            std_entete->setAccessibleDescription("1#" + procedures.at(i).toElement().attribute("name") + "##" + listeParas);

            QStandardItem * std_debut = new QStandardItem("Debut");
            std_debut->setEditable(false);
            std_debut->setWhatsThis("Debut");

             affiche_entetAlgo(procedures.at(i).toElement(),std_entete);
             affiche_BlokAlgo(procedures.at(i).toElement(),std_debut);
             std_entete->appendRow(std_debut);
            QStandardItem * finproc = new QStandardItem("Fin_"+procedures.at(i).toElement().attribute("name"));
            finproc->setEditable(false);
            finproc->setWhatsThis("fin");
            std_entete->appendRow(finproc);
            std_program->appendRow(std_entete);
        }

    }

}
