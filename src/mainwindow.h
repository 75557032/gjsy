#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class clyyControl;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_Close_clicked();

    void on_pb_Open_clicked();

    void on_pb_Set_clicked();

    void on_pb_Read_clicked();

    void on_pb_ReadVol_clicked();

    void on_pb_ReadCurrent_clicked();

    void on_pb_ReadPower_clicked();

    void on_pb_Test_clicked();

    void on_pb_Calc_clicked();

private:
    Ui::MainWindow *ui;
    clyyControl *m_pControl;
    int m_nTimerId;

private:
    void saveResultToFile(const QString &path, const QList<double> &line);
    void changeTemperature(double speed, double Aspeed);
    double getResistance(double speed);
    void compareTemperature(unsigned char nFrom, unsigned char nTo);
    bool isStable(double *tempera);
    void calc(double vol);

protected:
    void timerEvent(QTimerEvent *e);
};

#endif // MAINWINDOW_H
