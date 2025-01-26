﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	_userName = qgetenv("USER");
	if (_userName.isEmpty())
		_userName = qgetenv("USERNAME");
	setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	this->ui->vboard->SetMainWindow(this);
	this->ui->vboard->SetTextEdit(this->ui->textEdit);
	this->ui->vboard->SetTextEdit2(this->ui->textEdit_2);
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
	QString aboutStr;
	aboutStr.append("<center>QBoard 0.8.8 beta<br/>");
	aboutStr.append("Fire Lizard Software<br/>");
	aboutStr.append("Anatoliy Sova<br/>");
	aboutStr.append("Wa Shogi Mnemonic graphics by Ilya V. Novikov<br/>");
	aboutStr.append("Wa Shogi Kanji graphics by Shigeki Watanabe<br/>");
	aboutStr.append("Tenjiku Shogi Kanji graphics by Shigeki Watanabe<br/>");
	aboutStr.append("2025</center>");
	QMessageBox::about(this, "About", aboutStr);
}

void MainWindow::on_actionNew_game_triggered()
{
    NewGameDialog* newGameDialog = new NewGameDialog(this);
    newGameDialog->GetWhitePlayer()->addItem(_userName);
    newGameDialog->GetBlackPlayer()->addItem(_userName);
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
		newGameDialog->GetWhitePlayer()->addItem(std::get<0>(engine));
		newGameDialog->GetBlackPlayer()->addItem(std::get<0>(engine));
    }
	newGameDialog->exec();
	if (newGameDialog->result() == QDialog::Accepted)
	{
        this->ui->textEdit->setText("");
        this->ui->statusBar->showMessage("");
        const int bpSelectedIndex = newGameDialog->GetBlackPlayer()->currentIndex();
		const int wpSelectedIndex = newGameDialog->GetWhitePlayer()->currentIndex();

		if (bpSelectedIndex > 0)
        {
	        const std::tuple<QString, GameVariant, EngineProtocol, QString> tpl = _engines[bpSelectedIndex - 1];
			_blackEngineName = std::get<0>(tpl);
			_blackEngineProtocol = std::get<2>(tpl);
			_blackEngineExe = std::get<3>(tpl);
        }
        else
			_blackEngineExe = "";

		if (wpSelectedIndex > 0)
		{
			const std::tuple<QString, GameVariant, EngineProtocol, QString> tpl = _engines[wpSelectedIndex - 1];
			_whiteEngineName = std::get<0>(tpl);
			_whiteEngineProtocol = std::get<2>(tpl);
			_whiteEngineExe = std::get<3>(tpl);
		}
		else
			_whiteEngineExe = "";

		if (_blackEngineExe != "")
		{
			switch (_blackEngineProtocol)
			{
			case UCI:
				_blackEngine = new UciEngine();
				break;
			case UCCI:
				_blackEngine = new UcciEngine();
				break;
			case Qianhong:
				_blackEngine = new QianhongEngine();
				break;
			case USI:
				_blackEngine = new UsiEngine();
				break;
			case XBoard:
				_blackEngine = new WbEngine();
				break;
			}
			LoadEngine(_blackEngine, _blackEngineExe, Black);
		}
		else
			StopEngine(_blackEngine);

		if (_whiteEngineExe != "")
		{
			switch (_whiteEngineProtocol)
			{
			case UCI:
				_whiteEngine = new UciEngine();
				break;
			case UCCI:
				_whiteEngine = new UcciEngine();
				break;
			case Qianhong:
				_whiteEngine = new QianhongEngine();
				break;
			case USI:
				_whiteEngine = new UsiEngine();
				break;
			case XBoard:
				_whiteEngine = new WbEngine();
				break;
			}
			LoadEngine(_whiteEngine, _whiteEngineExe, White);
		}
		else
			StopEngine(_whiteEngine);

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

template <typename T> std::basic_string<T> MainWindow::lowercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::tolower(v)); });
	return s2;
}

void MainWindow::on_actionOpen_triggered()
{
	GameVariant gameVariant = this->ui->vboard->GetGameVariant();
	if (gameVariant != CrazyWa && gameVariant != WaShogi && gameVariant != ChuShogi && gameVariant != DaiShogi && gameVariant != TenjikuShogi)
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
			QStringList parts = QString(str).trimmed().split(' ', Qt::SkipEmptyParts);
			QString fen = parts[0];
			file.close();
			Board* board = this->ui->vboard->GetBoard();
			board->Clear();
			int w = board->GetWidth();
			int h = board->GetHeight();
			int i = 0, j = 0, k = 0;
			std::string promo;
			do
			{
				char c = fen[k].toLatin1();
				if (c == '/')
				{
					k++;
					j++;
					i = 0;
				}
				if (c == '+')
				{
					k++;
					promo = "+";
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
						pieceType = ShogiPiece::FromStringCode(promo + uppercase(stringCode));
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
					piece->SetPromoted(promo == "+");
					board->SetData(i, j, piece);
					promo = "";
					k++;
					i++;
				}
			} while ((i < w || j < h - 1) && k < fen.size());
			if (gameVariant == Chess)
			{
				ChessBoard* cb = dynamic_cast<ChessBoard*>(board);
				if (parts.size() >= 3)
				{
					cb->SetCastling(parts[2].toStdString());
				}
				if (parts.size() >= 4)
				{
					if (parts[3].size() == 2 && parts[3][0] >= 'a' && parts[3][0] <= 'h' && parts[3][1] >= '1' && parts[3][1] <= '8')
					{
						cb->SetEnPassant(parts[3].toStdString());
					}
					else
					{
						cb->SetEnPassant("-");
					}
				}
			}
			if (gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
			{
				if (parts.size() >= 3)
				{
					ShogiVariantBoard* svb = dynamic_cast<ShogiVariantBoard*>(board);
					k = 0;
					do
					{
						if (parts[2][k] >= 'a' && parts[2][k] <= 'z')
						{
							svb->AddCapturedPiece(ShogiPiece::FromStringCode(uppercase(std::string(1, parts[2][k].toLatin1()))), Black);
						}
						else if (parts[2][k] >= 'A' && parts[2][k] <= 'Z')
						{
							svb->AddCapturedPiece(ShogiPiece::FromStringCode(std::string(1, parts[2][k].toLatin1())), White);
						}
						k++;
					} while (k < parts[2].size() && ((parts[2][k] >= 'a' && parts[2][k] <= 'z') || (parts[2][k] >= 'A' && parts[2][k] <= 'Z')));
				}
			}
			LoadEngine(_blackEngine, _blackEngineExe, Black);
			if (_blackEngine != nullptr)
			{
				if (_blackEngine->GetType() == XBoard && !dynamic_cast<WbEngine*>(_blackEngine)->GetOption("setboard"))
				{
					dynamic_cast<WbEngine*>(_blackEngine)->Edit(ui->vboard->GetBoard());
				}
				else
				{
					_blackEngine->SetFEN(str.toStdString());
				}
			}
			LoadEngine(_whiteEngine, _whiteEngineExe, White);
			if (_whiteEngine != nullptr)
			{
				if (_whiteEngine->GetType() == XBoard && !dynamic_cast<WbEngine*>(_whiteEngine)->GetOption("setboard"))
				{
					dynamic_cast<WbEngine*>(_whiteEngine)->Edit(ui->vboard->GetBoard());
				}
				else
				{
					_whiteEngine->SetFEN(str.toStdString());
				}
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
				QString mcStr = QString::number((ui->vboard->GetBoard()->MoveCount()));
				QString clStr = gameVariant == Chess ? QString::fromStdString(dynamic_cast<ChessBoard*>(ui->vboard->GetBoard())->GetCastling()) : "-";
				QString epStr = gameVariant == Chess ? QString::fromStdString(dynamic_cast<ChessBoard*>(ui->vboard->GetBoard())->GetEnPassant()) : "-";
				str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
				str += this->ui->vboard->GetCurrentPlayer() == Black ? " b " : " w ";
				str += (clStr + " " + epStr + " 0 " + mcStr).toLatin1();
			}
			else if (fileDialog.selectedNameFilter() == "PGN Files (*.pgn)")
			{
				const QString evt = "[Event \"QBoard Game\"]\n";
				const QString site = "[Site \"" + QSysInfo::machineHostName() + "\"]\n";
				const QString currentDate = "[Date \"" + QDate::currentDate().toString("dd/MM/yyyy") + "\"]\n";
				const QString currentRound = "[Round 1]\n";
				const QString whiteName = "[White \"" + _whiteEngineName + "\"]\n";
				const QString blackName = "[Black \"" + _blackEngineName + "\"]\n";
				const QString result = "[Result \"*\"]\n\n";
				const QString pgn = QString::fromStdString(dynamic_cast<ChessBoard*>(this->ui->vboard->GetBoard())->GetPGN());
				str = (evt + site + currentDate + currentRound + whiteName + blackName + result + pgn).toLatin1();
			}
			str += "\n\n";
			QFile file(fileName);
			file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
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
				QString mcStr = QString::number((ui->vboard->GetBoard()->MoveCount()));
				str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
				str += this->ui->vboard->GetCurrentPlayer() == Black ? " b - - 0 " : " w - - 0 ";
				str += mcStr.toLatin1();
			}
			else if (fileDialog.selectedNameFilter() == "WXF Files (*.wxf)")
			{
				const QString header = "FORMAT\tWXF\n";
				const QString evt = "GAME\t" + _whiteEngineName + " vs. " + _blackEngineName + "\n";
				const QString gameTime = "TIME\t00:00 ; 00:00\n";
				const QString currentDate = "DATE\t" + QDate::currentDate().toString("yyyy-MM-dd") + "\n";
				const QString author = "AUTHOR\tQBoard (https://github.com/fire-lizard/QBoard)\n\n";
				const QString redName = "RED\t" + _whiteEngineName + "\n";
				const QString blackName = "BLACK\t" + _blackEngineName + "\n";
				const QString result = "RESULT\t0-0\n";
				const QString wxf = "START{\n" + QString::fromStdString(dynamic_cast<XiangqiBoard*>(this->ui->vboard->GetBoard())->GetWXF()) + "\n}END";
				str = (header + evt + gameTime + result + redName + blackName + currentDate + author + wxf).toLatin1();
			}
			str += "\n\n";
			QFile file(fileName);
			file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
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
			QByteArray str;
			if (fileDialog.selectedNameFilter() == "FEN Files (*.fen)")
			{
				QString mcStr = QString::number((ui->vboard->GetBoard()->MoveCount()));
				QString cpStr = QString::fromStdString(dynamic_cast<ShogiVariantBoard*>(ui->vboard->GetBoard())->CapturedPieceString());
				str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
				str += this->ui->vboard->GetCurrentPlayer() == Black ? " B " : " W ";
				str += cpStr.toLatin1();
				str += " ";
				str += mcStr.toLatin1();
			}
			else if (fileDialog.selectedNameFilter() == "KIF Files (*.kif)")
			{
				QString kifStr;
				kifStr += "#KIF version=2.0 encoding=UTF-8\n";
				kifStr += "# KIF形式棋譜ファイル\n";
				kifStr += "# Generated by QBoard\n";
				kifStr += "先手: " + _whiteEngineName + "\n";
				kifStr += "後手: " + _blackEngineName + "\n";
				kifStr += QString::fromStdString(dynamic_cast<ShogiBoard*>(this->ui->vboard->GetBoard())->GetKIF());
				str = kifStr.toUtf8();
			}
			else if (fileDialog.selectedNameFilter() == "CSA Files (*.csa)")
			{
				QString csaStr;
				csaStr += "V2.2\n";
				csaStr += "N+" + _whiteEngineName + "\n";
				csaStr += "N-" + _blackEngineName + "\n";
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
				const QString senteName = "[Sente \"" + _whiteEngineName + "\"]\n";
				const QString goteName = "[Gote \"" + _blackEngineName + "\"]\n\n";
				const QString psn = QString::fromStdString(dynamic_cast<ShogiBoard*>(this->ui->vboard->GetBoard())->GetPSN());
				str = (senteName + goteName + psn).toLatin1();
			}
			str += "\n\n";
			QFile file(fileName);
			file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
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
			str += "\n\n";
			QFile file(fileName);
			file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
			file.write(str);
			file.close();
		}
	}
}

void MainWindow::on_actionStop_game_triggered()
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
}

void MainWindow::on_actionExit_triggered()
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
	QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
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
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
	this->ui->vboard->SetGameVariant(newGameVariant);
	this->ui->vboard->GetBoard()->Initialize();
	this->ui->vboard->SetCurrentPlayer(White);
	this->ui->textEdit->setText("");
	this->ui->statusBar->showMessage(newGameVariant == Xiangqi ? "Red move" : "White move");
	this->ui->vboard->repaint();
}

void MainWindow::LoadEngine(Engine* engine, QString engineExe, PieceColour player)
{
	if (engine != nullptr)
	{
		const QProcess* process = engine->RunProcess(this, engineExe);
		if (process->processId() > 0 && process->state() != QProcess::ProcessState::NotRunning)
		{
			if (engine->GetType() == XBoard)
			{
				GameVariant gameVariant = ui->vboard->GetGameVariant();
				switch (gameVariant)
				{
				case MiniShogi:
					engine->StartGame("5x5+5_shogi");
					break;
				case JudkinShogi:
					engine->StartGame("6x6+6_shogi");
					break;
				case ShoShogi:
					engine->StartGame("sho");
					break;
				case WaShogi:
					engine->StartGame("washogi");
					break;
				case CrazyWa:
					engine->StartGame("crazywa");
					break;
				case ChuShogi:
					engine->StartGame("chu");
					break;
				case DaiShogi:
					engine->StartGame("dai");
					break;
				case TenjikuShogi:
					engine->StartGame("tenjiku");
					break;
				case Shogi:
					engine->StartGame("shogi");
					break;
				case Shatranj:
					engine->StartGame("shatranj");
					break;
				case Makruk:
					engine->StartGame("makruk");
					break;
				case Xiangqi:
					engine->StartGame("xiangqi");
					break;
				case Chess:
					engine->StartGame("normal");
					break;
				default:
					engine->StartGame();
					break;
				}
			}
			else
			{
				engine->StartGame();
			}
			if (player == Black)
			{
				connect(process, SIGNAL(readyReadStandardOutput()), this->ui->vboard, SLOT(blackEngineReadyReadStandardOutput()));
				connect(process, SIGNAL(readyReadStandardError()), this->ui->vboard, SLOT(blackEngineReadyReadStandardError()));
				connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this->ui->vboard, SLOT(blackEngineReadyReadStandardError()));
				this->ui->vboard->SetBlackEngine(engine);
			}
			else
			{
				connect(process, SIGNAL(readyReadStandardOutput()), this->ui->vboard, SLOT(whiteEngineReadyReadStandardOutput()));
				connect(process, SIGNAL(readyReadStandardError()), this->ui->vboard, SLOT(whiteEngineReadyReadStandardError()));
				connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this->ui->vboard, SLOT(whiteEngineReadyReadStandardError()));
				this->ui->vboard->SetWhiteEngine(engine);
				engine->Move();
			}
		}
		else
			this->ui->statusBar->showMessage("Error while running engine: " + process->errorString());
	}
}

void MainWindow::StopEngine(Engine *engine)
{
	if (engine != nullptr)
	{
		engine->Quit();
		engine = nullptr;
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
