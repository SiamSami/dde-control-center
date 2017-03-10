/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "setlocationpage.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QListView>

#include "weatherrequest.h"

static const int ItemSpacing = 2;

SetLocationPage::SetLocationPage(WeatherRequest *requestManager, QWidget *parent)
    : QWidget(parent),
      m_requestManager(requestManager),
      m_currentCityLabel(new LargeLabel),
      m_searchInput(new SearchInput),
      m_resultView(new SearchResultView),
      m_resultDelegate(new SearchDelegate),
      m_resultModel(new SearchModel)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addSpacing(20);
    layout->addWidget(m_currentCityLabel, 0, Qt::AlignHCenter);
    layout->addSpacing(20);
    layout->addWidget(m_searchInput);
    layout->addSpacing(10);
    layout->addWidget(m_resultView, 1);
    layout->addStretch();

    setLayout(layout);

    // TODO(hualet):
    setCurrentCity(City{});

    m_resultView->setItemDelegate(m_resultDelegate);
    m_resultView->setModel(m_resultModel);

    connect(m_searchInput, &SearchInput::textChanged, this, [this] {
        static QTime time;
        if (time.elapsed() == 0 || time.elapsed() > 500 ) {
            time.start(); // reset the timer.

            const QString input = m_searchInput->text();
            if (input.isEmpty()) {
                m_resultModel->setCities(QList<City>());
            } else {
                m_requestManager->searchCity(input);
            }
        }
    });

    connect(m_requestManager, &WeatherRequest::searchCityDone, m_resultModel, &SearchModel::setCities);

    connect(m_resultView, &SearchResultView::clicked, this, [this](const QModelIndex &index) {
        QVariant data = index.data(Qt::UserRole);
        QString geonameId = data.value<QString>();

        for (const City &city : m_resultModel->cities()) {
            if (city.geonameId == geonameId) {
                emit citySet(city);
                break;
            }
        }
    });
}

City SetLocationPage::currentCity() const
{
    return m_currentCity;
}

void SetLocationPage::setCurrentCity(const City &currentCity)
{
    m_currentCity = currentCity;
    m_currentCityLabel->setText(tr("Current City: %1").arg(m_currentCity.localizedName));
}

SearchModel::SearchModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int SearchModel::rowCount(const QModelIndex &) const
{
    return m_cities.length();
}

QVariant SearchModel::data(const QModelIndex &index, int role) const
{
    const City city = m_cities.at(index.row());

    if (role == Qt::UserRole) {
        return city.geonameId;
    }

    return QString("%1, %2").arg(city.localizedName).arg(city.country);
}

QList<City> SearchModel::cities() const
{
    return m_cities;
}

void SearchModel::setCities(const QList<City> &cities)
{
    beginResetModel();
    m_cities = cities;
    endResetModel();
}

SearchDelegate::SearchDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void SearchDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant textData = index.data(Qt::DisplayRole);
    QString cityName = textData.value<QString>();

    QRect rect( option.rect.adjusted(0, 0, 0, -ItemSpacing) );
    painter->fillRect(rect, QColor::fromRgbF(1, 1, 1, 0.15));

    QTextOption opt;
    opt.setAlignment(Qt::AlignCenter);
    painter->setPen(Qt::white);
    painter->drawText(rect, cityName, opt);
}

QSize SearchDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(36 + ItemSpacing);

    return size;
}

SearchResultView::SearchResultView(QWidget *)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background: transparent; margin: 0px; border: 0px; padding: 0px;");
}