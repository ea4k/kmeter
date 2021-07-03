/***************************************************************************
                          swrlevelmeter.cpp  -  description
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

#include "swrlevelmeter.h"

#include <QTimer>
#include <QDebug>



SWRLevelMeter::SWRLevelMeter(QWidget *parent)
{
    swrMeter = new LevelMeter;
    swrLabel = new QLabel;

    createUI();
}

SWRLevelMeter::~SWRLevelMeter()
{

}

void SWRLevelMeter::createUI()
{
    swrMeter->addTopBar(true);
    swrMeter->setWide(false);
    textLabel = QString(tr("SWR - 0.00"));
    qDebug() << "SWRLevelMeter::SWRLevelMeter: length: " << QString::number(textLabel.length()) << endl;
    swrLabel->setText(textLabel);
    swrLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    swrLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(swrMeter);
    layout->addWidget(swrLabel);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    setLayout(layout);

}

void SWRLevelMeter::levelChanged(qreal rmsLevel)
{
    //qDebug() << "SWRLevelMeter::levelChanged: "  << QString::number(rmsLevel) << endl;
    swrMeter->levelChanged(rmsLevel);
    if (rmsLevel == 1.0)
    {
        textLabel = QString(tr("SWR - 1.00"));
    }
    else
    {
        textLabel = QString(tr("SWR - ")) + QString::number(rmsLevel);
    }


    //qDebug() << "SWRLevelMeter::SWRLevelMeter: length1: " << QString::number(textLabel.length()) << endl;
    swrLabel->setText(textLabel);
}


