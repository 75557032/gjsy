﻿#ifndef CLYYCONTROL_H
#define CLYYCONTROL_H

#include <QObject>

class QSerialPort;
class QTcpSocket;

class clyyControl : public QObject
{
    Q_OBJECT

public:
    explicit clyyControl(QObject *parent = nullptr);
    ~clyyControl();
    void setPower(double dVoltage, double dCurrent);
    void openPower();
    void closePower();
    double readTemperature(unsigned char nAddr);

private:
    QSerialPort *m_pPowerControl;
    QTcpSocket *m_pTemperatureControl;
};

#endif // CLYYCONTROL_H
