/***************************************************************************
                          mainwindow.cpp  -  description
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
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)

{
    //mainWidget = new QWidget;
    numbersMeterWidget = new NumbersMeterWidget;
    setupWidget = new SetupWidget();

    AButton = new QPushButton(tr("Alarm"));
    MButton = new QPushButton(tr("Mode"));
    PButton = new QPushButton(tr("P"));
    FButton = new QPushButton(tr("Peak/Avg"));
    //serialPortComboBox = new QComboBox;
    pwrLevelMeterNormal = new PWRLevelMeter(this);
    pwrLevelMeterSmall = new PWRLevelMeter(this);
    swrLevelMeterNormal = new SWRLevelMeter(this);
    swrLevelMeterSmall = new SWRLevelMeter(this);

    continuousPoll = false;

    stackedWidget = new QStackedWidget;
    smallWidget = new QWidget(this);
    normalWidget = new QWidget(this);

    smallLayout = new QVBoxLayout;
    normalLayout = new QVBoxLayout;

    peakLevel = 0.0;

    setupAct = new QAction(tr("&Setup..."), this);
    smallUIAct = new QAction(tr("Small UI"), this);
    normalUIAct = new QAction(tr("Normal UI"), this);

    serial = new SerialRead;
    createUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createUI()
{
    setWindowTitle("KMeter");
    fileMenu = menuBar()->addMenu(tr("&File"));
    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    exitAct->setMenuRole(QAction::QuitRole);
    exitAct->setShortcut(Qt::CTRL + Qt::Key_X);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(slotFileClose()));

    setupMenu = menuBar()->addMenu(tr("&Setup"));

    setupMenu->addAction(setupAct);
    setupAct->setMenuRole(QAction::PreferencesRole);
    connect(setupAct, SIGNAL(triggered()), this, SLOT(slotSetup()));

    setupMenu->addAction(smallUIAct);
    smallUIAct->setMenuRole(QAction::PreferencesRole);
    connect(smallUIAct, SIGNAL(triggered()), this, SLOT(slotSmallUISetup()));

    setupMenu->addAction(normalUIAct);
    normalUIAct->setMenuRole(QAction::PreferencesRole);
    connect(normalUIAct, SIGNAL(triggered()), this, SLOT(slotNormalUISetup()));

    createNormalUI();
    createSmallUI();

    stackedWidget->addWidget(smallWidget);
    stackedWidget->addWidget(normalWidget);
    stackedWidget->setCurrentWidget(normalWidget);

    //QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(stackedWidget);
    //setLayout(layout);

    //setCentralWidget(stackedWidget);
    setCentralWidget(stackedWidget);

    //connect(scanSerialPortButton, SIGNAL(clicked(bool)), this, SLOT(slotScanPorts(QString)) );
    //connect(okButton, SIGNAL(clicked(bool)), this, SLOT(slotOKButtonClicked()) );
    connect(AButton, SIGNAL(clicked(bool)), this, SLOT(slotAButtonClicked()) );
    connect(MButton, SIGNAL(clicked(bool)), this, SLOT(slotMButtonClicked()) );
    connect(PButton, SIGNAL(clicked(bool)), this, SLOT(slotPButtonClicked()) );
    connect(FButton, SIGNAL(clicked(bool)), this, SLOT(slotFButtonClicked()) );
    connect(serial, SIGNAL(meterData(QStringList)), this, SLOT(slotReceiveData(QStringList)) );
    connect(serial, SIGNAL(serialPortOpened(bool)), this, SLOT(slotSerialPortOpened(bool)) );
    connect(&timer, SIGNAL(timeout()), this, SLOT(slotUpdateTime()) );
    connect(setupAct, SIGNAL(triggered()), this, SLOT(slotSetup()));
    connect(setupWidget, SIGNAL(portSelectedSignal(QString)), this, SLOT(slotSerialPortReceived(QString)));

}


void MainWindow::createNormalUI()
{
    //smallLayout->removeWidget(pwrLevelMeter);
    //smallLayout->removeWidget(swrLevelMeter);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(MButton);
    buttonsLayout->addWidget(AButton);
    buttonsLayout->addWidget(FButton);

    normalLayout->addLayout(buttonsLayout);
    normalLayout->addWidget(numbersMeterWidget);
    normalLayout->addWidget(pwrLevelMeterNormal);
    normalLayout->addWidget(swrLevelMeterNormal);

    normalWidget->setLayout(normalLayout);
}


void MainWindow::createSmallUI()
{
    smallLayout->addWidget(pwrLevelMeterSmall);
    smallLayout->addWidget(swrLevelMeterSmall);
    smallWidget->setLayout(smallLayout);

}

void MainWindow::slotNormalUISetup()
{
    stackedWidget->setCurrentWidget(normalWidget);
}

void MainWindow::slotSmallUISetup()
{
    stackedWidget->setCurrentWidget(smallWidget);
}

int MainWindow::slotFileClose()
{
     //qDebug() << "MainWindow::slotFileClose" << endl;
    exit(0);
}

void MainWindow::slotSerialPortOpened(bool _o)
{
    if (_o)
    {
         timer.start(80);
         //qDebug() << "MainWindow::slotSerialPortOpened Serial port Opened" << endl;
    }
    else
    {
         timer.stop();
         //qDebug() << "MainWindow::slotSerialPortOpened Serial port Closed" << endl;
    }
}

void MainWindow::slotSetup()
{
    qDebug() << "MainWindow::slotSetup" << endl;
    setupWidget->show();
    qDebug() << "MainWindow::slotSetup-END" << endl;
}

void MainWindow::slotSerialPortReceived(QString _sp)
{
    qDebug() << "MainWindow::slotScanPorts: " << _sp << endl;
    if (_sp.length()>0)
    {
        serial->setSerialPort(_sp);
        continuousPoll = true;
    }
}


void MainWindow::slotAButtonClicked()
{
     //qDebug() << "MainWindow::slotAButtonClicked" << endl;
    serial->sendA();

}

void MainWindow::slotMButtonClicked()
{
     //qDebug() << "MainWindow::slotMButtonClicked" << endl;
    serial->sendM();

}

void MainWindow::slotPButtonClicked()
{
     //qDebug() << "MainWindow::slotPButtonClicked" << endl;
    serial->sendP();
}

void MainWindow::slotFButtonClicked()
{
     //qDebug() << "MainWindow::slotFButtonClicked" << endl;
    serial->sendF();
}

void MainWindow::slotReceiveData(QStringList _d)
{
    double level;// = _d.at(0).toDouble();

    if (_d.at(5) == "0")
    {
        level =  _d.at(0).toDouble() / 1500;
          //qDebug() << "MainWindow::slotReceiveData - Power/1500: " << QString::number(level) << endl;
    }
    else if (_d.at(5) == "1")
    {
       level =  _d.at(0).toDouble() / 100;
        //qDebug() << "MainWindow::slotReceiveData - Power/100: " << QString::number(level) << endl;
    }
    else if (_d.at(5) == "2")
    {
        level =  _d.at(0).toDouble() / 15;
         //qDebug() << "MainWindow::slotReceiveData - Power/15: " << QString::number(level) << endl;
    }
    else
    {
        //qDebug() << "MainWindow::slotReceiveData - NO POWER"  << endl;
        return;
    }

    level =  _d.at(0).toDouble() ;

    pwrLevelMeterNormal->levelChanged(level);
    pwrLevelMeterSmall->levelChanged(level);
    numbersMeterWidget->setRange(_d.at(5).toInt());
    numbersMeterWidget->setPWR(_d.at(0).toDouble());
    numbersMeterWidget->setSWR(_d.at(8).toDouble());
    swrLevelMeterNormal->levelChanged(_d.at(8).toDouble());
    swrLevelMeterSmall->levelChanged(_d.at(8).toDouble());
    numbersMeterWidget->setdBm(_d.at(7).toDouble());

    numbersMeterWidget->setZ(_d.at(1));
    numbersMeterWidget->setAlarm(_d.at(3).toInt());
    numbersMeterWidget->setCall(_d.at(4));
    numbersMeterWidget->setMeasure(_d.at(6).toInt());
    numbersMeterWidget->setPhase(_d.at(2));

    //qDebug() << "MainWindow::slotReceiveData -        Pwr: " << _d.at(0) << endl;
    //qDebug() << "MainWindow::slotReceiveData - Pwr Normal: " << QString::number(level) << endl;
    //qDebug() << "MainWindow::slotReceiveData -  Impedance: " << _d.at(1)  << endl;
    //qDebug() << "MainWindow::slotReceiveData -      Phase: " << _d.at(2)  << endl;
    //qDebug() << "MainWindow::slotReceiveData -  SWR Alarm: " << _d.at(3)  << endl;
    //qDebug() << "MainWindow::slotReceiveData -   Callsign: " << _d.at(4)  << endl;
    //qDebug() << "MainWindow::slotReceiveData -  Pwr range: " << _d.at(5)  << endl;
    //qDebug() << "MainWindow::slotReceiveData -       Mode: " << _d.at(6) << endl;
    //qDebug() << "MainWindow::slotReceiveData -        dBm: " << _d.at(7) << endl;
    //qDebug() << "MainWindow::slotReceiveData -        SWR: " << _d.at(8)  << endl;

}

void MainWindow::slotUpdateTime()
{
    //qDebug() << "MainWindow::slotUpdateTime" << endl;
    if (continuousPoll)
    {
        serial->sendP();
    }
}


