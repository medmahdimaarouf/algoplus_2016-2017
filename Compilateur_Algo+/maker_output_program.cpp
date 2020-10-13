#include "maker_output_program.h"

Maker_Output_Program::Maker_Output_Program(QObject *parent):
    QObject(parent)
{
    fin_inst = "\n";//"\n Algorithm.ligne_Courant++;";
}

QString Maker_Output_Program::get_output_program(QDomDocument document)
{
    //QFile fileRScript(":/RScripts/Ressources/InitScript.txt");
    //QFile fileRScript(":/RScripts/Ressources/SourceProgramAlog+.js");
    QFile fileRScript(":/Fichiers/Fichiers/SourceProgramAlog+.js");
     if(!fileRScript.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         if(QMessageBox::question(0,"Erreur","Fichier d'initiation execution Algo+ n'est pas trouvé \n Voulez-Vous de charger on l'exrerieur de Algo+","Charger","Annuler")== 0)
         fileRScript.setFileName(QFileDialog::getOpenFileName(0,"Ouvrir une extention","c:"));
         if(!fileRScript.open(QIODevice::ReadOnly))
         {
             QMessageBox::warning(0,"Erreur","Fichier invalide");
             return "";
         }
     }
    QTextStream in(&fileRScript);
    QString initialisation = in.readAll();

    document_to_convert = document;
    QString partieJS = convert_entetAlgoJs(document.firstChildElement());
    partieJS = partieJS + convert_blok_algo(document.firstChildElement());
    return initialisation + "\ntry{ \n"+partieJS + "\nAlgorithm.Ecrire('************* Fin Algorithm ****************');\n}catch(erreur){Algorithm.Ecrire(erreur);Algorithm.Ecrire('************* Fin Algorithm ****************');}";
}

QString Maker_Output_Program::convert_entetAlgoJs(QDomElement element_program)
{
    QString scriptJs;
    QDomNodeList constantes = element_program.firstChildElement("constants").elementsByTagName("const");
    QDomElement types = element_program.firstChildElement("types");
    QDomNodeList variables = element_program.firstChildElement("variables").elementsByTagName("var");
    QDomNodeList fonctions = element_program.firstChildElement("fonctions").elementsByTagName("fct");
    QDomNodeList procedures = element_program.firstChildElement("procedures").elementsByTagName("proc");
    if(constantes.count()>0)
    {
        for(int i=0;i<constantes.count();i++)
        {
         scriptJs+= convert_constanteJs(constantes.at(i).toElement())+ fin_inst;
        }
    }
    if(types.hasChildNodes())
    {
            for(int t = 0;t < types.childNodes().count();t++)
            {
                QDomElement type = types.childNodes().at(t).toElement();
                if(type.tagName()=="tab")
                {
                    scriptJs+= convert_tableauxJs(type)+ fin_inst;
                }
                else if(type.tagName()== "mat")
                {
                    scriptJs+= convert_matricesJs(type)+fin_inst;
                }
                else if(type.tagName()== "enreg")
                {
                    scriptJs+= convert_enregistrementJs(type)+ fin_inst;
                }
                else if(type.tagName()== "fichier")
                {
                    scriptJs+= convert_fichiersJs(type)+ fin_inst;
                }
            }
    }
    if(variables.count()>0)
    {
        for(int i=0;i<variables.count();i++)
        {
            scriptJs += convert_variableJs(variables.at(i).toElement())+ fin_inst;
        }
    }
    if(fonctions.count()>0)
    {
        for(int i=0;i<fonctions.count();i++)
        {
           scriptJs+= convert_fonctionJs(fonctions.at(i).toElement())+ fin_inst;
           scriptJs+= convert_entetAlgoJs(fonctions.at(i).toElement())+ fin_inst;
           scriptJs+= convert_blok_algo(fonctions.at(i).toElement())+ "}" + fin_inst;
        }
    }
    if(procedures.count()>0)
    {
        for(int i=0;i<procedures.count();i++)
        {
            scriptJs+= convert_procedureJs(procedures.at(i).toElement());
            scriptJs+= convert_entetAlgoJs(procedures.at(i).toElement());
            scriptJs+= convert_blok_algo(procedures.at(i).toElement());
            QDomNodeList listp = procedures.at(i).toElement().elementsByTagName("para");
            for(int p = 0;p < listp.count();p++)
                if(listp.at(p).toElement().attribute("passage").toInt())
                    scriptJs += "Algorithm.procedure(false,"+ listp.at(p).toElement().attribute("name") +");";
              scriptJs += fin_inst + "}";

        }
    }
    return scriptJs;
}

QString Maker_Output_Program::convert_constanteJs(QDomElement element)
{
    return "var "+element.attribute("name")+"="+element.attribute("valeur")+";";
}

QString Maker_Output_Program::convert_enregistrementJs(QDomElement element)
{
    QString contenu = "function " + element.attribute("name") + " (){ var type = new Object();";

            QDomNodeList champs = element.elementsByTagName("champ");
            for(int i = 0;i < champs.count();i++)
            {
                contenu += convert_champJs(champs.at(i).toElement());
            }
           return contenu += " return type}";

}

QString Maker_Output_Program::convert_champJs(QDomElement element)
{
   QString type = element.attribute("type");
   if(type == "entier" || type == "reel" || type == "chaine" || type == "caractere" || type == "booleen")
       return "type." + element.attribute("name") + " = Algorithm."+element.attribute("type")+"("+get_valtype(type)+");";
   else
       if(type.mid(0,1) == "@")
           return "type." + element.attribute("name") + " = new Array();type." + element.attribute("name") + ".value = null;";
   else
       return "type." + element.attribute("name") + " = "+element.attribute("type")+"();";
}

QString Maker_Output_Program::convert_tableauxJs(QDomElement element)
{
    QString type = element.attribute("contenu"),contenu = "function " + element.attribute("name") + "(){ var type = new Object();";
    int i;
   for(i = 1; i <= element.attribute("taille").toInt();i++)

       if(type == "entier" || type == "reel" || type == "chaine" || type == "caractere" || type == "booleen")
            contenu +=  "type[" + QString::number(i) + "] = Algorithm." + type + "("+get_valtype(type)+");";
       else
           if(type.mid(0,1) == "@")
               contenu += "type[" + QString::number(i) + "] = new Array();type[" + QString::number(i) + "].value = null;";
               else
                    contenu +="type["+QString::number(i)+"] = " + type + "();";

    return contenu += "return type;}";
}

QString Maker_Output_Program::convert_matricesJs(QDomElement element)
{
    QString type = element.attribute("contenu"),contenu = "function " + element.attribute("name") + "(){ var type = new Object();";

    for(int i=0;i<element.attribute("colonne").toInt();i++)
        for(int j=0;j <element.attribute("ligne").toInt();j++)
            if(type == "entier" || type == "reel" || type == "chaine" || type == "caractere" || type == "booleen")
                 contenu += "type[" + QString::number(i) + "][" + QString::number(j) + "] = Algorithm." + type + "("+get_valtype(type)+");";
            else
                if(type.mid(0,1) == "@")
                    contenu += "type[" + QString::number(i) + "][" + QString::number(j) + "] = new Array();type[" + QString::number(i) + "][" + QString::number(j) + "].value = null;";
                    else
                         contenu += "type = " + type + "();";

    return contenu += " return type;}";

}

QString Maker_Output_Program::convert_fichiersJs(QDomElement element)
{
    return "var " + element.attribute("name") + ";";
}

QString Maker_Output_Program::convert_fonctionJs(QDomElement element)
{
    QString parametre = "",init_paras = "";
    QDomNodeList parametres = element.elementsByTagName("para");
    for(int i=0;i<parametres.count();i++)
    {
        parametre += parametres.at(i).toElement().attribute("name") + ",";
        if(parametres.at(i).toElement().attribute("passage").toInt() == 0)
            init_paras += "Algorithm.fonction = " + parametres.at(i).toElement().attribute("name") + ";" + parametres.at(i).toElement().attribute("name") + " = Algorithm.fonction ;";
    }
    parametre.replace(parametre.length()-1,1,"");

    return "function "+element.attribute("name")+"("+parametre+"){" + init_paras + fin_inst;
}

QString Maker_Output_Program::convert_variableJs(QDomElement element)
{

    QString  type = element.attribute("type");
    /*if(type == "entier" || type == "reel" || type == "chaine"  || type == "caractere" || type == "booleen")
        return /*"var " + element.attribute("name") + " = Algorithm." + type + "("+get_valtype(type)+");Algorithm.Allouer('" + element.attribute("name") + "','" + type + "');";
    else
        if(type.mid(0,1) == "@")
            return /*var +element.attribute("name") + " = new Array();";
        return /*"var " + element.attribute("name") + " = " + type +"();Algorithm.Allouer('" + element.attribute("name") + "','" + type + "');";*/
    return "var " + element.attribute("name") + " = Algorithm.declarer('"+ element.attribute("name") + "','" + type + "');";
}

QString Maker_Output_Program::convert_procedureJs(QDomElement element)
{
    return convert_fonctionJs(element);
}

QString Maker_Output_Program::convert_instructionJs(QDomElement element)
{

    switch (element.attribute("index").toInt())
    {
        case -1 :return fin_inst + "Algorithm.compteur = 0;do{Algorithm.Compter();" + fin_inst;break;
        case 0 :return "}"+ fin_inst;
        case 1 :return decript_Variable(element.attribute("var")) + " = Algorithm.affecter(" + decript_Variable(element.attribute("var")) + "," + get_condition_expression(element.attribute("exp"))+");" + fin_inst;break;
        case 2 :return decript_Variable(element.attribute("var")) + " = Algorithm.Lire(" + decript_Variable(element.attribute("var")) + ".id," + decript_message(element.attribute("msg")) +");" + fin_inst;break;
        case 3 :return "Algorithm.Ecrire(" + decript_message(element.attribute("msg")) + ");" + fin_inst;break;
        case 4 :return "/*"+element.attribute("com")+ fin_inst;break;
        case 5 :return "if("+get_condition_expression(element.attribute("condition"))+"){";break;
        case 6 :return fin_inst + "}else{" + fin_inst; break;
        case 7 :return "switch(" + decript_Variable(element.attribute("selectore")) + ")" + fin_inst +"{" + fin_inst; break;
        case 8 :return "case " + element.attribute("choix") + " : {"; break;
        case 9 :return "Algorithm.compteur = 0;for(" + decript_Variable(element.attribute("cmp")) + " = Algorithm.affecter(" + decript_Variable(element.attribute("cmp")) + "," + decript_Variable(element.attribute("vi")) + ");" + decript_Variable(element.attribute("cmp")) + "<=" + decript_Variable(element.attribute("vf")) + ";" + decript_Variable(element.attribute("cmp")) + " = Algorithm.affecter(" + decript_Variable(element.attribute("cmp")) + "," + decript_Variable(element.attribute("cmp")) + "+1)){Algorithm.Compter();" + fin_inst ;break;
        case 10:return "Algorithm.compteur = 0;while(" + get_condition_expression(element.attribute("condition")) + "){Algorithm.Compter();" + fin_inst;break;
        case 11:return "}while(("+get_condition_expression(element.attribute("condition"))+") == false);" + fin_inst;break;
        case 12:return Appelle_Procedure(element);break;
        case 13:return "return "+element.attribute("retour")+";" + fin_inst;
    default:
        break;
    }
    return "";
}

QString Maker_Output_Program::Appelle_Procedure(QDomElement element)
{
    if(element.attribute("isPred").toInt() != 0)
    {
        bool ok;
        int index = element.attribute("isPred").toInt(&ok);
        switch (index) {
        case 1:{// PROC    ALLOUER(P) //P : ID
                  if(element.attribute("para").isEmpty())
                      qDebug()<<"Erreur : Procedure Allouer(P : Pointeur) -> Le parametre P est introuvé";
                    else
                  {
                      QString pointeur = decript_Variable(element.attribute("para"));
                      return pointeur + " = Algorithm.Allouer(" + pointeur + ".id);" + fin_inst;
                  }
                }break;
        case 2:{// PROC LIBERER(P) // P : ID
                    if(element.attribute("para").isEmpty())
                        qDebug()<<"Erreur : Procedure Liberer(P : Pointeur) -> Le parametre P est introuvé";
                    else
                    {
                      QString pointeur = decript_Variable(element.attribute("para"));
                      return pointeur + " = Algorithm.Liberer(" + pointeur + ".id);" + fin_inst;
                    }
                }break;
        case 3:{// PROC ASSOCIER(F,ch) F : ID,ch : valeur
                  if(element.attribute("para").isEmpty())
                      qDebug()<<"Erreur  : Procedure Associer(F : Fichier,const ch : chaine) -> Les parametres F et ch sont introuvé";
                  else
                      {
                          if(element.attribute("para").split(",").count() > 2)
                              qDebug()<<"Erreur  : Procedure Associer(F : Fichier,const ch : chaine) -> Pas de signification de la parametre '" + element.attribute("para").split(",").at(2) +"'";
                          else
                              if(element.attribute("para").split(",").count() < 2)
                                  qDebug()<<"Erreur  : Procedure Associer(F : Fichier,const ch : chaine) -> Le parametre ch est introuvé";
                          else
                              {
                                  QString fichier = element.attribute("para").split(",").at(0),ch = element.attribute("para").split(",").at(1);
                                  return "Algorithm.Associer(" + decript_Variable(fichier) + ".id,'" + ch + "');" + fin_inst;
                              }
                      }
                }break;
        case 4:{// PROC OUVRIR(F) F : ID
                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Ouvrir(F : Fichier) -> Le parametre F est introuvé";
                else
                {
                    QString fichier = decript_Variable(element.attribute("para"));
                    return "Algorithm.Ouvrir(" + fichier + ".id);" + fin_inst;
                }

                }break;
        case 5:{// PROC FERMER(F) F : ID
                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Fermer(F : Fichier) -> Le parametre F est introuvé";
                else
                {
                    QString fichier = decript_Variable(element.attribute("para"));
                    return "Algorithm.Fermer(" + fichier + ".id);" + fin_inst;
                }
                }break;
        case 6:{// PROC RECREER(F) F : ID
                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Recreer(F : Fichier) -> Le parametre F est introuvé";
                else
                {
                    QString fichier = decript_Variable(element.attribute("para"));
                    return "Algorithm.Recreer(" + fichier + ".id);" + fin_inst;
                }
                }break;
        case 7:{// PROC POINTER(F : Fichier , P : entier) F : ID P : VALEUR
                    if(element.attribute("para").isEmpty())
                        qDebug()<<"Erreur  : Procedure Pointer(F : Fichier,P : entier) -> Le parametre F est introuvé";
                    else
                    {
                        if(element.attribute("para").split(",").count() > 2)
                            qDebug()<<"Erreur  : Procedure Pointer(F : Fichier,P : entier) -> Pas de signification de la parametre '" + element.attribute("para").split(",").at(2) +"'";
                        else
                            if(element.attribute("para").split(",").count() < 2)
                                qDebug()<<"Erreur  : Procedure Pointer(F : Fichier,P : entier) -> Le parametre P est introuvé";
                        else
                            {
                                QString fichier = element.attribute("para").split(",").at(0),P = element.attribute("para").split(",").at(1);
                                return "Algorithm.Pointer(" + decript_Variable(fichier) + ".id," + decript_Variable(P) + ");" + fin_inst;
                            }
                    }

                }break;
        case 8:{// PROC LIRE(F : Fichier, P : entier) F : ID P : VALEUR
                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Lire(F : Fichier,var V : Variable) -> Le parametre F est introuvé";
                else
                {
                    if(element.attribute("para").split(",").count() > 2)
                        qDebug()<<"Erreur  : Procedure Lire(F : Fichier,var V : Variable) -> Pas de signification de la parametre '" + element.attribute("para").split(",").at(2) +"'";
                    else
                        if(element.attribute("para").split(",").count() < 2)
                            qDebug()<<"Erreur  : Procedure Lire(F : Fichier,var V : Variable) -> Le parametre V est introuvé";
                    else
                        {
                            QString fichier = element.attribute("para").split(",").at(0),V = element.attribute("para").split(",").at(1);
                            return decript_Variable(V) + " = Algorithm.affecter(" + decript_Variable(V) + ",Algorithm.Proc_Lire(" + decript_Variable(fichier) + ".id," + decript_Variable(V) + ");" + fin_inst;
                        }
                }

                }break;
        case 9:{// PREOC VALEUR(ch,var N : entier,var e : booleen)
                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Valeur(ch : chaine,var N,e : booleen) -> Le parametre ch est introuvé";
                else
                {
                    if(element.attribute("para").split(",").count() == 1)
                        qDebug()<<"Erreur  : Procedure Valeur(ch : chaine,var N,e : booleen) -> Le parametre N est introuvé";
                      else
                        if(element.attribute("para").split(",").count() > 3)
                            qDebug()<<"Erreur  : Procedure Lire(F : Fichier,var V : Variable) -> Pas de signification de la parametre '" + element.attribute("para").split(",").at(3) +"'";
                            else
                                {
                                    if(element.attribute("para").split(",").size() == 3)
                                    {
                                        QString ch = element.attribute("para").split(",").at(0),N = element.attribute("para").split(",").at(1),e = element.attribute("para").split(",").at(2);
                                        ch = decript_Variable(ch),N = decript_Variable(N),e = decript_Variable(e);
                                            return  "Algorithm.fonction = Algorithm.Valeur(" + ch + "," + N + "," + e + ");" + N + " = Algorithm.affecter(" + N + ",Algorithm.fonction.N);" + e + " = Algorithm.affecter(" + e + ",Algorithm.fonction.e);" + fin_inst;
                                    }
                                     else
                                    {
                                        QString ch = element.attribute("para").split(",").at(0),N = element.attribute("para").split(",").at(1);
                                        ch = decript_Variable(ch),N = decript_Variable(N);
                                        return  N + " = Algorithm.affecter(" + N + ",Algotithm.Valeur(" + ch +"," + N +"));" + fin_inst;
                                    }
                                }
                }
                }break;
        case 10:{// PROC CONVCH(N,var ch)
                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Convch(N : entier, var ch : chaine) -> Le parametre N est introuvé";
                else
                {
                    if(element.attribute("para").split(",").count() > 2)
                        qDebug()<<"Erreur  : Procedure Convch(N : entier, var ch : chaine) -> Pas de signification de la parametre '" + element.attribute("para").split(",").at(2) +"'";
                    else
                        if(element.attribute("para").split(",").count() < 2)
                            qDebug()<<"Erreur  : Procedure Convch(N : entier, var ch : chaine) -> Le parametre ch est introuvé";
                    else
                        {
                            QString N = element.attribute("para").split(",").at(0),ch = element.attribute("para").split(",").at(1);
                            N = decript_Variable(N);ch = decript_Variable(ch);
                            return ch + " = Algorithm.affecter(" + ch + ",Algorithm.Convch(" + N + "," + ch + "));" + fin_inst;
                        }
                }
                }break;
        case 11:{// PROC EFFACE(var ch : entier, pi : entier,pi : entier)
                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Efface(var ch : entier, pi : entier,pi : entier) -> Le parametre ch est introuvé";
                else
                {
                    if(element.attribute("para").split(",").size() == 1)
                        qDebug()<<"Erreur  : Procedure Efface(var ch : entier, pi : entier,pi : entier) -> Le parametre pi est introuvé";
                    else
                        if(element.attribute("para").split(",").size() == 2)
                            qDebug()<<"Erreur  : Procedure Convch(N : entier, var ch : chaine) -> Le parametre pf est introuvé";
                       else
                           if(element.attribute("para").split(",").size() > 3)
                               qDebug()<<"Erreur  : Procedure Efface(var ch : entier, pi : entier,pi : entier) -> Pas de signification de la parametre '" + element.attribute("para").split(",").at(3) +"'";
                             else
                           {
                               QString ch = element.attribute("para").split(",").at(0),pi = element.attribute("para").split(",").at(1),pf = element.attribute("para").split(",").at(2);
                               return decript_Variable(ch) + " = Algorithm.affecter("+ decript_Variable(ch) + ",Algorithm.Efface(" + decript_Variable(ch) + "," + decript_Variable(pi) + "," + decript_Variable(pf) + "));" + fin_inst;
                           }
                }

                }break;
        case 12:{ // PROC INSERER(ch1 : chaine,var ch2 : chaine ,p : entier)

                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Inserer(ch1 : chaine,var ch2 : chaine ,p : entier) -> Le parametre ch1 est introuvé";
                else
                {
                    if(element.attribute("para").split(",").size() == 1)
                        qDebug()<<"Erreur  : Procedure Inserer(ch1 : chaine,var ch2 : chaine ,p : entier) -> Le parametre ch2 est introuvé";
                    else
                        if(element.attribute("para").split(",").size() == 2)
                            qDebug()<<"Erreur  : Procedure Inserer(ch1 : chaine,var ch2 : chaine ,p : entier) -> Le parametre p est introuvé";
                       else
                           if(element.attribute("para").split(",").size() > 3)
                               qDebug()<<"Erreur  : Procedure Inserer(ch1 : chaine,var ch2 : chaine ,p : entier) -> Pas de signification de la parametre '" + element.attribute("para").split(",").at(3) +"'";
                             else
                           {
                               QString ch1 = element.attribute("para").split(",").at(0),ch2 = element.attribute("para").split(",").at(1),p = element.attribute("para").split(",").at(2);
                               return decript_Variable(ch2) + " = Algorithm.affecter(" + decript_Variable(ch2) + ",Algorithm.Inserer("+ decript_Variable(ch1) + "," + decript_Variable(ch2) + "," + decript_Variable(p) + "));" + fin_inst;
                           }
                }
                }break;
        case 13:{// PROC CONCATE(var ch : chaine,ch1..chN : chaine)
                if(element.attribute("para").isEmpty())
                    qDebug()<<"Erreur  : Procedure Concate(var ch : chaine,ch1..chN : chaine) N > 1 et N < 10 -> parametre ch est introuvé";
                else
                    if(element.attribute("para").split(",").count() == 1)
                        qDebug()<<"Erreur  : Procedure Concate(var ch : chaine,ch1..chN : chaine) N > 1 et N < 10 -> parametre ch1 est introuvé";
                else
                    {
                        QString ch = element.attribute("para").split(",").at(0);
                        return decript_Variable(ch) + " = Algorithm.affecter(" + decript_Variable(ch) + ",Algorithm.Concate(" + element.attribute("para") + "));" + fin_inst;
                    }
        }break;
        default:
            qDebug()<<"L index " + QString::number(index) + " de procedure conserné est invalide";
            break;
        }
    }
    else
    {
        QString initps = "";
        QStringList listps;
        listps = element.attribute("para").split(",");
        QDomElement proc = get_elementProcByName(element.attribute("proc"));
        QDomNodeList listprs = proc.elementsByTagName("para");
        if(listps.count() != listprs.count())
            qDebug()<<"nombre des prarametre effectif n'est juste";
        else
            for(int i = 0; i < listprs.count();i++)
                if(listprs.at(i).toElement().attribute("passage").toInt())
                    initps += listps.at(i) + "= Algorithm.procedure(true);";
        return element.attribute("proc")+"("+element.attribute("para")+");" + initps + fin_inst;
    }

}

QString Maker_Output_Program::convert_blok_algo(QDomElement element_program)
{
    QString scriptJs="";
    QDomElement debut = element_program.firstChildElement("Debut");
    QDomNodeList instructions = debut.elementsByTagName("item");
    convert_instructionsJs(instructions,&scriptJs);
    return scriptJs;
}

int Maker_Output_Program::convert_instructionsJs(QDomNodeList list, QString *script)
{
    int i;
    for(i=0;i< list.count();i++)
    {
        QDomElement instruction = list.at(i).toElement();
        *script+= convert_instructionJs(instruction);
        if(instruction.hasChildNodes())
        {
            i+=convert_instructionsJs(instruction.elementsByTagName("item"),script);
        }
    }
    return list.count();
}

QString Maker_Output_Program::get_valtype(QString type)
{
    if(type == "entier")
        return "0";
    else
        if(type == "reel")
        return "0.0";
    else
        if(type == "chaine" || type=="caractere")
            return "''";
    else
        if(type == "booleen")
           return "true";
        else{}
}

QString Maker_Output_Program::get_condition_expression(QString attribut)
{
    //condition.replace("=","==");
    while (attribut.contains("<>")) {
        attribut = attribut.replace("<>","!=");
    }
    while (attribut.contains("@")) {
        attribut = attribut.replace("@",".value");
    }
    for(int i = 0; i < attribut.size();i++)
        if(attribut.at(i) == '+')
        {
            attribut = attribut.replace(i,1,"*1+1*");
            i+= 2;
        }
    return attribut;
}

QString Maker_Output_Program::decript_message(QString message)
{
    while (message.contains("<>")) {
        message = message.replace("<>","!=");
    }
    while (message.contains("@")) {
        message = message.replace("@",".value");
    }
    /*for(int i = 0; i < message.size();i++)
        if(message.at(i) == '+')
        {
            message = message.replace(i,1,"*1+1*");
            i+= 2;
        }
   /* while (message.contains(',')) {
        message = message.replace(',','+');
    }    */
    return message;
}

QString Maker_Output_Program::decript_Variable(QString variable)
{
    while (variable.contains('@')) {
        variable.replace('@',".value");
    }
    return variable;
}

QString Maker_Output_Program::get_typePassage(QDomElement function)
{
    QString resultat = "";
    QDomNodeList parametres = function.elementsByTagName("para");
        for(int i = 0; i < parametres.count();i++)
        {
            if(parametres.at(i).toElement().attribute("passage").toInt() == 0)
            resultat += "var " + parametres.at(i).toElement().attribute("name") + " = " + parametres.at(i).toElement().attribute("type")+"("+get_valtype(parametres.at(i).toElement().attribute("type")) + ");";
        }
        return resultat;
}

QDomElement Maker_Output_Program::get_elementProcByName(QString nameproc)
{
    QDomNodeList listprocs = document_to_convert.elementsByTagName("proc");
            for(int i = 0;i < listprocs.count();i++)
                if(listprocs.at(i).toElement().attribute("name") == nameproc)
                    return listprocs.at(i).toElement();
            qDebug()<<nameproc<<"proc not fined";
            return listprocs.at(0).toElement();
}

QString Maker_Output_Program::Convert_typeByName(QDomDocument document,QString type)
{
    QDomElement types = document.firstChildElement().firstChildElement("types");
    for(int i = 0;i <types.elementsByTagName("tab").count();i++)
    {
        if(types.elementsByTagName("tab").at(i).toElement().attribute("name") == type)
           {
            QString valtype = get_valtype(types.elementsByTagName("tab").at(i).toElement().attribute("contenu"));
            QString contenu="";
            for(int j=1;j<=types.elementsByTagName("tab").at(i).toElement().attribute("taille").toInt();j++)
             {
               contenu = contenu+valtype+",";
             }
             contenu.replace(contenu.length()-1,1,"");
             return "["+contenu+"]";
             break;
           }
    }
    for(int i = 0;i <types.elementsByTagName("mat").count();i++)
    {
        if(types.elementsByTagName("mat").at(i).toElement().attribute("name") == type)
           {
            QString contenuc = "",valtype = get_valtype(types.elementsByTagName("mat").at(i).toElement().attribute("contenu")),contenul="";
            for(int k=0;k<types.elementsByTagName("mat").at(i).toElement().attribute("colonne").toInt();k++)
            {
                contenuc = contenuc+valtype+",";
            }
            contenuc.replace(contenuc.length()-1,1,"");
            contenuc = "["+contenuc+"],";
            for(int j=0;j <types.elementsByTagName("mat").at(i).toElement().attribute("ligne").toInt();j++)
            {
                contenul = contenul+contenuc+",";
            }
            contenul.replace(contenul.length()-1,1,"");
            return "["+contenul+"]";
             break;
           }
    }
    for(int i = 0;i <types.elementsByTagName("enreg").count();i++)
    {
        if(types.elementsByTagName("enreg").at(i).toElement().attribute("name") == type)
           {QString contenu="";
            QDomNodeList champs = types.elementsByTagName("enreg").at(i).toElement().elementsByTagName("champ");
            for(int j=0;j<champs.count();j++)
            {
                contenu = contenu+convert_champJs(champs.at(j).toElement())+",";
            }
            contenu.replace(contenu.length()-1,1,"");
            return "{"+contenu+"}";
           }
    }
    for(int i = 0;i <types.elementsByTagName("fich").count();i++)
    {
        if(types.elementsByTagName("fich").at(i).toElement().attribute("name") == type)
           {qDebug()<<"fich";
            return "Fichier()";
             break;
           }
    }
    return type;
}
