#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newWindows = new WaveViever();
    connect(newWindows, &WaveViever::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionWave_Viewer_triggered()
{
    newWindows->show();
    this->close();
}


void MainWindow::on_actionAbout_triggered()
{
    Dialog *dlg = new Dialog();
    dlg->exec();
}

