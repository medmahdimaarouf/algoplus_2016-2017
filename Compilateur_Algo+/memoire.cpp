#include "memoire.h"

Memoire::Memoire(QDomDocument Source_program)
{
    root_algo = Source_program.firstChildElement();
    QDomElement root_memoire = memoire.createElement("memoire");
    memoire.appendChild(root_memoire);
    maker_out_put = new Maker_Output_Program();
}

QString Memoire::setLocation(QString namevar,QString typevar)
{
    // --------------- Preparation de memoire -------------------------

    QString script = " ";
    QDomElement newvar = memoire.createElement("var");
    newvar.setAttribute("name",namevar);
    newvar.setAttribute("type",typevar);
    go_to_simplevar(root_algo,newvar,&newvar);
    newvar.setAttribute("location",QString::number(get_new_location()));
    memoire.firstChildElement().appendChild(newvar);

        // ---------------- preparation de script --------------------------
    script = newvar.attribute("name") + ".id = " + newvar.attribute("location") + "; ";
    //QString type = newvar.attribute("type");

    for(int i = 0;i < newvar.elementsByTagName("var").count();i++)
    {
        QDomElement sousvar = newvar.elementsByTagName("var").at(i).toElement();
        sousvar.setAttribute("location",QString::number(get_new_location()));
        script += sousvar.attribute("name") + ".id = " + sousvar.attribute("location")+";";
    }
    return script;
}

QString Memoire::setpointer(QString namePointer, QString typePointer)
{
      QDomElement elmPointer  = memoire.createElement("var");
      QDomElement rootmemoire = memoire.firstChildElement();
      elmPointer.setAttribute("name",namePointer);
      elmPointer.setAttribute("type",typePointer);
      rootmemoire.appendChild(elmPointer);
      elmPointer.setAttribute("location",QString::number(get_new_location()));
      namePointer += " = new Array();" + namePointer + ".id = " + elmPointer.attribute("location")+";"+ namePointer + ".value = ";
      if(typePointer.mid(1,-1) == "entier")
          return namePointer + "Algorithm.entier(0);";
      else
          if(typePointer.mid(1,-1) == "reel")
              return namePointer + "Algorithm.reel(0.0);";
          else
              if(typePointer.mid(1,-1) == "chaine")
                  return namePointer + "Algorithm.chaine('');";
                else
                    if(typePointer.mid(1,-1) == "caractere")
                        return namePointer + "Algorithm.caractere('');";
                      else
                        if(typePointer.mid(1,-1) == "booleen")
                            return namePointer + "Algorithm.booleen(true);";
                            else
                               return namePointer + typePointer.remove(0,1) + "();";
}


void Memoire::go_to_simplevar(QDomElement root, QDomElement variable, QDomElement *element_new_var)
{
    QString oftype = variable.attribute("type");
    if(oftype == "")
    {
        qDebug()<<"gotosimplevar type = """;
        return;
    }

    element_new_var->setAttribute("name",variable.attribute("name"));
    if(oftype != "entier" && oftype!="reel" && oftype!="caractere" && oftype!="chaine" && oftype!="booleen" && oftype.mid(0,1) != "@" )
    {
        QDomElement elmtype ;
        QDomElement root_types = root.firstChildElement("types");
        QDomNodeList types = root_types.childNodes();
            for(int i = 0;i < types.count();i++)
            {
                elmtype = types.at(i).toElement();
                if(elmtype.attribute("name") == oftype)
                    break;
            }

          if(elmtype.tagName() == "tab")
            get_std_tabs(root,variable,elmtype,element_new_var);
                else if(elmtype.tagName() == "mat")
                   get_std_mats(root,variable,elmtype,element_new_var);
                        else if(elmtype.tagName() == "enreg")
                            get_std_engres(root,variable,elmtype,element_new_var);
                                else if(elmtype.tagName() == "fich")
                                    {
                                        QDomElement fich = memoire.createElement("var");
                                        fich.setAttribute("type",elmtype.attribute("contenu"));
                                        fich.setAttribute("name",variable.attribute("name"));
                                        fich.setAttribute("location",get_new_location());
                                        //** new declaration de fichier ***                                        FichierAlgo fichAlgo;
                                        FichierAlgoPlus fichAlgo;
                                        fichAlgo.fichier = new QFile(this);
                                        fichAlgo.location = fich.attribute("location").toInt();
                                        ListFichiers.append(fichAlgo);
                                        //** END ***
                                        element_new_var->appendChild(fich);
                                     }
    }
    else
    {
        element_new_var->setAttribute("type",oftype);
    }
}

QString Memoire::get_script_location(int location)
{
    QDomElement elmvar = getvariableElemByLoc(location);
    QString script = elmvar.attribute("name") + ".id = " + elmvar.attribute("location") + ";";
        QDomNodeList sousvarlist = elmvar.elementsByTagName("var");
        for(int i = 0;i<sousvarlist.count();i++)
        script += sousvarlist.at(i).toElement().attribute("name") + ".id = " + sousvarlist.at(i).toElement().attribute("location") + ";";
        return script;
}

bool Memoire::islocatedAsFile(int location)
{
    bool trouve;
    for(int i = 0,trouve = false; i < ListFichiers.count() && trouve == false;i++)
        trouve = ListFichiers.at(i).location == location;
     return trouve;

}

QFile *Memoire::getFileByLocation(int location)
{
    for(int i = 0;i < ListFichiers.count();i++)
        if(ListFichiers.at(i).location == location)
            return ListFichiers.at(i).fichier;
    return NULL;
}

bool Memoire::remouve_var(int location)
{
    QDomNodeList listevar = memoire.elementsByTagName("var");
    int i;
    for(i = 0;i < listevar.count();i++)
    {
        if(listevar.at(i).toElement().attribute("location").toInt() == location )
            break;
    }
    if(i == listevar.count())
        return false;
    memoire.removeChild(listevar.at(i).toElement());
    return true;
}

QString Memoire::get_type_ofvar(int location)
{
    QDomElement root = memoire.firstChildElement();
    QDomNodeList listevar = root.elementsByTagName("var");
    for(int i = 0; i < listevar.count();i++)
    {
        if(listevar.at(i).toElement().attribute("location").toInt() == location)
        {
            return listevar.at(i).toElement().attribute("type");
            break;
        }
    }
    return "";
}

void Memoire::get_std_tabs(QDomElement root,QDomElement variable,QDomElement elemtype,QDomElement *elm_new_var)
{
    for(int i= 1; i <= elemtype.attribute("taille").toInt();i++)
    {
        QDomElement casetab = memoire.createElement("var");
        casetab.setAttribute("name",variable.attribute("name")+"["+QString::number(i)+"]");
        // ajout de auxiliere varaible .
        casetab.setAttribute("type",elemtype.attribute("contenu"));
        go_to_simplevar(root,casetab,&casetab);
        elm_new_var->appendChild(casetab);
     }
}

void Memoire::get_std_mats(QDomElement root,QDomElement variable,QDomElement elemtype,QDomElement *elm_new_var)
{
     for(int i = 1; i<= elemtype.attribute("ligne").toInt();i++)
        {
                for(int j = 1; j <= elemtype.attribute("colonne").toInt();j++)
                    {
                        QDomElement casemat = memoire.createElement("var");
                        casemat.setAttribute("type",elemtype.attribute("contenu"));
                        casemat.setAttribute("name",variable.attribute("name")+"["+QString::number(i)+"]["+QString::number(j)+"]");
                        go_to_simplevar(root,casemat,&casemat);
                        elm_new_var->appendChild(casemat);
                    }
     }
}

void Memoire::get_std_engres(QDomElement root,QDomElement variable,QDomElement elemtype,QDomElement *elm_new_var)
{
    for(int i = 0; i < elemtype.elementsByTagName("champ").count();i++)
    {
        QDomElement newcahmp = memoire.createElement("var");
        QDomElement champ = elemtype.elementsByTagName("champ").at(i).toElement();
        newcahmp.setAttribute("name",variable.attribute("name")+"."+champ.attribute("name"));
        newcahmp.setAttribute("type",champ.attribute("type"));
        go_to_simplevar(root,newcahmp,&newcahmp);
        elm_new_var->appendChild(newcahmp);
    }
}

QDomElement Memoire::getvariableElemByLoc(int location)
{
    QDomNodeList listvar = memoire.elementsByTagName("var");
    if(!islocated(location))
    {
        QDomElement elm = memoire.createElement("Erreur");
        return elm;
    }
    for(int i = 0;i< listvar.count();i++)
        if(listvar.at(i).toElement().attribute("location") == QString::number(location))
            return listvar.at(i).toElement();
    qDebug()<< "getvariableElemByLoc ->var in memory not founed";
}

int Memoire::get_new_location()
{
    int location = 1;

    while (islocated(location)) {
     location++;
    }
   return location;
}

bool Memoire::islocated(int location)
{
    QDomNodeList listevar = memoire.firstChildElement().elementsByTagName("var");
    for(int i = 0;i < listevar.count();i++)
        if(listevar.at(i).toElement().attribute("location").toInt() == location)
        {
            return true;
            break;
        }
    return false;
}

QString Memoire::get_name_ofvar(int location)
{
    QDomElement root = memoire.firstChildElement();
    QDomNodeList listevar = root.elementsByTagName("var");
    for(int i = 0; i < listevar.count();i++)
    {
        if(listevar.at(i).toElement().attribute("location").toInt() == location)
        {
            return listevar.at(i).toElement().attribute("name");
            break;
        }
    }
    return "Erreur";
}
