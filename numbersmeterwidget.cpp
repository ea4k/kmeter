/***************************************************************************
                          numbersmeterwidget.cpp  -  description
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
#include "numbersmeterwidget.h"

NumbersMeterWidget::NumbersMeterWidget(QWidget *parent) : QWidget(parent)
{

    //QLabel pwrLabel, SWRLabel, pwrRangeLabel, dBmLabel;
    createUI();
}

void NumbersMeterWidget::createUI()
{
    pwrLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    pwrLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    SWRLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    SWRLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    pwrRangeLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    pwrRangeLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    dBmLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    dBmLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);

    zLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    zLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    AlarmLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    AlarmLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    callLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    callLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    measureLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    measureLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    phaseLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    phaseLabel.setAlignment(Qt::AlignVCenter| Qt::AlignCenter);

    QLabel *pwrTLabel = new QLabel();
    pwrTLabel->setText(tr("PWR"));
    pwrTLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    pwrTLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QLabel *swrTLabel = new QLabel();
    swrTLabel->setText(tr("SWR"));
    swrTLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    swrTLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QLabel *rangeTLabel = new QLabel();
    rangeTLabel->setText(tr("Range"));
    rangeTLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    rangeTLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QLabel *dBmTLabel = new QLabel();
    dBmTLabel->setText(tr("dBm"));
    dBmTLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    dBmTLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QLabel *ZTLabel = new QLabel();
    ZTLabel->setText(tr("Impedance"));
    ZTLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    ZTLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QLabel *ATLabel = new QLabel();
    ATLabel->setText(tr("Alarm"));
    ATLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    ATLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QLabel *callTLabel = new QLabel();
    callTLabel->setText(tr("Call"));
    callTLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    callTLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QLabel *mTLabel = new QLabel();
    mTLabel->setText(tr("Peak/Avg"));
    mTLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    mTLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QLabel *pTLabel = new QLabel();
    pTLabel->setText(tr("Phase"));
    pTLabel->setAlignment(Qt::AlignVCenter| Qt::AlignCenter);
    pTLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);


    QGridLayout *layout = new QGridLayout;

    layout->addWidget(callTLabel, 0, 0);
    layout->addWidget(&callLabel, 1, 0);

    layout->addWidget(pwrTLabel, 0, 1);
    layout->addWidget(&pwrLabel, 1, 1);

    layout->addWidget(swrTLabel, 0, 2);
    layout->addWidget(&SWRLabel, 1, 2);

    layout->addWidget(dBmTLabel, 2, 0);
    layout->addWidget(&dBmLabel, 3, 0);

    layout->addWidget(mTLabel, 2, 1);
    layout->addWidget(&measureLabel, 3, 1);

    layout->addWidget(ATLabel, 2, 2);
    layout->addWidget(&AlarmLabel, 3, 2);

    layout->addWidget(rangeTLabel, 4, 0);
    layout->addWidget(&pwrRangeLabel, 5, 0);

    layout->addWidget(ZTLabel, 4, 1);
    layout->addWidget(&zLabel, 5, 1);

    layout->addWidget(pTLabel, 4, 2);
    layout->addWidget(&phaseLabel, 5, 2);

    setLayout(layout);

}

void NumbersMeterWidget::setPWR(const double _pwr)
{
    pwrLabel.setText(QString::number(_pwr));
}

void NumbersMeterWidget::setSWR(const double _swr)
{
    SWRLabel.setText(QString::number(_swr));
}

void NumbersMeterWidget::setdBm(const double _dBm)
{
    dBmLabel.setText(QString::number(_dBm));
}

void NumbersMeterWidget::setRange(const int _i)
{
    switch (_i)
    {
    case 0:
        pwrRangeLabel.setText(tr("High"));
    break;
    case 1:
        pwrRangeLabel.setText(tr("Mid"));
    break;
    case 2:
        pwrRangeLabel.setText(tr("Low"));
    break;
    default:
        pwrRangeLabel.setText(tr("Error"));
    break;

    }
}

void NumbersMeterWidget::setZ(const QString &_z)
{
    zLabel.setText(_z);
}

void NumbersMeterWidget::setAlarm(const int _a)
{// Off
    switch (_a)
    {
    case 0:
        AlarmLabel.setText("Off");
    break;
    case 1:
        AlarmLabel.setText(QString::number(1.5));
    break;
    case 2:
        AlarmLabel.setText(QString::number(2.0));
    break;
    case 3:
        AlarmLabel.setText(QString::number(2.5));
    break;
    case 4:
        AlarmLabel.setText(QString::number(3.0));
    break;
    case 5:
        AlarmLabel.setText(tr("Manual"));
    break;
    default:
        AlarmLabel.setText(tr("Error"));
    break;

    }
}

void NumbersMeterWidget::setCall(const QString &_c)
{
    callLabel.setText(_c.trimmed());
}

void NumbersMeterWidget::setMeasure(const int _i)
{
    if (_i == 0)
    {
        measureLabel.setText(tr("Peak"));
    }
    else if (_i == 1)
    {
        measureLabel.setText(tr("Avg"));
    }
    else if (_i == 2)
    {
        measureLabel.setText(tr("Tune"));
    }
    else
    {
        measureLabel.setText(tr("Error"));
    }

}

void NumbersMeterWidget::setPhase(const QString &_p)
{
    phaseLabel.setText(_p);
}

