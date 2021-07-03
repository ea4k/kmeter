#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/***************************************************************************
                          mainwindow.h  -  description
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

#include <QMainWindow>
#include <QtWidgets>
#include <QSerialPortInfo>
#include "setupwidget.h"
#include "serialread.h"
#include "pwrlevelmeter.h"
#include "swrlevelmeter.h"
#include "numbersmeterwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    int slotFileClose();
    void slotSetup();
    void slotSerialPortReceived(QString _sp);
    //void slotOKButtonClicked();
    void slotAButtonClicked();
    void slotMButtonClicked();
    void slotPButtonClicked();
    void slotFButtonClicked();
    void slotReceiveData(QStringList _d);
    void slotUpdateTime();
    void slotSerialPortOpened(bool _o);
    void slotNormalUISetup();
    void slotSmallUISetup();

private:
    void createUI();
    void createSmallUI();
    void createNormalUI();

    QStackedWidget *stackedWidget;
    QWidget *smallWidget;
    QWidget *normalWidget;

    QMenu *fileMenu;
    QMenu *setupMenu;

    QAction *exitAct;
    QAction *setupAct;
    QAction *smallUIAct;
    QAction *normalUIAct;


    SerialRead *serial;

    QWidget *mainWidget;
    QPushButton *AButton, *MButton, *PButton, *FButton;

    SetupWidget *setupWidget;
    PWRLevelMeter *pwrLevelMeterNormal, *pwrLevelMeterSmall;
    SWRLevelMeter *swrLevelMeterNormal, *swrLevelMeterSmall;

    double peakLevel;

    NumbersMeterWidget *numbersMeterWidget;

    QTimer timer;
    bool continuousPoll;

    QVBoxLayout *smallLayout, *normalLayout;

};

#endif // MAINWINDOW_H
