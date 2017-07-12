#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtNetwork>
#include "decodemachine.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    ui->serverProgressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_serverButton_clicked()
{
    start();
}
void MainWindow::start()
{
    if(!tcpServer.listen(QHostAddress::LocalHost,6666))
    {
        cout<<tcpServer.errorString().toStdString()<<endl;
         cout<<"2222222222222"<<endl;
         ui->statusLabel->setText(tr("无连接"));
        close();
        return;
    }
    ui->serverButton->setEnabled(false);
    totalBytes = 0;
    bytesReceived=0;
    fileNameSize = 0;
    ui->statusLabel->setText(tr("监听"));
    ui->serverProgressBar->reset();
}
void MainWindow::acceptConnection()
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection,SIGNAL(readyRead()),this,SLOT(updateServerProgress()));
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    ui->statusLabel->setText(tr("接受连接"));
    tcpServer.close();

}
void MainWindow::updateServerProgress()
{
   QDataStream in(tcpServerConnection);
   in.setVersion(QDataStream::Qt_4_0);
   if(bytesReceived<= sizeof(qint64)*2)
   {
       if((tcpServerConnection->bytesAvailable()>=sizeof(qint64)*2) &&(fileNameSize==0))
       {
           in>>totalBytes>>fileNameSize;
           bytesReceived+=sizeof(qint64)*2;
       }
       if((tcpServerConnection->bytesAvailable()>=fileNameSize) &&(fileNameSize!=0))
       {
           in>>fileName;
           ui->statusLabel->setText(tr("接受文件%1").arg(fileName));
           bytesReceived+=fileNameSize;
           localFile = new QFile("./"+fileName);
           cout<<fileName.toStdString()<<endl;
           if(!localFile->open(QFile::WriteOnly)) return;
       }else{
           return;
       }
   }
   if(bytesReceived<totalBytes)
   {
       bytesReceived+=tcpServerConnection->bytesAvailable();
       inBlock = tcpServerConnection->readAll();
       localFile->write(inBlock);
       inBlock.resize(0);
   }
   ui->serverProgressBar->setMaximum(totalBytes);
   ui->serverProgressBar->setValue(bytesReceived);
   if(bytesReceived==totalBytes)
   {
       tcpServerConnection->close();
       localFile->close();
       ui->serverButton->setEnabled(true);
       ui->statusLabel->setText(tr("接受文件成功"));
   }
}
void MainWindow::displayError(QAbstractSocket::SocketError error)
{
   cout<<tcpServerConnection->errorString().toStdString()<<endl;
   tcpServerConnection->close();
   ui->serverProgressBar->reset();
   ui->statusLabel->setText(tr("就绪"));
   ui->serverButton->setEnabled(true);
}

void MainWindow::on_serverButton_2_clicked()
{
    DecodeMachine machine;
    machine.start();
    ui->textBrowser->setText(machine.getText());
}
