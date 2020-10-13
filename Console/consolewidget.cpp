#include "consolewidget.h"
#include<QDebug>
#include<QTextCodec>
ConsoleWidget::ConsoleWidget(QTextEdit * TextEditConsole, QLineEdit *LineEdit_Input) //:
    //QWidget(parent),QObject(Object)
{
    Console = TextEditConsole;
    Console->clear();
    Timer = new QTimer(this);
    NumberTimeOut = 1;
    LineEditInput = LineEdit_Input;
    LineEditInput->setFixedHeight(0);
    LineEditInput->setFixedWidth(0);
    /*LineEditInput->setShortcutEnabled(Qt::Key_BraceLeft);
    LineEdit_Input->setShortcutEnabled(Qt::Key_Left);
    LineEdit_Input->setShortcutEnabled(Qt::CTRL + Qt::Key_Z);*/
    connect(LineEdit_Input,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(SetLineEditInputCursorAtTheEnd()));

    PaltextEdit.setColor(QPalette::Active, QPalette::Base, QColor(52,49,49));
    PaltextEdit.setColor(QPalette::Inactive, QPalette::Base, QColor(52,49,49));
    Console->setPalette(PaltextEdit);

    Console->setUndoRedoEnabled(true);
    Console->setReadOnly(true);

    connect(Timer,SIGNAL(timeout()),this,SLOT(timeIsOut()));
    connect(Console,SIGNAL(cursorPositionChanged()),this,SLOT(ConsoleCursorPositionChanged()));
    //connect(this->LineEditInput,SIGNAL(textChanged(QString)),this,SLOT(InputIsChanged(QString)));
    connect(LineEditInput,SIGNAL(editingFinished()),this,SLOT(InputIsFinished()));

    Console->setTextColor(QColor("Green"));
    //Console->insertPlainText("FD");

    Timer->start();
}

void ConsoleWidget::Clear()
{
    Timer->stop();
    Console->clear();
    Timer->start(500);
}

void ConsoleWidget::Lire(const QString message,const bool retour)
{
    Ecrire(message,retour,QColor(255,255,255));
    LineEditInput->setFocus();
    CurentInput = "";
    LineEditInput->setText("");
    connect(LineEditInput,SIGNAL(textChanged(QString)),this,SLOT(InputIsChanged(QString)));
}

void ConsoleWidget::Ecrire(const QString message, const bool retour, const QColor color)
{
    Timer->stop();
    if(!Console->toPlainText().isEmpty())
        if(Console->toPlainText().at(Console->toPlainText().length()-1) == '|')
            Console->textCursor().deletePreviousChar();

    Console->setTextColor(color);

    if(retour)
    {
        Console->insertPlainText("\n" + message);
    }
    else
    {
        Console->insertPlainText(message);
    }
    Timer->start(500);
}

void ConsoleWidget::timeIsOut()
{
    NumberTimeOut++;

    if(NumberTimeOut % 2 == 0 && Console->textCursor().atEnd())
    {

        QColor CurrentColor = Console->textColor();
        Console->setTextColor(QColor(255,255,255));
        Console->textCursor().insertText("|");
        Console->setTextColor(CurrentColor);
    }
    else
        if(!Console->toPlainText().isEmpty())
            if(Console->toPlainText().at(Console->toPlainText().length()-1) == '|' && Console->textCursor().atEnd())
                 Console->textCursor().deletePreviousChar();

    Timer->start(500);
}

void ConsoleWidget::InputIsChanged(const QString &arg1)
{
    if(!LineEditInput->text().isEmpty() || CurentInput.length() == 1)
    {
        if(CurentInput.length() < LineEditInput->text().length())
        {
            CurentInput = LineEditInput->text();

            Timer->stop();
            if(!Console->toPlainText().isEmpty())
                if(Console->toPlainText().at(Console->toPlainText().length()-1) == '|')
                    Console->textCursor().deletePreviousChar();

            Console->insertPlainText(CurentInput.mid(CurentInput.length()-1,1));

            Timer->start(500);
        }
        else
            if(CurentInput.length() > LineEditInput->text().length() || CurentInput.length() == 1)
            {
                Timer->stop();
                CurentInput = LineEditInput->text();
                if(!Console->toPlainText().isEmpty())
                    if(Console->toPlainText().at(Console->toPlainText().length()-1) == '|')
                        Console->textCursor().deletePreviousChar();


                Console->textCursor().deletePreviousChar();

                Timer->start(500);
            }
    }

}

void ConsoleWidget::InputIsFinished()
{
    disconnect(LineEditInput,SIGNAL(textChanged(QString)),this,SLOT(InputIsChanged(QString)));
    input = LineEditInput->text();
    LineEditInput->clear();
    //qDebug()<<"Result stream"<<input;
    LineEditInput->setFocusPolicy(Qt::NoFocus);
    emit this->sentInput(input);
}

void ConsoleWidget::ConsoleCursorPositionChanged()
{
    SetConsoleCursorAtTheEnd();
}

void ConsoleWidget::SetConsoleCursorAtTheEnd()
{
    QTextCursor cursor = Console->textCursor();
    cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
    Console->setTextCursor(cursor);

}

void ConsoleWidget::SetLineEditInputCursorAtTheEnd()
{


}
