#include "mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupModbus();
    readModbusRegisters();
    readModbusCoils();
    writeModbusRegisters();
}

MainWindow::~MainWindow()
{
    if (my_bus) {
        modbus_close(my_bus);
        modbus_free(my_bus);
    }
}

void MainWindow::setupModbus()
{
    const char *ip = "127.0.0.1";  // 你的Modbus服务器IP地址
    int port = 502;                // Modbus TCP默认端口

    my_bus = modbus_new_tcp(ip, port);
    if (my_bus == nullptr) {
        qDebug() << "Unable to allocate libmodbus context";
        return;
    }

    if (modbus_connect(my_bus) == -1) {
        qDebug() << "Connection failed: " << modbus_strerror(errno);
        modbus_free(my_bus);
        my_bus = nullptr;
        return;
    }

    qDebug() << "Modbus connection successful";
}

void MainWindow::readModbusRegisters()
{
    if (my_bus == nullptr) {
        qDebug() << "Modbus context is null";
        return;
    }

    int rc = modbus_read_registers(my_bus, 0, 20, modbus_hold_reg);
    if (rc == -1) {
        qDebug() << "Failed to read holding registers: " << modbus_strerror(errno);
        return;
    }

    qDebug() << "Read" << rc << "holding registers successfully";

    // 示例：打印读取到的前10个寄存器值
    for (int i = 0; i < 20; ++i) {
        qDebug() << "Register" << i << ":" << modbus_hold_reg[i];
    }
}

void MainWindow::readModbusCoils()
{
    if (my_bus == nullptr) {
        qDebug() << "Modbus context is null";
        return;
    }

    int starting_address = 0; // 起始地址
    int num_coils = 10; // 请求的线圈数量

    int rc = modbus_read_bits(my_bus, starting_address, num_coils, modbus_coil_status);
    if (rc == -1) {
        qDebug() << "Failed to read coils: " << modbus_strerror(errno);
        return;
    }

    qDebug() << "Read" << rc << "coils successfully";

    // 示例：打印读取到的线圈状态
    for (int i = 0; i < num_coils; ++i) {
        qDebug() << "Coil" << i << ":" << (modbus_coil_status[i] ? "ON" : "OFF");
    }
}


void MainWindow::writeModbusRegisters()
{
    if (my_bus == nullptr) {
        qDebug() << "Modbus context is null";
        return;
    }

    int starting_address = 0; // 起始地址
    int num_registers = 10; // 请求的寄存器数量
    uint16_t values_to_write[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // 要写入的值

    int rc = modbus_write_registers(my_bus, starting_address, num_registers, values_to_write);
    if (rc == -1) {
        qDebug() << "Failed to write holding registers: " << modbus_strerror(errno);
        return;
    }

    qDebug() << "Wrote" << rc << "holding registers successfully";
}
