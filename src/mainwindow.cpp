#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>

#include "clyycontrol.h"
#include "clyypid.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pControl(new clyyControl)
{
    ui->setupUi(this);
    PID_init();
    qDebug() << PID_realize(10, 20);
}

MainWindow::~MainWindow()
{
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

void MainWindow::saveResultToFile(const QString &path, const QStringList &line)
{
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Append)) {
        return;
    }
    QTextStream out(&file);
    QString strLine;
    for (int i = 0; i < line.size(); ++i) {
        strLine += line.at(i);
        strLine += " ";
    }
    out << strLine << "\n";
}

void MainWindow::on_pb_Test_clicked()
{
    //测试
}
