#ifndef STREAMDECODER_H
#define STREAMDECODER_H
#include "mainwindow.h"
#include <QUdpSocket>
#include <QPixmap>
class StreamDecoder : public QObject
{
Q_OBJECT
public:
    StreamDecoder();
    ~StreamDecoder();
    QByteArray imageBuffer;
    QPixmap image;
    QWidget* mainWindow = mainWindow;

signals:
    void newImage(QPixmap);
public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    QByteArray buffer;
};

#endif // STREAMDECODER_H
