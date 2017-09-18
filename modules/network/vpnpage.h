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

#ifndef VPNPAGE_H
#define VPNPAGE_H

#include "contentwidget.h"

#include <QList>
#include <QJsonObject>
#include <QMap>
#include <QPointer>

namespace dcc {

namespace widgets {

class SettingsGroup;
class SwitchWidget;
class NextPageWidget;

}

namespace network {

class NetworkModel;
class ConnectionEditPage;
class VpnPage : public ContentWidget
{
    Q_OBJECT

public:
    explicit VpnPage(QWidget *parent = 0);
    ~VpnPage();

signals:
    void requestDeleteConnection(const QString &uuid) const;
    void requestDeactiveConnection(const QString &uuid) const;
    void requestNextPage(ContentWidget * const w) const;
    void requestVpnEnabled(const bool enabled) const;
    void requestEditVpn(const QString &devPath, const QString &uuid) const;
    void requestActivateConnection(const QString &devPath, const QString &uuid) const;
    void requestCreateConnection(const QString &type, const QString &devicePath) const;
    void requestFrameKeepAutoHide(const bool autoHide) const;

public slots:
    void setModel(NetworkModel *model);
    void refershVpnList(const QList<QJsonObject> &vpnList);

private slots:
    void onVpnDetailClicked();
    void onVpnSelected();
    void onSessionPageFinished();
    void onVpnSessionCreated(const QString &device, const QString &sessionPath);
    void onActiveConnsInfoChanged(const QList<QJsonObject> &infos);

    void importVPN();
    void createVPNSession();
    void createVPN(const QString &type);

private:
    NetworkModel *m_model;

    widgets::SwitchWidget *m_vpnSwitch;
    widgets::SettingsGroup *m_vpnGroup;

    QPointer<ConnectionEditPage> m_editPage;
    QString m_editingConnUuid;
    ContentWidget *m_vpnTypePage;

    QMap<widgets::NextPageWidget *, QJsonObject> m_vpns;
};

}

}

#endif // VPNPAGE_H
