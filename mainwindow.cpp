#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	this->ui->vboard->SetMainWindow(this);
	this->ui->vboard->SetTextEdit(this->ui->textEdit);
	this->ui->vboard->SetStatusBar(this->ui->statusBar);
	QFont font = this->ui->statusBar->font();
	font.setBold(true);
	this->ui->statusBar->setFont(font);
	this->ui->statusBar->showMessage("White move");

	QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	if (QDir(settingsDir).exists())
	{
		QString settingsFile = settingsDir + "/QBoardSettings.xml";
		QFile file(settingsFile);
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QXmlStreamReader xmlStreamReader(&file);
		while (!xmlStreamReader.atEnd()) {
			QXmlStreamReader::TokenType tokenType = xmlStreamReader.readNext();
			if (tokenType == QXmlStreamReader::StartElement)
			{
				if (xmlStreamReader.name() == "Style")
				{
					tokenType = xmlStreamReader.readNext();
					if (tokenType == QXmlStreamReader::Characters)
					{
						QString style = xmlStreamReader.text().toString();
						if (QStyleFactory::keys().contains(style))
						{
							QApplication::setStyle(style);
							_currentStyle = style;
						}
						else
							this->ui->statusBar->showMessage("Unsupported style");
					}
				}
				else if (xmlStreamReader.name() == "GameVariant")
				{
					tokenType = xmlStreamReader.readNext();
					if (tokenType == QXmlStreamReader::Characters)
					{
						int gameVariant = xmlStreamReader.text().toInt();
						if (gameVariant < 6)
							this->ui->vboard->SetGameVariant(static_cast<GameVariant>(gameVariant));
						else
							this->ui->statusBar->showMessage("Unsupported game variant");
					}
				}
				else if (xmlStreamReader.name() == "EngineExe")
				{
					tokenType = xmlStreamReader.readNext();
					if (tokenType == QXmlStreamReader::Characters)
						_engineExe = xmlStreamReader.text().toString();
				}
				else if (xmlStreamReader.name() == "EngineProtocol")
				{
					tokenType = xmlStreamReader.readNext();
					if (tokenType == QXmlStreamReader::Characters)
					{
						QString selectedEngineProtocol = xmlStreamReader.text().toString();
						if (selectedEngineProtocol == "UCI")
							_engineProtocol = UCI;
						else if (selectedEngineProtocol == "UCCI")
							_engineProtocol = UCCI;
						else if (selectedEngineProtocol == "USI")
							_engineProtocol = USI;
						else
							_engineProtocol = WinBoard;
					}
				}
			}
		}
		if (xmlStreamReader.hasError())
			this->ui->statusBar->showMessage("Error while opening settings file: " + xmlStreamReader.errorString());
		
		file.close();
	}
	on_actionNew_game_triggered();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
	SettingsDialog *settingsDialog = new SettingsDialog(this);
	settingsDialog->GetGameVariants()->setCurrentIndex(this->ui->vboard->GetGameVariant());
	settingsDialog->GetStyles()->setCurrentText(_currentStyle);
	settingsDialog->exec();
	if (settingsDialog->result() == QDialog::Accepted)
	{
		QApplication::setStyle(settingsDialog->GetStyles()->itemText(settingsDialog->GetStyles()->currentIndex()));
		_currentStyle = settingsDialog->GetStyles()->currentText();
		GameVariant newGameVariant = static_cast<GameVariant>(settingsDialog->GetGameVariants()->currentIndex());
		if (newGameVariant != this->ui->vboard->GetGameVariant())
		{
			this->ui->vboard->SetGameVariant(newGameVariant);
			this->ui->vboard->GetBoard()->Initialize();
			this->ui->vboard->SetCurrentPlayer(White);
			this->ui->vboard->repaint();
		}
		QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
		if (!QDir(settingsDir).exists())
		{
			QDir().mkdir(settingsDir);
		}
		QString settingsFile = settingsDir + "/QBoardSettings.xml";
		QFile file(settingsFile);
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		QXmlStreamWriter xmlStreamWriter(&file);
		xmlStreamWriter.setAutoFormatting(true);
		xmlStreamWriter.writeStartDocument();
		xmlStreamWriter.writeStartElement("Settings");
		xmlStreamWriter.writeTextElement("Style", settingsDialog->GetStyles()->currentText());
		xmlStreamWriter.writeTextElement("GameVariant", QString::number(settingsDialog->GetGameVariants()->currentIndex()));
		_engineExe = settingsDialog->GetBlackPlayer()->currentText();
		/*if (settingsDialog->SelectedEngineProtocol == "UCI")
			_engineProtocol = UCI;
		else if (settingsDialog->SelectedEngineProtocol == "UCCI")
			_engineProtocol = UCCI;
		else if (settingsDialog->SelectedEngineProtocol == "USI")
			_engineProtocol = USI;
		else
			_engineProtocol = WinBoard;*/
		xmlStreamWriter.writeTextElement("EngineExe", _engineExe);
		//xmlStreamWriter.writeTextElement("EngineProtocol", settingsDialog->SelectedEngineProtocol);
		xmlStreamWriter.writeEndElement();
		xmlStreamWriter.writeEndDocument();
		file.close();
	}
}

void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::about(this, "About", "QBoard 1.0");
}

void MainWindow::on_actionNew_game_triggered()
{
	if (_engine != nullptr)
	{
		_engine->Quit();
		delete _engine;
	}
	if (_engineExe != "")
	{
		switch (_engineProtocol)
		{
		case UCI:
			_engine = new UciEngine();
			break;
		case UCCI:
			_engine = new UcciEngine();
			break;
		case Qianhong:
			_engine = new QianhongEngine();
			break;
		case USI:
			_engine = new UsiEngine();
			break;
		default:
			_engine = new WbEngine();
			break;
		}
		QString _engineFolder = "Pulsar";
		QString workingDir = QCoreApplication::applicationDirPath() + "/engines/" + _engineFolder;
		_engineExe = "pulsar2009-9b.exe";
		QProcess *process = _engine->RunProcess(this, workingDir, _engineExe);
		if (process->processId() > 0 && process->state() != QProcess::ProcessState::NotRunning)
		{
			_engine->StartGame();
			connect(process, SIGNAL(readyReadStandardOutput()), this->ui->vboard, SLOT(readyReadStandardOutput()));
			connect(process, SIGNAL(readyReadStandardError()), this->ui->vboard, SLOT(readyReadStandardError()));
			connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this->ui->vboard, SLOT(errorOccurred(QProcess::ProcessError)));
			this->ui->vboard->SetEngine(_engine);
		}
		else
			this->ui->statusBar->showMessage("Error while running engine: " + process->errorString());
	}
	else
		this->ui->statusBar->showMessage("Engine not set");
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
		QJsonParseError *jsonParseError = new QJsonParseError();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8(), jsonParseError);
		if (jsonParseError->error != QJsonParseError::NoError)
		{
			this->ui->statusBar->setStyleSheet("QStatusBar { color : red; }");
			this->ui->statusBar->showMessage("Error while opening file: " + jsonParseError->errorString());
			return;
		}
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

void MainWindow::on_actionStop_game_triggered()
{
	if (_engine != nullptr)
	{
		_engine->Quit();
		delete _engine;
	}
}

void MainWindow::on_actionExit_triggered()
{
	if (_engine != nullptr)
	{
		_engine->Quit();
		delete _engine;
	}
	QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (_engine != nullptr)
	{
		_engine->Quit();
		delete _engine;
	}
}
