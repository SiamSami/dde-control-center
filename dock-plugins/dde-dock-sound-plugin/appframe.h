#ifndef APPFRAME_H
#define APPFRAME_H

#include <QMap>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "appiconslider.h"
#include "dbus/dbusaudio.h"

class AppFrame : public QWidget
{
    Q_OBJECT
public:
    explicit AppFrame(QWidget *parent = 0);

signals:
    void appCountChanged(int count);

public slots:

private:
    void initTitle();
    void initAppList();
    void updateAppList();

private:
    DBusAudio *m_audio = NULL;
    QMap<QString, AppIconSlider *> m_appsMap;
    QVBoxLayout * m_mainLayout = NULL;
};

#endif // APPFRAME_H
