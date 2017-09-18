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

#ifndef BASICSETTINGSPAGE_H
#define BASICSETTINGSPAGE_H

#include "dccslider.h"

#include <QFrame>
#include <QDBusObjectPath>

#include <dmpriscontrol.h>
#include <QGSettings>
#include <com_deepin_daemon_audio.h>
#include <com_deepin_daemon_audio_sink.h>
#include <com_deepin_daemon_display.h>

class QLabel;

namespace dcc {

class BasicSettingsModel : public QObject {
    Q_OBJECT
public:
    explicit BasicSettingsModel(QObject *parent = 0);

    inline double volume() const { return m_volume; }
    void setVolume(double volume);

    inline double brightness() const { return m_brightness; }
    void setBrightness(double brightness);

    inline bool mute() const { return m_mute; }
    void setMute(bool mute);

signals:
    void muteChanged(const bool &mute) const;
    void volumeChanged(const double &volume) const;
    void brightnessChanged(const double &brightness) const;

private:
    bool m_mute;
    double m_volume;
    double m_brightness;
};

class BasicSettingsWorker : public QObject {
    Q_OBJECT
public:
    explicit BasicSettingsWorker(BasicSettingsModel *model, QObject *parent=0);

public slots:
    void setMute(const bool &mute);
    void setVolume(const double &volume);
    void setBrightness(const double brightness);

private slots:
    void onDefaultSinkChanged(const QDBusObjectPath & value);
    void onBrightnessChanged(const BrightnessMap value);

private:
    BasicSettingsModel *m_model;
    QStringList m_monitors;
    com::deepin::daemon::Audio *m_audioInter;
    QPointer<com::deepin::daemon::audio::Sink> m_sinkInter;
    com::deepin::daemon::Display *m_displayInter;
};

class BasicSettingsPage : public QFrame
{
    Q_OBJECT
public:
    explicit BasicSettingsPage(QWidget *parent = 0);

private slots:
    void onMuteChanged(const bool &mute);
    void onGSettingsChanged(const QString &name);

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    QLabel *m_volumeLow;
    QLabel *m_volumeHigh;
    QSlider *m_soundSlider;
    QLabel *m_brightnessLow;
    QLabel *m_brightnessHigh;
    QSlider *m_lightSlider;

    BasicSettingsModel *m_model;
    BasicSettingsWorker *m_worker;

    Dtk::Widget::DMPRISControl *m_mprisWidget;
    QGSettings *m_gsettings;
};

}

#endif // BASICSETTINGSPAGE_H
