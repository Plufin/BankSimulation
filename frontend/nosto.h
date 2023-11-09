#ifndef NOSTO_H
#define NOSTO_H

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDialog>

namespace Ui {
class nosto;
}

class nosto : public QDialog
{
    Q_OBJECT

public:
    explicit nosto(QWidget *parent = nullptr);
    ~nosto();

private slots:
    void withdrawSlot(QNetworkReply *reply);

    void logsSlot(QNetworkReply *reply2);

    void on_Button20_clicked();

    void on_nosto_edellinenButton_clicked();

    void on_Button40_clicked();

    void on_Button50_clicked();

    void on_Button100_clicked();

    void on_hetkellinenButton_clicked();

    void on_muu_edellinenButton_clicked();

    void on_ButtonEnter_clicked();

    void on_ei_kuittia_clicked();

    void on_Ulos_Button_clicked();

    void on_KuittiButton_clicked();

    void on_edellinenButton_clicked();

    void on_saldoButton_clicked();

    void on_ulosButton_clicked();

    void getSaldoSlot(QNetworkReply *reply);

private:
    Ui::nosto *ui;
    QNetworkAccessManager *getSaldo;
    double withdrawAmount;
    QNetworkAccessManager *withdrawManager;
    QNetworkAccessManager *logsManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QByteArray response_data;
};

#endif // NOSTO_H
