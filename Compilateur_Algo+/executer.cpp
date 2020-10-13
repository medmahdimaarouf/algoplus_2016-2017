#include "executer.h"
Memoire * Ram;
QString input;
QScriptValueList listeparas;
Executer * This;
#include<math.h>

Executer::Executer(QDomDocument Source_program, QString input_program)
{
    Ram = new Memoire(Source_program);
    memoire = Ram;
    Input_program = input_program;
    This = this;

}
bool isIntegerInput(QString input)
{
    for(int  i = 0;i < input.length();i++)
        if(!input.at(i).isNumber())
            return false;
    return true;
}

bool isfloatInput(QString input)
{
    if(input.contains("."))
    {
        return isIntegerInput(input.remove("."));
    }
    return false;

}

//-------------------------------- TYPES ALGO+------------------------------------------------------
QScriptValue entier(QScriptContext * context,QScriptEngine * engine)
{
    int type ;
    engine->globalObject().setProperty("type",engine->newVariant(type,context->argument(0).toString().toInt()));
    return engine->evaluate("type");
}

QScriptValue reel(QScriptContext * context,QScriptEngine * engine)
{
    float type ;
    engine->globalObject().setProperty("type",engine->newVariant(type,context->argument(0).toString().toFloat()));
    return engine->evaluate("type");

}

QScriptValue chaine(QScriptContext * context,QScriptEngine * engine)
{
    QString type;
    engine->globalObject().setProperty("type",engine->newVariant(type,context->argument(0).toString()));
    return engine->evaluate("type");
}

QScriptValue caractere(QScriptContext * context,QScriptEngine * engine)
{
    QString type;
    engine->globalObject().setProperty("type",engine->newVariant(type,context->argument(0).toString()));
    return engine->evaluate("type");

}

QScriptValue booleen(QScriptContext * context,QScriptEngine * engine)
{
    bool type;
    engine->globalObject().setProperty("type",engine->newVariant(type,context->argument(0).toBool()));
    return engine->evaluate("type");

}
//----------------------------------TRAITEMENT VARIABLES TYPES----------------------------------
QScriptValue estAllouer(QScriptContext * context,QScriptEngine * engine)
{
    return engine->toScriptValue(Ram->islocated(context->argument(0).toString().toInt()));
}

QScriptValue gettypeOfvar(QScriptContext * context,QScriptEngine * engine)
{
   QString typevar =  Ram->get_type_ofvar(context->argument(0).toString().toInt());
   if(typevar.isEmpty())
       return engine->evaluate("throw 'Erreur : Opération de détection de type d'un variable ->type introuvable'");
   else
       return engine->toScriptValue(typevar);
}

QScriptValue gettypeOfValue(QScriptContext * context,QScriptEngine * engine)
{
    if(context->argument(0).isBool())
        {
            return "booleen";
        }
    else
        if(context->argument(0).isString())
        {
            if(context->argumentCount() == 2)// il y a un test sur le caractere
            {
               if(context->argument(0).toString().length() == 1)
                  return "caractere";
               else
                  return "chaine";
            }
            else
            {
                return "chaine";
            }
        }

    else
        if(context->argument(0).isNumber())
        {
            if(context->argument(0).toString().contains("."))
                return "reel";
            else
                return "entier";
        }
     else
         return "";

}

QString get_valtype(QString type)
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

QScriptValue isPointer(QScriptContext * context, QScriptEngine * engine)
{
    if(context->argument(0).isArray())
        return true;
    else
        return false;
}

QScriptValue isVar(QScriptContext * context, QScriptEngine * engine)
{
    if(context->argument(0).isObject())
        return true;
    else
        return false;
}

QString typeOfValue(QScriptValue valeur)
{
    if(valeur.isBool())
        return "booleen";
    else
        if(valeur.isString())
            if(valeur.toString().length() == 1)
                return "caractere";
            else
                return "chaine";
    else
        if(valeur.isNumber())
            if(valeur.toString().contains("."))
                return "reel";
            else
                return "entier";
    else
         return "Object";
}

QScriptValue declarer(QScriptContext * context,QScriptEngine * engine)
{
    QString type = context->argument(1).toString();
    QString name = context->argument(0).toString();
    QString script = "";

    if(type.mid(0,1) == "@")
         script = "var " + Ram->setpointer(name,type) + name + ".value = null;" + name;
    else
    {
        if(type== "entier" || type == "reel" || type== "caractere" || type== "chaine" || type== "booleen")
         script = "var " + name + " = Algorithm." + type +"("+get_valtype(type) + ");" + Ram->setLocation(name,type) + name+";";
        else
         script = "var " + name + " = " + type +"();" + Ram->setLocation(name,type) + ";"+name+";";
    }
    return context->engine()->evaluate(script);
}

QScriptValue Allouer(QScriptContext * context,QScriptEngine * engine)
{
    int location  = context->argument(0).toString().toInt();
    if(!Ram->islocated(location))
        return engine->evaluate("throw 'Invalid paramtre passed to Allouer():the Pointer for allocation is not declarated';");
    QString type = Ram->get_type_ofvar(location);
    if(type == "")
        return engine->evaluate("throw 'not defined type of this Pointer '");
    if(type.mid(0,1) != "@")
        return engine->evaluate("throw ' Can not Allocate a not Pointer variable';");
    return engine->evaluate("var Pointer = new Array();Pointer.id = " + QString::number(location) + ";Pointer.value = Algorithm.declarer('Pointer','"+type.remove(0,1)+"');Pointer;");
}

//---------------------------------------------------------------------------------------------

QScriptValue affectePoiners(QScriptContext * context,QScriptEngine * engine)
{
    if(!Ram->islocated(context->argument(0).toString().toInt()))
        return engine->evaluate("throw ' Pointer 1 is Not located';");
    if(!Ram->islocated(context->argument(1).toString().toInt()))
        return engine->evaluate("throw ' Pointer 2 is Not located';");
    if(Ram->get_type_ofvar(context->argument(0).toString().toInt()) == Ram->get_type_ofvar(context->argument(1).toString().toInt()))
        return context->argument(2);
    else
        return engine->evaluate("throw 'No convertion type Pointers " + Ram->get_type_ofvar(context->argument(0).toString().toInt()) + " to " + Ram->get_type_ofvar(context->argument(1).toString().toInt())+ "';") ;
}

QScriptValue affecteSimleVars(QScriptContext * context,QScriptEngine * engine)
{
    if(context->argument(2).isError() || context->argument(2).isUndefined() || context->argument(2).isNull())
    {
        return engine->evaluate("throw 'Invalude value to affecte .the value my be undefined or Null or a Erreur'");
    }
    if(!Ram->islocated(context->argument(0).toString().toInt()))
        return engine->evaluate("throw 'the varaible to be affect is not declarated';");

    QString type = Ram->get_type_ofvar(context->argument(0).toString().toInt());if(type == "")return engine->evaluate("throw 'No knowen type of the varaible for affecte';");
    QString valeur = context->argument(2).toString();
    if(!context->argument(1).isNull())
    {
        QString typeval = Ram->get_type_ofvar(context->argument(1).toString().toInt());
        if(typeval == "")return engine->evaluate("throw 'Type Value is not defined'");
        if(type == "entier")
            {
                if(typeval == "entier")
                    return engine->evaluate("var v = Algorithm.entier(" + valeur + ");v.id = " + context->argument(0).toString() + ";v");
                else
                    return engine->evaluate("throw 'No convertion type [" + typeval + "] to entier';");
             }
                if(type == "reel")
                {
                    if(typeval == "reel")
                        return engine->evaluate("var v = Algorithm.reel(" + valeur + ");v.id = " + context->argument(0).toString() + ";v");
                    else
                        return engine->evaluate("throw 'No convertion type [" + typeval + "] to reel';");
                }
                       else
                            if(type == "caractere")
                            {
                                if(typeval == "caractere")
                                  return engine->evaluate("var v = Algorithm.caractere('" + valeur + "');v.id = " + context->argument(0).toString() + ";v");
                                else
                                    return engine->evaluate("throw 'No convertion type [" + typeval + "] to caractere';");
                            }
                                else
                                    if(type == "chaine")
                                    {
                                        if(typeval == "chaine")
                                            return engine->evaluate("var v = Algorithm.chaine('" + valeur + "');v.id = " + context->argument(0).toString() + ";v");
                                        else
                                            return engine->evaluate("throw 'No convertion type [" + typeval + "] to chaine';");
                                    }
                                        else
                                            if(type == "booleen")
                                            {
                                                if(typeval == "booleen")
                                                   return engine->evaluate("var v = Algorithm.booleen(" + valeur + ");v.id = " + context->argument(0).toString() + ";v");
                                                else
                                                    return engine->evaluate("throw 'No convertion type [" + typeval + "] to booleen';");
                                            }
                                           else

                                             return engine->evaluate("throw 'Can not affecte variable of the type :"+ type +"';");


    }

    if(type == "entier")
        {
            if(typeOfValue(context->argument(2)) == "entier")
                return engine->evaluate("var v = Algorithm.entier(" + valeur + ");v.id = " + context->argument(0).toString() + ";v");
            else
                return engine->evaluate("throw 'No convertion type [" + typeOfValue(context->argument(2)) + "] to entier';");
         }
            if(type == "reel")
            {
                if(typeOfValue(context->argument(2)) == "reel" ||typeOfValue(context->argument(2)) == "entier" )
                    return engine->evaluate("var v = Algorithm.reel(" + valeur + ");v.id = " + context->argument(0).toString() + ";v");
                else
                    return engine->evaluate("throw 'No convertion type [" + typeOfValue(context->argument(2)) + "] to reel';");
            }
                   else
                        if(type == "caractere")
                        {
                            if(typeOfValue(context->argument(2)) == "caractere")
                              return engine->evaluate("var v = Algorithm.caractere('" + valeur + "');v.id = " + context->argument(0).toString() + ";v");
                            else
                                return engine->evaluate("throw 'No convertion type [" + typeOfValue(context->argument(2)) + "] to caractere';");
                        }
                            else
                                if(type == "chaine")
                                {
                                    if(typeOfValue(context->argument(2)) == "chaine" || context->argument(2).toString().length() <= 1)
                                        return engine->evaluate("var v = Algorithm.chaine('" + valeur + "');v.id = " + context->argument(0).toString() + ";v");
                                    else
                                        return engine->evaluate("throw 'No convertion type [" + typeOfValue(context->argument(2)) + "] to chaine';");
                                }
                                    else
                                        if(type == "booleen")
                                        {
                                            if(typeOfValue(context->argument(2)) == "booleen")
                                               return engine->evaluate("var v = Algorithm.booleen(" + valeur + ");v.id = " + context->argument(0).toString() + ";v");
                                            else
                                                return engine->evaluate("throw 'No convertion type [" + typeOfValue(context->argument(2)) + "] to booleen';");
                                        }
                                       else

                                         return engine->evaluate("throw 'Can not affecte variable of the type :"+ typeOfValue(context->argument(2))+"';");
     }

QScriptValue procedure(QScriptContext *context,QScriptEngine * engine)
{   QScriptValue p;
    if(context->argument(0).toBool())
    {
        if(!listeparas.isEmpty())
        {
            p = listeparas.at(0);
            listeparas.removeAt(0);
            //qDebug()<<" return"<<p.toString();
            return p;
        }
        else
            {
              engine->evaluate("throw 'Erreur dans procedure';");
            }
    }else
    {
        listeparas.append(context->argument(1));
        //qDebug()<<"appended"<<listeparas.at(listeparas.count()-1).toString();
    }
}

// --------------------------------- PROCEDURES ALGO + -----------------------------------------

QScriptValue Ecrire(QScriptContext * contexte,QScriptEngine * engine)
{
    QString message = contexte->argument(0).toString();
    if(contexte->argument(0).isArray())
        return engine->evaluate("throw 'Can not show a Pointer varaiable';");
    else
        if(contexte->argument(0).isUndefined())
            return engine->evaluate("throw 'No deffinition value [" + contexte->argument(0).toString() + "] to show';");
    else
        if(contexte->argument(0).isBool())
        {
            if(contexte->argument(0).toString() == "true")
                message = "VRAI";
            else
                message = "FAUX";
        }
    while (message.contains(',')) {
        message.remove(',');
    }
    emit This->SentMessage("Ecrire : " + message ,true,QColor(255,255,255));
    return 0;
}

QScriptValue Lire(QScriptContext *context, QScriptEngine *engine)
{
    if(context->argument(0).isUndefined() || !Ram->islocated(context->argument(0).toString().toInt()))
        return engine->evaluate("throw 'Not declarated or allocated variable input '");
    //qDebug()<<"Vous etez en lecture id = "<<context->argument(0).toString()<<" var"<< Ram->get_name_ofvar(context->argument(0).toString().toInt())<<"->";

    emit This->GetInput(context->argument(1).toString(),true);
    //qDebug()<<context->argument(1).toString();
    input = "";
    while (input == "") {

    }
    QString type = Ram->get_type_ofvar(context->argument(0).toString().toInt());
    if(type == "")
        return engine->evaluate("throw 'not founed type of varaible for input';");

    if(type == "entier")
    {
        bool ok;
        int res = input.toInt(&ok);
        if(ok)
            return engine->evaluate("var v = Algorithm.entier("+input+");v.id = " + context->argument(0).toString() + ";v;");
        else
            return engine->evaluate("throw 'Invalid input for the Integer variable';");
    }
    else
        if(type == "reel")
        {
            bool ok;
            int res = input.toFloat(&ok);
            if(ok)
            {
                if(input.contains('.'))
                    return engine->evaluate("var v = Algorithm.reel("+input+");v.id = " + context->argument(0).toString() + ";v;");
                else
                    return engine->evaluate("var v = Algorithm.reel("+input+".01);v.id = " + context->argument(0).toString() + ";v;");
            }
            else
                return engine->evaluate("throw 'Invalid input for the float variable';");


        }
    else
        if(type == "chaine")
            return engine->evaluate("var v = Algorithm.chaine('"+ input + "');v.id = " + context->argument(0).toString() + ";v;");
    else
        if(type == "caractere")
            if(input.length() > 1)
            {
                return engine->evaluate("throw 'input Erreur : no convertion string to char'");
            }
            else
                return engine->evaluate("var v = Algorithm.caractere('"+ input + "');v.id = " + context->argument(0).toString() + ";v;");
    else
        if(type == "booleen")
            if(input.toUpper() == "VRAI")
                return engine->evaluate("var v = Algorithm.booleen(true);v.id = " + context->argument(0).toString() + ";v;");
        else if(input.toUpper() == "FAUX")
                return engine->evaluate("var v = Algorithm.booleen(false);v.id = " + context->argument(0).toString() + ";v;");
        else
            {
                return engine->evaluate("throw 'invalide input for the booleen variable'");
            }
    else
        {
            return engine->evaluate("'the type of this variable is enable for to input him'");
        }
}

/////////////////////////// PROCEDURES PREDIFINIT DE L ALGORITHM ////////////////////////////

bool estChaineOUCaractere(QScriptValue valeur)
{
    if(typeOfValue(valeur) == "chaine" || typeOfValue(valeur) == "caractere")
        return true;
    else
        return false;
}


QScriptValue Proc_Efface(QScriptContext * context,QScriptEngine * engine)
{
    bool ok = true;
    int pi = context->argument(1).toString().toInt(&ok),pf = context->argument(2).toString().toInt(&ok);
    if(!ok)
        return engine->evaluate("throw 'Erreur :Procedure Efface(var ch : chaine,pi,pf : entier) -> Un erreur a éte produit';");
    if(pi <= pf)
       return context->argument(0).toString().remove(pi,pf-pi);
    else
       return context->argument(0).toString();
}

QScriptValue Proc_inserer(QScriptContext * context,QScriptEngine * engine)
{

    QString ch1 = context->argument(0).toString(),ch2 = context->argument(1).toString();
    int p = context->argument(2).toString().toInt();
     if(p <= ch2.length())
        return engine->toScriptValue(ch2.insert(p,ch1));
     else
       return engine->toScriptValue(ch2);
}

QScriptValue Proc_concat(QScriptContext * context,QScriptEngine * engine)
{
    QString res = "";
  for(int i = 0; i < context->argumentCount() && !context->argument(i).isUndefined();i++)
      res += context->argument(i).toString();
  return res;
}

QScriptValue Proc_convch(QScriptContext * context,QScriptEngine * engine)
{
  return engine->toScriptValue(context->argument(1).toString());
}

QScriptValue Proc_valeur(QScriptContext * context,QScriptEngine * engine)
{
  bool ok;
  int res = context->argument(0).toString().toInt(&ok);
  if(ok)
  {
      if(context->argumentCount() == 3)
          return engine->evaluate("var a = new Object();a.e = true;a.N = " + QString::number(res) + ";a");
      else
          return engine->toScriptValue(res);
  }else
  {
      if(context->argumentCount() == 3)
          return engine->evaluate("var a = new Object();a.e = false;a.N = " + QString::number(res) + ";a");
      else
          return engine->toScriptValue(res);
  }
}

QScriptValue Proc_associer(QScriptContext * context,QScriptEngine * engine)
{
    if(context->argumentCount() != 2)
        engine->evaluate("throw ' Invalide parametres passeé a la procedure associer(f,ch)';");
    if(!Ram->islocated(context->argument(0).toString().toInt()))
        return engine->evaluate("throw 'Le pametre f de la procedure associer(f,ch) n est pas encore decalrer';");
    if(!Ram->islocatedAsFile(context->argument(0).toString().toInt()))
        return engine->evaluate("throw ' Le parametre f passee a la procdedure associer(f,ch) ne correspand pas a une Fichier");
    if(estChaineOUCaractere(context->argument(1)))
        return engine->evaluate("throw ' le parametre ch passe a la procedure associer(f,ch) ne correspand pas a une chaine");
    QDir *test = new QDir(context->argument(1).toString());
    if(!test->isReadable())
        return engine->evaluate("throw 'Le nom associer a la fichier passee en parametre de la procedure assecier(f,ch) n existe pas en votre';");
    if(Ram->getFileByLocation(context->argument(0).toString().toInt()))
    {
        Ram->getFileByLocation(context->argument(0).toString().toInt())->setFileName(context->argument(1).toString());
    }
  return "1";
}


QScriptValue Proc_ouvrir(QScriptContext * context,QScriptEngine * engine)
{
    if(context->argumentCount() != 2 && context->argumentCount() != 3)
        return engine->evaluate("throw 'Invalide paraùetres passee a la procedure ouvrir(f,Mode)';");
    if(!Ram->islocated(context->argument(0).toString().toInt()))
        return engine->evaluate("throw 'not loc';");
    if(!Ram->islocatedAsFile(context->argument(0).toString().toInt()))
        return engine->evaluate("throw 'pa';");
    //if(context->argumentCount() == 3)

    //return engine->evaluate("throw 'Invalide Mode d ouverture de la fichier en la procedure ouvrir(f,Mode)';");

    Ram->getFileByLocation(context->argument(0).toString().toInt())->open(QIODevice::ReadWrite);
    return "";
}


QScriptValue Proc_fermer(QScriptContext * context,QScriptEngine * engine)
{
    if(context->argumentCount() != 1)
        return engine->evaluate("throw 'invalide parametres passee a procedure fermer(f)';");
    if(!Ram->islocated(context->argument(1).toString().toInt()))
        return engine->evaluate("throw 'procedure fermer(f) : parametre f non decalrer';");
    if(!Ram->islocatedAsFile(context->argument(0).toString().toInt()))
        return engine->evaluate("throw 'Procedure fermer(f) : parametre f ne correspand pas a une fichier';");
    Ram->getFileByLocation(context->argument(0).toString().toInt())->close();
    return "";
}

/////////////////////////// FONCTIONS PREDIFINIT DE L ALGORITHM ////////////////////////////

QScriptValue FN_Long(QScriptContext * context,QScriptEngine * engine)
{
   return context->argument(0).toString().length();
}


QScriptValue FN_Souschaine(QScriptContext * context,QScriptEngine * engine)
{
    QString ch = context->argument(0).toString();
    bool ok;
    int pi = context->argument(1).toString().toInt(&ok),pf = context->argument(2).toString().toInt(&ok);
    if(!ok)
        return engine->evaluate("throw 'Erreur : fonction Sous_chaine(var ch : chaine,pi,pf : entier) : chaine -> Un erreur a éte produit';");
    if(pi <= pf)
        return engine->toScriptValue(ch.mid(pi,pf-pi));
    else
        return "";
}


QScriptValue FN_Pos(QScriptContext * context,QScriptEngine * engine)
{
    return context->argument(1).toString().indexOf(context->argument(0).toString());
}

QScriptValue FN_Carre(QScriptContext * context,QScriptEngine * engine)
{
    if(context->argument(1).toString() == "entier")
        return context->argument(0).toString().toInt() * context->argument(0).toString().toInt();
    else
        if(context->argument(1).toString() == "reel")
           return context->argument(0).toString().toFloat() * context->argument(0).toString().toFloat();
    else
        return engine->evaluate("throw 'Fonction Carre(N : entier/reel) : entier/reel -> Un erreur a éte produit';");
}

QScriptValue FN_Racine(QScriptContext * context,QScriptEngine * engine)
{
     bool ok;
     float x = context->argument(0).toString().toFloat(&ok);
     if(!ok)
         return engine->evaluate("throw 'Erreur : Fonction Racine(N : entier/reel) : entier/reel -> Un erreur a ete produit';");
     x = sqrt(x);
     for(int i = 1; i < context->argument(1).toString().toInt();i++)
         x = sqrt(x);
     return x;
}

QScriptValue FN_Tronque(QScriptContext * context,QScriptEngine * engine)
{
    bool ok;int r ;
    QString X = context->argument(0).toString();
    if(X.contains('.'))
    {
        r = X.mid(0,X.indexOf('.')).toInt(&ok);
        if(ok)
            return r;
        else
            return engine->evaluate("throw 'Erreur : Fonction Tronque(R : reel) : entier -> Un erreur a éte produit';");
    }
    r =  X.toInt(&ok);
    if(ok)
        return r;
    else
        return engine->evaluate("throw 'Erreur : Fonction Tronque(R : reel) : entier -> Un erreur a éte produit';");

}

QScriptValue FN_Abs(QScriptContext * context,QScriptEngine * engine)
{
    QString X = context->argument(0).toString();
    if(X.at(0) == '-')
        X = X.remove(0,1);
    if(context->argument(1).toString() == "entier")
        return X.toInt();
    else
        if(context->argument(1).toString() == "reel")
            return X.toFloat();
    else
            return engine->evaluate("throw 'Erreur  : fonction Abs(N : entier/reel) : entier/reel -> Un erreur a éte produit';");
}

QScriptValue FN_Entiere(QScriptContext * context,QScriptEngine * engine)
{
    QString X = context->argument(0).toString();
    if(X.contains("."))
        return (X.mid(0,X.indexOf('.')) + ".00").toFloat();
    else
        return engine->evaluate("throw 'fonction Entiere(R : reel): reel -> Un erreur a éte produit';");
}

QScriptValue FN_Frac(QScriptContext * context,QScriptEngine * engine)
{
    QString X = context->argument(0).toString();
    if(X.contains("."))
        return ("0" + X.mid(X.indexOf('.'),-1)).toFloat();
    else
        return engine->evaluate("throw 'fonction Frac(R : reel): reel -> Un erreur a éte produit';");
}

QScriptValue FN_Puissance(QScriptContext * context,QScriptEngine * engine)
{
    bool ok;
    int a = context->argument(0).toString().toInt(&ok);
    if(!ok)
        return engine->evaluate("throw 'Erreur : fonction Puissance(A,B : entier) : entier -> Un erreur a éte produit (1)';");
    int b = context->argument(1).toString().toInt(&ok);
    if(!ok)
        return engine->evaluate("throw 'Erreur : fonction Puissance(A,B : entier) : entier -> Un erreur a éte produit (2)';");
    else
    {
        int P = a;
        for(int i  = 1; i < b;i++)
             P = P*a;
        return P;
    }
}

QScriptValue FN_Sin(QScriptContext * context,QScriptEngine * engine)
{
    bool ok = true;
    QScriptValue res = sin(context->argument(0).toString().toDouble(&ok));
    if(!ok)
        return engine->evaluate("throw 'Erreur : fonction Sin(R : reel) : reel -> Un erreur a éte produit';");
    else
        return res.toString().toFloat();
}


QScriptValue FN_Cos(QScriptContext * context,QScriptEngine * engine)
{
    bool ok = true;
    QScriptValue res = cos(context->argument(0).toString().toDouble(&ok));
    if(!ok)
        return engine->evaluate("throw 'Erreur : fonction Cos(R : reel) : reel -> Un erreur a éte produit';");
    else
        return res.toString().toFloat();
}


QScriptValue FN_Tan(QScriptContext * context,QScriptEngine * engine)
{
    bool ok = true;
    QScriptValue res = tan(context->argument(0).toString().toDouble(&ok));
    if(!ok)
        return engine->evaluate("throw 'Erreur : fonction Tan(R : reel) : reel -> Un erreur a éte produit';");
    else
        return res.toString().toFloat();

}


QScriptValue FN_Arcsin(QScriptContext * context,QScriptEngine * engine)
{
    bool ok = true;
    QScriptValue res = asin(context->argument(0).toString().toDouble(&ok));
    if(!ok)
        return engine->evaluate("throw 'Erreur : fonction Arcsin(R : reel) : reel -> Un erreur a éte produit';");
    else
        return res.toString().toFloat();
}


// _____________________________________________________________________________________________________________________________
void setup_functions(QScriptEngine * curentEngine)
{

    curentEngine->globalObject().setProperty("Ecrire",curentEngine->newFunction(Ecrire));

    curentEngine->globalObject().setProperty("Lire",curentEngine->newFunction(Lire));

    curentEngine->globalObject().setProperty("declarer",curentEngine->newFunction(declarer));

    curentEngine->globalObject().setProperty("entier",curentEngine->newFunction(entier));

    curentEngine->globalObject().setProperty("reel",curentEngine->newFunction(reel));

    curentEngine->globalObject().setProperty("chaine",curentEngine->newFunction(chaine));

    curentEngine->globalObject().setProperty("caractere",curentEngine->newFunction(caractere));

    curentEngine->globalObject().setProperty("booleen",curentEngine->newFunction(booleen));

    curentEngine->globalObject().setProperty("procedure",curentEngine->newFunction(procedure));

    curentEngine->globalObject().setProperty("isPointer",curentEngine->newFunction(isPointer));

    curentEngine->globalObject().setProperty("affectePoiners",curentEngine->newFunction(affectePoiners));

    curentEngine->globalObject().setProperty("affecteSimleVars",curentEngine->newFunction(affecteSimleVars));

    curentEngine->globalObject().setProperty("isVar",curentEngine->newFunction(isVar));

    curentEngine->globalObject().setProperty("Allouer",curentEngine->newFunction(Allouer));
    // -----------------------

    curentEngine->globalObject().setProperty("estAllouer",curentEngine->newFunction(estAllouer));

    curentEngine->globalObject().setProperty("gettypeOfvar",curentEngine->newFunction(gettypeOfvar));

    curentEngine->globalObject().setProperty("gettypeOfValue",curentEngine->newFunction(gettypeOfValue));

    //*************************** LES PROCEDURE PREDIFINIT ALGO+ *************************

    curentEngine->globalObject().setProperty("Proc_efface",curentEngine->newFunction(Proc_Efface));
    curentEngine->globalObject().setProperty("Proc_inserer",curentEngine->newFunction(Proc_inserer));
    curentEngine->globalObject().setProperty("Proc_concat",curentEngine->newFunction(Proc_concat));
    curentEngine->globalObject().setProperty("Proc_convch",curentEngine->newFunction(Proc_convch));
    curentEngine->globalObject().setProperty("Proc_valeur",curentEngine->newFunction(Proc_valeur));
    curentEngine->globalObject().setProperty("Proc_associer",curentEngine->newFunction(Proc_associer));
    curentEngine->globalObject().setProperty("Proc_ouvrir",curentEngine->newFunction(Proc_ouvrir));
    curentEngine->globalObject().setProperty("Proc_fermer",curentEngine->newFunction(Proc_fermer));

    // ************************ LES FONCTIONS PRDEFFINIT ALGO+ *****************************
    curentEngine->globalObject().setProperty("FN_Long",curentEngine->newFunction(FN_Long));
    curentEngine->globalObject().setProperty("FN_Souschaine",curentEngine->newFunction(FN_Souschaine));
    curentEngine->globalObject().setProperty("FN_Carre",curentEngine->newFunction(FN_Carre));
    curentEngine->globalObject().setProperty("FN_Racine",curentEngine->newFunction(FN_Racine));
    curentEngine->globalObject().setProperty("FN_Tronque",curentEngine->newFunction(FN_Tronque));
    curentEngine->globalObject().setProperty("FN_Abs",curentEngine->newFunction(FN_Abs));
    curentEngine->globalObject().setProperty("FN_Entiere",curentEngine->newFunction(FN_Entiere));
    curentEngine->globalObject().setProperty("FN_Frac",curentEngine->newFunction(FN_Frac));
    curentEngine->globalObject().setProperty("FN_Sin",curentEngine->newFunction(FN_Sin));
    curentEngine->globalObject().setProperty("FN_Cos",curentEngine->newFunction(FN_Cos));
    curentEngine->globalObject().setProperty("FN_Tan",curentEngine->newFunction(FN_Tan));
    //curentEngine->globalObject().setProperty("FN_Arcsin",curentEngine->newFunction(FN_Arcsin));
    curentEngine->globalObject().setProperty("FN_Puissance",curentEngine->newFunction(FN_Puissance));

}


void Executer::run()
{
    try
    {
        engine = new QScriptEngine();
        // ----------- SETUPS ----------------------------//
        setup_functions(engine);
        //------------------------------------------------//
        engine->evaluate(Input_program);
        if(engine->hasUncaughtException())
        {
            QMessageBox::warning(0,"Erreur",QString::number(engine->uncaughtExceptionLineNumber()) + ":->" + engine->uncaughtException().toString(),QMessageBox::Ok);
        }
    }catch(std::exception e)
    {
        QMessageBox::warning(0,"Erreur","Erreur se produise " + QString(e.what()),QMessageBox::Ok);
    }
}


void Executer::change_input(const QString Input)
{
    input = Input;
}


QString Executer::police_thread()
{
    while (input == "") {
        this->msleep(50);
    }
    return input;
}

//------------------------------   TESTES -----------------------------------------//



QDomDocument Executer::reload_RAM()
{
    return Ram->memoire;
}

//---------------------------------------------------------------------------------//
