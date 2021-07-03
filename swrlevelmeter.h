#ifndef SWRSWRLevelMeter_H
#define SWRSWRLevelMeter_H
/***************************************************************************
                          swrlevelmeter.h  -  description
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
#include <QTime>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

class SWRLevelMeter : public QWidget
{
    Q_OBJECT

public:
    explicit SWRLevelMeter(QWidget *parent = nullptr);
    ~SWRLevelMeter();

public slots:
    void levelChanged(qreal rmsLevel);

private slots:


private:
    void createUI();
    LevelMeter *swrMeter;
    QLabel *swrLabel;
    QString textLabel;

};

#endif // SWRSWRLevelMeter_H
