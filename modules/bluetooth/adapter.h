/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef DCC_BLUETOOTH_ADAPTER_H
#define DCC_BLUETOOTH_ADAPTER_H

#include <QObject>

#include "device.h"

namespace dcc {
namespace bluetooth {

class Adapter : public QObject
{
    Q_OBJECT
public:
    explicit Adapter(QObject *parent = 0);

    inline QString name() const { return m_name; }
    void setName(const QString &name);

    inline QString id() const { return m_id; }
    void setId(const QString &id);

    QList<const Device *> devices() const;

public slots:
    void addDevice(const Device *device);
    void removeDevice(const QString &deviceId) const;

signals:
    void nameChanged(const QString &name) const;
    void deviceAdded(const Device *device) const;
    void deviceRemoved(const QString &deviceId) const;

private:
    QString m_id;
    QString m_name;
    QList<const Device *> m_devices;
};

} // namespace bluetooth
} // namespace dcc

#endif // DCC_BLUETOOTH_ADAPTER_H