#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "waveviever.h"
#include "dialog.h"

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

    void on_actionWave_Viewer_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    WaveViever *newWindows;
};
#endif // MAINWINDOW_H
