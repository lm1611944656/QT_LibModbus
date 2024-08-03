#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "modbus.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void setupModbus();
    void readModbusRegisters();
    void readModbusCoils();
    void writeModbusRegisters();

    modbus_t *my_bus;   // 定义modbus上下文
    uint16_t modbus_hold_reg[100];  // 缓存读取到的数据
    uint16_t modbus_input_reg[100]; // 缓存输入寄存器数据

    uint8_t modbus_coil_status[10]; // 缓存读取到的线圈状态
};
#endif // MAINWINDOW_H
