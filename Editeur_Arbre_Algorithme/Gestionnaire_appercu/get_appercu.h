#ifndef GET_APPERCU_H
#define GET_APPERCU_H

#include <QObject>
#include<QtGui>
#include<QtCore>
#include<QtXml>
class Get_Appercu : public QObject
{
    Q_OBJECT
public:
    explicit Get_Appercu(QObject *parent = 0);

signals:

public slots:
    QString constante(QDomElement element);

    QString enregistrement(QDomElement element);

    QString champ(QDomElement element);

    QString tableaux(QDomElement element);

    QString matrices(QDomElement element);

    QString fichiers(QDomElement element);

    QString fonction(QDomElement element);

    QString variable(QDomElement element);

    QString procedure(QDomElement element);

    QString instruction(QDomElement element);

private:
    QString appercu;
};

#endif // GET_APPERCU_H
