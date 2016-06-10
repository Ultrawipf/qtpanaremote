#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include "streamdecoder.h"
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QNetworkAccessManager* mgr;
    ~MainWindow();
    QString address;
    QTimer *timer;

public slots:
    void replyFinished(QNetworkReply *reply);
    void newImage(QPixmap image);
    void refreshStream();

private slots:
    void on_connectButton_clicked();

    void zoomStop();

    void on_wideFast_pressed();

    void on_wideSlow_pressed();

    void on_teleSlow_pressed();

    void on_teleFast_pressed();

    void on_wideFast_released();

    void on_wideSlow_released();

    void on_teleSlow_released();

    void on_teleFast_released();

    void on_videoModeButton_clicked();

    void on_pictureModeButton_clicked();

    void on_playModeButton_clicked();

    void on_recButton_clicked();

    void on_recstopButton_clicked();

    void on_pictureButton_clicked();

    void on_shutDownButton_clicked();

private:
    Ui::MainWindow *ui;
    void request(QString);
    QGraphicsScene scene;
    void camcmd(QString);
};

#endif // MAINWINDOW_H
