#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>       
#include <QAbstractSocket>
#include<QTcpServer>
class QTcpSocket;
class QFile;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_serverButton_clicked();
    void start();
    void acceptConnection();
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError error);
    void on_serverButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 fileNameSize;
    QFile *localFile;
    QString fileName;
    QByteArray inBlock;
};

#endif // MAINWINDOW_H
