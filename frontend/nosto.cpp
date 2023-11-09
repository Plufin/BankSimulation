#include "nosto.h"
#include "ui_nosto.h"
#include "tokenmanager.h"
#include "menu.h"
#include "mainwindow.h"

nosto::nosto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nosto)
{
    ui->setupUi(this);
}

nosto::~nosto()
{
    delete ui;
}

void nosto::on_nosto_edellinenButton_clicked()
{
    menu *menu = new class menu(this);

    menu->show();
    this->hide();
}


void nosto::on_Button20_clicked()
{
    withdrawAmount = 20;
    tokenManager *my = tokenManager::getInstance();
    QJsonObject jsonObj;
    jsonObj.insert("amount", withdrawAmount);

    QString site_url="http://localhost:3000/account/withdraw";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray token = my->getToken();
    qDebug()<<"Token: "<<token;
    request.setRawHeader(QByteArray("Authorization"),(token));

    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));

    reply = withdrawManager->post(request, QJsonDocument(jsonObj).toJson());
}


void nosto::on_Button40_clicked()
{
    withdrawAmount = 40;
    tokenManager *my = tokenManager::getInstance();
    QJsonObject jsonObj;
    jsonObj.insert("amount", withdrawAmount);

    QString site_url="http://localhost:3000/account/withdraw";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray token = my->getToken();
    qDebug()<<"Token: "<<token;
    request.setRawHeader(QByteArray("Authorization"),(token));

    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));

    reply = withdrawManager->post(request, QJsonDocument(jsonObj).toJson());
}


void nosto::on_Button50_clicked()
{
    withdrawAmount = 50;
    tokenManager *my = tokenManager::getInstance();
    QJsonObject jsonObj;
    jsonObj.insert("amount", withdrawAmount);

    QString site_url="http://localhost:3000/account/withdraw";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray token = my->getToken();
    qDebug()<<"Token: "<<token;
    request.setRawHeader(QByteArray("Authorization"),(token));

    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));

    reply = withdrawManager->post(request, QJsonDocument(jsonObj).toJson());
}


void nosto::on_Button100_clicked()
{
    withdrawAmount = 100;
    tokenManager *my = tokenManager::getInstance();
    QJsonObject jsonObj;
    jsonObj.insert("amount", withdrawAmount);

    QString site_url="http://localhost:3000/account/withdraw";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray token = my->getToken();
    qDebug()<<"Token: "<<token;
    request.setRawHeader(QByteArray("Authorization"),(token));

    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));

    reply = withdrawManager->post(request, QJsonDocument(jsonObj).toJson());
}


void nosto::on_hetkellinenButton_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex > 0) {
     ui->stackedWidget->setCurrentIndex(currentIndex - 2);
}
}


void nosto::on_muu_edellinenButton_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex > 0) {
     ui->stackedWidget->setCurrentIndex(currentIndex - 1);
}
}

void nosto::on_ButtonEnter_clicked()
{
    ui ->stackedWidget->setCurrentIndex(2);
}


void nosto::on_ei_kuittia_clicked()
{
    MainWindow *mainwindow = new class MainWindow(this);

    mainwindow->show();
    this->hide();
}


void nosto::on_Ulos_Button_clicked()
{
    MainWindow *mainwindow = new class MainWindow(this);

    mainwindow->show();
    this->hide();
}


void nosto::on_KuittiButton_clicked()
{
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
    QString kuitti = "Nosto: "+QString::number(withdrawAmount)+"€\n"+"\n\n"+"Päivämäärä: "+formattedTimeMsg;
    ui->lineEditKuitti->setText(kuitti);
    ui->stackedWidget->setCurrentIndex(4);
}


void nosto::on_edellinenButton_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex > 0) {
     ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }
}


void nosto::on_saldoButton_clicked()
{
    tokenManager *my = tokenManager::getInstance();
    QString site_url="http://localhost:3000/account/balance";
    QNetworkRequest request((site_url));

    QByteArray token = my->getToken();
    qDebug()<<"Token: "<<token;
    request.setRawHeader(QByteArray("Authorization"),(token));

    getSaldo = new QNetworkAccessManager(this);

    connect(getSaldo, SIGNAL(finished(QNetworkReply*)), this, SLOT(getSaldoSlot(QNetworkReply*)));

    reply = getSaldo->get(request);
    ui ->stackedWidget->setCurrentIndex(3);
}


void nosto::on_ulosButton_clicked()
{
    MainWindow *mainwindow = new class MainWindow(this);

    mainwindow->show();
    this->hide();
}

void nosto::getSaldoSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    double saldoCredit;
    double saldoDebit;
    foreach (const QJsonValue &value, json_array) {
     QJsonObject json_obj = value.toObject();
     saldoCredit = json_obj["saldo_credit"].toDouble();
     saldoDebit = json_obj["saldo_debit"].toDouble();

    }
    QString saldoAll = "Credit: "+ QString::number(saldoCredit) + "\n\n" + "Debit: "+ QString::number(saldoDebit);
    ui->lineEditSaldoNosto->setText(saldoAll);

    reply->deleteLater();
    getSaldo->deleteLater();
}


void nosto::withdrawSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    if (jsonDoc.isObject()) {
     QJsonObject jsonObj = jsonDoc.object();
     if (jsonObj.contains("message")) {
         QString message = jsonObj.value("message").toString();
         if (message == "Insufficient funds") {
            ui->labelErrorNosto->setText("Tilin kate ei riitä");
            reply->deleteLater();
            withdrawManager->deleteLater();
            }
         else {
            QJsonObject logsObj;
            tokenManager *my = tokenManager::getInstance();
            logsObj.insert("account_id", my->getId());
            logsObj.insert("event", "Nosto");
            logsObj.insert("amount", withdrawAmount);
            qDebug()<<logsObj;

            QString site_url2="http://localhost:3000/logs";
            QNetworkRequest request2((site_url2));
            request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            QByteArray token = my->getToken();
            qDebug()<<"Token: "<<token;
            request2.setRawHeader(QByteArray("Authorization"),(token));

            logsManager = new QNetworkAccessManager(this);
            connect(logsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(logsSlot(QNetworkReply*)));

            reply2 = logsManager->post(request2, QJsonDocument(logsObj).toJson());
            ui ->stackedWidget->setCurrentIndex(2);
         }
        }
     }


}

void nosto::logsSlot(QNetworkReply *reply2)
{
    response_data=reply2->readAll();
    qDebug()<<response_data;
    reply2->deleteLater();
    logsManager->deleteLater();
}


