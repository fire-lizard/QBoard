﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	this->ui->vboard->SetMainWindow(this);
	this->ui->vboard->SetTextEdit(this->ui->textEdit);
	this->ui->vboard->SetStatusBar(this->ui->statusBar);
	QFont font = this->ui->statusBar->font();
	font.setBold(true);
	this->ui->statusBar->setFont(font);
	this->ui->statusBar->showMessage(this->ui->vboard->GetGameVariant() == Xiangqi ? "Red move" : "White move");
	_settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	if (QFile::exists(_settingsDir + "/" + _settingsFileName))
	{
		QStringList settings = IniFile::readFromIniFile(_settingsDir + "/" + _settingsFileName);
		_currentStyle = settings[0];
		QApplication::setStyle(_currentStyle);
		this->ui->vboard->SetGameVariant(EngineManager::StringToGameVariant(settings[1]));
		this->ui->vboard->SetPieceStyle(settings[2] == "Asian" ? Asian : European);
		this->ui->vboard->SetEngineOutput(settings[3] == "Verbose" ? Verbose : Concise);
		this->ui->vboard->GetBoard()->Initialize();
		this->ui->statusBar->showMessage(settings[1] == "Xiangqi" ? "Red move" : "White move");
		this->ui->vboard->repaint();
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
	SettingsDialog *settingsDialog = new SettingsDialog(this);
	settingsDialog->GetGameVariants()->setCurrentIndex(this->ui->vboard->GetGameVariant());
	settingsDialog->GetGamePieces()->setCurrentIndex(this->ui->vboard->GetPieceStyle());
	settingsDialog->GetEngineOutput()->setCurrentIndex(this->ui->vboard->GetEngineOutput());
	settingsDialog->GetStyles()->setCurrentText(_currentStyle);
	settingsDialog->exec();
	if (settingsDialog->result() == QDialog::Accepted)
	{
		QApplication::setStyle(settingsDialog->GetStyles()->itemText(settingsDialog->GetStyles()->currentIndex()));
		_currentStyle = settingsDialog->GetStyles()->currentText();
		const GameVariant newGameVariant = static_cast<GameVariant>(settingsDialog->GetGameVariants()->currentIndex());
		const PieceStyle pieceStyle = static_cast<PieceStyle>(settingsDialog->GetGamePieces()->currentIndex());
		const EngineOutput engineOutput = static_cast<EngineOutput>(settingsDialog->GetEngineOutput()->currentIndex());
		if (pieceStyle != this->ui->vboard->GetPieceStyle())
		{
			this->ui->vboard->SetPieceStyle(pieceStyle);
			this->ui->vboard->repaint();
		}
		if (engineOutput != this->ui->vboard->GetEngineOutput())
		{
			this->ui->vboard->SetEngineOutput(engineOutput);
		}
		if (newGameVariant != this->ui->vboard->GetGameVariant())
		{
			if (_engine != nullptr)
			{
				_engine->Quit();
				delete _engine;
				_engine = nullptr;
			}
			this->ui->vboard->SetGameVariant(newGameVariant);
			this->ui->vboard->GetBoard()->Initialize();
			this->ui->vboard->SetCurrentPlayer(White);
			this->ui->textEdit->setText("");
			this->ui->statusBar->showMessage(newGameVariant == Xiangqi ? "Red move" : "White move");
			this->ui->vboard->repaint();
		}
		IniFile::writeToIniFile(_settingsDir + "/" + _settingsFileName, _currentStyle, 
			settingsDialog->GetGameVariants()->currentText(), 
			settingsDialog->GetGamePieces()->currentText(),
			settingsDialog->GetEngineOutput()->currentText());
	}
}

void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::about(this, "About", "QBoard 0.4 alpha\nFire Lizard Software\nAnatoliy Sova\n2024");
}

void MainWindow::on_actionNew_game_triggered()
{
    NewGameDialog* newGameDialog = new NewGameDialog(this);
    newGameDialog->GetWhitePlayer()->addItem("Human");
    newGameDialog->GetBlackPlayer()->addItem("Human");
	if (this->ui->vboard->GetGameVariant() == Xiangqi)
	{
		newGameDialog->GetWhitePlayerLabel()->setText("<html><head/><body><p><span style='color:#ffffff;background:#ff0000; '>Red player</span></p></body></html>");
	}
	else
	{
		newGameDialog->GetWhitePlayerLabel()->setText("<html><head/><body><p><span style='background:#ffffff; '>White player</span></p></body></html>");
	}
	_engines.clear();
	QFile file(_settingsDir + "/" + _enginesListFileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the file for reading.";
		return;
	}

	QXmlStreamReader xml(&file);

	while (!xml.atEnd() && !xml.hasError()) {
		const QXmlStreamReader::TokenType token = xml.readNext();

		if (token == QXmlStreamReader::StartElement) {

			// Read attributes
			QString engineName;
            GameVariant gameVariant = Chess;
            EngineProtocol engineProtocol;
			QString enginePath;
			QString engineParameters;
			foreach(const QXmlStreamAttribute & attr, xml.attributes()) {
				if (attr.name().toString() == "EngineName") engineName = attr.value().toString();
                if (attr.name().toString() == "GameVariant") gameVariant = EngineManager::StringToGameVariant(attr.value().toString());
                if (attr.name().toString() == "EngineProtocol") engineProtocol = EngineManager::StringToEngineProtocol(attr.value().toString());
				if (attr.name().toString() == "EnginePath") enginePath = attr.value().toString();
				if (attr.name().toString() == "EngineParameters") engineParameters = attr.value().toString();
			}
            if (engineName != "" && enginePath != "" && gameVariant == this->ui->vboard->GetGameVariant())
			{
                _engines.emplace_back(engineName, gameVariant, engineProtocol, enginePath, engineParameters);
			}
		}
	}

	if (xml.hasError()) {
		qDebug() << "Error reading XML:" << xml.errorString();
	}

	file.close();

	for (auto& engine : _engines)
	{
        newGameDialog->GetBlackPlayer()->addItem(std::get<0>(engine));
    }
	newGameDialog->exec();
	if (newGameDialog->result() == QDialog::Accepted)
	{
        this->ui->textEdit->setText("");
        this->ui->statusBar->showMessage("");
        const int selectedIndex = newGameDialog->GetBlackPlayer()->currentIndex();
        if (selectedIndex > 0)
        {
	        const std::tuple<QString, GameVariant, EngineProtocol, QString, QString> tpl = _engines[selectedIndex - 1];
            _engineProtocol = std::get<2>(tpl);
            _engineExe = std::get<3>(tpl);
            _engineArguments.clear();
            _engineArguments << std::get<4>(tpl).trimmed().split(' ', Qt::SkipEmptyParts);
        }
        else _engineExe = "";
        if (_engine != nullptr)
		{
			_engine->Quit();
			delete _engine;
            _engine = nullptr;
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
			case XBoard:
				constexpr GameVariant gameVariants[] = { ChuShogi, ShoShogi, MiniShogi };
				if (std::find(std::begin(gameVariants), std::end(gameVariants), this->ui->vboard->GetGameVariant()) != std::end(gameVariants))
				{
					_engine = new ChuShogiEngine();
				}
				else 
				{
					_engine = new WbEngine();
				}
				break;
			}
			LoadEngine();
		}
		else
			this->ui->statusBar->showMessage("Engine not set");
		this->ui->vboard->GetBoard()->Initialize();
		this->ui->vboard->SetCurrentPlayer(White);
		this->ui->vboard->repaint();
	}
}

void MainWindow::on_actionOpen_triggered()
{
	/*if (this->ui->vboard->GetGameVariant() == Chess)
	{
		const QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "PGN Files (*.pgn)");
		if (fileName != "")
		{
		}
	}*/
}

void MainWindow::on_actionSave_triggered()
{
	/*if (this->ui->vboard->GetGameVariant() == Chess)
	{
		const QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "PGN Files (*.pgn)");
		if (fileName != "")
		{
			const QString evt = "[Event \"QBoard Game\"]\n";
			const QString site = "[Site \"" + QSysInfo::machineHostName() + "\"]\n";
			const QString currentDate = "[Date \"" + QDate::currentDate().toString("dd/MM/yyyy") + "\"]\n";
			const QString currentRound = "[Round 1]\n";
			QString userName = qgetenv("USER");
			if (userName.isEmpty())
				userName = qgetenv("USERNAME");
			const QString whiteName = "[White \"" + userName + "\"]\n";
			const QString blackName = "[Black \"" + _engineName + "\"]\n";
			const QString result = "[Result \"*\"]\n\n";
		}
	}*/
}

void MainWindow::on_actionStop_game_triggered()
{
	if (_engine != nullptr)
	{
		_engine->Quit();
		delete _engine;
		_engine = nullptr;
	}
}

void MainWindow::on_actionExit_triggered()
{
	if (_engine != nullptr)
	{
		_engine->Quit();
		delete _engine;
		_engine = nullptr;
	}
	QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (_engine != nullptr)
	{
		_engine->Quit();
		delete _engine;
		_engine = nullptr;
	}
}

void MainWindow::on_actionEngine_Manager_triggered()
{
	EngineManager *engineManager = new EngineManager(this);
	readXmlUsingStream(_settingsDir + "/" + _enginesListFileName, engineManager->GetEngineTable());
	engineManager->exec();
	if (engineManager->result() == QDialog::Accepted)
	{
		createXmlFromTable(_settingsDir + "/" + _enginesListFileName, engineManager->GetEngineTable());
	}
}

void MainWindow::LoadEngine()
{
	if (_engine != nullptr)
	{
		const QProcess* process = _engine->RunProcess(this, _engineExe, _engineArguments);
		if (process->processId() > 0 && process->state() != QProcess::ProcessState::NotRunning)
		{
			if (_engine->GetType() == XBoard)
			{
				if (ui->vboard->GetGameVariant() == MiniShogi)
				{
					_engine->StartGame("mini");
				}
				else if (ui->vboard->GetGameVariant() == ShoShogi)
				{
					_engine->StartGame("sho");
				}
				else
				{
					_engine->StartGame();
				}
			}
			else
			{
				_engine->StartGame();
			}
			connect(process, SIGNAL(readyReadStandardOutput()), this->ui->vboard, SLOT(readyReadStandardOutput()));
			connect(process, SIGNAL(readyReadStandardError()), this->ui->vboard, SLOT(readyReadStandardError()));
            connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this->ui->vboard, SLOT(readyReadStandardError()));
			this->ui->vboard->SetEngine(_engine);
		}
		else
			this->ui->statusBar->showMessage("Error while running engine: " + process->errorString());
	}
}

void MainWindow::readXmlUsingStream(const QString& fileName, QTableWidget *engineTable)
{
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the file for reading.";
		return;
	}

	QXmlStreamReader xml(&file);

	while (!xml.atEnd() && !xml.hasError()) {
		const QXmlStreamReader::TokenType token = xml.readNext();

		if (token == QXmlStreamReader::StartElement) {

			// Read attributes
			QString engineName;
			QString gameVariant;
			QString engineProtocol;
			QString enginePath;
			QString engineParameters;
			foreach(const QXmlStreamAttribute & attr, xml.attributes()) {
				if (attr.name().toString() == "EngineName") engineName = attr.value().toString();
				if (attr.name().toString() == "GameVariant") gameVariant = attr.value().toString();
				if (attr.name().toString() == "EngineProtocol") engineProtocol = attr.value().toString();
				if (attr.name().toString() == "EnginePath") enginePath = attr.value().toString();
				if (attr.name().toString() == "EngineParameters") engineParameters = attr.value().toString();
			}
			if (engineName != "" && enginePath != "")
			{
				engineTable->insertRow(engineTable->rowCount());
				const int currentRow = engineTable->rowCount() - 1;
				engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
				engineTable->setItem(currentRow, 1, new QTableWidgetItem(gameVariant));
				engineTable->setItem(currentRow, 2, new QTableWidgetItem(engineProtocol));
				engineTable->setItem(currentRow, 3, new QTableWidgetItem(enginePath));
				engineTable->setItem(currentRow, 4, new QTableWidgetItem(engineParameters));
			}
		}
		else if (token == QXmlStreamReader::Characters && !xml.isWhitespace()) {
			qDebug() << "Element text:" << xml.text().toString();
		}
	}

	if (xml.hasError()) {
		qDebug() << "Error reading XML:" << xml.errorString();
	}

	file.close();
}

void MainWindow::createXmlFromTable(const QString& fileName, const QTableWidget* engineTable)
{
	QFile file(fileName);
	QFile tempFile(QFileInfo(fileName).absolutePath() + "/" + "temp.xml");

	if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the temp file for writing.";
		file.close();
		return;
	}

	QXmlStreamWriter writer(&tempFile);

	writer.setAutoFormatting(true);
	writer.writeStartDocument();

	writer.writeStartElement("Engines");

	for (int index = 0; index < engineTable->rowCount(); index++)
	{
		writer.writeStartElement("Engine");
		writer.writeAttribute("EngineName", engineTable->item(index, 0)->text());
		writer.writeAttribute("GameVariant", engineTable->item(index, 1)->text());
		writer.writeAttribute("EngineProtocol", engineTable->item(index, 2)->text());
		writer.writeAttribute("EnginePath", engineTable->item(index, 3)->text());
		writer.writeAttribute("EngineParameters", engineTable->item(index, 4)->text());
		writer.writeEndElement();
	}

	writer.writeEndDocument();

	file.close();
	tempFile.close();

	file.remove();
	tempFile.rename(fileName);
}
