#ifndef DIALOG_CONSOLE_H
#define DIALOG_CONSOLE_H

#include <QDialog>
#include<Compilateur_Algo+/compilateur.h>
#include<Console/consolewidget.h>
namespace Ui {
class Dialog_Console;
}

class Dialog_Console : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Console(QWidget *parent, QDomDocument Source_ProgramAlgo);
    ~Dialog_Console();
    Compilateur * compilateur;
private slots:
    void on_actionaffichage_d_triggered();

private:
    Ui::Dialog_Console *ui;
};

#endif // DIALOG_CONSOLE_H
