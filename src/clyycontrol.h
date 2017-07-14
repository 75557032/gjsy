#ifndef CLYYCONTROL_H
#define CLYYCONTROL_H

#include <QObject>

class QSerialPort;
class QTcpSocket;

class clyyControl : public QObject
{
    Q_OBJECT

public:
    explicit clyyControl(const QString &portName, const QString &addr, QObject *parent = nullptr);
    ~clyyControl();
    void setPower(double dVoltage, double dCurrent);
    void openPower();
    void closePower();
    double readPower();
    double readCurrent();
    double readVoltage();
    double readTemperature(unsigned char nAddr);

private:
    QSerialPort *m_pPowerControl;
    QTcpSocket *m_pTemperatureControl;

protected:
    QString readDataFromPowerControl(const QString &cmd);
    void writeDataToPowerControl(const QString &cmd);
};

#endif // CLYYCONTROL_H
