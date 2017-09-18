/*
 * Copyright (C) 2016 ~ 2017 Deepin Technology Co., Ltd.
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

#ifndef THEMEITEM_H
#define THEMEITEM_H

#include "settingsitem.h"
#include "../../../widgets/labels/normallabel.h"
#include <QWidget>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QLabel>

using namespace dcc::widgets;

namespace dcc {
namespace personalization {
class ThemeItemPic;
class ThemeItem : public widgets::SettingsItem
{
    Q_OBJECT
public:
    explicit ThemeItem(const QJsonObject &json);

    void setTitle(const QString &title);
    void setSelected(bool selected);
    void setPic(const QString &picPath);
    const QString id() const;

protected:
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void selectedChanged(const bool selected) const;

private:
    QVBoxLayout *m_mainLayout;
    NormalLabel *m_title;
    QLabel *m_selectLabel;
    bool m_state;
    ThemeItemPic *m_itemPic;
    QString m_id;

};
}
}

#endif // THEMEITEM_H
