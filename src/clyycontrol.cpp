#include "clyycontrol.h"

#include <QSerialPort>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QEventLoop>
#include <QModbusReply>

#include <QDebug>

clyyControl::clyyControl(QObject *parent) : QObject(parent),
    m_pPowerControl(new QSerialPort),
    m_pTemperatureControl(new QModbusTcpClient)
{
    m_pPowerControl->setPortName("COM7");
    m_pPowerControl->open(QIODevice::ReadWrite);
    m_pPowerControl->setBaudRate(QSerialPort::Baud9600);
    m_pPowerControl->setDataBits(QSerialPort::Data8);
    m_pPowerControl->setParity(QSerialPort::NoParity);
    m_pPowerControl->setStopBits(QSerialPort::OneStop);
    m_pPowerControl->setFlowControl(QSerialPort::NoFlowControl);

    m_pTemperatureControl->setConnectionParameter(QModbusDevice::NetworkPortParameter, 10000);
    m_pTemperatureControl->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.232");
    qDebug() << m_pTemperatureControl->connectDevice();
}

clyyControl::~clyyControl()
{
    if (QModbusDevice::UnconnectedState != m_pTemperatureControl->state()) {
        m_pTemperatureControl->disconnectDevice();
    }
    if (m_pPowerControl->isOpen()) {
        m_pPowerControl->close();
    }
    delete m_pTemperatureControl;
    delete m_pPowerControl;
}

void clyyControl::setPower(double dVoltage, double dCurrent)
{
    m_pPowerControl->write(QString::fromUtf8(":APPL %1,%2\n").arg(dVoltage).arg(dCurrent).toLocal8Bit());
    m_pPowerControl->waitForBytesWritten(3000);
}

void clyyControl::openPower()
{
    m_pPowerControl->write(QString::fromUtf8(":OUTP ON\n").toLocal8Bit());
    m_pPowerControl->waitForBytesWritten(3000);
}

void clyyControl::closePower()
{
    m_pPowerControl->write(QString::fromUtf8(":OUTP OFF\n").toLocal8Bit());
    m_pPowerControl->waitForBytesWritten(3000);
}

QVariant clyyControl::readTemperature(int nAddr)
{
    QModbusDataUnit unit(QModbusDataUnit::InputRegisters, 0, 8);
    QEventLoop e;
    QModbusReply *modbusReply = m_pTemperatureControl->sendReadRequest(unit, nAddr);
    connect(modbusReply, &QModbusReply::finished, &e, &QEventLoop::quit);
    e.exec();
    return modbusReply->result().value(0);
}
