#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QtGui>
#include<QtCore>
#include<QDebug>
#include<QtXml>
#include<QProgressBar>

#include<Editeur_Arbre_Algorithme/editeur_arbre_algo.h>
#include<dialog_console.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Editeur_Arbre_Algo * EDT_Arbre_Algo;
private slots:

    void on_actionEnregistrer_triggered();

    void on_actionSupprimer_triggered();

    void on_actionEnregistrer_sous_triggered();

    void on_actionOuvrir_triggered();

    void on_actionNouveau_triggered();

    void on_actionQuitter_triggered();

    void on_actionAide_triggered();

    void on_actionExecuter_triggered();

    void on_actionModifier_triggered();

    void on_actionCopier_triggered();

    void on_actionColler_triggered();

    void on_actionCouper_triggered();

    void on_actionInserer_triggered();

    void on_actionAnnuler_triggered();

    void on_actionA_propot_Algo_triggered();

    void closeEvent(QCloseEvent * event);

    void on_actionOuvrir_un_exemple_triggered();

private:
    Ui::MainWindow *ui;
    QString nomFichier;
    Dialog_Console * Console;

};

#endif // MAINWINDOW_H
