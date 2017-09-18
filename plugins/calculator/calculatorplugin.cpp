/*
 * Copyright (C) 2011 ~ 2017 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "calculatorplugin.h"

CalculatorPlugin::CalculatorPlugin(QObject *parent)
    : QObject(parent),

      m_exampleLbl(nullptr)
{

}

void CalculatorPlugin::initialize(FrameProxyInterface *proxy)
{
    m_proxyInter = proxy;

    m_exampleLbl = new QLabel;
    m_exampleLbl->setText("calculator");
    m_exampleLbl->setStyleSheet("color:while;"
                                "background-color:red;");
}

QWidget *CalculatorPlugin::centralWidget()
{
    return m_exampleLbl;
}
