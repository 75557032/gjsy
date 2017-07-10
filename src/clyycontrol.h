#ifndef CLYYCONTROL_H
#define CLYYCONTROL_H

#include <QObject>

class QSerialPort;
class QModbusTcpClient;

class clyyControl : public QObject
{
    Q_OBJECT

public:
    explicit clyyControl(QObject *parent = nullptr);
    ~clyyControl();
    void setPower(double dVoltage, double dCurrent);
    void openPower();
    void closePower();
    QVariant readTemperature(int nAddr);

private:
    QSerialPort *m_pPowerControl;
    QModbusTcpClient *m_pTemperatureControl;
};

#endif // CLYYCONTROL_H
