/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DBusUpdateJobManager -p dbusupdatejobmanager org.deepin.lastore.Manager.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUSUPDATEJOBMANAGER_H_1446173369
#define DBUSUPDATEJOBMANAGER_H_1446173369

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.deepin.lastore.Manager
 */
class DBusUpdateJobManager: public QDBusAbstractInterface
{
    Q_OBJECT

    Q_SLOT void __propertyChanged__(const QDBusMessage& msg)
    {
        QList<QVariant> arguments = msg.arguments();
        if (3 != arguments.count())
            return;
        QString interfaceName = msg.arguments().at(0).toString();
        if (interfaceName !="org.deepin.lastore.Manager")
            return;
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        QStringList keys = changedProps.keys();
        foreach(const QString &prop, keys) {
        const QMetaObject* self = metaObject();
            for (int i=self->propertyOffset(); i < self->propertyCount(); ++i) {
                QMetaProperty p = self->property(i);
                if (p.name() == prop) {
 	            Q_EMIT p.notifySignal().invoke(this);
                }
            }
        }
   }
public:
    static inline const char *staticInterfaceName()
    { return "org.deepin.lastore.Manager"; }

public:
    DBusUpdateJobManager(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~DBusUpdateJobManager();

    Q_PROPERTY(QList<QDBusObjectPath> JobList READ jobList NOTIFY JobListChanged)
    inline QList<QDBusObjectPath> jobList() const
    { return qvariant_cast< QList<QDBusObjectPath> >(property("JobList")); }

    Q_PROPERTY(QStringList SystemArchitectures READ systemArchitectures NOTIFY SystemArchitecturesChanged)
    inline QStringList systemArchitectures() const
    { return qvariant_cast< QStringList >(property("SystemArchitectures")); }

    Q_PROPERTY(QStringList UpgradableApps READ upgradableApps NOTIFY UpgradableAppsChanged)
    inline QStringList upgradableApps() const
    { return qvariant_cast< QStringList >(property("UpgradableApps")); }

    Q_PROPERTY(QString Version READ version NOTIFY VersionChanged)
    inline QString version() const
    { return qvariant_cast< QString >(property("Version")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> CleanJob(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("CleanJob"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> DistUpgrade3()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("DistUpgrade3"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> DownloadPackage(const QString &in0, const QString &in1)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0) << QVariant::fromValue(in1);
        return asyncCallWithArgumentList(QStringLiteral("DownloadPackage"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> InstallPackage(const QString &in0, const QString &in1)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0) << QVariant::fromValue(in1);
        return asyncCallWithArgumentList(QStringLiteral("InstallPackage"), argumentList);
    }

    inline QDBusPendingReply<QString> PackageCategory1(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("PackageCategory1"), argumentList);
    }

    inline QDBusPendingReply<QString> PackageDesktopPath(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("PackageDesktopPath"), argumentList);
    }

    inline QDBusPendingReply<qlonglong> PackageDownloadSize(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("PackageDownloadSize"), argumentList);
    }

    inline QDBusPendingReply<bool> PackageExists(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("PackageExists"), argumentList);
    }

    inline QDBusPendingReply<qlonglong> PackagesDownloadSize(const QStringList &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("PackagesDownloadSize"), argumentList);
    }

    inline QDBusPendingReply<> PauseJob2(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("PauseJob2"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> RemovePackage(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("RemovePackage"), argumentList);
    }

    inline QDBusPendingReply<> StartJob(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("StartJob"), argumentList);
    }

Q_SIGNALS: // SIGNALS
// begin property changed signals
void JobListChanged();
void SystemArchitecturesChanged();
void UpgradableAppsChanged();
void VersionChanged();
};

namespace org {
  namespace deepin {
    namespace lastore {
      typedef ::DBusUpdateJobManager Manager;
    }
  }
}
#endif
