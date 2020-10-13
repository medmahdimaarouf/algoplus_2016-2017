#ifndef VECTEUR_H
#define VECTEUR_H

#include <QDialog>

namespace Ui {
class Vecteur;
}

class Vecteur : public QDialog
{
    Q_OBJECT

public:
    explicit Vecteur(QWidget *parent = 0);
    ~Vecteur();

private:
    Ui::Vecteur *ui;
};

#endif // VECTEUR_H
