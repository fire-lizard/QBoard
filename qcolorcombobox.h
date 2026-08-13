#pragma once

#include <QComboBox>
#include <QColor>
#include <QColorDialog>
#include <QPainter>
#include <QPixmap>

class QColorComboBox : public QComboBox
{
    Q_OBJECT
        Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor
            NOTIFY colorChanged USER true)

public:
    explicit QColorComboBox(QWidget* parent = nullptr);

    /// The currently selected color (invalid QColor if none).
    QColor currentColor() const;

    /// Color stored at a given index.
    QColor color(int index) const;

    /// Append a color. If name is empty, a hex string ("#rrggbb") is used.
    void addColor(const QColor& color, const QString& name = QString());

    /// Replace all colors with the given list.
    void setColors(const QList<QColor>& colors);

    /// Remove all color entries (keeps the "Custom..." entry if enabled).
    void clearColors();

    /// Populate with the SVG named colors (QColorConstants::Svg set,
    /// via QColor::colorNames()). Called by default on construction.
    void addStandardColors();

    /// Enable/disable the trailing "Custom..." entry (QColorDialog).
    void setCustomColorsEnabled(bool enabled);
    bool customColorsEnabled() const;

public slots:
    /// Select the given color; the color is appended if not present.
    void setCurrentColor(const QColor& color);

signals:
    /// Emitted whenever the selected color changes (user or programmatic).
    void colorChanged(const QColor& color);

protected:
    /// Builds the swatch icon shown next to each entry.
    virtual QIcon colorIcon(const QColor& color) const;

private slots:
    void handleActivated(int index);
    void handleCurrentIndexChanged(int index);

private:
    int findColor(const QColor& color) const;
    int colorCount() const;          // entry count excluding "Custom..."
    void insertCustomEntry();

    bool m_customEnabled = true;
    QColor m_lastColor;              // restore target if dialog is cancelled
};
