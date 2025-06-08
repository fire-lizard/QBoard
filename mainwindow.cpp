#include "mainwindow.h"
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
		else if (settings[2] == "Asian 2")
		{
			pieceStyle = Asian2;
		}
		else if (settings[2] == "Asian 3")
		{
			pieceStyle = Asian3;
		}
		else if (settings[2] == "Asian 4")
		{
			pieceStyle = Asian4;
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
	aboutStr.append("<center>QBoard 0.9.9.4 beta<br/>");
	aboutStr.append("Fire Lizard Software<br/>");
	aboutStr.append("Programming by Anatoliy Sova<br/>");
	aboutStr.append("Wa Shogi Mnemonic graphics by Ilya V. Novikov<br/>");
	aboutStr.append("Ko Shogi graphics by TKR101010 (from Deviantart)<br/>");
	aboutStr.append("Maka Dai Dai Shogi Kanji graphics by Joe Henbethydd<br/>");
	aboutStr.append("Shogi Variants Kanji graphics by Shigeki Watanabe<br/>");
	aboutStr.append("2025</center>");
	QMessageBox::about(this, "About", aboutStr);
}

void MainWindow::on_actionPlace_triggered() const
{
	ui->vboard->SetEditorMode(!ui->vboard->GetEditorMode());
	ui->vboard->repaint();
}

void MainWindow::on_actionClear_triggered() const
{
	QMessageBox mb(QMessageBox::Question, "Warning", "Are you sure you want to clear the board?",
		QMessageBox::Yes | QMessageBox::No);
	const int response = mb.exec();
	if (response == QMessageBox::Yes)
	{
		StopEngine(_whiteEngine);
		StopEngine(_blackEngine);
		Board* board = ui->vboard->GetBoard();
		const int width = board->GetWidth();
		const int height = board->GetHeight();
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				const Piece* p = board->GetData(i, j);
				delete p;
				board->SetData(i, j, nullptr);
			}
		}
		if (!ui->vboard->GetEditorMode())
		{
			ui->vboard->SetEditorMode(true);
		}
		ui->vboard->repaint();
	}
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
		this->ui->textEdit_2->setText("");
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
				_blackEngine = std::make_shared<UciEngine>();
				break;
			case UCCI:
				_blackEngine = std::make_shared<UcciEngine>();
				break;
			case Qianhong:
				_blackEngine = std::make_shared<QianhongEngine>();
				break;
			case USI:
				_blackEngine = std::make_shared<UsiEngine>();
				break;
			case XBoard:
				_blackEngine = std::make_shared<WbEngine>();
				break;
			}
			_blackEngine->SetTextEdit(ui->textEdit_2);
			_blackEngine->SetActive(true);
			LoadEngine(_blackEngine, _blackEngineExe, Black);
		}
		else
			StopEngine(_blackEngine);

		if (_whiteEngineExe != "")
		{
			switch (_whiteEngineProtocol)
			{
			case UCI:
				_whiteEngine = std::make_shared<UciEngine>();
				break;
			case UCCI:
				_whiteEngine = std::make_shared<UcciEngine>();
				break;
			case Qianhong:
				_whiteEngine = std::make_shared<QianhongEngine>();
				break;
			case USI:
				_whiteEngine = std::make_shared<UsiEngine>();
				break;
			case XBoard:
				_whiteEngine = std::make_shared<WbEngine>();
				break;
			}
			_whiteEngine->SetTextEdit(ui->textEdit);
			_whiteEngine->SetActive(true);
			LoadEngine(_whiteEngine, _whiteEngineExe, White);
		}
		else
			StopEngine(_whiteEngine);

		this->ui->vboard->GetBoard()->Initialize();
		this->ui->vboard->SetCurrentPlayer(White);
		this->ui->vboard->repaint();
	}
}

void MainWindow::on_actionOpen_triggered()
{
	QFileDialog fileDialog(this);
	fileDialog.setNameFilter("FEN Files (*.fen)");
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setWindowTitle("Open file");
	if (fileDialog.exec())
	{
		const QString fileName = fileDialog.selectedFiles()[0];
		QFile file(fileName);
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		const QByteArray str = file.readAll();
		file.close();
		Board* board = this->ui->vboard->GetBoard();
		const QString errorStr = EngineOutputHandler::SetFenToBoard(board, str, ui->vboard->GetGameVariant());
		if (!errorStr.isEmpty())
		{
			QMessageBox::critical(this, "Error", errorStr);
		}
		if (_blackEngine != nullptr && _blackEngine->IsActive())
		{
			if (_blackEngine->GetType() == XBoard && !std::dynamic_pointer_cast<WbEngine>(_blackEngine)->GetOption("setboard"))
			{
				std::dynamic_pointer_cast<WbEngine>(_blackEngine)->Edit(ui->vboard->GetBoard());
			}
			else
			{
				_blackEngine->SetFEN(str.toStdString());
			}
		}
		if (_whiteEngine != nullptr && _whiteEngine->IsActive())
		{
			if (_whiteEngine->GetType() == XBoard && !std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->GetOption("setboard"))
			{
				std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->Edit(ui->vboard->GetBoard());
			}
			else
			{
				_whiteEngine->SetFEN(str.toStdString());
			}
		}
	}
}

void MainWindow::on_actionSave_triggered()
{
	GameVariant gameVariant = this->ui->vboard->GetGameVariant();
	if (gameVariant == Chess || gameVariant == Shatranj || gameVariant == Makruk)
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
				if (gameVariant == Chess)
				{
					QString mcStr = QString::number(ui->vboard->GetBoard()->MoveCount());
					QString hmStr = QString::number(dynamic_cast<ChessBoard*>(ui->vboard->GetBoard())->HalfMoveCount());
					QString clStr = gameVariant == Chess ? QString::fromStdString(dynamic_cast<ChessBoard*>(ui->vboard->GetBoard())->GetCastling()) : "-";
					QString epStr = gameVariant == Chess ? QString::fromStdString(dynamic_cast<ChessBoard*>(ui->vboard->GetBoard())->GetEnPassant()) : "-";
					str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
					str += this->ui->vboard->GetCurrentPlayer() == Black ? " b " : " w ";
					str += (clStr + " " + epStr + " " + hmStr + " " + mcStr).toLatin1();
				}
				else
				{
					str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
					str += this->ui->vboard->GetCurrentPlayer() == Black ? " b " : " w ";
				}
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
				const QString pgn = QString::fromStdString(dynamic_cast<ShatranjBoard*>(this->ui->vboard->GetBoard())->GetPGN());
				str = (evt + site + currentDate + currentRound + whiteName + blackName + result + pgn).toLatin1();
			}
			str += "\n\n";
			QFile file(fileName);
			const QIODevice::OpenMode flags = fileDialog.selectedNameFilter() == "FEN Files (*.fen)" ?
				QIODevice::WriteOnly | QIODevice::Text : QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text;
			file.open(flags);
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
				QString mcStr = QString::number(ui->vboard->GetBoard()->MoveCount());
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
			const QIODevice::OpenMode flags = fileDialog.selectedNameFilter() == "FEN Files (*.fen)" ?
				QIODevice::WriteOnly | QIODevice::Text : QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text;
			file.open(flags);
			file.write(str);
			file.close();
		}
	}
	else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi ||
			 gameVariant == JudkinShogi || gameVariant == WaShogi || gameVariant == CrazyWa)
	{
		QFileDialog fileDialog(this);
		if (gameVariant == CrazyWa || gameVariant == WaShogi)
		{
			fileDialog.setNameFilter("FEN Files (*.fen);;PGN Files (*.pgn)");
		}
		else
		{
			fileDialog.setNameFilter("FEN Files (*.fen);;PSN Files (*.psn);;CSA Files (*.csa);;KIF Files (*.kif);;KI2 Files (*.ki2)");
		}
		fileDialog.setAcceptMode(QFileDialog::AcceptSave);
		fileDialog.setWindowTitle("Save file");
		if (fileDialog.exec())
		{
			QString fileName = fileDialog.selectedFiles()[0];
			QByteArray str;
			if (fileDialog.selectedNameFilter() == "FEN Files (*.fen)")
			{
				QString mcStr = QString::number(ui->vboard->GetBoard()->MoveCount());
				QString cpStr = QString::fromStdString(dynamic_cast<ShogiVariantBoard*>(ui->vboard->GetBoard())->CapturedPieceString());
				str = QByteArray::fromStdString(ui->vboard->GetBoard()->GetFEN());
				str += this->ui->vboard->GetCurrentPlayer() == Black ? " b " : " w ";
				if (gameVariant != ShoShogi && gameVariant != WaShogi)
				{
					str += cpStr.toLatin1();
					str += " ";
				}
				str += mcStr.toLatin1();
			}
			else if (fileDialog.selectedNameFilter() == "PGN Files (*.pgn)")
			{
				const QString senteName = "[Sente \"" + _whiteEngineName + "\"]\n";
				const QString goteName = "[Gote \"" + _blackEngineName + "\"]\n\n";
				const QString psn = QString::fromStdString(dynamic_cast<WaShogiBoard*>(this->ui->vboard->GetBoard())->GetPGN());
				str = (senteName + goteName + psn).toLatin1();
			}
			else if (fileDialog.selectedNameFilter() == "KIF Files (*.kif)" || fileDialog.selectedNameFilter() == "KI2 Files (*.ki2)")
			{
				QString kifStr;
				kifStr += "#KIF version=2.0 encoding=UTF-8\n";
				kifStr += "# KIF形式棋譜ファイル\n";
				kifStr += "# Generated by QBoard\n";
				kifStr += "先手: " + _whiteEngineName + "\n";
				kifStr += "後手: " + _blackEngineName + "\n";
				if (fileDialog.selectedNameFilter() == "KIF Files (*.kif)")
				{
					kifStr += QString::fromStdString(dynamic_cast<ShogiBoard*>(this->ui->vboard->GetBoard())->GetKIF());
				}
				else
				{
					kifStr += QString::fromStdString(dynamic_cast<ShogiBoard*>(this->ui->vboard->GetBoard())->GetKI2());
				}
				str = kifStr.toUtf8();
			}
			else if (fileDialog.selectedNameFilter() == "CSA Files (*.csa)")
			{
				QString csaStr;
				csaStr += "V2.2\n";
				csaStr += "N+" + _whiteEngineName + "\n";
				csaStr += "N-" + _blackEngineName + "\n";
				if (gameVariant == Shogi)
				{
					csaStr += "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n";
					csaStr += "P2 * -HI *  *  *  *  * -KA *\n";
					csaStr += "P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n";
					csaStr += "P4 *  *  *  *  *  *  *  *  *\n";
					csaStr += "P5 *  *  *  *  *  *  *  *  *\n";
					csaStr += "P6 *  *  *  *  *  *  *  *  *\n";
					csaStr += "P7+FU+FU+FU+FU+FU+FU+FU+FU+FU\n";
					csaStr += "P8 * +KA *  *  *  *  * +HI *\n";
					csaStr += "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n";
				}
				else if (gameVariant == ShoShogi)
				{
					csaStr += "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n";
					csaStr += "P2 * -HI *  *  SZ *  * -KA *\n";
					csaStr += "P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n";
					csaStr += "P4 *  *  *  *  *  *  *  *  *\n";
					csaStr += "P5 *  *  *  *  *  *  *  *  *\n";
					csaStr += "P6 *  *  *  *  *  *  *  *  *\n";
					csaStr += "P7+FU+FU+FU+FU+FU+FU+FU+FU+FU\n";
					csaStr += "P8 * +KA *  *  SZ *  * +HI *\n";
					csaStr += "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n";
				}
				else if (gameVariant == MiniShogi)
				{
					csaStr += "P1-HI-KA-GI-KI-OU\n";
					csaStr += "P2 *  *  *  * -FU\n";
					csaStr += "P3 *  *  *  *  *\n";
					csaStr += "P4+FU *  *  *  *\n";
					csaStr += "P5+OU+KI+GI+KA+HI\n";
				}
				else if (gameVariant == JudkinShogi)
				{
					csaStr += "P1-HI-KA-KE-GI-KI-OU\n";
					csaStr += "P2 *  *  *  *  * -FU\n";
					csaStr += "P3 *  *  *  *  *  *\n";
					csaStr += "P4 *  *  *  *  *  *\n";
					csaStr += "P5+FU *  *  *  *  *\n";
					csaStr += "P6+OU+KI+GI+KE+KA+HI\n";
				}
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
			const QIODevice::OpenMode flags = fileDialog.selectedNameFilter() == "FEN Files (*.fen)" ?
				QIODevice::WriteOnly | QIODevice::Text : QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text;
			file.open(flags);
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
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			file.write(str);
			file.close();
		}
	}
}

void MainWindow::on_actionStop_game_triggered() const
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
}

void MainWindow::on_actionExit_triggered() const
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

void MainWindow::StartNewGame(GameVariant newGameVariant) const
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
	this->ui->vboard->SetGameVariant(newGameVariant);
	this->ui->vboard->GetBoard()->Initialize();
	this->ui->vboard->SetCurrentPlayer(White);
	this->ui->textEdit->setText("");
	this->ui->textEdit_2->setText("");
	this->ui->statusBar->showMessage(newGameVariant == Xiangqi ? "Red move" : "White move");
	this->ui->vboard->repaint();
}

void MainWindow::LoadEngine(const std::shared_ptr<Engine>& engine, const QString& engineExe, PieceColour player)
{
	if (engine != nullptr)
	{
		const QProcess* process = engine->RunProcess(this, engineExe);
		if (process->processId() > 0 && process->state() != QProcess::ProcessState::NotRunning)
		{
			if (engine->GetType() == XBoard)
			{
				switch (ui->vboard->GetGameVariant())
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
				case DaiDaiShogi:
				case MakaDaiDaiShogi:
				case KoShogi:
					engine->StartGame();
					break;
				}
				if (engineExe.toLower().contains("hachu"))
				{
					std::dynamic_pointer_cast<WbEngine>(engine)->SetMemory(_engineMemorySize);
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

void MainWindow::StopEngine(std::shared_ptr<Engine> engine)
{
	if (engine)
	{
		engine->SetActive(false);
		engine->Quit();
		engine.reset();
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
