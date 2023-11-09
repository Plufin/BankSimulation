#include "menu.h"
#include "nosto.h"
#include "ui_menu.h"
#include "tokenmanager.h"
#include "mainwindow.h"

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

}

menu::~menu()
{
    delete ui;
}

void menu::on_btnSaldo_clicked()
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
    ui ->stackedWidget->setCurrentIndex(2);
}


void menu::on_btnTapahtumat_clicked()
{
    tokenManager *my = tokenManager::getInstance();
    int account_id = my->getId();
    qDebug() << "ID:" << account_id;
    QString site_url = QString("http://localhost:3000/logs/history/%1").arg(account_id);
    qDebug() << "URL: " << site_url;
    QNetworkRequest request((site_url));

    getLogs = new QNetworkAccessManager(this);

    connect(getLogs, SIGNAL(finished(QNetworkReply*)), this, SLOT(getLogsSlot(QNetworkReply*)));

    reply = getLogs->get(request);
    ui ->stackedWidget->setCurrentIndex(1);
}

void menu::on_btnLogsEdellinen_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex > 0) {
        ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }
}


void menu::on_btnEdellinenSaldo_clicked()
{
        int currentIndex = ui->stackedWidget->currentIndex();
        if (currentIndex > 0) {
            ui->stackedWidget->setCurrentIndex(currentIndex - 2);
        }
}

void menu::on_btnNosto_clicked()
{
    nosto *nosto = new class nosto(this);

    nosto->show();
    this->hide();
}


void menu::on_btnUlos_clicked()
{
    MainWindow *mainwindow = new class MainWindow(this);

    mainwindow->show();
    this->hide();
}

void menu::getSaldoSlot(QNetworkReply *reply)
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
    ui->textEditSaldo->setText(saldoAll);

    reply->deleteLater();
    getSaldo->deleteLater();
}

void menu::getLogsSlot(QNetworkReply *reply)
{
    QString tapahtuma;
    response_data = reply->readAll();
    qDebug() << "DATA: " << response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            QString date_str = json_obj["date"].toString();
            QDateTime date_time = QDateTime::fromString(date_str, Qt::ISODate);
            QString date = date_time.toString("dd.MM.yyyy");
            tapahtuma += date + ",  " + json_obj["event"].toString() + ",  " + QString::number(json_obj["amount"].toDouble()) + "€ \r";
    }

    ui->textEditLogs->setText(tapahtuma);

    reply->deleteLater();
    getLogs->deleteLater();
}

