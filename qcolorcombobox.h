#pragma once

#include <QAbstractItemDelegate>
#include <QComboBox>
#include <QLineEdit>
#include <QColor>
#include <QModelIndex>
#include <QPersistentModelIndex>
#include <QSize>
#include <QStyleOptionViewItem>
#include <QWidget>

class QColorComboItemDelegate final : public QAbstractItemDelegate
{
public:
    explicit QColorComboItemDelegate(QObject *parent = nullptr);

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

class ColorComboLineEdit final : public QLineEdit
{
public:
    explicit ColorComboLineEdit(QWidget *parent = nullptr);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

class QColorComboBox final : public QComboBox
{
    Q_OBJECT

public:
    enum class InvalidColorPolicy
    {
        Ignore = 1,
        Warn,
        Raise
    };
    Q_ENUM(InvalidColorPolicy)

    explicit QColorComboBox(QWidget *parent = nullptr, bool allowUserColors = false,
                            QString addColorText = QStringLiteral("Add Color..."));

    void setInvalidColorPolicy(InvalidColorPolicy policy);
    InvalidColorPolicy invalidColorPolicy() const;

    bool userColorsAllowed() const;
    void setUserColorsAllowed(bool allow);

    void clear();

    void addColor(const QVariant &color);
    void addColors(const QList<QVariant> &colors);

    QColor itemColor(int index) const;

    QColor currentColor() const;
    void setCurrentColor(const QVariant &color);

    QString currentColorName() const;

signals:
    void currentColorChanged(const QColor &color);

private slots:
    void onActivated(int index);
    void onIndexChanged(int index);

private:
    static QColor castColor(const QVariant &value);
    static QColor pickFontColor(const QColor &color);

    InvalidColorPolicy m_invalidPolicy = InvalidColorPolicy::Ignore;
    QString m_addColorText = QStringLiteral("Add Color...");
    bool m_allowUserColors = false;
    QColor m_lastColor;

    static constexpr int ColorRole = Qt::ItemDataRole::BackgroundRole;
};
