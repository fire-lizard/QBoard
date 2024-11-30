#include "mainwindow.h"
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
		if (newGameVariant != this->ui->vboard->GetGameVariant() || pieceStyle != this->ui->vboard->GetPieceStyle() || engineOutput != this->ui->vboard->GetEngineOutput())
		{
			this->ui->vboard->SetGameVariant(newGameVariant);
			this->ui->vboard->SetPieceStyle(pieceStyle);
			this->ui->vboard->SetEngineOutput(engineOutput);
			this->ui->vboard->GetBoard()->Initialize();
			this->ui->vboard->SetCurrentPlayer(White);
			this->ui->statusBar->showMessage(newGameVariant == Xiangqi ? "Red move" : "White move");
			this->ui->vboard->repaint();
		}
	}
}

void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::about(this, "About", "QBoard 0.1 alpha\nFire Lizard Software\nAnatoliy Sova");
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
		case WinBoard:
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

void MainWindow::on_actionOpen_triggered()
{
	const QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "PGN Files (*.pgn)");
	if (fileName != "")
	{
		QFile file;
		file.setFileName(fileName);
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QString data = file.readAll();
		file.close();
		this->ui->vboard->repaint();
	}
}

void MainWindow::on_actionSave_triggered()
{
	const QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "PGN Files (*.pgn)");
	if (fileName != "")
	{
		QFile file;
		file.setFileName(fileName);
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		file.write("[Event \"QBoard Game\"]\n");
		const QString site = "[Site \"" + QSysInfo::machineHostName() + "\"]\n";
		file.write(site.toLocal8Bit());
		const QString currentDate = "[Date \"" + QDate::currentDate().toString("dd/MM/yyyy") + "\"]\n";
		file.write(currentDate.toLocal8Bit());
		const std::vector<std::string> gameRecord = ui->vboard->GetGameRecord();
		const QString currentRound = "[Round \"" + QString::number(gameRecord.size()) + "\"]\n";
		file.write(currentRound.toLocal8Bit());
		QString userName = qgetenv("USER");
		if (userName.isEmpty())
			userName = qgetenv("USERNAME");
		const QString whiteName = "[White \"" + userName + "\"]\n";
		const QString blackName = "[Black \"" + _engineName + "\"]\n\n";
		file.write(whiteName.toLocal8Bit());
		file.write(blackName.toLocal8Bit());
		GameVariant gameVariant = ui->vboard->GetGameVariant();
		for (size_t index = 0; index < gameRecord.size(); index++)
		{
			file.write(QString::number(index + 1).toLocal8Bit());
			file.write(". ");
			file.write(gameRecord[index].c_str());
			file.write(" ");
		}
		file.close();
	}
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
	readXmlUsingStream("QBoardEngines.xml", engineManager->GetEngineTable());
	engineManager->exec();
	if (engineManager->result() == QDialog::Accepted)
	{
		createXmlFromTable("QBoardEngines.xml", engineManager->GetEngineTable());
	}
}

void MainWindow::LoadEngine()
{
	if (_engine != nullptr)
	{
		const QProcess* process = _engine->RunProcess(this, _engineExe, _engineArguments);
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
}

void MainWindow::readXmlUsingStream(const QString& fileName, QTableWidget *engineTable)
{
	const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	QFile file(settingsDir + "/" + fileName);

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
	const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	QFile file(settingsDir + "/" + fileName);
	QFile tempFile(settingsDir + "/temp.xml");

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
	tempFile.rename(settingsDir + "/" + fileName);
}
