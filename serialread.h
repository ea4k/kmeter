#ifndef SERIALREAD_H
#define SERIALREAD_H
/***************************************************************************
                          serialread.h  -  description
                             -------------------
    begin                : april 2020
    copyright            : (C) 2020 by Jaime Robles
    email                : jaime@robles.es
 ***************************************************************************/

/*****************************************************************************
 * This file is part of KMeter.                                              *
 *                                                                           *
 *    KMeter is free software: you can redistribute it and/or modify         *
 *    it under the terms of the GNU General Public License as published by   *
 *    the Free Software Foundation, either version 3 of the License, or      *
 *    (at your option) any later version.                                    *
 *                                                                           *
 *    KMeter is distributed in the hope that it will be useful,              *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *    GNU General Public License for more details.                           *
 *                                                                           *
 *    You should have received a copy of the GNU General Public License      *
 *    along with KMeter.  If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                           *
 *****************************************************************************/
#include <QObject>
#include <QSerialPort>
#include <QTimer>


#include <QDebug>

class SerialRead : public QObject
{
    Q_OBJECT

public:
    SerialRead();
    ~SerialRead();
    void setSerialPort(const QString &_p);

    void sendM();
    void sendP();
    void sendA();
    void sendF();

private slots:
    void slotTXTimeOut();
    void slotRXTimeOut();
    void slotRXReadyRead();
    void slotRXHandleError(QSerialPort::SerialPortError error);

signals:
    void meterData(QStringList _data);
    void serialPortOpened(bool _o);

private:

    void sendData(const QString &_d);
    void createActions();
    void parseAnswer(const QByteArray &_d);

    int bauds, bits, stopBit;
    bool parity;
    QString serialPortString;

    QSerialPort *serialPort;
    QByteArray m_readData;

    QTimer *timer;
    float pwr, impedance, phase;

};

#endif // SERIALREAD_H
