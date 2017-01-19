#include "theme.h"
#include "settingsheaderitem.h"
#include "labels/largelabel.h"
#include "../../widget/themeitempic.h"
#include "../../model/thememodel.h"
#include "optionitem.h"
#include "personalization/personalizationmodel.h"
#include "../../widget/themeitem.h"

using namespace dcc;
using namespace dcc::personalization;
using namespace dcc::widgets;

Theme::Theme(const QString &title, QWidget *parent)
    : TranslucentFrame(parent)
{
    m_mainLayout = new QVBoxLayout;
    m_mainGroup = new SettingsGroup(title);
    m_mainLayout->addWidget(m_mainGroup);

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);
    setAccessibleName(title);
}

void Theme::setModel(ThemeModel *const model)
{
    m_model = model;
    connect(m_model, &ThemeModel::defaultChanged, this, &Theme::setDefault);
    connect(m_model, &ThemeModel::listChanged,    this, &Theme::setList);

    setList(m_model->getJson());
    setDefault(m_model->getDefault());
}

void Theme::setList(const QList<QJsonObject> &list)
{
    for (QJsonObject json : list) {
        ThemeItem *theme = new ThemeItem(json);
        m_mainGroup->appendItem(theme);
        m_valueMap.insert(theme, json);
        connect(theme, &ThemeItem::selectedChanged, this, &Theme::onItemClicked);
    }
}

void Theme::setDefault(const QString &name)
{
    QMap<ThemeItem *, QJsonObject>::const_iterator i = m_valueMap.constBegin();
    while (i != m_valueMap.constEnd()) {
        ThemeItem *w = i.key();
        if (w) {
            if (i.value()["Id"].toString() == name) {
                w->setTitle(name + tr(" (Default)"));
                w->setSelected(true);
            } else {
                w->setTitle(i.value()["Id"].toString());
                w->setSelected(false);
            }
        }
        ++i;
    }
}

void Theme::onItemClicked(const bool selected)
{
    if (selected) {
        ThemeItem *item = qobject_cast<ThemeItem *>(sender());
        Q_ASSERT(m_valueMap.contains(item));
        emit requestSetDefault(m_valueMap[item]);
    }
}
