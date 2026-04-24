#include "arduino.h"

#include <QDebug>

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor / Destructor
// ─────────────────────────────────────────────────────────────────────────────

Arduino::Arduino(QObject *parent)
    : QObject(parent)
    , serial(new QSerialPort(this))
    , arduino_is_available(false)
{
    qDebug() << "Arduino serial pointer:" << serial;
}

Arduino::~Arduino()
{
    close_arduino();
}

// ─────────────────────────────────────────────────────────────────────────────
//  connect_arduino()
//  Search the port on which the arduino card identified by arduino_uno_vendor_id
//  is connected (mirrors the slide implementation).
// ─────────────────────────────────────────────────────────────────────────────
int Arduino::connect_arduino()
{
    arduino_is_available = false;
    arduino_port_name.clear();
    pendingInput.clear();

    if (serial->isOpen()) {
        serial->close();
    }

    // ── 1. Try to identify the board by vendor / product ID ──────────
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier()  == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_product_id) {
                arduino_is_available = true;
                arduino_port_name    = serial_port_info.portName();
            }
        }
    }

    // ── 2. Fallback: match by description keywords (CH340, Arduino, USB Serial) ──
    if (!arduino_is_available) {
        foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
            const QString sig = (serial_port_info.description() + " " +
                                 serial_port_info.manufacturer()).toLower();
            if (sig.contains("arduino") || sig.contains("ch340") ||
                sig.contains("usb serial")) {
                arduino_is_available = true;
                arduino_port_name    = serial_port_info.portName();
                break;
            }
        }
    }

    qDebug() << "arduino_port_name is:" << arduino_port_name;

    if (arduino_is_available) {
        // ── Configuration of the communication (flow, baud, bits …) ──
        serial->setPortName(arduino_port_name);

        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);   // bit rate: 9600 bits/s
            serial->setDataBits(QSerialPort::Data8);      // data length: 8 bit
            serial->setParity(QSerialPort::NoParity);     // 1 optional parity bit
            serial->setStopBits(QSerialPort::OneStop);    // number of stop bits: 1
            serial->setFlowControl(QSerialPort::NoFlowControl);

            QObject::disconnect(serial, nullptr, this, nullptr);
            QObject::connect(serial, &QSerialPort::readyRead,
                             this, &Arduino::handleReadyRead);
            return 0;  // connected successfully
        }
        return 1;      // found but could not open
    }

    return -1;         // not found
}

// ─────────────────────────────────────────────────────────────────────────────
//  close_arduino()
// ─────────────────────────────────────────────────────────────────────────────
int Arduino::close_arduino()
{
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

// ─────────────────────────────────────────────────────────────────────────────
//  write_to_arduino()
// ─────────────────────────────────────────────────────────────────────────────
int Arduino::write_to_arduino(QByteArray d)
{
    if (serial->isWritable()) {
        serial->write(d);   // send data to Arduino
    } else {
        qDebug() << "Couldn't write to serial!";
    }
    return 0;
}

// ─────────────────────────────────────────────────────────────────────────────
//  read_from_arduino()
// ─────────────────────────────────────────────────────────────────────────────
QByteArray Arduino::read_from_arduino()
{
    if (!pendingInput.isEmpty()) {
        data = pendingInput;
        pendingInput.clear();
        return data;
    }

    if (serial->isReadable()) {
        data = serial->readAll();
        return data;
    }
    return QByteArray();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Accessors
// ─────────────────────────────────────────────────────────────────────────────
QSerialPort *Arduino::getserial()
{
    return serial;
}


QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

void Arduino::handleReadyRead()
{
    pendingInput.append(serial->readAll());

    int lineEnd = -1;
    while ((lineEnd = pendingInput.indexOf('\n')) != -1) {
        QByteArray line = pendingInput.left(lineEnd);
        pendingInput.remove(0, lineEnd + 1);

        QString uid = QString::fromUtf8(line).trimmed();
        if (!uid.isEmpty()) {
            emit cardScanned(uid);
        }
    }
}
void Arduino::sendResponse(const QString &response)
{
    if (serial->isOpen()) {
        QByteArray data = response.toUtf8() + "\n";
        serial->write(data);
        serial->flush(); 
    }
}
