#ifndef AFFECTATION_H
#define AFFECTATION_H

#include <QDialog>

namespace Ui {
class Affectation;
}

class Affectation : public QDialog
{
    Q_OBJECT

public:
    explicit Affectation(QWidget *parent = 0);
    ~Affectation();

private:
    Ui::Affectation *ui;
};

#endif // AFFECTATION_H
