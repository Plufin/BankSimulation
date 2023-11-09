#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tokenmanager.h"
#include "menu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::on_numberButton_clicked);
    pReader = new RfidReaderDLL(this);
    ui ->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_numberButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString number = button->text();
        QString currentText = ui->pinLineEdit->text();
        if (currentText.length() < ui->pinLineEdit->maxLength()) {
            ui->pinLineEdit->setText(currentText + number);
        }
    }
}

void MainWindow::on_pushButton_enter_clicked()
{
    qDebug() << "CardNumber: " << cardNumber;
    pin = ui->pinLineEdit->text();
    QJsonObject jsonObj;
    jsonObj.insert("card_number", cardNumber);
    jsonObj.insert("pin", pin);

    QString site_url="http://localhost:3000/card/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->pinLineEdit->setText("");
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument resdata = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = resdata.object();
    QString status = jsonObj.value("status").toString();
    qDebug()<<status;

    if (QString::compare(status, "invalid pin") == 0 || response_data.length()<10) {
        ui->labelLoginError->setText("Väärä PIN-koodi");
        ui->pinLineEdit->setText("");
    }
    else {
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject jsonObj = json_doc.object();
        token = "Bearer " + jsonObj.value("token").toString().toUtf8();
        id = jsonObj.value("account_id").toInt();
        tokenManager *my = tokenManager::getInstance();
        my->setToken(token);
        my->setId(id);
        menu *menu = new class menu(this);
        menu->show();
        this->hide();
        reply->deleteLater();
        loginManager->deleteLater();
    }

}


void MainWindow::on_pushButton_card1_clicked()
{
    cardNumber = "0000000600064988";
    pReader->deleteLater();
    ui ->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_card2_clicked()
{
    cardNumber = "00000005009B101A";
    pReader->deleteLater();
    ui ->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_readRfid_clicked()
{
    cardNumber = "0000000000000000";

    connect(pReader, SIGNAL(sendCard(QString)),
            this, SLOT(receiveCard(QString)));

    emit readCard();
}

void MainWindow::receiveCard(QString cardString)
{
    cardNumber = cardString;
    pReader->deleteLater();
    ui ->stackedWidget->setCurrentIndex(1);
}


