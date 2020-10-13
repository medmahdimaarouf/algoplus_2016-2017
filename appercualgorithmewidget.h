#ifndef APPERCUALGORITHMEWIDGET_H
#define APPERCUALGORITHMEWIDGET_H

#include <QWidget>
#include<QTreeView>
#include<QTextEdit>
#include<QLabel>
#include<Editeur_Arbre_Algorithme/Gestionnaire_appercu/gestion_arbre_algo.h>
namespace Ui {
class AppercuAlgorithmeWidget;
}

class AppercuAlgorithmeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AppercuAlgorithmeWidget(QWidget *parent = 0);
    ~AppercuAlgorithmeWidget();
    QTreeView * TreeViewCodeAlgo;
    QTextEdit * TextEditDescAlgo;
    QLabel * labComDesc,*labComCode;
    Gestion_Arbre_Algo * ArbreAlgo;

private:
    Ui::AppercuAlgorithmeWidget *ui;
};

#endif // APPERCUALGORITHMEWIDGET_H
