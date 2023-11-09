#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QString>
#include "rfidreaderdll.h"

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

    void on_numberButton_clicked();

    void on_pushButton_enter_clicked();

    void on_pushButton_clear_clicked();

    void loginSlot (QNetworkReply *reply);

    void on_pushButton_card1_clicked();

    void on_pushButton_readRfid_clicked();

    void receiveCard(QString);

    void on_pushButton_card2_clicked();

private:
    Ui::MainWindow *ui;
    RfidReaderDLL *pReader;
    QString cardNumber;
    QString pin;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray token;
    int id;

signals:
    void readCard();
};
#endif // MAINWINDOW_H
