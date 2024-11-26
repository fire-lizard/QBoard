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
	this->ui->statusBar->showMessage("White move");

	const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	if (QDir(settingsDir).exists())
	{
		const QString settingsFile = settingsDir + "/QBoardSettings.xml";
		QFile file(settingsFile);
		if (file.exists())
		{
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				this->ui->statusBar->showMessage("Error while opening settings file");
			}
			else
			{
				QXmlStreamReader xmlStreamReader(&file);
				while (!xmlStreamReader.atEnd()) {
					QXmlStreamReader::TokenType tokenType = xmlStreamReader.readNext();
					if (tokenType == QXmlStreamReader::StartElement)
					{
						if (xmlStreamReader.name().toString() == "Style")
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
						else if (xmlStreamReader.name().toString() == "GameVariant")
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
					}
				}
				if (xmlStreamReader.hasError())
					this->ui->statusBar->showMessage("Error while reading settings file: " + xmlStreamReader.errorString());

				file.close();
			}
		}
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
	settingsDialog->GetStyles()->setCurrentText(_currentStyle);
	settingsDialog->exec();
	if (settingsDialog->result() == QDialog::Accepted)
	{
		QApplication::setStyle(settingsDialog->GetStyles()->itemText(settingsDialog->GetStyles()->currentIndex()));
		_currentStyle = settingsDialog->GetStyles()->currentText();
		const GameVariant newGameVariant = static_cast<GameVariant>(settingsDialog->GetGameVariants()->currentIndex());
		if (newGameVariant != this->ui->vboard->GetGameVariant())
		{
			this->ui->vboard->SetGameVariant(newGameVariant);
			this->ui->vboard->GetBoard()->Initialize();
			this->ui->vboard->SetCurrentPlayer(White);
			this->ui->vboard->repaint();
		}
		const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
		if (!QDir(settingsDir).exists())
		{
			if (!QDir().mkdir(settingsDir))
			{
				this->ui->statusBar->showMessage("Error while creating directory for the settings file");
				return;
			}
		}
		const QString settingsFile = settingsDir + "/QBoardSettings.xml";
		QFile file(settingsFile);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			this->ui->statusBar->showMessage("Error while creating the settings file");
		}
		else
		{
			QXmlStreamWriter xmlStreamWriter(&file);
			xmlStreamWriter.setAutoFormatting(true);
			xmlStreamWriter.writeStartDocument();
			xmlStreamWriter.writeStartElement("Settings");
			xmlStreamWriter.writeTextElement("Style", settingsDialog->GetStyles()->currentText());
			xmlStreamWriter.writeTextElement("GameVariant", QString::number(settingsDialog->GetGameVariants()->currentIndex()));
			xmlStreamWriter.writeEndElement();
			xmlStreamWriter.writeEndDocument();
			file.close();
		}
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
	if (_engineExe != "" && _engineExe != "Human")
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
		for (int index = 0; index < gameRecord.size(); index++)
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
	_engineExe = "pulsar2009-9b.exe";
	const QProcess* process = _engine->RunProcess(this, _engineExe);
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
			QString engineProtocol;
			QString enginePath;
			foreach(const QXmlStreamAttribute & attr, xml.attributes()) {
				if (attr.name().toString() == "EngineName") engineName = attr.value().toString();
				if (attr.name().toString() == "EngineProtocol") engineProtocol = attr.value().toString();
				if (attr.name().toString() == "EnginePath") enginePath = attr.value().toString();
			}
			if (engineName != "" && enginePath != "")
			{
				engineTable->insertRow(engineTable->rowCount());
				const int currentRow = engineTable->rowCount() - 1;
				engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
				engineTable->setItem(currentRow, 1, new QTableWidgetItem(engineProtocol));
				engineTable->setItem(currentRow, 2, new QTableWidgetItem(enginePath));
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
		writer.writeAttribute("EngineProtocol", engineTable->item(index, 1)->text());
		writer.writeAttribute("EnginePath", engineTable->item(index, 2)->text());
		writer.writeEndElement();
	}

	writer.writeEndDocument();

	file.close();
	tempFile.close();

	file.remove();
	tempFile.rename(settingsDir + "/" + fileName);
}
