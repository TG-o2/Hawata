#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QString>

/**
 * Arduino class — wraps QSerialPort to provide a clean interface
 * for communicating with an Arduino board over a serial link.
 *
 * Slide-pattern methods:
 *   connect_arduino()      — open the connection
 *   close_arduino()        — close the connection
 *   write_to_arduino()     — send data to the board
 *   read_from_arduino()    — receive data from the board
 *   getserial()            — accessor for the underlying QSerialPort*
 *   getarduino_port_name() — accessor for the detected port name
 */
class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    ~Arduino();

    /**
     * Searches all available ports for the Arduino UNO (by vendor/product ID
     * or by common description keywords such as "arduino", "ch340", "usb serial").
     * Configures and opens the port at 9600 baud, 8N1.
     *
     * Returns:
     *   0  — Arduino found AND successfully connected
     *   1  — Arduino found but could NOT open the port
     *  -1  — Arduino not found on any port
     */
    int connect_arduino();
    int connectArduino() { return connect_arduino(); }

    /**
     * Closes the serial port if it is currently open.
     * Returns 0 on success, 1 if the port was already closed.
     */
    int close_arduino();

    /**
     * Writes the supplied byte array to the Arduino via the serial link.
     * No-op (with qDebug warning) if the port is not writable.
     */
    int write_to_arduino(QByteArray d);
    void sendResponse(const QString &response);


    /**
     * Reads all available bytes from the Arduino.
     * Returns an empty QByteArray if nothing is readable.
     */
    QByteArray read_from_arduino();

    /** Returns a pointer to the underlying QSerialPort object. */
    QSerialPort *getserial();

    /** Returns the name of the port the Arduino was found on (e.g. "COM3", "/dev/ttyUSB0"). */
    QString getarduino_port_name();

signals:
    void cardScanned(const QString &uid);

private slots:
    void handleReadyRead();

private:
    // ── Vendor / product identifiers for Arduino UNO ──────────────────
    static const quint16 arduino_uno_vendor_id  = 9025;   // 0x2341
    static const quint16 arduino_uno_product_id = 67;     // 0x0043

    QSerialPort *serial;               ///< Serial-port object (heap-allocated in ctor)
    QString      arduino_port_name;    ///< Name of the detected port
    bool         arduino_is_available; ///< True once a matching port is found
    QByteArray   data;                 ///< Buffer for data read from Arduino
    QByteArray   pendingInput;         ///< Raw bytes collected from readyRead()
};

#endif // ARDUINO_H
