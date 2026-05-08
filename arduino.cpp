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
    cardScanBuffer.clear();

    if (serial->isOpen()) {
        serial->close();
    }

    // ── DEBUG: Log all available ports ────────────────────────────────
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    qDebug() << "──────────────────────────────────────────────────────";
    qDebug() << "Available COM ports:" << availablePorts.size();
    for (const QSerialPortInfo &port : availablePorts) {
        qDebug() << "  Port:" << port.portName()
                 << "| Description:" << port.description()
                 << "| Manufacturer:" << port.manufacturer()
                 << "| VendorID:" << port.vendorIdentifier()
                 << "| ProductID:" << port.productIdentifier();
    }
    qDebug() << "──────────────────────────────────────────────────────";

    // ── 1. Try to identify the board by vendor / product ID ──────────
    foreach (const QSerialPortInfo &serial_port_info, availablePorts) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier()  == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_product_id) {
                arduino_is_available = true;
                arduino_port_name    = serial_port_info.portName();
                qDebug() << "✓ Found Arduino by Vendor/Product ID on port:" << arduino_port_name;
            }
        }
    }

    // ── 2. Fallback: match by description keywords (extended list) ────
    if (!arduino_is_available) {
        foreach (const QSerialPortInfo &serial_port_info, availablePorts) {
            const QString desc = serial_port_info.description().toLower();
            const QString manuf = serial_port_info.manufacturer().toLower();
            const QString combined = desc + " " + manuf;
            
            // Expanded keyword list: supports CH340, FT232, CP2102, WCH, etc.
            if (combined.contains("arduino") || 
                combined.contains("ch340") ||
                combined.contains("ch341") ||
                combined.contains("usb serial") ||
                combined.contains("ft232") ||
                combined.contains("cp2102") ||
                combined.contains("cp210x") ||
                combined.contains("wch") ||
                combined.contains("silicon labs") ||
                combined.contains("prolific") ||
                combined.contains("pl2303")) {
                arduino_is_available = true;
                arduino_port_name    = serial_port_info.portName();
                qDebug() << "✓ Found Arduino by description match on port:" << arduino_port_name;
                qDebug() << "  Description:" << desc << "| Manufacturer:" << manuf;
                break;
            }
        }
    }

    // ── 3. Last resort: if any COM port exists and previous methods failed ──
    if (!arduino_is_available && !availablePorts.isEmpty()) {
        // Take the first available COM port (useful for unknown USB chips)
        arduino_port_name = availablePorts.first().portName();
        arduino_is_available = true;
        qDebug() << "⚠ Arduino not recognized by ID/keyword - using first available port:" << arduino_port_name;
        qDebug() << "  Description:" << availablePorts.first().description();
        qDebug() << "  Manufacturer:" << availablePorts.first().manufacturer();
    }

    if (!arduino_is_available) {
        qDebug() << "✗ No COM ports found - Arduino not connected";
        return -1;  // not found
    }

    qDebug() << "Attempting to open port:" << arduino_port_name;

    if (arduino_is_available) {
        // ── Configuration of the communication (flow, baud, bits …) ──
        serial->setPortName(arduino_port_name);

        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);   // bit rate: 9600 bits/s
            serial->setDataBits(QSerialPort::Data8);      // data length: 8 bit
            serial->setParity(QSerialPort::NoParity);     // 1 optional parity bit
            serial->setStopBits(QSerialPort::OneStop);    // number of stop bits: 1
            serial->setFlowControl(QSerialPort::NoFlowControl);

            qDebug() << "✓ Successfully opened serial port:" << arduino_port_name;

            QObject::disconnect(serial, nullptr, this, nullptr);
            QObject::connect(serial, &QSerialPort::readyRead,
                             this, &Arduino::handleReadyRead);
            return 0;  // connected successfully
        } else {
            qDebug() << "✗ Failed to open port:" << arduino_port_name;
            qDebug() << "  Error:" << serial->errorString();
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
    const QByteArray chunk = serial->readAll();
    if (chunk.isEmpty()) {
        return;
    }

    // Keep a full raw stream for consumers that call read_from_arduino().
    pendingInput.append(chunk);

    // Parse card lines from a dedicated buffer so we do not consume pendingInput.
    cardScanBuffer.append(chunk);

    int lineEnd = -1;
    while ((lineEnd = cardScanBuffer.indexOf('\n')) != -1) {
        QByteArray line = cardScanBuffer.left(lineEnd);
        cardScanBuffer.remove(0, lineEnd + 1);

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
