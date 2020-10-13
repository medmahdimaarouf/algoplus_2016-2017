#ifndef DECLARATIONCONST_H
#define DECLARATIONCONST_H

#include <QDialog>

namespace Ui {
class DeclarationConst;
}

class DeclarationConst : public QDialog
{
    Q_OBJECT

public:
    explicit DeclarationConst(QWidget *parent = 0);
    ~DeclarationConst();

private:
    Ui::DeclarationConst *ui;
};

#endif // DECLARATIONCONST_H
