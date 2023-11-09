#include "rfidreaderdll.h"

RfidReaderDLL::RfidReaderDLL(QObject *parent)
    :QObject(parent), rfidSerial(new QSerialPort)
{
        qDebug() << "readRFID luotu";
        // asetukset
        rfidSerial->setPortName("/dev/tty.usbmodem14201");
        rfidSerial->setBaudRate(QSerialPort::Baud9600);
        rfidSerial->setDataBits(QSerialPort::DataBits(8));
        rfidSerial->setParity(QSerialPort::Parity(0));  // ei pariteettitarkistusta
        rfidSerial->setStopBits(QSerialPort::OneStop);
        rfidSerial->setFlowControl(QSerialPort::NoFlowControl);    // ei flow controllia, vain tx/rx

        connect(rfidSerial, &QSerialPort::readyRead,
                this, &RfidReaderDLL::readData);

        if(rfidSerial->open(QIODevice::ReadWrite)) {
            qDebug() << rfidSerial->errorString();
        } else {
            qDebug() << "Serial opened succesfully.";
        }
}

RfidReaderDLL::~RfidReaderDLL()
{
    delete rfidSerial;
    qDebug() << "readRFID tuhottu";
}

void RfidReaderDLL::readData()  // public slot
{
    QByteArray cardId = rfidSerial->readAll();
    qDebug() << "readData: " << cardId;

    // Stringin siistiminen
    QString cardString = QString::fromUtf8(cardId);
    cardString = cardString.mid(3,10);                  // aloita 3. merkistä, ota 10 merkin pätkä
    cardString = cardString.rightJustified(16, '0');    // 16 pitkä, täytä nollilla
    qDebug() << "cardString = " << cardString;

    emit sendCard(cardString);
}

