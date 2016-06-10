#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mgr = new QNetworkAccessManager(this);
    connect(mgr, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
    this->address = "192.168.1.124";
    StreamDecoder *decoder = new StreamDecoder();
    connect(decoder,SIGNAL(newImage(QPixmap)),this,SLOT(newImage(QPixmap)));
    ui->videoFrame->setScene(&scene);
    timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(refreshStream()));

}

MainWindow::~MainWindow()
{
    request("http://"+address+"/cam.cgi?mode=stopstream");
    delete ui;
}


void MainWindow::replyFinished(QNetworkReply* reply){
    QString rMsg(reply->readAll());
    if(rMsg.contains("<result>ok</result>"))
        qDebug()<<"Request okay";
    else
        qDebug() << reply->readAll();
}

void MainWindow::request(QString reqString){

    QNetworkReply *reply = mgr->get(QNetworkRequest(QUrl(reqString)));
}

void MainWindow::on_connectButton_clicked()
{
    // create custom temporary event loop on stack
    address = ui->lineEdit->text();
    request("http://"+address+"/cam.cgi?mode=getinfo&type=capability");
    request("http://"+address+"/cam.cgi?mode=startstream&value=49199");
    timer->start(10000);
}
void MainWindow::refreshStream(){
   // request("http://"+address+"/cam.cgi?mode=stopstream");
    request("http://"+address+"/cam.cgi?mode=startstream&value=49199");
}

void MainWindow::camcmd(QString cmd){
    request("http://"+address+"/cam.cgi?mode=camcmd&value="+cmd);
}

void MainWindow::newImage(QPixmap image){
    scene.clear();
    scene.addPixmap(image);
    ui->videoFrame->update();
}

void MainWindow::zoomStop()
{
    camcmd("zoomstop");
}
void MainWindow::on_wideFast_pressed()
{
    camcmd("wide-fast");
}

void MainWindow::on_wideSlow_pressed()
{
    camcmd("wide-normal");
}

void MainWindow::on_teleSlow_pressed()
{
    camcmd("tele-normal");
}

void MainWindow::on_teleFast_pressed()
{
    camcmd("tele-fast");
}

void MainWindow::on_wideFast_released()
{
    zoomStop();
}

void MainWindow::on_wideSlow_released()
{
    zoomStop();
}

void MainWindow::on_teleSlow_released()
{
    zoomStop();
}

void MainWindow::on_teleFast_released()
{
    zoomStop();
}

void MainWindow::on_videoModeButton_clicked()
{
    camcmd("recmode");
    request("http://"+address+"/cam.cgi?mode=startstream&value=49199");
    timer->start(10000);
}

void MainWindow::on_pictureModeButton_clicked()
{
    request("http://"+address+"/cam.cgi?mode=stopstream");
    camcmd("pictmode");
    request("http://"+address+"/cam.cgi?mode=startstream&value=49199");
    timer->stop();
}

void MainWindow::on_playModeButton_clicked()
{
    request("http://"+address+"/cam.cgi?mode=stopstream");
    camcmd("playmode");
    timer->stop();
}



void MainWindow::on_recButton_clicked()
{
    camcmd("recstart");
}

void MainWindow::on_recstopButton_clicked()
{
    camcmd("recstop");
}

void MainWindow::on_pictureButton_clicked()
{
    camcmd("capture");
}

void MainWindow::on_shutDownButton_clicked()
{
    camcmd("poweroff");
}