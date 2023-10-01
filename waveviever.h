#ifndef WAVEVIEVER_H
#define WAVEVIEVER_H
#include <QWidget>
#include "qcustomplot.h"
#include <QUdpSocket>
#include "QNetworkDatagram"
#include "QVector"
#include "QString"
namespace Ui {
class WaveViever;
}

class WaveViever : public QWidget
{
    Q_OBJECT
public:
    explicit WaveViever(QWidget *parent = nullptr);
    void readPendingDatagrams();
    ~WaveViever();
signals:
    void firstWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::WaveViever *ui;
    QUdpSocket *socket;
    QVector<double> X;
};

#endif // WAVEVIEVER_H
