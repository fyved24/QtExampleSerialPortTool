#include "stateprovider.h"
#include <QJsonDocument>
#include <QFile>
StateProvider::StateProvider()
{
    loadFromFile();
     emit stateChanged();
}

void StateProvider::setState(const QString &key, const QVariant &value)
{
    qDebug() << value.typeName();
    if (value.typeName() == QStringLiteral("QString")) {
        settings[key] = value.toString();
    } else if (value.typeName() == QStringLiteral("int")){
        settings[key] = value.toInt();
    } else if (value.typeName() == QStringLiteral("double")){
        settings[key] = value.toDouble();
    }
    emit stateChanged();
    saveToFile();
}

void StateProvider::setState(const QString &key, const QJsonObject &value)
{
    qDebug() << value;
    settings[key] = value;
    emit stateChanged();
    saveToFile();
}
void StateProvider::setState(const QString &key, const QJsonArray &value)
{
    qDebug() << value;
    settings[key] = value;
    emit stateChanged();
    saveToFile();
}
void StateProvider::saveToFile()
{
    QJsonDocument doc;
    doc.setObject(settings);
    QFile file("config.json");

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Fail to save contents to JSON file";

    }

    file.write(doc.toJson());
    file.close();

}

void StateProvider::loadFromFile()
{
    QFile loadFile("config.json");

    if (!loadFile.open(QIODevice::ReadOnly))
        qDebug() << "Unable to load JSON file";

    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if (json_error.error != QJsonParseError::NoError)
        qDebug() << "JSON error!";

    settings = jsonDoc.object();
}

QJsonObject StateProvider::getState() {
    return settings;
}
