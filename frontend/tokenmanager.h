#ifndef TOKENMANAGER_H
#define TOKENMANAGER_H

#include <QString>


class tokenManager
{
private:
    static tokenManager* instance;
    QByteArray token;
    int id;

public:
    static tokenManager* getInstance();

    QByteArray getToken() const;
    void setToken(const QByteArray &value);
    int getId() const;
    void setId(const int &value);
};

#endif // TOKENMANAGER_H
