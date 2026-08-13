#include "qcolorcombobox.h"

namespace {
    // Role used to store the QColor on each item.
    constexpr int ColorRole = Qt::UserRole;
    // Marker stored on the "Custom..." entry.
    constexpr int CustomRole = Qt::UserRole + 1;
}

QColorComboBox::QColorComboBox(QWidget* parent)
    : QComboBox(parent)
{
    addStandardColors();
    insertCustomEntry();

    connect(this, QOverload<int>::of(&QComboBox::activated),
        this, &QColorComboBox::handleActivated);
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &QColorComboBox::handleCurrentIndexChanged);

    if (count() > 0)
        m_lastColor = color(0);
}

QColor QColorComboBox::currentColor() const
{
    return color(currentIndex());
}

QColor QColorComboBox::color(int index) const
{
    if (index < 0 || index >= count())
        return {};
    return itemData(index, ColorRole).value<QColor>();
}

void QColorComboBox::addColor(const QColor& color, const QString& name)
{
    if (!color.isValid())
        return;

    const QString text = name.isEmpty() ? color.name() : name;
    const int insertAt = colorCount();          // keep "Custom..." last

    insertItem(insertAt, colorIcon(color), text);
    setItemData(insertAt, color, ColorRole);
}

void QColorComboBox::setColors(const QList<QColor>& colors)
{
    clearColors();
    for (const QColor& c : colors)
        addColor(c);
}

void QColorComboBox::clearColors()
{
    const QSignalBlocker blocker(this);
    while (colorCount() > 0)
        removeItem(0);
}

void QColorComboBox::addStandardColors()
{
    // Adds the full SVG 1.0 named-color set — the same colors defined in
    // QColorConstants::Svg (Qt >= 5.14). The constants themselves can't be
    // iterated, but QColor::colorNames() returns exactly this SVG list, so
    // we enumerate through it instead of hardcoding all 148 entries.
    const QStringList names = QColor::colorNames();
    for (const QString& name : names) {
        QColor c(name);
        if (!c.isValid())
            continue;
        // "aliceblue" -> "Aliceblue" for slightly nicer display.
        QString display = name;
        display[0] = display[0].toUpper();
        addColor(c, display);
    }
}

void QColorComboBox::setCustomColorsEnabled(bool enabled)
{
    if (enabled == m_customEnabled)
        return;
    m_customEnabled = enabled;

    if (enabled) {
        insertCustomEntry();
    }
    else if (count() > 0 && itemData(count() - 1, CustomRole).toBool()) {
        removeItem(count() - 1);
    }
}

bool QColorComboBox::customColorsEnabled() const
{
    return m_customEnabled;
}

void QColorComboBox::setCurrentColor(const QColor& color)
{
    if (!color.isValid())
        return;

    int index = findColor(color);
    if (index < 0) {
        addColor(color);
        index = findColor(color);
    }
    setCurrentIndex(index);
}

QIcon QColorComboBox::colorIcon(const QColor& color) const
{
    const int size = iconSize().height() > 0 ? iconSize().height() : 16;
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(palette().color(QPalette::Shadow), 1));
    painter.setBrush(color);
    painter.drawRoundedRect(QRectF(0.5, 0.5, size - 1.0, size - 1.0), 2, 2);

    return {pixmap};
}

void QColorComboBox::handleActivated(int index)
{
    if (!itemData(index, CustomRole).toBool())
        return;

    // "Custom..." was chosen: open a color dialog.
    const QColor picked = QColorDialog::getColor(
        m_lastColor.isValid() ? m_lastColor : Qt::white,
        this, tr("Select color"));

    if (picked.isValid()) {
        setCurrentColor(picked);
    }
    else {
        // Cancelled: restore previous selection without firing colorChanged.
        const QSignalBlocker blocker(this);
        const int prev = findColor(m_lastColor);
        setCurrentIndex(prev >= 0 ? prev : 0);
    }
}

void QColorComboBox::handleCurrentIndexChanged(int index)
{
    if (index < 0 || itemData(index, CustomRole).toBool())
        return;

    const QColor c = color(index);
    if (c.isValid() && c != m_lastColor) {
        m_lastColor = c;
        emit colorChanged(c);
    }
}

int QColorComboBox::findColor(const QColor& color) const
{
    for (int i = 0; i < colorCount(); ++i) {
        if (this->color(i) == color)
            return i;
    }
    return -1;
}

int QColorComboBox::colorCount() const
{
    int n = count();
    if (n > 0 && itemData(n - 1, CustomRole).toBool())
        --n;
    return n;
}

void QColorComboBox::insertCustomEntry()
{
    if (!m_customEnabled)
        return;
    addItem(tr("Custom..."));
    setItemData(count() - 1, true, CustomRole);
}
