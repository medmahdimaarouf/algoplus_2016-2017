#ifndef COMMENTAIRE_H
#define COMMENTAIRE_H

#include <QDialog>

namespace Ui {
class Commentaire;
}

class Commentaire : public QDialog
{
    Q_OBJECT

public:
    explicit Commentaire(QWidget *parent = 0);
    ~Commentaire();

private:
    Ui::Commentaire *ui;
};

#endif // COMMENTAIRE_H
