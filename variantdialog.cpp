#include "variantdialog.h"
#include "ui_variantdialog.h"
#include <QKeyEvent>

VariantDialog::VariantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariantDialog)
{
    ui->setupUi(this);
    std::ranges::for_each(variantMap(), [&](const QPair<GameVariant, QString>& p) {
        auto* item = new QListWidgetItem(p.second, ui->variantList);
        item->setData(Qt::UserRole, static_cast<int>(p.first));
    });
    ui->variantList->setStyleSheet(R"(QListWidget::item:selected { background-color: #0078D7; color: white; })");
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &VariantDialog::ApplyFilter);
    for (auto* rb : {ui->allGamesRadioButton, ui->chessGamesRadioButton, ui->shogiGamesRadioButton, ui->otherGamesRadioButton})
    {
        connect(rb, &QRadioButton::toggled, this, [this](bool checked) { if (checked) ApplyFilter(); });
    }
    ui->searchLineEdit->installEventFilter(this);
    ui->searchLineEdit->setFocus();
    ApplyFilter();
}

bool VariantDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->searchLineEdit && event->type() == QEvent::KeyPress)
    {
        const auto* keyEvent = static_cast<QKeyEvent*>(event);
        if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) &&
            ui->variantList->selectionMode() != QAbstractItemView::SingleSelection)
        {
            return true;
        }
    }
    return QDialog::eventFilter(watched, event);
}

VariantDialog::~VariantDialog()
{
    delete ui;
}

QListWidget* VariantDialog::GetVariant() const
{
    return ui->variantList;
}

void VariantDialog::on_variantList_itemDoubleClicked(QListWidgetItem *item)
{
    item->setSelected(true); // in MultiSelection the first click of a double-click toggles the item off
    accept();
}

void VariantDialog::ApplyFilter() const
{
    const QString needle = ui->searchLineEdit->text().trimmed();
    const bool chessOnly = ui->chessGamesRadioButton->isChecked();
    const bool shogiOnly = ui->shogiGamesRadioButton->isChecked();
    const bool otherOnly = ui->otherGamesRadioButton->isChecked();
    for (int i = 0; i < ui->variantList->count(); i++)
    {
        auto* item = ui->variantList->item(i);
        const auto variant = static_cast<GameVariant>(item->data(Qt::UserRole).toInt());
        const bool isChess = std::ranges::find(chessVariants, variant) != std::end(chessVariants);
        const bool isShogi = std::ranges::find(shogiVariants, variant) != std::end(shogiVariants);
        bool visible = !(chessOnly && !isChess) && !(shogiOnly && !isShogi) && !(otherOnly && (isChess || isShogi));
        visible = visible && (needle.isEmpty() || item->text().contains(needle, Qt::CaseInsensitive));
        item->setHidden(!visible);
    }
    if (ui->variantList->selectionMode() == QAbstractItemView::SingleSelection)
    {
        auto* current = ui->variantList->currentItem();
        if (current == nullptr || current->isHidden())
        {
            int firstVisible = -1;
            for (int i = 0; i < ui->variantList->count(); i++)
            {
                if (!ui->variantList->item(i)->isHidden())
                {
                    firstVisible = i;
                    break;
                }
            }
            ui->variantList->setCurrentRow(firstVisible); // -1 clears current when nothing matches
        }
    }
}
