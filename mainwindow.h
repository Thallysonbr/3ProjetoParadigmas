#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  //Inicia a conexao (Construtor).
  explicit MainWindow(QWidget *parent = 0);

  //Destrutor.
  ~MainWindow();

public slots:
  //Escreve e gera dados.
  void putData();

  //Funcao botao 'Connet'.
  void on_Connect_clicked();

  //Funcao botao 'Disconnet'.
  void on_Disconnect_clicked();
private slots:
  //Funcao botao 'Start'.
  void on_Start_released();



  //Funcao botao 'Stop'.
  void on_Stop_clicked();

  //Temporizador
  void timerEvent(QTimerEvent *e);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
