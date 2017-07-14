#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>

#include "clyycontrol.h"
#include "clyypid.h"

#define ERRTIMERID (-1)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pControl(new clyyControl("COM3", "192.168.1.232:10000")),
    m_nTimerId(ERRTIMERID)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if (ERRTIMERID != m_nTimerId) {
        killTimer(m_nTimerId);
        m_nTimerId = ERRTIMERID;
    }
    delete m_pControl;
    delete ui;
}

void MainWindow::on_pb_Close_clicked()
{
    m_pControl->closePower();
}

void MainWindow::on_pb_Open_clicked()
{
    m_pControl->openPower();
}

void MainWindow::on_pb_Set_clicked()
{
    bool isOk = false;
    double dVoltage = ui->le_Voltage->text().trimmed().toDouble(&isOk);
    if (!isOk) {
        dVoltage = 5;
    }
    double dCurrent = ui->le_Voltage->text().trimmed().toDouble(&isOk);
    if (!isOk) {
        dCurrent = 1;
    }
    m_pControl->setPower(dVoltage, dCurrent);
}

void MainWindow::on_pb_Read_clicked()
{
    unsigned char nAddr = ui->lineEdit->text().trimmed().toUInt();
    ui->lb_out->setText(QString::fromUtf8("%1").arg(m_pControl->readTemperature(nAddr)));
}

void MainWindow::on_pb_ReadVol_clicked()
{
    ui->lb_Vol->setText(QString::fromUtf8("%1").arg(m_pControl->readVoltage()));
}

void MainWindow::on_pb_ReadCurrent_clicked()
{
    ui->lb_Current->setText(QString::fromUtf8("%1").arg(m_pControl->readCurrent()));
}

void MainWindow::on_pb_ReadPower_clicked()
{
    ui->lb_Power->setText(QString::fromUtf8("%1").arg(m_pControl->readPower()));
}

void MainWindow::saveResultToFile(const QString &path, const QList<double> &line)
{
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Append)) {
        return;
    }
    QTextStream out(&file);
    QString strLine;
    for (int i = 0; i < line.size(); ++i) {
        strLine += QString("%1 ").arg(line.at(i));
    }
    out << strLine << "\n";
}

void MainWindow::changeTemperature(double speed, double Aspeed)
{
    double power = PID_realize(speed, Aspeed);
    double dResistance = getResistance(speed);
    double dVol = power / dResistance;
    m_pControl->setPower(dVol, 2);
}

double MainWindow::getResistance(double speed)
{
    return speed;
}

void MainWindow::compareTemperature(unsigned char nFrom, unsigned char nTo)
{
    double speed = m_pControl->readTemperature(nFrom);
    double Aspeed = m_pControl->readTemperature(nTo);
    if (speed != Aspeed) {
        changeTemperature(speed, Aspeed);
    }
    double dPower = m_pControl->readPower();
    double dCurrent = m_pControl->readCurrent();
    double dVoltage = m_pControl->readVoltage();
    saveResultToFile("D:\\xx.txt", {dPower, dVoltage, dCurrent, speed, Aspeed});
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    compareTemperature(1, 2);
}

void MainWindow::on_pb_Test_clicked()
{
    if (ERRTIMERID == m_nTimerId) {
        m_nTimerId = startTimer(100);
        PID_init();
        ui->pb_Test->setText("停止");
    } else {
        killTimer(m_nTimerId);
        m_nTimerId = ERRTIMERID;
        ui->pb_Test->setText("测试");
    }
}
