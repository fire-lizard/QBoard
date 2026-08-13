#include "qcolorcombobox.h"

#include <QColorDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QSignalBlocker>
#include <QStyle>
#include <QStyleOptionViewItem>

namespace
{
    QMap<QString, QString> makeNameMap()
    {
        QMap<QString, QString> result;

        const QStringList names = QColor::colorNames();
        for (const QString& name : names)
        {
            // QColor::name() gives the normalized #RRGGBB representation.
            const QColor color(name);
            result.insert(color.name(), name);
        }

        return result;
    }

    const QMap<QString, QString> NAME_MAP = makeNameMap();

    QColor castColorImpl(const QVariant& value)
    {
        if (value.canConvert<QColor>())
        {
            const QColor color = value.value<QColor>();
            if (color.isValid())
                return color;
        }

        // Support RGB/RGBA values supplied as a QVariantList.
        if (value.canConvert<QVariantList>())
        {
            const QVariantList list = value.toList();

            if (list.size() == 3 || list.size() == 4)
            {
                bool okR = false;
                bool okG = false;
                bool okB = false;

                const int r = list.at(0).toInt(&okR);
                const int g = list.at(1).toInt(&okG);
                const int b = list.at(2).toInt(&okB);

                if (okR && okG && okB)
                {
                    if (list.size() == 4)
                    {
                        bool okA = false;
                        const int a = list.at(3).toInt(&okA);

                        if (okA)
                        {
                            const QColor color(r, g, b, a);
                            if (color.isValid())
                                return color;
                        }
                    }
                    else
                    {
                        const QColor color(r, g, b);
                        if (color.isValid())
                            return color;
                    }
                }
            }
        }

        // Also accept a color string such as "#ff0000" or "red".
        if (value.canConvert<QString>())
        {
            const QColor color(value.toString());
            if (color.isValid())
                return color;
        }

        return {};
    }

    QColor pickFontColorImpl(const QColor& color)
    {
        const double brightness =
            color.red() * 0.299 +
            color.green() * 0.587 +
            color.blue() * 0.114;

        if (brightness > 80.0)
            return { 0, 0, 0, 128 };

        return { 255, 255, 255, 128 };
    }
}

// -----------------------------------------------------------------------------
// ColorComboLineEdit
// -----------------------------------------------------------------------------

ColorComboLineEdit::ColorComboLineEdit(QWidget *parent) : QLineEdit(parent)
{
    setReadOnly(true);

    // Hide the original text. The background color is used to represent
    // the selected color.
    setStyleSheet(QStringLiteral("color: transparent"));
    clear();
}

void ColorComboLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    // The Python implementation deliberately uses mouseReleaseEvent:
    // mousePressEvent would open the popup and then immediately close it.
    if (auto *combo = qobject_cast<QComboBox *>(parentWidget()))
        combo->showPopup();
}

// -----------------------------------------------------------------------------
// QColorComboItemDelegate
// -----------------------------------------------------------------------------

QColorComboItemDelegate::QColorComboItemDelegate(QObject *parent) : QAbstractItemDelegate(parent)
{
}

QSize QColorComboItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return {20, 20};
}

void QColorComboItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QVariant data = index.data(Qt::ItemDataRole::BackgroundRole);

    const QColor color = data.value<QColor>();
    const QRect rect = option.rect;

    const bool selected = option.state & QStyle::State_Selected;

    const QColor border(QStringLiteral("lightgray"));

    if (!color.isValid())
    {
        const QColor textColor = selected ? Qt::black : Qt::gray;

        painter->setPen(textColor);

        const QString text = index.data(Qt::ItemDataRole::DisplayRole).toString();

        painter->drawText(rect, Qt::AlignCenter, text);

        return;
    }

    QPen pen = painter->pen();
    pen.setWidth(2);
    pen.setColor(border);
    painter->setPen(pen);

    if (selected)
    {
        // When selected/hovered, slightly lighten the color and show
        // the friendly color name.
        painter->setBrush(color.lighter(110));
        painter->drawRect(rect);

        const QString name = NAME_MAP.value(color.name(), color.name());

        painter->setPen(pickFontColorImpl(color));

        painter->drawText(rect, Qt::AlignCenter, name);
    }
    else
    {
        painter->setBrush(color);
        painter->drawRect(rect);
    }
}

// -----------------------------------------------------------------------------
// QColorComboBox
// -----------------------------------------------------------------------------

QColorComboBox::QColorComboBox(QWidget *parent, bool allowUserColors, QString addColorText)
    : QComboBox(parent), m_addColorText(std::move(addColorText)), m_allowUserColors(allowUserColors)
{
    setLineEdit(new ColorComboLineEdit(this));
    setItemDelegate(new QColorComboItemDelegate(this));

    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &QColorComboBox::onIndexChanged);

    connect(this, QOverload<int>::of(&QComboBox::activated), this, &QColorComboBox::onActivated);

    setUserColorsAllowed(allowUserColors);
}

void QColorComboBox::setInvalidColorPolicy(
    InvalidColorPolicy policy)
{
    m_invalidPolicy = policy;
}

QColorComboBox::InvalidColorPolicy
QColorComboBox::invalidColorPolicy() const
{
    return m_invalidPolicy;
}

bool QColorComboBox::userColorsAllowed() const
{
    return m_allowUserColors;
}

void QColorComboBox::setUserColorsAllowed(bool allow)
{
    m_allowUserColors = allow;

    const int index = findData(m_addColorText, Qt::DisplayRole);

    if (index < 0)
    {
        if (m_allowUserColors)
            addItem(m_addColorText);
    }
    else if (!m_allowUserColors)
    {
        removeItem(index);
    }
}

void QColorComboBox::clear()
{
    QComboBox::clear();

    // Keep "Add Color..." when user colors are enabled.
    setUserColorsAllowed(m_allowUserColors);
}

void QColorComboBox::addColor(const QVariant &color)
{
    const QColor converted = castColor(color);

    if (!converted.isValid())
    {
        switch (m_invalidPolicy)
        {
        case InvalidColorPolicy::Raise:
            qWarning() << "Invalid color:" << color;
            Q_ASSERT_X(false, "QColorComboBox::addColor", "Invalid color");
            return;

        case InvalidColorPolicy::Warn:
            qWarning() << "Ignoring invalid color:" << color;
            return;

        case InvalidColorPolicy::Ignore:
            return;
        }
    }

    const QColor current = currentColor();

    // Avoid duplicates.
    if (findData(converted) >= 0)
        return;

    // Add the actual color as item data.
    addItem(QString(), converted);

    setItemData(count() - 1, converted, Qt::ItemDataRole::BackgroundRole);

    if (!current.isValid())
        onIndexChanged(count() - 1);

    // Make sure "Add Color..." stays last.
    const int addColorIndex = findData(m_addColorText, Qt::DisplayRole);

    if (addColorIndex >= 0)
    {
        QSignalBlocker blocker(this);

        removeItem(addColorIndex);
        addItem(m_addColorText);
    }
}

QColor QColorComboBox::itemColor(int index) const
{
    return itemData(index, Qt::ItemDataRole::BackgroundRole).value<QColor>();
}

void QColorComboBox::addColors(
    const QList<QVariant> &colors)
{
    for (const QVariant &color : colors)
        addColor(color);
}

QColor QColorComboBox::currentColor() const
{
    return currentData(Qt::ItemDataRole::BackgroundRole).value<QColor>();
}

void QColorComboBox::setCurrentColor(
    const QVariant &color)
{
    const QColor converted = castColor(color);

    if (!converted.isValid())
        return;

    const int index = findData(converted, Qt::ItemDataRole::BackgroundRole);

    if (index >= 0)
        setCurrentIndex(index);
}

QString QColorComboBox::currentColorName() const
{
    const QColor color = currentColor();

    return color.isValid()
        ? color.name()
        : QStringLiteral("#000000");
}

void QColorComboBox::onActivated(int index)
{
    if (itemText(index) != m_addColorText)
        return;

    if (!lineEdit())
        return;

    // Show temporary text while the dialog is open.
    lineEdit()->setStyleSheet(QStringLiteral("background-color: white; color: gray;"));

    lineEdit()->setText(QStringLiteral("Pick a Color ..."));

    QColor color;

    try
    {
        color = QColorDialog::getColor(QColor(), this, QStringLiteral("Select Color"));
    }
    catch (...)
    {
        lineEdit()->clear();
        throw;
    }

    lineEdit()->clear();

    if (color.isValid())
    {
        addColor(color);
    }
    else if (m_lastColor.isValid())
    {
        const int previousIndex = findData(m_lastColor, Qt::ItemDataRole::BackgroundRole);

        if (previousIndex >= 0)
        {
            QSignalBlocker blocker(this);

            setCurrentIndex(previousIndex);

            const QString hex = m_lastColor.name();

            lineEdit()->setStyleSheet(QStringLiteral("background-color: %1;").arg(hex));
        }
    }
}

void QColorComboBox::onIndexChanged(int index)
{
    const QColor color = itemData(index, Qt::ItemDataRole::BackgroundRole).value<QColor>();

    if (!color.isValid())
        return;

    lineEdit()->setStyleSheet(QStringLiteral("background-color: %1;").arg(color.name()));

    emit currentColorChanged(color);

    m_lastColor = color;
}

QColor QColorComboBox::castColor(const QVariant &value)
{
    return castColorImpl(value);
}

QColor QColorComboBox::pickFontColor(const QColor &color)
{
    return pickFontColorImpl(color);
}
