#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
}

MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}

void MainWindow::putData()
{
  //max e min valores dos dados(inteiros).
  int max = ui->Max_slider->value();
  int min = ui->Min_slider->value();

  //Armazena data e hora.
  QDateTime datetime;
  //Armazena valores da data/hora e dados gerados.
  QString str;

  //Mostra valores gerados no 'Tex Browser'.
  if(socket->state()== QAbstractSocket::ConnectedState){
      datetime = QDateTime::currentDateTime();
      str = "set "+
          datetime.toString(Qt::ISODate)+
          " "+
          QString::number(qrand()%(max-min)+min)+"\r\n";

      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "Wrote";
      }
  }

  ui->textBrowser->append(str);
}

void MainWindow::on_Connect_clicked()
{
    QString ip = "127.0.0.1";
    int port = 1234;

    //Conecta ao host.
    on_Connect_clicked();

    connect(ui->Connect_Button,
            SIGNAL(clicked(bool)),
            this,
            SLOT(putData()));

    socket->connectToHost("127.0.0.1",1234);
    if(socket->waitForConnected(3000)){
      qDebug() << "Conectado";
    }
    else{
      qDebug() << "Disconnected";
    }

   // ui->IP_textBox->append(ip);
}

void MainWindow::on_Disconnect_clicked()
{
    //Disconecta do host.
    socket->close();
}

void MainWindow::on_Start_released()
{
    //Inicia a producao de dados.

    //Armazena o tempo de inicio.
    int temporizador = startTimer((ui->Timing_box->value())*1000);
}

void MainWindow::on_Stop_clicked()
{
    //Para o a contagem do temporizador.
    //killTimer();
    //Funcao predefinida. ver QTimerEvent.
}

void MainWindow::timerEvent(QTimerEvent *e)
{
  putData();
}
