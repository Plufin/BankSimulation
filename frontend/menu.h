#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:

    void on_btnSaldo_clicked();

    void on_btnTapahtumat_clicked();

    void on_btnLogsEdellinen_clicked();

    void on_btnEdellinenSaldo_clicked();

    void on_btnNosto_clicked();

    void on_btnUlos_clicked();

    void getSaldoSlot (QNetworkReply *reply);

    void getLogsSlot (QNetworkReply *reply);

private:
    Ui::menu *ui;
    QNetworkAccessManager *getSaldo;
    QNetworkAccessManager *getLogs;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // MENU_H
