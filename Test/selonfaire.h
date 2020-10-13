#ifndef SELONFAIRE_H
#define SELONFAIRE_H

#include <QDialog>

namespace Ui {
class SelonFaire;
}

class SelonFaire : public QDialog
{
    Q_OBJECT

public:
    explicit SelonFaire(QWidget *parent = 0);
    ~SelonFaire();

private:
    Ui::SelonFaire *ui;
};

#endif // SELONFAIRE_H
