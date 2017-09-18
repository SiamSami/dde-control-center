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

#include "monitorproxywidget.h"
#include "monitor.h"
#include "monitorindicator.h"
#include <QPainter>
#include <QMouseEvent>

using namespace dcc::display;

MonitorProxyWidget::MonitorProxyWidget(Monitor *mon, QWidget *parent)
    : QWidget(parent),

      m_monitor(mon),
      m_movedX(m_monitor->x()),
      m_movedY(m_monitor->y()),
      m_mouseState(false),
      m_fullIndication(new MonitorIndicator)
{
    connect(m_monitor, &Monitor::xChanged, this, &MonitorProxyWidget::setMovedX);
    connect(m_monitor, &Monitor::yChanged, this, &MonitorProxyWidget::setMovedY);
    connect(m_monitor, &Monitor::geometryChanged, this, &MonitorProxyWidget::setIndicatorGeometry);
}

int MonitorProxyWidget::w() const
{
    return m_monitor->w();
}

int MonitorProxyWidget::h() const
{
    return m_monitor->h();
}

const QString MonitorProxyWidget::name() const
{
    return m_monitor->name();
}

void MonitorProxyWidget::setIndicatorGeometry()
{
    m_fullIndication->setGeometry(m_monitor->rect());
}

void MonitorProxyWidget::paintEvent(QPaintEvent *)
{
    const QRect r(rect());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(r, Qt::gray);
//    painter.fillRect(r, m_monitor->isPrimary() ? Qt::blue : Qt::gray);
    painter.setPen(Qt::darkGray);
    painter.drawRect(r);

    if (m_mouseState) {
        QPen pen(QColor("#2ca7f8"));
        pen.setWidth(4);
        painter.setPen(pen);
        painter.drawRect(rect());
    }

    const QFontMetrics fm(painter.font());
    const int width = fm.boundingRect(m_monitor->name()).width();
    painter.setPen(Qt::white);
    painter.drawText(r.width() - width - 20, 30, m_monitor->name());

    if (!m_monitor->isPrimary())
        return;

    const int radius = 5;
    QRectF dockRect = r;
    dockRect.setTop(r.bottom() - 15);
    dockRect.setRight(r.width() - r.width() / 4);
    dockRect.setLeft(r.width() / 4);
    dockRect.moveTop(dockRect.top() + radius);

    painter.setPen(Qt::transparent);
    painter.setBrush(Qt::darkGray);
//    painter.fillRect(dockRect, Qt::red);
    painter.drawRoundedRect(dockRect, radius, radius);
}

void MonitorProxyWidget::mousePressEvent(QMouseEvent *e)
{
    m_lastPos = e->globalPos();

    m_mouseState = true;

    m_fullIndication->setGeometry(m_monitor->rect());
    m_fullIndication->show();

    update();
}

void MonitorProxyWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!(e->buttons() & Qt::LeftButton))
        return;

    move(pos() + e->globalPos() - m_lastPos);
    m_lastPos = e->globalPos();
}

void MonitorProxyWidget::mouseReleaseEvent(QMouseEvent *e)
{
    emit requestApplyMove(this);

    m_mouseState = false;

    m_fullIndication->hide();

    update();

    QWidget::mouseReleaseEvent(e);
}

