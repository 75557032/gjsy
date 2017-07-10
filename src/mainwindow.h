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

private:
    Ui::MainWindow *ui;
    clyyControl *m_pControl;
};

#endif // MAINWINDOW_H
