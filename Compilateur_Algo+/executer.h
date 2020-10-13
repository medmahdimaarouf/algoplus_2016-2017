#ifndef EXECUTER_H
#define EXECUTER_H

#include <QThread>
#include<QtXml>
#include"memoire.h"
#include<QtScript>
#include<QTextEdit>
#include<Console/consolewidget.h>
#include<QMessageBox>
class Executer : public QThread
{
    Q_OBJECT
public:
    explicit Executer(QDomDocument Source_program, QString input_program);

  void run();
//private:
  Memoire *memoire;
  QDomDocument reload_RAM();
  QString police_thread();
//private:
  QString Input_program;
  QScriptEngine * engine;

public slots:

  void change_input(const QString Input);

signals:

  void SentMessage(const QString message, const bool retour, const QColor color);

  void GetInput(const QString message, const bool retour);

  void DebutExec();

  void FinExec();

private:

};

#endif // EXECUTER_H
