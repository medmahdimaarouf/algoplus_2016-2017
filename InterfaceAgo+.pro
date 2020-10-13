#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T00:56:16
#
#-------------------------------------------------

QT       += core gui xml script webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterfaceAgo+
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Editeur_Arbre_Algorithme/editeur_arbre_algo.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_affecation.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_champ_parametre.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_const.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_enregistrement.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_fichiers.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_matrice.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_procedure.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_variable.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_vecteur.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_lire_variable.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_pour_faire.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_repeter_jusqua.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_selon_faire.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_si_sinon.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_tanteque_faire.cpp \
    Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.cpp \
    Editeur_Arbre_Algorithme/Gestionnaire_appercu/get_appercu.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_ecrire.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_appelle_procedure.cpp \
    dialog_console.cpp \
    Compilateur_Algo+/compilateur.cpp \
    Compilateur_Algo+/executer.cpp \
    Compilateur_Algo+/maker_output_program.cpp \
    Compilateur_Algo+/memoire.cpp \
    Console/consolewidget.cpp \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_retournefn.cpp \
    appercualgorithmewidget.cpp


HEADERS  += mainwindow.h \
    Editeur_Arbre_Algorithme/editeur_arbre_algo.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_affecation.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_champ_parametre.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_const.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_enregistrement.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_fichiers.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_matrice.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_procedure.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_variable.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_vecteur.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_lire_variable.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_pour_faire.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_repeter_jusqua.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_selon_faire.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_si_sinon.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_tanteque_faire.h \
    Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h \
    Editeur_Arbre_Algorithme/Gestionnaire_appercu/get_appercu.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_ecrire.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_appelle_procedure.h \
    dialog_console.h \
    Compilateur_Algo+/compilateur.h \
    Compilateur_Algo+/executer.h \
    Compilateur_Algo+/maker_output_program.h \
    Compilateur_Algo+/memoire.h \
    Console/consolewidget.h \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_retournefn.h \
    appercualgorithmewidget.h

FORMS    += mainwindow.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_affecation.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_champ_parametre.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_const.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_enregistrement.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_fichiers.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_matrice.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_procedure.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_variable.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_declaration_vecteur.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_lire_variable.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_pour_faire.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_repeter_jusqua.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_selon_faire.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_si_sinon.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_tanteque_faire.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_affecation.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_ecrire.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_appelle_procedure.ui \
    dialog_console.ui \
    Editeur_Arbre_Algorithme/Dialogs_Editeur/dialog_retournefn.ui \
    appercualgorithmewidget.ui

RESOURCES += \
    Source.qrc

OTHER_FILES += \
    Text.txt
win32{
RC_FILE = winAlgoP.rc
}
