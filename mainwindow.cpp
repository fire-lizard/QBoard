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
		PieceStyle pieceStyle;
		if (settings[2] == "Mnemonic")
		{
			pieceStyle = Mnemonic;
		}
		else if (settings[2] == "Asian")
		{
			pieceStyle = Asian;
		}
		else
		{
			pieceStyle = European;
		}
		this->ui->vboard->SetPieceStyle(pieceStyle);
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
			StartNewGame(newGameVariant);
		}
		IniFile::writeToIniFile(_settingsDir + "/" + _settingsFileName, _currentStyle, 
			settingsDialog->GetGameVariants()->currentText(), 
			settingsDialog->GetGamePieces()->currentText(),
			settingsDialog->GetEngineOutput()->currentText());
	}
}

void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::about(this, "About", "<center>QBoard 0.8.4 beta<br/>Fire Lizard Software<br/>Anatoliy Sova<br/>Wa Shogi graphics by Ilya V. Novikov<br/>2025</center>");
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
			foreach(const QXmlStreamAttribute & attr, xml.attributes()) {
				if (attr.name().toString() == "EngineName") engineName = attr.value().toString();
                if (attr.name().toString() == "GameVariant") gameVariant = EngineManager::StringToGameVariant(attr.value().toString());
                if (attr.name().toString() == "EngineProtocol") engineProtocol = EngineManager::StringToEngineProtocol(attr.value().toString());
				if (attr.name().toString() == "EnginePath") enginePath = attr.value().toString();
			}
            if (engineName != "" && enginePath != "" && gameVariant == this->ui->vboard->GetGameVariant())
			{
                _engines.emplace_back(engineName, gameVariant, engineProtocol, enginePath);
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
	        const std::tuple<QString, GameVariant, EngineProtocol, QString> tpl = _engines[selectedIndex - 1];
			_engineName = std::get<0>(tpl);
        	_engineProtocol = std::get<2>(tpl);
            _engineExe = std::get<3>(tpl);
        }
        else _engineExe = "";
		StopEngine();
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
				_engine = new WbEngine();
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

template <typename T> std::basic_string<T> MainWindow::uppercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::toupper(v)); });
	return s2;
}

void MainWindow::on_actionOpen_triggered()
{
	GameVariant gameVariant = this->ui->vboard->GetGameVariant();
	if (gameVariant != WaShogi && gameVariant != ChuShogi && gameVariant != DaiShogi && gameVariant != TenjikuShogi)
	{
		QFileDialog fileDialog(this);
		fileDialog.setNameFilter("FEN Files (*.fen)");
		fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
		fileDialog.setWindowTitle("Open file");
		if (fileDialog.exec())
		{
			QString fileName = fileDialog.selectedFiles()[0];
			QFile file(fileName);
			file.open(QIODevice::ReadOnly | QIODevice::Text);
			QByteArray str = file.readAll();
			file.close();
			Board* board = this->ui->vboard->GetBoard();
			board->Clear();
			int w = board->GetWidth();
			int h = board->GetHeight();
			int i = 0, j = 0, k = 0;
			do
			{
				char c = str[k];
				if (c == '/')
				{
					k++;
					j++;
					i = 0;
				}
				else if (c >= '0' && c <= '9')
				{
					k++;
					i += c - 48;
				}
				else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
				{
					std::string stringCode(1, c);
					PieceType pieceType = None;
					if (gameVariant == Chess || gameVariant == Shatranj)
					{
						pieceType = ShatranjPiece::FromStringCode(uppercase(stringCode));
					}
					else if (gameVariant == Xiangqi)
					{
						pieceType = XiangqiPiece::FromStringCode(uppercase(stringCode));
					}
					else if (gameVariant == Makruk)
					{
						pieceType = MakrukPiece::FromStringCode(uppercase(stringCode));
					}
					else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
					{
						pieceType = ShogiPiece::FromStringCode(uppercase(stringCode));
					}
					if (pieceType == None)
					{
						QMessageBox::critical(this, "Error", "Invalid character found in the FEN string at position " + QString::number(k));
						return;
					}
					if (j == h || i == w)
					{
						QMessageBox::critical(this, "Error", "Invalid FEN string for this game");
						return;
					}
					Piece* piece = board->CreatePiece(pieceType, c >= 'a' && c <= 'z' ? Black : White);
					board->SetData(i, j, piece);
					k++;
					i++;
				}
			} while (i < w || j < h - 1);
			LoadEngine();
			if (_engine != nullptr)
			{
				_engine->SetFEN(str.toStdString());
			}
		}
	}
}

void MainWindow::on_actionSave_triggered()
{
	GameVariant gameVariant = this->ui->vboard->GetGameVariant();
	if (gameVariant == Chess || gameVariant == Shatranj)
	{
		QFileDialog fileDialog(this);
		fileDialog.setNameFilter("FEN Files (*.fen);;PGN Files (*.pgn)");
		fileDialog.setAcceptMode(QFileDialog::AcceptSave);
		fileDialog.setWindowTitle("Save file");
		if (fileDialog.exec())
		{
			QString fileName = fileDialog.selectedFiles()[0];
			QByteArray str;
			if (fileDialog.selectedNameFilter() == "FEN Files (*.fen)")
			{
				str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
				str += this->ui->vboard->GetCurrentPlayer() == Black ? " b KQkq - 0 1" : " w KQkq - 0 1";
			}
			else if (fileDialog.selectedNameFilter() == "PGN Files (*.pgn)")
			{
				QString userName = qgetenv("USER");
				if (userName.isEmpty())
					userName = qgetenv("USERNAME");
				const QString evt = "[Event \"QBoard Game\"]\n";
				const QString site = "[Site \"" + QSysInfo::machineHostName() + "\"]\n";
				const QString currentDate = "[Date \"" + QDate::currentDate().toString("dd/MM/yyyy") + "\"]\n";
				const QString currentRound = "[Round 1]\n";
				const QString whiteName = "[White \"" + userName + "\"]\n";
				const QString blackName = "[Black \"" + _engineName + "\"]\n";
				const QString result = "[Result \"*\"]\n\n";
				const QString pgn = QString::fromStdString(dynamic_cast<ChessBoard*>(this->ui->vboard->GetBoard())->GetPGN());
				str = (evt + site + currentDate + currentRound + whiteName + blackName + result + pgn).toLatin1();
			}
			QFile file(fileName);
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			file.write(str);
			file.close();
		}
	}
	else if (this->ui->vboard->GetGameVariant() == Xiangqi)
	{
		QFileDialog fileDialog(this);
		fileDialog.setNameFilter("FEN Files (*.fen);;WXF Files (*.wxf)");
		fileDialog.setAcceptMode(QFileDialog::AcceptSave);
		fileDialog.setWindowTitle("Save file");
		if (fileDialog.exec())
		{
			QString fileName = fileDialog.selectedFiles()[0];
			QByteArray str;
			if (fileDialog.selectedNameFilter() == "FEN Files (*.fen)")
			{
				str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
				str += this->ui->vboard->GetCurrentPlayer() == Black ? " b - - 0 1" : " w - - 0 1";
			}
			else if (fileDialog.selectedNameFilter() == "WXF Files (*.wxf)")
			{
				const QString header = "FORMAT\tWXF\n";
				QString userName = qgetenv("USER");
				if (userName.isEmpty())
					userName = qgetenv("USERNAME");
				const QString evt = "GAME\t" + userName + " vs. " + _engineName + "\n";
				const QString gameTime = "TIME\t00:00 ; 00:00\n";
				const QString currentDate = "DATE\t" + QDate::currentDate().toString("yyyy-MM-dd") + "\n";
				const QString author = "AUTHOR\tQBoard (https://github.com/fire-lizard/QBoard)\n\n";
				const QString redName = "RED\t" + userName + "\n";
				const QString blackName = "BLACK\t" + _engineName + "\n";
				const QString result = "RESULT\t0-0\n";
				const QString wxf = "START{\n" + QString::fromStdString(dynamic_cast<XiangqiBoard*>(this->ui->vboard->GetBoard())->GetWXF()) + "\n}END";
				str = (header + evt + gameTime + result + redName + blackName + currentDate + author + wxf).toLatin1();
			}
			QFile file(fileName);
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			file.write(str);
			file.close();
		}
	}
	else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
	{
		QFileDialog fileDialog(this);
		fileDialog.setNameFilter("FEN Files (*.fen);;PSN Files (*.psn);;CSA Files (*.csa);;KIF Files (*.kif)");
		fileDialog.setAcceptMode(QFileDialog::AcceptSave);
		fileDialog.setWindowTitle("Save file");
		if (fileDialog.exec())
		{
			QString fileName = fileDialog.selectedFiles()[0];
			QString userName = qgetenv("USER");
			if (userName.isEmpty())
				userName = qgetenv("USERNAME");
			QByteArray str;
			if (fileDialog.selectedNameFilter() == "FEN Files (*.fen)")
			{
				str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
				if (gameVariant == Shogi)
				{
					str += this->ui->vboard->GetCurrentPlayer() == Black ? " B - 1" : " W - 1";
				}
				else if (gameVariant == MiniShogi || gameVariant == JudkinShogi)
				{
					str += this->ui->vboard->GetCurrentPlayer() == Black ? " B" : " W";
				}
			}
			else if (fileDialog.selectedNameFilter() == "KIF Files (*.kif)")
			{
				QString kifStr;
				kifStr += "#KIF version=2.0 encoding=UTF-8\n";
				kifStr += "# KIF形式棋譜ファイル\n";
				kifStr += "# Generated by QBoard\n";
				kifStr += "先手: " + userName + "\n";
				kifStr += "後手: " + _engineName + "\n";
				kifStr += QString::fromStdString(dynamic_cast<ShogiBoard*>(this->ui->vboard->GetBoard())->GetKIF());
				str = kifStr.toUtf8();
			}
			else if (fileDialog.selectedNameFilter() == "CSA Files (*.csa)")
			{
				QString csaStr;
				csaStr += "V2.2\n";
				csaStr += "N+" + userName + "\n";
				csaStr += "N-" + _engineName + "\n";
				csaStr += "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n";
				csaStr += "P2 * -HI *  *  *  *  * -KA *\n";
				csaStr += "P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n";
				csaStr += "P4 *  *  *  *  *  *  *  *  *\n";
				csaStr += "P5 *  *  *  *  *  *  *  *  *\n";
				csaStr += "P6 *  *  *  *  *  *  *  *  *\n";
				csaStr += "P7+FU+FU+FU+FU+FU+FU+FU+FU+FU\n";
				csaStr += "P8 * +KA *  *  *  *  * +HI *\n";
				csaStr += "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n";
				csaStr += "P+\n";
				csaStr += "P-\n";
				csaStr += "+\n";
				csaStr += QString::fromStdString(dynamic_cast<ShogiBoard*>(this->ui->vboard->GetBoard())->GetCSA());
				str = csaStr.toLatin1();
			}
			else if (fileDialog.selectedNameFilter() == "PSN Files (*.psn)")
			{
				const QString senteName = "[Sente \"" + userName + "\"]\n";
				const QString goteName = "[Gote \"" + _engineName + "\"]\n\n";
				const QString psn = QString::fromStdString(dynamic_cast<ShogiBoard*>(this->ui->vboard->GetBoard())->GetPSN());
				str = (senteName + goteName + psn).toLatin1();
			}
			QFile file(fileName);
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			file.write(str);
			file.close();
		}
	}
	else
	{
		QFileDialog fileDialog(this);
		fileDialog.setNameFilter("FEN Files (*.fen)");
		fileDialog.setAcceptMode(QFileDialog::AcceptSave);
		fileDialog.setWindowTitle("Save file");
		if (fileDialog.exec())
		{
			QString fileName = fileDialog.selectedFiles()[0];
			QByteArray str;
			str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
			str += this->ui->vboard->GetCurrentPlayer() == Black ? " b" : " w";
			QFile file(fileName);
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			file.write(str);
			file.close();
		}
	}
}

void MainWindow::on_actionStop_game_triggered()
{
	StopEngine();
}

void MainWindow::on_actionExit_triggered()
{
	StopEngine();
	QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	StopEngine();
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

void MainWindow::StartNewGame(GameVariant newGameVariant)
{
	StopEngine();
	this->ui->vboard->SetGameVariant(newGameVariant);
	this->ui->vboard->GetBoard()->Initialize();
	this->ui->vboard->SetCurrentPlayer(White);
	this->ui->textEdit->setText("");
	this->ui->statusBar->showMessage(newGameVariant == Xiangqi ? "Red move" : "White move");
	this->ui->vboard->repaint();
}

void MainWindow::LoadEngine()
{
	if (_engine != nullptr)
	{
		const QProcess* process = _engine->RunProcess(this, _engineExe);
		if (process->processId() > 0 && process->state() != QProcess::ProcessState::NotRunning)
		{
			if (_engine->GetType() == XBoard)
			{
				if (ui->vboard->GetGameVariant() == MiniShogi)
				{
					_engine->StartGame("5x5+5_shogi");
				}
				else if (ui->vboard->GetGameVariant() == JudkinShogi)
				{
					_engine->StartGame("6x6+6_shogi");
				}
				else if (ui->vboard->GetGameVariant() == WaShogi)
				{
					_engine->StartGame("washogi");
				}
				else if (ui->vboard->GetGameVariant() == CrazyWa)
				{
					_engine->StartGame("crazywa");
				}
				else if (ui->vboard->GetGameVariant() == ShoShogi)
				{
					_engine->StartGame("sho");
				}
				else if (ui->vboard->GetGameVariant() == DaiShogi)
				{
					_engine->StartGame("dai");
				}
				else if (ui->vboard->GetGameVariant() == TenjikuShogi)
				{
					_engine->StartGame("tenjiku");
				}
				else if (ui->vboard->GetGameVariant() == Shogi)
				{
					_engine->StartGame("shogi");
				}
				else if (ui->vboard->GetGameVariant() == Shatranj)
				{
					_engine->StartGame("shatranj");
				}
				else if (ui->vboard->GetGameVariant() == Makruk)
				{
					_engine->StartGame("makruk");
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

void MainWindow::StopEngine()
{
	if (_engine != nullptr)
	{
		_engine->Quit();
		delete _engine;
		_engine = nullptr;
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
			foreach(const QXmlStreamAttribute & attr, xml.attributes()) {
				if (attr.name().toString() == "EngineName") engineName = attr.value().toString();
				if (attr.name().toString() == "GameVariant") gameVariant = attr.value().toString();
				if (attr.name().toString() == "EngineProtocol") engineProtocol = attr.value().toString();
				if (attr.name().toString() == "EnginePath") enginePath = attr.value().toString();
			}
			if (engineName != "" && enginePath != "")
			{
				engineTable->insertRow(engineTable->rowCount());
				const int currentRow = engineTable->rowCount() - 1;
				engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
				engineTable->setItem(currentRow, 1, new QTableWidgetItem(gameVariant));
				engineTable->setItem(currentRow, 2, new QTableWidgetItem(engineProtocol));
				engineTable->setItem(currentRow, 3, new QTableWidgetItem(enginePath));
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
		writer.writeEndElement();
	}

	writer.writeEndDocument();

	file.close();
	tempFile.close();

	file.remove();
	tempFile.rename(fileName);
}
