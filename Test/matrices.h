#ifndef MATRICES_H
#define MATRICES_H

#include <QDialog>

namespace Ui {
class Matrices;
}

class Matrices : public QDialog
{
    Q_OBJECT

public:
    explicit Matrices(QWidget *parent = 0);
    ~Matrices();

private:
    Ui::Matrices *ui;
};

#endif // MATRICES_H
