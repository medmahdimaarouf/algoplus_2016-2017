#ifndef TANTEQUEFAIRE_H
#define TANTEQUEFAIRE_H

#include <QDialog>

namespace Ui {
class TantequeFaire;
}

class TantequeFaire : public QDialog
{
    Q_OBJECT

public:
    explicit TantequeFaire(QWidget *parent = 0);
    ~TantequeFaire();

private:
    Ui::TantequeFaire *ui;
};

#endif // TANTEQUEFAIRE_H
