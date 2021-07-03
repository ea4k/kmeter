/***************************************************************************
                          levelmeter.cpp  -  description
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

#include "levelmeter.h"

//#include <math.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>


// Constants
const int RedrawInterval = 00; // 50ms
const qreal PeakDecayRate = 1; //1
const int PeakHoldLevelDuration = 000; // 200 ms


LevelMeter::LevelMeter(QWidget *parent)
    :   QWidget(parent)
    ,   m_rmsLevel(0.0)
    ,   m_redrawTimer(new QTimer(this))
    ,   m_rmsColor(Qt::blue)
    ,   m_peakColor(Qt::green)
{

    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    setMinimumWidth(5);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    //setMinimumWidth(parent->width()/3);
    setMinimumHeight(5);
    topBar = false;
    wideBar = true;

    connect(m_redrawTimer, &QTimer::timeout, this, &LevelMeter::redrawTimerExpired);
    m_redrawTimer->start(RedrawInterval);
}

LevelMeter::~LevelMeter()
{

}

void LevelMeter::reset()
{
    //qDebug() << "LevelMeter::reset" << endl;
    m_rmsLevel = 0.0;
    update();
}

void LevelMeter::levelChanged(qreal rmsLevel)
{
    //qDebug() << "LevelMeter::levelChanged" << endl;

    m_rmsLevel = rmsLevel;

    update();
}

void LevelMeter::redrawTimerExpired()
{
    //qDebug() << "LevelMeter::redrawTimerExpired" << endl;
    update();
}
void LevelMeter::addTopBar(bool _b)
{
    topBar = _b;
    setMinimumHeight(5);
}

void LevelMeter::setWide(bool _b)
{
    if (!_b)
    {
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    }

}
void LevelMeter::paintEvent(QPaintEvent *event)
{
    //qDebug() << "LevelMeter::paintEvent" << endl;
    Q_UNUSED(event)

    QRect bar = rect();

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    double barRight = (m_rmsLevel * width());
    bar.setRight(barRight);
    painter.fillRect(bar, m_rmsColor);

    if (topBar)
    {
        QRect barR = rect();
        barR.setWidth(width());
        barR.setHeight(height() / 5);
        painter.fillRect(barR, Qt::red);

        QRect barY = rect();
        //barY.setLeft(100 * 60 / width());
        barY.setWidth(100 * width() / 300);
        barY.setHeight(height() / 5);
        painter.fillRect(barY, Qt::yellow);

        QRect barG = rect();
        barG.setWidth(60 * width() / 300);
        barG.setHeight(height() / 5);
        painter.fillRect(barG, Qt::green);

    }

}
