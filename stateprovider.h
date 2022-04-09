#ifndef STATEPROVIDER_H
#define STATEPROVIDER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class StateProvider: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject settings READ getState NOTIFY stateChanged)
public:
    StateProvider();
    QJsonObject settings;
    QJsonObject getState();
    Q_INVOKABLE void setState(const QString &key, const QJsonObject &value);
    Q_INVOKABLE void setState(const QString &key, const QJsonArray &value);
    Q_INVOKABLE void setState(const QString &key, const QVariant &value);

signals:
    void stateChanged();
private:
    void saveToFile();
    void loadFromFile();
};

#endif // STATEPROVIDER_H
