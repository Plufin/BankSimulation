#ifndef RFIDREADERDLL_H
#define RFIDREADERDLL_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class RfidReaderDLL:public QObject
{
Q_OBJECT
public:
    RfidReaderDLL(QObject *parent = nullptr);
    ~RfidReaderDLL();

public slots:
    // slots which receives signals from main exe
    void readData();

signals:
    // signals to be sent to main exe or other dll:s
    void sendCard(QString);

private:
    QSerialPort *rfidSerial = nullptr;

private slots:
};

#endif // RFIDREADERDLL_H
