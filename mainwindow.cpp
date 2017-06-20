#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	setFixedSize(this->ui->vboard->width() + 100, this->ui->vboard->height() + 100);
	this->ui->vboard->SetStatusBar(this->ui->statusBar);
	this->ui->statusBar->showMessage("White move");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
	SettingsDialog *settingsDialog = new SettingsDialog();
	settingsDialog->exec();
	if (settingsDialog->result() == QDialog::Accepted)
	{
	}

}

void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::information(this, "About", "QBoard 1.0");
}

void MainWindow::on_actionExit_triggered()
{
	QApplication::quit();
}

void MainWindow::on_actionNew_game_triggered()
{
	this->ui->vboard->GetBoard()->Initialize();
	this->ui->vboard->SetCurrentPlayer(White);
	this->ui->vboard->repaint();
}

void MainWindow::on_actionOpen_triggered()
{
	QFileDialog openFileDialog;
	QString fileName = openFileDialog.getOpenFileName(this, "Open file", "", "*.json");
	if (fileName != "")
	{
		QFile file;
		file.setFileName(fileName);
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QString data = file.readAll();
		file.close();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
		QJsonObject jsonObj = jsonDoc.object();
		PieceColour currentPlayer = static_cast<PieceColour>(jsonObj["current_player"].toInt());
		this->ui->vboard->SetCurrentPlayer(currentPlayer);
		Board *board = this->ui->vboard->GetBoard();
		for (int i = 0; i < board->GetWidth(); i++)
		{
			for (int j = 0; j < board->GetHeight(); j++)
			{
				QString key = QString::number(i) + "_" + QString::number(j);
				if (jsonObj.contains(key))
				{
					QJsonArray jsonArray = jsonObj[key].toArray();
					PieceColour pieceColour = static_cast<PieceColour>(jsonArray[0].toInt());
					PieceType pieceType = static_cast<PieceType>(jsonArray[1].toInt());
					bool isPromoted = jsonArray[2].toBool();
					Piece *piece = board->CreatePiece(pieceType, pieceColour, isPromoted);
					board->SetData(i, j, piece);
				}
				else
				{
					board->SetData(i, j, nullptr);
				}
			}
		}
		this->ui->vboard->repaint();
	}
}

void MainWindow::on_actionSave_triggered()
{
	QFileDialog saveFileDialog;
	QString fileName = saveFileDialog.getSaveFileName(this, "Save file", "", "*.json");
	if (fileName != "")
	{
		QJsonDocument jsonDoc;
		QJsonObject jsonObj;
		QJsonValue currentPlayer(this->ui->vboard->GetCurrentPlayer());
		jsonObj.insert("current_player", currentPlayer);
		Board *board = this->ui->vboard->GetBoard();
		for (int i = 0; i < board->GetWidth(); i++)
		{
			for (int j = 0; j < board->GetHeight(); j++)
			{
				Piece *piece = board->GetData(i, j);
				if (piece != nullptr)
				{
					QJsonValue pieceColour(piece->GetColour());
					QJsonValue pieceType(piece->GetType());
					QJsonValue pieceIsPromoted(piece->IsPromoted());
					QString key = QString::number(i) + "_" + QString::number(j);
					QJsonArray jsonArray;
					jsonArray.push_back(pieceColour);
					jsonArray.push_back(pieceType);
					jsonArray.push_back(pieceIsPromoted);
					jsonObj.insert(key, jsonArray);
				}
			}
		}
		jsonDoc.setObject(jsonObj);
		QByteArray json = jsonDoc.toJson();
		QFile file;
		file.setFileName(fileName);
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		file.write(json);
		file.close();
	}
}
