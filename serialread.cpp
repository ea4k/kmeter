/***************************************************************************
                          serialread.cpp  -  description
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
#include "serialread.h"
// http://ea7tb.com/index.php/2020/04/26/lp-100a-puerto-serie/

SerialRead::SerialRead()
{
    serialPort = new QSerialPort;
    bauds = 115200;
    bits = 8;
    stopBit = 1;
    parity = false;
    timer = new QTimer(this);

    createActions();

    //connect(timer, SIGNAL(timeout()), this, SLOT(slotTimeOut()) );
}

SerialRead::~SerialRead()
{}

void SerialRead::createActions()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTXTimeOut()));
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(slotRXReadyRead()));
    connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(slotRXHandleError(QSerialPort::SerialPortError)));

    //serialPort = new QSerialPort();
}

void SerialRead::setSerialPort(const QString &_p)
{
    qDebug() << "SerialRead::setSerialPort: " << _p << endl;
    serialPort->clearError();
    serialPortString = _p.toLocal8Bit().constData();
    //serialPort->toLocal8Bit().constData()

    serialPort->setPortName(_p.toLocal8Bit().constData());
    serialPort->setBaudRate(bauds);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->clearError();
    bool opened = serialPort->open(QIODevice::ReadWrite);
    if (opened)
    {
         qDebug() << "SerialRead::sendData: OPENED"  << endl;
         emit serialPortOpened(true);

    }
    else
    {
        emit serialPortOpened(false);
        qDebug() << "SerialRead::sendData: NOT OPENED: " << QString::number(serialPort->error())  << endl;
    }

    //bool opened = serialPort->open(QIODevice::WriteOnly);

}

void SerialRead::slotTXTimeOut()
{
     qDebug() << "SerialRead::slotTimeOut " << endl;
    timer->stop();

}

void SerialRead::sendM()
{
     qDebug() << "SerialRead::sendM" << endl;
    sendData("M");
}

void SerialRead::sendP()
{
     //qDebug() << "SerialRead::sendP" << endl;
    sendData("P");
}

void SerialRead::sendA()
{
     qDebug() << "SerialRead::sendA" << endl;
    sendData("A");
}

void SerialRead::sendF()
{
     qDebug() << "SerialRead::sendA" << endl;
    sendData("F");
}

void SerialRead::sendData(const QString &_d)
{
   //qDebug() << "SerialRead::sendData: " << _d  << endl;
    QString dataToSend;
    if (_d == "P")
    {
        dataToSend = "P";
    }
    else if (_d == "M")
    {
        dataToSend = "M";
    }
    else if (_d == "A")
    {
        dataToSend = "A";
    }
    else if (_d == "F")
    {
        dataToSend = "F";
    }
    else
    {
        return;
    }



    QByteArray writeData;
    writeData.clear();


    writeData.append(dataToSend.toLocal8Bit());

    if ((!writeData.isEmpty()) && (serialPort->isOpen()))
    {
        //qDebug() << "SerialRead::sendData: Writing... : "   << endl;
        serialPort->write(writeData);
        timer->start(5000);
    }
    else
    {
        if (!serialPort->isOpen())
        {
            qDebug() << "SerialRead::sendData: Serial port is closed"   << endl;
            emit serialPortOpened(false);
        }

    }

}

void SerialRead::slotRXTimeOut()
{
     qDebug() << "SerialRead::slotRXTimeOut"   << endl;
}

void SerialRead::slotRXReadyRead()
{
     //qDebug() << "SerialRead::slotRXReadyRead"   << endl;
    m_readData.append(serialPort->readAll());


    parseAnswer(m_readData);
     //qDebug() << "SerialRead::slotRXReadyRead" << m_readData   << endl;
     //qDebug() << "SerialRead::slotRXReadyRead - length: " << QString::number(m_readData.length())   << endl;
    //";0000.00,046.9,087.5,3,EA4K  ,2,1,-2.3,1.00"
    //if (!timer.isActive())
    //    timer.start(5000)
}

void SerialRead::slotRXHandleError(QSerialPort::SerialPortError error)
{
     qDebug() << "SerialRead::slotRXHandleError"   << endl;
    if (error == QSerialPort::ReadError) {
         qDebug() << QObject::tr("An I/O error occurred while reading "
                                         "the data from port %1, error: %2")
                             .arg(serialPort->portName())
                             .arg(serialPort->errorString())
                          << endl;
        //it errorSignal;
     }

}

void SerialRead::parseAnswer(const QByteArray &_d)
{ //https://ea7tb.com/index.php/2020/04/26/lp-100a-puerto-serie/
     //qDebug() << "SerialRead::parseAnswer: " << QString::number(_d.length())  << endl;
    if ((_d.startsWith(';')) &&  (_d.length() == 43) )
    {
         //qDebug() << "SerialRead::parseAnswer: COMPLETE: " << _d   << endl;
        QString _data = _d.right(_d.length()-1);
         //qDebug() << "SerialRead::parseAnswer: DATA: " << _data   << endl;
        //DATA:  "0000.00,046.9,087.6,3,EA4K  ,2,1,-2.3,1.00"
        QStringList fields;
        fields.clear();
        fields << _data.split(',');
        emit meterData(fields);
        m_readData.clear();

         //qDebug() << "SerialRead::parseAnswer: meterData emitted "   << endl;
    // m_readData.clear();
    }
    else if (_d.startsWith(';'))
    {
       //qDebug() << "SerialRead::parseAnswer: Receiving...: " << _d   << endl;
    }
    else
    {
         //qDebug() << "SerialRead::parseAnswer: Non valid data: " << _d   << endl;
    }
}
