
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->clientButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    m_port = ui->port->text().toUShort();
    m_ip = ui->ipadress->text().toUShort();

    if(ui->serverButton->isChecked())
    {
        m_server = new QTcpServer(this);
        if(!m_server->listen(QHostAddress(m_ip), m_port))
        {
            qDebug() << "Server could not start";
        }
        else
        {
            qDebug() << "Server startet";
            connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
        }
    }
    else
    {
        m_client = new QTcpSocket;
        connect(m_client, SIGNAL(readyRead()), this, SLOT(readData()));
        m_client->connectToHost(ui->ipadress->text(), m_port);
    }

}

void MainWindow::readData()
{
    QByteArray data = m_client->readAll();
    ui->data_out->addItem(data);
}

void MainWindow::newConnection()
{
    QTcpSocket* newclient = m_server->nextPendingConnection();
    client_list.push_back(newclient);
    connect(newclient, SIGNAL(readyRead()), this, SLOT(dataReady()));

}

void MainWindow::dataReady()
{
    QByteArray data;
    for (QTcpSocket* s : client_list)
    {
        QByteArray temp = s->readAll();
        if(temp.size() == 0) continue;
        data = temp;
    }
    for (QTcpSocket* s : client_list)
    {
        s->write(data);
        s->flush();
    }
}

void MainWindow::on_sendBuutton_clicked()
{
    QByteArray msg = ui->data_in->toPlainText().toLatin1().data();
    m_client->write(msg);
}

