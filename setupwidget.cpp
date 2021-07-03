/***************************************************************************
                          setupwidget.cpp  -  description
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
#include "setupwidget.h"

SetupWidget::SetupWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "SetupWidget::SetupWidget" << endl;
    scanSerialPortButton = new QPushButton(tr("Scan"));
    serialPortComboBox = new QComboBox;
    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    createUI();
    qDebug() << "SetupWidget::SetupWidget-END" << endl;
}

//void portSelectedSignal(QString);

void SetupWidget::createUI()
{
    qDebug() << "SetupWidget::createUI" << endl;
    QHBoxLayout * buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(scanSerialPortButton, 0, 0);
    layout->addWidget(serialPortComboBox, 0, 1);
    layout->addLayout(buttonLayout, 1, 1);

    setLayout(layout);
    connect (scanSerialPortButton, SIGNAL(clicked()), SLOT(slotScanPorts()));
    connect (okButton, SIGNAL(clicked()), SLOT(slotOKButtonClicked()));
    connect (cancelButton, SIGNAL(clicked()), SLOT(slotCancelButtonClicked()));

    qDebug() << "SetupWidget::createUI-END" << endl;
}

void SetupWidget::slotOKButtonClicked()
{
    emit portSelectedSignal(serialPortComboBox->currentText());
    qDebug() << "SetupWidget::slotOKButtonClicked: " << serialPortComboBox->currentText() << endl;
    close();
}

void SetupWidget::slotCancelButtonClicked()
{
    close();
}

void SetupWidget::slotScanPorts()
{
     //qDebug() << "MainWindow::slotScanPorts" << endl;
    fillSerialPortsComboBox();
}

void SetupWidget::fillSerialPortsComboBox()
{
     //qDebug() << "MainWindow::fillSerialPortsComboBox" << endl;
    serialPortComboBox->clear();
    serialPortComboBox->addItems(getAvailableSerialPorts());
}

QStringList SetupWidget::getAvailableSerialPorts()
{
     //qDebug() << "MainWindow::getAvailableSerialPorts" << endl;
    QStringList st;
    st.clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        //st << info.portName();
         //qDebug() << "MainWindow::getAvailableSerialPorts: " << info.systemLocation() << endl;
        st << info.systemLocation();
    }
    st.sort();
    return st;
}


void SetupWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    fillSerialPortsComboBox();
}

