#include "clyycontrol.h"

#include <QSerialPort>

clyyControl::clyyControl(QObject *parent) : QObject(parent),
    m_pPowerControl(new QSerialPort)
{
    m_pPowerControl->setPortName("COM7");
    m_pPowerControl->open(QIODevice::ReadWrite);
    m_pPowerControl->setBaudRate(QSerialPort::Baud9600);
    m_pPowerControl->setDataBits(QSerialPort::Data8);
    m_pPowerControl->setParity(QSerialPort::NoParity);
    m_pPowerControl->setStopBits(QSerialPort::OneStop);
    m_pPowerControl->setFlowControl(QSerialPort::NoFlowControl);
}

clyyControl::~clyyControl()
{
    if (m_pPowerControl->isOpen()) {
        m_pPowerControl->close();
    }
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
