
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_sendBuutton_clicked();
    void newConnection();
    void dataReady();
    void readData();

private:
    Ui::MainWindow *ui;

    unsigned short m_ip = 0;
    unsigned short m_port = 0;
    QList<QTcpSocket*> client_list;

    QTcpServer *m_server;
    QTcpSocket *m_client;
private:
    void startServer();
};

#endif // MAINWINDOW_H
