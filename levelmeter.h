#ifndef LEVELMETER_H
#define LEVELMETER_H
/***************************************************************************
                          levelmeter.h  -  description
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

#include <QTime>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

/**
 * Widget which displays a vertical audio level meter, indicating the
 * RMS and peak levels of the window of audio samples most recently analyzed
 * by the Engine.
 */
class LevelMeter : public QWidget
{
    Q_OBJECT

public:
    explicit LevelMeter(QWidget *parent = nullptr);
    ~LevelMeter();
    void addTopBar(bool _b);
    void setWide(bool _b);
    void paintEvent(QPaintEvent *event) override;

public slots:
    void reset();
    void levelChanged(qreal rmsLevel);

private slots:
    void redrawTimerExpired();

private:
    bool topBar, wideBar;
    /**
     * Height of RMS level bar.
     * Range 0.0 - 1.0.
     */
    qreal m_rmsLevel;

    QTimer *m_redrawTimer;

    QColor m_rmsColor;
    QColor m_peakColor;


};

#endif // LEVELMETER_H
