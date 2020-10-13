#ifndef REPETERJUSQUA_H
#define REPETERJUSQUA_H

#include <QDialog>

namespace Ui {
class RepeterJusqua;
}

class RepeterJusqua : public QDialog
{
    Q_OBJECT

public:
    explicit RepeterJusqua(QWidget *parent = 0);
    ~RepeterJusqua();

private:
    Ui::RepeterJusqua *ui;
};

#endif // REPETERJUSQUA_H
