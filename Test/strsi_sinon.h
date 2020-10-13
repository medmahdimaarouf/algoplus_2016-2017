#ifndef STRSI_SINON_H
#define STRSI_SINON_H

#include <QDialog>

namespace Ui {
class StrSi_SInon;
}

class StrSi_SInon : public QDialog
{
    Q_OBJECT

public:
    explicit StrSi_SInon(QWidget *parent = 0);
    ~StrSi_SInon();

private:
    Ui::StrSi_SInon *ui;
};

#endif // STRSI_SINON_H
