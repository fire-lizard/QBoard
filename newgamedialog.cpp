#include "newgamedialog.h"
#include "ui_newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget* parent) : QDialog(parent), ui(new Ui::NewGameDialog)
{
	ui->setupUi(this);
}

NewGameDialog::~NewGameDialog()
{
	delete ui;
}

QComboBox* NewGameDialog::GetWhitePlayer() const
{
	return ui->whitePlayerComboBox;
}

QComboBox* NewGameDialog::GetBlackPlayer() const
{
	return ui->blackPlayerComboBox;
}

QLabel* NewGameDialog::GetWhitePlayerLabel() const
{
	return ui->whitePlayerLabel;
}
