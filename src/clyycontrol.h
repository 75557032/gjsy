#ifndef CLYYCONTROL_H
#define CLYYCONTROL_H

#include <QObject>

class QSerialPort;

class clyyControl : public QObject
{
    Q_OBJECT

public:
    explicit clyyControl(QObject *parent = nullptr);
    ~clyyControl();
    void setPower(double dVoltage, double dCurrent);
    void openPower();
    void closePower();

private:
    QSerialPort *m_pPowerControl;
};

#endif // CLYYCONTROL_H
