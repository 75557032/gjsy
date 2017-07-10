#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clyycontrol.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pControl(new clyyControl)
{
    ui->setupUi(this);
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
