#include "waveviever.h"
#include "ui_waveviever.h"

WaveViever::WaveViever(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaveViever)
{
    ui->setupUi(this);
    for (int i = 0; i< 4096; i++)
        X.push_back(i);
}

WaveViever::~WaveViever()
{
    delete ui;
}

void WaveViever::on_pushButton_clicked()
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 10002);
    connect(socket, &QUdpSocket::readyRead, this, &WaveViever::readPendingDatagrams);
}

void WaveViever::readPendingDatagrams()
{
    QString IP;             //Sender IP                //Sender port no.
    ui->widget->xAxis->setRange(0, 4500);
    ui->widget->yAxis->setRange(-500,4500);
    QPen penMid, penMax;
    penMid.setStyle(Qt::DashDotLine);
    penMid.setWidth(3);
    penMax.setColor(Qt::black);
    penMax.setWidth(2);
    while (socket->hasPendingDatagrams())
    {
        ui->widget->clearGraphs();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress senderIP;
        quint16 senderPort;
        socket->readDatagram(datagram.data(), datagram.size(), &senderIP, &senderPort);
        int mid = 0, maxY = 0, maxX = 0;
        QDataStream str(datagram);
        ui->widget->addGraph();
        for (auto& i : X)
        {
            qint16 tmp;
            str >> tmp;

            ui->widget->graph(0)->addData(i,tmp);
            mid +=tmp;
            if (maxY < tmp)
            {
                maxY = tmp;
                maxX = i;
            }
        }
        mid = mid / X.count();
        ui->widget->addGraph();
        ui->widget->graph(1)->setPen(penMid);
        ui->widget->graph(1)->addData(0, mid);
        ui->widget->graph(1)->addData(X.count(), mid);
        ui->lineEdit->insert(QString::number(mid));
        ui->lineEdit_2->insert(QString::number(maxX));
        ui->lineEdit_3->insert(QString::number(maxY));
        ui->widget->addGraph();
        ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));
        ui->widget->graph(2)->setPen(penMid);
        ui->widget->graph(2)->addData(maxX, maxY);
        ui->widget->replot();
    }
}

void WaveViever::on_pushButton_2_clicked()
{
    socket->close();
}



