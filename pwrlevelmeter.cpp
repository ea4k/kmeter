/***************************************************************************
                          pwrlevelmeter.cpp  -  description
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

#include "pwrlevelmeter.h"

#include <QTimer>
#include <QDebug>



PWRLevelMeter::PWRLevelMeter(QWidget *parent)
{
    pwrMeter = new LevelMeter;
    pwrLabel = new QLabel;
    LCDNumber = new QLCDNumber;

    LCDNumber->setMode(QLCDNumber::Dec);
    LCDNumber->setSegmentStyle(QLCDNumber::Flat);
    //LCDNumber->setSegmentStyle(QLCDNumber::Outline);
    LCDNumber->setDigitCount(6);
    LCDNumber->setSmallDecimalPoint(false);
    textLabel = QString(tr("0000.00 - W"));
    //qDebug() << "PWRLevelMeter::PWRLevelMeter: length: " << QString::number(textLabel.length()) << endl;
    //pwrLabel->setText(textLabel);
    //pwrLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    //pwrLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(pwrMeter);
    layout->addWidget(LCDNumber);
    //layout->addWidget(pwrLabel);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    setLayout(layout);

}

PWRLevelMeter::~PWRLevelMeter()
{

}

void PWRLevelMeter::levelChanged(qreal rmsLevel)
{
    //qDebug() << "PWRLevelMeter::levelChanged: "  << QString::number(rmsLevel) << endl;
    pwrMeter->levelChanged(rmsLevel/100);
    LCDNumber->display(rmsLevel);
    /*
    if (rmsLevel == 0.0)
    {
        textLabel = QString(tr("0000.00 - W"));
    }
    else if (rmsLevel<10)
    {
        textLabel = "   " + QString::number(rmsLevel) + " - W";
    }
    else if (rmsLevel<100)
    {
        textLabel = "  " + QString::number(rmsLevel) + " - W";
    }
    else if (rmsLevel<1000)
    {
        textLabel = " " + QString::number(rmsLevel) + " - W";
    }
    else
    {
        textLabel = QString::number(rmsLevel) + " - W";
    }


    //qDebug() << "PWRLevelMeter::PWRLevelMeter: length1: " << QString::number(textLabel.length()) << endl;
    pwrLabel->setText(textLabel);
    */
}


