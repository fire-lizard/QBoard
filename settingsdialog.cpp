#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFormLayout>
#include <QScrollArea>
#include <QRegularExpression>

namespace {
// "ChuShogiRelayMoveColor" -> "Chu Shogi Relay Move"
QString colorLabel(QString key)
{
	key.remove(QRegularExpression("Color$"));
	return key.replace(QRegularExpression("([a-z])([A-Z])"), "\\1 \\2");
}
}

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	foreach(const QString &str, QStyleFactory::keys()) {
		ui->stylesComboBox->addItem(str);
	}

    ui->variantsLineEdit->setStyleSheet("QLineEdit { background: rgb(0, 223, 223); selection-background-color: rgb(223, 99, 0); }");
	ui->engine1DepthHorizontalSlider->setEnabled(ui->engine1DepthCheckBox->isChecked());
	ui->engine2DepthHorizontalSlider->setEnabled(ui->engine2DepthCheckBox->isChecked());
	ui->engine1TimeSpinBox->setEnabled(ui->engine1TimeCheckBox->isChecked());
	ui->engine2TimeSpinBox->setEnabled(ui->engine2TimeCheckBox->isChecked());
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

QComboBox* SettingsDialog::GetStyles() const
{
	return ui->stylesComboBox;
}

QLineEdit* SettingsDialog::GetGameVariant() const
{
    return ui->variantsLineEdit;
}

QComboBox* SettingsDialog::GetGamePieces() const
{
	return ui->piecesComboBox;
}

QComboBox* SettingsDialog::GetEngineOutput() const
{
	return ui->engineOutputComboBox;
}

QCheckBox* SettingsDialog::GetHighlightMoves() const
{
	return ui->highlightMovesCheckBox;
}

QCheckBox* SettingsDialog::GetHighlightShoots() const
{
	return ui->highlightShootsCheckBox;
}

QCheckBox* SettingsDialog::GetHighlightAttackers() const
{
	return ui->highlightAttackersCheckBox;
}

QCheckBox* SettingsDialog::GetHighlightDefenders() const
{
	return ui->highlightDefendersCheckBox;
}

QCheckBox* SettingsDialog::GetHighlightLastMoves() const
{
	return ui->highlightLastMovesCheckBox;
}

QCheckBox* SettingsDialog::GetTimerState() const
{
    return ui->timerCheckBox;
}

QCheckBox* SettingsDialog::GetUseBlackEngineDepth() const
{
	return ui->engine1DepthCheckBox;
}

QSlider* SettingsDialog::GetBlackEngineDepth() const
{
	return ui->engine1DepthHorizontalSlider;
}

QCheckBox* SettingsDialog::GetUseWhiteEngineDepth() const
{
	return ui->engine2DepthCheckBox;
}

QSlider* SettingsDialog::GetWhiteEngineDepth() const
{
    return ui->engine2DepthHorizontalSlider;
}

QCheckBox* SettingsDialog::GetUseBlackEngineTime() const
{
	return ui->engine1TimeCheckBox;
}

QSpinBox* SettingsDialog::GetBlackEngineTime() const
{
	return ui->engine1TimeSpinBox;
}

QCheckBox* SettingsDialog::GetUseWhiteEngineTime() const
{
	return ui->engine2TimeCheckBox;
}

QSpinBox* SettingsDialog::GetWhiteEngineTime() const
{
	return ui->engine2TimeSpinBox;
}

void SettingsDialog::SetColors(const QMap<QString, QBrush>& colors, const QStringList& order)
{
	// Too many colours to hand-place in Designer, so the rows are built here and put in a
	// scroll area; the tab is the only page that gets a layout.
	QWidget* rows = new QWidget;
	QFormLayout* form = new QFormLayout(rows);
	// Rows follow `order` (VBoard::ColorTable()), not the QMap's alphabetical key order.
	for (const QString& key : order)
	{
		const auto it = colors.constFind(key);
		if (it == colors.constEnd())
			continue;
		QColorComboBox* combo = new QColorComboBox(rows);
		// Qt::NoBrush has no colour of its own; "transparent" paints the same and survives the round-trip through QColor.
		combo->setCurrentColor(it.value().style() == Qt::NoBrush ? QColor(Qt::transparent) : it.value().color());
		form->addRow(colorLabel(key), combo);
		_colorCombos.insert(key, combo);
	}
	QScrollArea* area = new QScrollArea(ui->tab_3);
	area->setWidget(rows);
	area->setWidgetResizable(true);
	QVBoxLayout* layout = new QVBoxLayout(ui->tab_3);
	layout->addWidget(area);
}

QMap<QString, QBrush> SettingsDialog::GetColors() const
{
	QMap<QString, QBrush> colors;
	for (auto it = _colorCombos.constBegin(); it != _colorCombos.constEnd(); ++it)
	{
		const QColor color = it.value()->currentColor();
		colors.insert(it.key(), color.alpha() == 0 ? QBrush(Qt::NoBrush) : QBrush(color));
	}
	return colors;
}

void SettingsDialog::on_engine1DepthCheckBox_checkStateChanged(Qt::CheckState state) const
{
	ui->engine1DepthHorizontalSlider->setEnabled(ui->engine1DepthCheckBox->isChecked());
}

void SettingsDialog::on_engine2DepthCheckBox_checkStateChanged(Qt::CheckState state) const
{
	ui->engine2DepthHorizontalSlider->setEnabled(ui->engine2DepthCheckBox->isChecked());
}

void SettingsDialog::on_engine1TimeCheckBox_checkStateChanged(Qt::CheckState state) const
{
	ui->engine1TimeSpinBox->setEnabled(ui->engine1TimeCheckBox->isChecked());
}

void SettingsDialog::on_engine2TimeCheckBox_checkStateChanged(Qt::CheckState state) const
{
	ui->engine2TimeSpinBox->setEnabled(ui->engine2TimeCheckBox->isChecked());
}

void SettingsDialog::on_variantsLineEdit_textChanged(const QString& text)
{
	GameVariant gameVariant = EngineManager::StringToGameVariant(text);
	_pieceStyle = ui->piecesComboBox->currentText();
	ui->piecesComboBox->clear();
	switch (gameVariant)
	{
	case Chess:
	case AmazonChess:
	case AtomicChess:
	case CylinderChess:
	case CrazyHouse:
	case Shatranj:
	case Shatar:
	case Sittuyin:
	case Janggi:
	case Xiangqi:
	case ChuShogi:
	case Shogi:
	case MiniShogi:
	case JudkinShogi:
	case EuroShogi:
	case ShoShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Mnemonic");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		ui->piecesComboBox->addItem("Asian 3");
		ui->piecesComboBox->addItem("Asian 4");
		break;
	case MicroShogi:
	case KyotoShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Mnemonic");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		ui->piecesComboBox->addItem("Asian 3");
		ui->piecesComboBox->addItem("Asian 4");
		ui->piecesComboBox->addItem("Asian 5");
		break;
	case DaiShogi:
	case HeianShogi:
	case HeianDaiShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		ui->piecesComboBox->addItem("Asian 3");
		ui->piecesComboBox->addItem("Asian 4");
		break;
	case DaiDaiShogi:
	case MakaDaiDaiShogi:
	case TaiShogi:
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		break;
	case Makruk:
	case YariShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Mnemonic");
		ui->piecesComboBox->addItem("Asian");
		break;
	case TenjikuShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		break;
	case ToriShogi:
	case KoShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Mnemonic");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		break;
	case CrazyWa:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Asian");
		break;
	default:
		ui->piecesComboBox->addItem("European");
		break;
	}
	ui->piecesComboBox->setCurrentText(_pieceStyle);
}

void SettingsDialog::on_toolButton_clicked()
{
    VariantDialog* vd = new VariantDialog(this);
    vd->exec();
    if (vd->result() == Accepted && vd->GetVariant()->currentItem() != nullptr)
    {
        ui->variantsLineEdit->setText(vd->GetVariant()->currentItem()->text());
    }
}
