#ifndef SERIALPORTTOOL_H
#define SERIALPORTTOOL_H

#include <QObject>
#include <QJsonArray>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPortTool : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray availablePorts READ availablePorts NOTIFY availablePortsChanged)
    Q_PROPERTY(QString serialPortName READ getSerialPortName WRITE setSerialPortName NOTIFY serialPortNameChanged)
    Q_PROPERTY(int baudRate READ getBaudRate WRITE setBaudRate NOTIFY baudRateChanged)
public:
    SerialPortTool();
    QJsonArray  availablePorts();
    void setSerialPortName(QString name);
    QString getSerialPortName();
    void setBaudRate(int rate);
    int getBaudRate();

public slots:
    void start();
    void stop();
    //发送数据
    void send(const QString &text);

signals:
    void error(const QString &errorString, const QString &detailError = QString());
    void received(const QString &text);
    void availablePortsChanged();
    void serialPortNameChanged();
    void baudRateChanged();


private:
    void init();
    //接收数据
    void onReadyRead();
    //串口出错
    void onErrorOccurred();

    QString serialPortName;
    QSerialPort *serial;
    int baudRate;

};

#endif // SERIALPORTTOOL_H
