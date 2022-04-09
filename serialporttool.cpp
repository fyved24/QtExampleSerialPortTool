#include "serialporttool.h"

SerialPortTool::SerialPortTool()
{
    this->serial = new QSerialPort;
    init();
}
void SerialPortTool::init()
{

    connect(serial, &QSerialPort::errorOccurred, this, &SerialPortTool::onErrorOccurred);
    connect(serial, &QSerialPort::readyRead, this, &SerialPortTool::onReadyRead);
}
void SerialPortTool::start()
{
    stop();
    serial->setPortName(serialPortName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        qDebug()<<tr("Connected to %1 : %2")
                          .arg(serialPortName).arg(baudRate);
//        emit connected();
    }
}
void SerialPortTool::stop()
{
#ifndef QT_NO_DEBUG
    qInfo()<<"Tool_SerialPort::onStop";
#endif
    if(serial!=nullptr)
    {
        if(serial->isOpen()) {
            serial->close();
        }

    }
}
void SerialPortTool::send(const QString &text)
{
#ifndef QT_NO_DEBUG
    qInfo()<<"Tool_serialPort::onSend"<<text;
#endif
    if(text.isEmpty())
        return;
    if(serial == nullptr)
    {
        emit error(tr("串口未初始化!"));
        return;
    }

    if(serial->write(text.toUtf8())!=text.size())
    {
        emit error(tr("串口写入错误!"),
                   tr("%1 : %2").arg(serial->portName())
                   .arg(serial->errorString()));
        return;
    }
}

void SerialPortTool::setSerialPortName(QString name) {
    this->serial->setPortName(name);
    this->serialPortName = name;


}
QString SerialPortTool::getSerialPortName() {
    return serialPortName;
}

void SerialPortTool::setBaudRate(int rate) {
    this->serial->setBaudRate(rate);
    this->baudRate = rate;
}
int SerialPortTool::getBaudRate() {
    return baudRate;
}

QJsonArray SerialPortTool::availablePorts() {
    QJsonArray m;
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        m.append(port.portName());
    }
    return m;
}
/*!
 * \brief Tool_SerialPort::onReadyRead 接收数据
 */
void SerialPortTool::onReadyRead()
{
#ifndef QT_NO_DEBUG
    qInfo()<<"Tool_SerialPort::onReadyRead";
#endif
    if(serial==nullptr)
        return;
    emit received(serial->readAll());
}

void SerialPortTool::onErrorOccurred()
{
#ifndef QT_NO_DEBUG
    qInfo()<<"Tool_SerialPort::onErrorOccurred";
#endif
    if(serial==nullptr||serial->error()==QSerialPort::NoError)
        return;
    emit error(tr("串口错误!"), tr("%1 : %2, %3, %4, %5, %6 %7")
               .arg(serial->portName()).arg(serial->baudRate()).arg(serial->dataBits())
               .arg(serial->parity()).arg(serial->stopBits()).arg(serial->flowControl())
               .arg(serial->errorString()));
}
