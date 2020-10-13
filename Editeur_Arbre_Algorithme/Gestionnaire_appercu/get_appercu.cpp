#include "get_appercu.h"

Get_Appercu::Get_Appercu(QObject *parent) :
    QObject(parent)
{
}
QString decrypte_condition_expression(QString attribue)
{
    attribue.replace(attribue.indexOf("µ"),1,"<");
    return attribue;

}

QString Get_Appercu::constante(QDomElement element)
{
    return element.attribute("name")+" = "+element.attribute("valeur");
}

QString Get_Appercu::enregistrement(QDomElement element)
{
    return element.attribute("name")+" = enregistrement";
}

QString Get_Appercu::champ(QDomElement element)
{
    return variable(element);
}

QString Get_Appercu::tableaux(QDomElement element)
{
    return element.attribute("name")+" = "+"Tableau[1.."+element.attribute("taille")+"] Des "+element.attribute("contenu");
}

QString Get_Appercu::matrices(QDomElement element)
{
    return element.attribute("name")+" = "+"Tableau[1.."+element.attribute("ligne")+",1.."+element.attribute("colonne")+"] Des "+element.attribute("type");
}

QString Get_Appercu::fichiers(QDomElement element)
{
    return element.attribute("name")+"Fichier des "+element.attribute("type");
}

QString Get_Appercu::fonction(QDomElement element)
{
    QDomNodeList parametres = element.elementsByTagName("para");
    QString parametre ;
    for(int i=0;i<parametres.count();i++)
    {
        parametre += variable(parametres.at(i).toElement())+",";
    }
    parametre.replace(parametre.length()-1,1,"");
    return "Fonction "+element.attribute("name")+" ("+parametre+" ): "+element.attribute("type");
}

QString Get_Appercu::variable(QDomElement element)
{
    return element.attribute("name")+" :"+element.attribute("type");
}

QString Get_Appercu::procedure(QDomElement element)
{
    QDomNodeList parametres = element.elementsByTagName("para");
    QString parametre,passage ;
    for(int i=0;i<parametres.count();i++)
    {passage="";
        if(parametres.at(i).toElement().attribute("passage").toInt())
            passage = "var ";
        parametre += passage+variable(parametres.at(i).toElement())+",";
    }
    parametre.replace(parametre.length()-1,1,"");
    return "Procedure "+element.attribute("name")+" ("+parametre+" )";
}

QString Get_Appercu::instruction(QDomElement element)
{
    switch (element.attribute("index").toInt())
    {
        case -1 :return "Repeter";break;
        case 0 :return element.attribute("app");break;
        case 1 :return element.attribute("var")+" <--- "+element.attribute("exp");break;
        case 2 :{
                    if(!element.attribute("msg").isEmpty())
                        return "Ecrire('" + element.attribute("msg") + "')Lire("+element.attribute("var")+")";
                    else
                       return "Lire("+element.attribute("var")+")";
                }break;
        case 3 :return "Ecrire("+element.attribute("msg")+")";break;
        case 4 :return "{* "+element.attribute("com")+" *}";break;
        case 5 :return "SI("+decrypte_condition_expression(element.attribute("condition"))+")Alors";break;
        case 6 :return "SI NON"; break;
        case 7 :return "SELON("+element.attribute("selectore")+")FAIRE"; break;
        case 8 :return element.attribute("choix")+" : "; break;
        case 9 :return "POUR "+element.attribute("cmp")+" DE "+element.attribute("vi")+" A "+element.attribute("vf")+" FAIRE";break;
        case 10:return "TANTE_QUE("+decrypte_condition_expression(element.attribute("condition"))+")FAIRE";break;
        case 11:return "JUSQU'A("+decrypte_condition_expression(element.attribute("condition"))+")";break;
        case 12:return element.attribute("proc")+"("+element.attribute("para")+")";break;
        case 13:return element.attribute("name")+" <--- "+element.attribute("retour");
    default:
        break;
    }
}
