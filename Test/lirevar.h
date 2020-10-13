#ifndef LIREVAR_H
#define LIREVAR_H

#include <QDialog>

namespace Ui {
class LireVar;
}

class LireVar : public QDialog
{
    Q_OBJECT

public:
    explicit LireVar(QWidget *parent = 0);
    ~LireVar();

private:
    Ui::LireVar *ui;
};

#endif // LIREVAR_H
