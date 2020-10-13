#ifndef POURFAIRE_H
#define POURFAIRE_H

#include <QDialog>

namespace Ui {
class Pourfaire;
}

class Pourfaire : public QDialog
{
    Q_OBJECT

public:
    explicit Pourfaire(QWidget *parent = 0);
    ~Pourfaire();

private:
    Ui::Pourfaire *ui;
};

#endif // POURFAIRE_H
