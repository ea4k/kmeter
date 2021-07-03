#ifndef NUMBERSMETERWIDGET_H
#define NUMBERSMETERWIDGET_H
/***************************************************************************
                          numbersmeterwidget.h  -  description
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
#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class NumbersMeterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NumbersMeterWidget(QWidget *parent = nullptr);
    void setPWR(const double _pwr);
    void setSWR(const double _swr);
    void setdBm(const double _dBm);
    void setRange(const int _i);

    void setZ(const QString &_z);
    void setAlarm(const int _a);
    void setCall(const QString &_c);
    void setMeasure(const int _i);
    void setPhase(const QString &_p);

signals:

public slots:

private:
    void createUI();

    QLabel pwrLabel, SWRLabel, pwrRangeLabel, dBmLabel;
    QLabel zLabel, AlarmLabel, callLabel, measureLabel, phaseLabel;
};

#endif // NUMBERSMETERWIDGET_H

