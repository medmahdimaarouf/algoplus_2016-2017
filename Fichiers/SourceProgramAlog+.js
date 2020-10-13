NIL = null;
VRAI = true;
FAUX = false;

Algorithm = new Object();

// ***** PROCEDURES EXECUTION ALGO+***
Algorithm.compteur = new Number();
Algorithm.Compter = function()
{
  if (Algorithm.compteur >= 50) 
    throw "Erreur  : Un boucle infinit a ete produit";
  Algorithm.compteur++;
  
}
function estNIL(p)
{
    if(!Algorithm.isPointer(p))
       {
        if(Algorithm.isVar(p))
             throw "Erreur : Fonction estNulle(P : Pointeur) : booleen -> P ne s'agie pas d'un pointeur";
          else
             return
       }
    else
        return p.value == NIL;
}

Algorithm.ligne_Courant = new Number();
Algorithm.Lire = Lire;
Algorithm.Ecrire = Ecrire;
Algorithm.procedure = procedure;
Algorithm.entier = entier;
Algorithm.reel = reel;
Algorithm.chaine = chaine;
Algorithm.caractere = caractere;
Algorithm.booleen = booleen;
Algorithm.affectePoiners = affectePoiners;
Algorithm.affecteSimleVars = affecteSimleVars;
Algorithm.isPointer = isPointer;
Algorithm.isVar = isVar;
Algorithm.declarer = declarer;
Algorithm.Allouer = Allouer;
Algorithm.estAllouer = estAllouer;
Algorithm.gettypeOfvar = gettypeOfvar;
Algorithm.gettypeOfValue = gettypeOfValue;
//***** Proc def ***********

Algorithm.Proc_Efface = Proc_efface ;
Algorithm.Proc_Inserer = Proc_inserer ;
Algorithm.Proc_Concater = Proc_concat ;
Algorithm.Proc_Convch = Proc_convch ;
Algorithm.Proc_Valeur = Proc_valeur ;
Algorithm.Proc_Associer = Proc_associer ;
Algorithm.Proc_Ouvrir = Proc_ouvrir ;
Algorithm.Proc_Fermer = Proc_fermer ;

// ***** Fonctions predf ********

Algorithm.FN_Concater = Proc_concat;
Algorithm.FN_Long = FN_Long ;
Algorithm.FN_Sous_chaine = FN_Souschaine ;
Algorithm.FN_Carre = FN_Carre ;
Algorithm.FN_Racine = FN_Racine ;
Algorithm.FN_Tronque = FN_Tronque ;
Algorithm.FN_Abs = FN_Abs ;
Algorithm.FN_Entiere = FN_Entiere ;
Algorithm.FN_Frac = FN_Frac ;
Algorithm.FN_Sin = FN_Sin ;
Algorithm.FN_Cos = FN_Cos ;
Algorithm.FN_Tan = FN_Tan ;
Algorithm.FN_Puissance = FN_Puissance ;

Algorithm.Liberer = function(P)
{
  if(P.isPointer)
  {
    P.valeur = null; 
    return P;
  }
  else
    throw "Erreur : Procedure Liberer(var P : Pointeur) -> P ne s'agie pas d'un Pointeur";
}

Algorithm.affecter = function(v,val)
{
    if(Algorithm.isPointer(v))
        {

          if(Algorithm.isPointer(val))
           {
             v.value = Algorithm.affectePoiners(v.id,val.id,val.value);
             return v;
           }
           else
             if(val == null)
               {
                 v.value = null;
                 return v;
               }
             else
               throw "Erreur : Operation d'affectation -> Impossible d'affecter un variable a un poiteur";
        }
        else
            if(Algorithm.isVar(v))
            {
                if(Algorithm.isVar(val))
                      return Algorithm.affecteSimleVars(v.id,val.id,val);
                else
                      return Algorithm.affecteSimleVars(v.id,null,val);
             }
             else
                throw " Erreur  : Operation d'affectation -> Impossible d'affecter un valeur a une expression ou a un constante";
}
Algorithm.TypeOfValue  = function(valeur,car)
{
  Algorithm.fonction = valeur;var valeur = Algorithm.fonction;
  Algorithm.fonction = car;var car = Algorithm.fonction;

  if(valeur == undefined || valeur == null)
    throw "Erreur : OpÃ©ration de dÃ©tection de type d'un valeur ->valeur est nulle";

  if(Algorithm.isVar(valeur) || Algorithm.isPointer(valeur))
    return Algorithm.gettypeOfvar(valeur.id);
  else
    if(car != null && car != undefined)
      return Algorithm.gettypeOfValue(valeur,1);    
    else
      return Algorithm.gettypeOfValue(valeur);
}
Algorithm.TypeOfVariable = function(variable)
{
  Algorithm.fonction = variable;var variable = Algorithm.fonction;
  
  if(variable == undefined || variable == null)
    throw "Erreur : Opration de detection de type de variable ->variable est nulle";
  else
    if(Algorithm.isVar(variable) || Algorithm.isPointer(variable))
    {    
      if(Algorithm.estAllouer(variable.id))
        return Algorithm.gettypeOfvar(variable.id);
      else
        throw "Variable non Alloueer";
    }
    else
       return "constante";

}
// --------------------------------------------------------------- PROCEDURE PREDEINIT ALGO + ----------------------------------------------------------
Algorithm.Efface = function(ch,pi,pf)
{
    Algorithm.fonction = pi; var pi = Algorithm.fonction;
    Algorithm.fonction = pf; var pf = Algorithm.fonction;
    Algorithm.fonction = ch; var ch = Algorithm.fonction;
    
    if(Algorithm.TypeOfVariable(ch) != "chaine")
      throw "Erreur : procedure Efface(ch,pi,pf) -> Pas de convertion ch[" + Algorithm.TypeOfVariable(ch) + "] en une chaine";
    if(Algorithm.TypeOfValue(pi) != "entier")
      throw "Erreur : procedure Efface(ch,pi,pf) -> Pas de convertion pi[" + Algorithm.TypeOfValue(pi) + "] en un entier";
    if(Algorithm.TypeOfValue(pf) != "entier")
      throw "Erreur : procedure Efface(ch,pi,pf) -> Pas de convertion pf[" + Algorithm.TypeOfValue(pf) + "] en un entier";
    return Algorithm.Proc_Efface(ch,pi,pf);
}

Algorithm.Inserer = function(ch1,ch2,pos)
{
    Algorithm.fonction = ch1; var ch1 = Algorithm.fonction;
    Algorithm.fonction = ch2; var ch2 = Algorithm.fonction;
    Algorithm.fonction = pos; var pos = Algorithm.fonction;

    if(Algorithm.TypeOfValue(ch1) != "chaine")
      throw "Erreur : procedure Inserer(ch1,ch2,pos) -> Pas de convertion ch1[" + Algorithm.TypeOfValue(ch1) + "] en une chaine";
    if(Algorithm.TypeOfVariable(ch2) != "chaine")
      throw "Erreur : procedure Inserer(ch1,ch2,pos) -> Pas de convertion ch2[" + Algorithm.TypeOfVariable(ch2) + "] en une chaine";
    if(Algorithm.TypeOfValue(pos) != "entier")
      throw "Erreur : procedure Inserer(ch1,ch2,pos) -> Pas de convertion pos[" + Algorithm.TypeOfValue(pos) + "] en un entier";

    return Algorithm.Proc_Inserer(ch1,ch2,pos);
}
Algorithm.Convch = function(N,ch)
{
    Algorithm.fonction = N; var N = Algorithm.fonction;
    Algorithm.fonction = ch;var ch = Algorithm.fonction;

    if(Algorithm.TypeOfVariable(ch) != "chaine")
      throw "Erreur : procedure Convch(N,ch) -> Pas de convertion ch[" + Algorithm.TypeOfVariable(ch) + "] en une chaine";
    if(Algorithm.TypeOfValue(N) != "entier")
      throw "Erreur : procedure Convch(N,ch) -> Pas de convertion N[" + Algorithm.TypeOfValue(N) + "] en un entier";

    return Algorithm.Proc_Convch(N,ch);
}

Algorithm.Valeur = function(ch,N,e)
{
    Algorithm.fonction = ch; var ch = Algorithm.fonction;
    Algorithm.fonction = N; var N = Algorithm.fonction;
    Algorithm.fonction = e; var e = Algorithm.fonction;

    if(Algorithm.TypeOfValue(ch) != "chaine")
      throw "Erreur : procedure Valeur(ch,N,e) -> Pas de convertion ch[" + Algorithm.TypeOfValue(ch) + "] en une chaine";
    if(Algorithm.TypeOfVariable(N) != "entier")
      throw "Erreur : procedure Valeur(ch,N,e) -> Pas de convertion N[" + Algorithm.TypeOfVariable(N) + "] en un entier";
    if(e != undefined || e != null)
    {
      if(Algorithm.TypeOfVariable(e) != "booleen")
        throw "Erreur : procedure Valeur(ch,N,e) -> Pas de convertion e[" + Algorithm.TypeOfVariable(e) + "] en un booleen";
      else
        return Algorithm.Proc_Valeur(ch,N,e);
    }
    else
       return Algorithm.Proc_Valeur(ch,N);
}
Algorithm.Concater = function(ch,ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10)
{
  var tab = [ch,ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10];
  Algorithm.fonction = ch;var ch = Algorithm.fonction;

  if(Algorithm.TypeOfVariable(ch) != "chaine")
    throw "Erreur : procedure concate(ch..chN) N = 10 -> Pas de convertion ch[" + Algorithm.TypeOfVariable(ch) + "] en une chaine";

  for(var i = 1; i < tab.length && tab[i] != undefined && tab[i] != null;i++)
  {
    if(Algorithm.TypeOfValue(tab[i]) != "chaine")
      throw "Erreur : procedure concate(ch,ch1 .. chN) N = 10 -> Pas de convertion ch" + i + "[" + Algorithm.TypeOfValue(tab[i]) + "] en une chaine";
  }

  return Algorithm.Proc_Concater(ch,ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10);
}

//------------------------------------------------ LES FONCTION PREDIFINIT ALGO ET ALGO + -------------------------------------------------------------------//

//***************** LES CHAINES DE CARACTETRE ********************

function Concater(ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10) // Nchaine --> chaine 
{
  Algorithm.fonction = ch;var ch = Algorithm.fonction;
  var tab = ["",ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10];

    for(var i = 1; i < tab.length && tab[i] != undefined && tab[i] != null;i++)
    {
      if(Algorithm.TypeOfValue(tab[i]) != "chaine")
        throw "Erreur : fonction concate(ch1 .. chN : chaine) : chaine N <= 10 -> Pas de convertion ch" + i + "[" + Algorithm.TypeOfValue(tab[i]) + "] en une chaine";
    }
    return Algorithm.FN_Concater("",ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10);

}

function Long(ch)// chaine --> entier
{
  if(Algorithm.TypeOfValue(ch) == "chaine")
    return Algorithm.FN_Long(ch);
  else
    throw "Erreur : fonction Long(ch: chaine) : entier -> Pas de convertion ch[" + Algorithm.TypeOfValue(ch) + "] en une chaine";
}

function Sous_chaine(ch,pi,pf)
{
  if(Algorithm.TypeOfValue(ch) != "chaine")
        throw "Erreur : fonction Sous_chaine(ch: chaine,pi,pf : entier) : chaine -> Pas de convertion ch[" + Algorithm.TypeOfValue(ch) + "] en une chaine";
  if(Algorithm.TypeOfValue(pi) != "entier")
        throw "Erreur : fonction Sous_chaine(ch: chaine,pi,pf : entier) : chaine -> Pas de convertion pi[" + Algorithm.TypeOfValue(pi) + "] en un entier";
  if(Algorithm.TypeOfValue(pf) != "entier")
        throw "Erreur : fonction Sous_chaine(ch: chaine,pi,pf : entier) : chaine -> Pas de convertion pf[" + Algorithm.TypeOfValue(pf) + "] en un entier";
  return Algorithm.FN_Sous_chaine(ch,pi,pf);
}
function Pos(ch1,ch2) // chaine,chaine --> entier
{
  if(Algorithm.TypeOfValue(ch1) != "chaine")
    throw "Erreur : fonction Pos(ch1,ch2: chaine) : entier -> Pas de convertion ch1[" + Algorithm.TypeOfValue(ch1) + "] en une chaine";
  if(Algorithm.TypeOfValue(ch2))
    throw "Erreur : fonction Pos(ch1,ch2: chaine) : entier -> Pas de convertion ch2[" + Algorithm.TypeOfValue(ch2) + "] en une chaine";
  return Algorithm.FN_Pos(ch1,ch2);
}
// ************************ LES CARACTERES OU LES PARTIELLES DES CHAINES DE CARACTERE *******************
 function Ord(C)
 {
  Algorithm.fonction = C;var C  = Algorithm.fonction;
  if(Algorithm.TypeOfValue(C,1) == "caractere")
    return Algorithm.FN_Ord(C);
  else
    throw "Erreur : fonction Ord(C : caractere) : entier -> Pas de convertion C[" + Algorithm.TypeOfValue(C,1) + "] en un caractere";
 }

 function Car(N)
 {
  Algorithm.fonction = N;var N  = Algorithm.fonction;
  if(Algorithm.TypeOfValue(N) == "entier")
    return Algorithm.FN_Car(N);
  else
    throw "Erreur : fonction Car(N : entier) : caractere -> Pas de convertion N[" + Algorithm.TypeOfValue(N) + "] en un entier";

 }
function Succ(C)
{
  Algorithm.fonction = C;var C  = Algorithm.fonction;

  if(Algorithm.TypeOfValue(C,1) == "caractere")
    return Algorithm.FN_Succ(C);
  else
    throw "Erreur : fonction Succ(C : caractere) : caractere -> Pas de convertion C[" + Algorithm.TypeOfValue(C,1) + "] en un caractere";
 }

function Pred(C)
{
  Algorithm.fonction = C;var C  = Algorithm.fonction;

  if(Algorithm.TypeOfValue(C,1) == "caractere")
    return Algorithm.FN_Pred(C);
  else
    throw "Erreur : fonction Pred(C : caractere) : caractere -> Pas de convertion C[" + Algorithm.TypeOfValue(C,1) + "] en un caractere";
}

function Maj(L)
{
  Algorithm.fonction = L;var L = Algorithm.fonction;
  if(Algorithm.TypeOfValue(L,1) == "caractere")
    return Algorithm.FN_Maj(L);
  else
    throw "Erreur : fonction Maj(L : caractere) : caractere -> Pas de convertion L[" + Algorithm.TypeOfValue(L,1) + "] en un caractere";
}

function Min(L)
{
  Algorithm.fonction = L;var L = Algorithm.fonction;
  if(Algorithm.TypeOfValue(L,1) == "caractere")
    return Algorithm.FN_Min(L);
  else
    throw "Erreur : fonction Min(L : caractere) : caractere -> Pas de convertion L[" + Algorithm.TypeOfValue(L,1) + "] en un caractere";
}

// ********************************************************* LES TYPES ARITHMETIQUE ********************************
function Carre(N)// entier/reel --> entier/reel
{
  Algorithm.fonction = N;var N  = Algorithm.fonction;
  if(Algorithm.TypeOfValue(N) != "entier" && Algorithm.TypeOfValue(N) != "reel")
    throw "Erreur fonction Carre(N : entier/reel) : entier/reel -> Pas de convertion N[" + Algorithm.TypeOfValue(N) + "] en un entier";
  return Algorithm.FN_Carre(N,Algorithm.TypeOfValue(N));
  
}

function Racine(N,n) // entier/reel --> reel
{
  Algorithm.fonction = N; var N = Algorithm.fonction;
  Algorithm.fonction = n; var n = Algorithm.fonction;

  if (Algorithm.TypeOfValue(N) != "entier" && Algorithm.TypeOfValue(N) != "reel")
   throw "Erreur fonction Racie(N : entier/reel,n : entier) : reel avec n = 1 -> Pas de convertion N[" + Algorithm.TypeOfValue(N) + "] en un entier/reel";
  
  if(n == null || n == undefined)
      return Algorithm.FN_Racine(N,1);
   else
   {
    if(Algorithm.TypeOfValue(n) == "entier")
        return Algorithm.FN_Racine(N,n);
       else
        throw "Erreur : fonction Racine(N : entier,n : entier) : reel avec n = 1 -> Pas de convertion n[" + Algorithm.TypeOfValue(n) + "] en un entier";
   }    
}

function Tronque(R)
{
  Algorithm.fonction = R;var R = Algorithm.fonction;
  if(Algorithm.TypeOfValue(R) == "reel")
    return Algorithm.FN_Tronque(R);
  else
    throw "Erreur : fonction Tronque(R : reel) : entier -> Pas de convertion R[" + Algorithm.TypeOfValue(R) + "] en un reel";
}

function Arrondit(R,n) //n = 0
{
  Algorithm.fonction = R; var R  = Algorithm.fonction;
  Algorithm.fonction = n; var n = Algorithm.fonction;
  
  if(Algorithm.TypeOfValue(R) != "reel")
    throw "Erreur : fonction Arrondit(R : reel,n : entier) : entier avec n = 2 -> Pas de convertion R[" + Algorithm.TypeOfValue(R) + "] en un reel";
  if(n != null && n != undefined)
    {    
      if(Algorithm.TypeOfValue(n) == "entier")
        return Algorithm.FN_Arrondit(R,n);
      else
        throw "Erreur : fonction Arrondit(R : reel,n : entier) : reel avec n = 2 -> Pas de convertion n[" + Algorithm.TypeOfValue(n) + "] en un entier";
    } 
    else
        return Algorithm.FN_Arrondit(R,2);   
  
}

function Abs(N) // N est entier ou reel
{
  Algorithm.fonction = N; N  = Algorithm.fonction;
  if(Algorithm.TypeOfValue(N) == "entier" || Algorithm.TypeOfValue(N) == "reel")
    return Algorithm.FN_Abs(N,Algorithm.TypeOfValue(N));
    else
        throw "Erreur : fonction Abs(N : entier/reel): entier/reel -> Pas de convertion N[" + Algorithm.TypeOfValue(N) + "] en un entier/reel";

}

function Entiere(R) // reel -->reel 
{
  Algorithm.fonction = R;var R = Algorithm.fonction;
  if(Algorithm.TypeOfValue(R) == "reel")
    return Algorithm.FN_Entiere(R);
  else
    throw "Erreur : fonction Entiere(R : reel): reel -> Pas de convertion R[" + Algorithm.TypeOfValue(R) + "] en un reel";

}

function Frac(R) //reel --> reel
{
  Algorithm.fonction = R; R  = Algorithm.fonction;
  if(Algorithm.TypeOfValue(R) == "reel")
    return Algorithm.FN_Frac(R);
  else
    throw "Erreur : fonction Frac(R : reel): reel -> Pas de convertion R[" + Algorithm.TypeOfValue(R) + "] en un reel";
}

function Puissance(A,n)// entier,entier --> entier
{
  Algorithm.fonction = A; A = Algorithm.fonction;
  Algorithm.fonction = n; n = Algorithm.fonction;
  if(Algorithm.TypeOfValue(A) != "entier")
    throw "Erreur : fonction Puissance(A,n : entier): entier -> Pas de convertion A[" + Algorithm.TypeOfValue(A) + "] en un entier";
  if(Algorithm.TypeOfValue(n) != "entier")
    throw "Erreur : fonction Puissance(A,n : entier): entier -> Pas de convertion n[" + Algorithm.TypeOfValue(n) + "] en un entier";
  return Algorithm.FN_Puissance(A,n);
}

function Sin(R) // reel --> reel
{
  Algorithm.fonction = R;var R  = Algorithm.fonction;
  if(Algorithm.TypeOfValue(R) == "reel")
    return Algorithm.FN_Sin(R);
  else
    throw "Erreur : fonction Sin(R : reel) : reel -> Pas de convertion R[" + Algorithm.TypeOfValue(R) + "] en un reel";
}
function Cos(R)// reel --> reel
{
  Algorithm.fonction = R;var R  = Algorithm.fonction;
  if(Algorithm.TypeOfValue(R) == "reel")
    return Algorithm.FN_Cos(R);
  else
    throw "Erreur : fonction Cos(R : reel) : reel -> Pas de convertion R[" + Algorithm.TypeOfValue(R) + "] en un reel";
  
}

function Tan(R)// reel --> reel
{
  Algorithm.fonction = R;var R  = Algorithm.fonction;
  if(Algorithm.TypeOfValue(R) == "reel")
    return Algorithm.FN_Tan(R);
  else
    throw "Erreur : fonction Tan(R : reel) : reel -> Pas de convertion R[" + Algorithm.TypeOfValue(R) + "] en un reel";
  
}

delete Lire;
delete Ecrire;
delete entier;
delete reel;
delete chaine;
delete caractere;
delete booleen;
delete affectePoiners;
delete affecteSimleVars;
delete isPointer;
delete isVar;
delete declarer;
delete Allouer;
delete estAllouer;
delete gettypeOfvar;
delete gettypeOfValue;
//***** Proc def ***********
delete Proc_Efface ;
delete Proc_inserer ;
delete Proc_concat ;
delete Proc_convch ;
delete Proc_valeur ;
delete Proc_associer ;
delete Proc_ouvrir ;
delete Proc_fermer ;

// ***** Fonctions predf ********
 
delete Proc_Concate;
delete FN_Long ;
delete FN_Souschaine ;
delete FN_Carre ;
delete FN_Racine ;
delete FN_Tronque ;
delete FN_Abs ;
delete FN_Entiere ;
delete FN_Frac ;
delete FN_Sin ;
delete FN_Cos ;
delete FN_Tan ;
delete FN_Puissance ;
Algorithm.chaine = function(ch)
{var t = [];
  for(var i = 0; i < ch.length;i++)
	t[i] = ch.charAt(i);
 return t;
}
Algorithm.Ecrire("************ Debut Algorithm ***************");
