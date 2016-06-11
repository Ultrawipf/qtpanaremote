#include "streamdecoder.h"
#include <QUdpSocket>
#include <QDebug>
#include <QThread>
#include <QTextStream>
#include <QFile>
StreamDecoder::StreamDecoder()
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 49199);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

StreamDecoder::~StreamDecoder()
{
    socket->close();
}

void StreamDecoder::readyRead(){

    QByteArray buf;
    buf.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buf.data(), buf.size(),
                             &sender, &senderPort);
    buffer.append(buf);
    if(buffer.size()>2000000){
        buffer.clear();
        qDebug() << "Debuff";
        return;
    }
    //Search for jpeg markers
    QByteArray sb = QByteArray::fromHex("ffd8");
    QByteArray eb = QByteArray::fromHex("ffd9");
    int start = buffer.indexOf(sb);
    int end = buffer.indexOf(eb,start);

    //We have not enough data
    if(start < 0 | end < 0){
        return;
    }else{
        //Generate an image from the data
        imageBuffer.clear();
        imageBuffer=buffer.mid(start,end-start);
        buffer.clear();
        if(image.loadFromData(imageBuffer,"JPG")){
            emit(newImage(image));
        }
    }
}
