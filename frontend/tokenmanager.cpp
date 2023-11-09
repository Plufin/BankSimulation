#include "tokenmanager.h"

tokenManager* tokenManager::instance = nullptr;

tokenManager* tokenManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new tokenManager();
    }

    return instance;
}

QByteArray tokenManager::getToken() const
{
    return token;
}

void tokenManager::setToken(const QByteArray &value)
{
    token = value;
}

int tokenManager::getId() const
{
    return id;
}

void tokenManager::setId(const int &value)
{
    id = value;
}

