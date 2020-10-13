#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include<QTimer>

#include <QWidget>

#include<QLineEdit>
#include<QTextEdit>
#include<QThread>
class ConsoleWidget : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QTextEdit *TextEditConsole, QLineEdit * LineEdit_Input);

    void Clear();
    QString input;

public slots:

    void Lire(const QString message, const bool retour);

    void Ecrire(const QString message,const bool retour,const QColor color);

signals:

    void sentInput(const QString Input);

private slots:

    void timeIsOut();

    void InputIsChanged(const QString &arg1);

    void InputIsFinished();

    void ConsoleCursorPositionChanged();
    void SetLineEditInputCursorAtTheEnd();
private:
    QPalette PaltextEdit;

    QTextEdit * Console;
    QLineEdit * LineEditInput;
    QTimer * Timer;

    int NumberTimeOut;
    QString CurentInput;
    void SetConsoleCursorAtTheEnd();

};

#endif // CONSOLEWIDGET_H
