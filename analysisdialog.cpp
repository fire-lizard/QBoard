#include <algorithm>
#include <cmath>
#include "analysisdialog.h"
#include "ui_analysisdialog.h"
#include "vboard.h"

// Mate in N is scored Mate - N (and mated in N as -(Mate - N)), which keeps "mate sooner" above
// "mate later" and both above any material score.
constexpr int Mate = 100000;

static QString FormatScore(int score)
{
	if (std::abs(score) > Mate - 1000)
	{
		const int distance = Mate - std::abs(score);
		return (score < 0 ? "-#" : "#") + (distance > 0 ? QString::number(distance) : QString());
	}
	return QString::asprintf("%+.2f", score / 100.0);
}

// Lichess's curve from a score to the chance of winning, in percent. Judging a move by the chance it
// threw away, rather than by centipawns, ignores the swing of a tempo bonus in an even position and a
// mate in 3 becoming a mate in 5, and still catches the move that turns a win into a loss.
static double WinPercent(int score)
{
	return 50 + 50 * (2 / (1 + std::exp(-0.00368208 * std::clamp(score, -1000, 1000))) - 1);
}

static QString PositionName(size_t index)
{
	return index == 0 ? QObject::tr("the starting position") : QObject::tr("the position after move %1").arg(index);
}

static QString Judge(double loss)
{
	if (loss >= 30) return "?? Blunder";
	if (loss >= 20) return "? Mistake";
	if (loss >= 10) return "?! Inaccuracy";
	return "";
}

void EvalGraph::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	const QRectF area = QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5);
	painter.fillRect(area, QColor(45, 45, 45)); // what White has not won is Black's
	if (scores == nullptr || scores->size() < 2) return;
	const int positions = static_cast<int>(scores->size());
	const auto x = [&](const int index) { return area.left() + area.width() * index / (positions - 1); };
	const auto y = [&](const int score) { return area.bottom() - area.height() * WinPercent(score) / 100; };
	std::optional<int> carried; // a position the engine could not score keeps the one before it
	QPolygonF curve;
	for (int index = 0; index < analysed && index < positions; index++)
	{
		if ((*scores)[index].has_value()) carried = (*scores)[index];
		if (!carried.has_value()) continue; // nothing scored yet at all
		curve << QPointF(x(index), y(*carried));
	}
	if (!curve.empty())
	{
		QPolygonF filled = curve;
		filled << QPointF(curve.back().x(), area.bottom()) << QPointF(curve.front().x(), area.bottom());
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(235, 235, 235));
		painter.drawPolygon(filled);
	}
	painter.setPen(QColor(110, 110, 110));
	painter.drawLine(QPointF(area.left(), y(0)), QPointF(area.right(), y(0))); // an even game
	if (current > 0 && current < positions)
	{
		painter.setPen(QPen(QColorConstants::Svg::orangered, 2));
		painter.drawLine(QPointF(x(current), area.top()), QPointF(x(current), area.bottom()));
	}
}

void EvalGraph::mousePressEvent(QMouseEvent* event)
{
	if (scores == nullptr || scores->size() < 2 || !onPick) return;
	const int positions = static_cast<int>(scores->size());
	const double step = static_cast<double>(width() - 1) / (positions - 1);
	onPick(std::clamp(static_cast<int>(std::lround(event->position().x() / step)), 1, positions - 1));
}

AnalysisDialog::AnalysisDialog(VBoard* vboard, QWidget* parent) : QDialog(parent), ui(new Ui::AnalysisDialog), _vboard(vboard)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	_graph = new EvalGraph(this);
	_graph->setFixedHeight(80);
	_graph->setCursor(Qt::PointingHandCursor);
	_graph->setToolTip(tr("The game so far. Click to see a position on the board."));
	_graph->onPick = [this](const int index) { ui->resultTable->selectRow(index - 1); };
	ui->verticalLayout->insertWidget(1, _graph);
	ui->resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui->resultTable->horizontalHeader()->setStretchLastSection(true);
	_startTimer.setSingleShot(true);
	_watchdog.setSingleShot(true);
	connect(&_startTimer, &QTimer::timeout, this, &AnalysisDialog::Begin);
	connect(&_watchdog, &QTimer::timeout, this, [this]
	{
		if (!_searching)
		{
			Fail(tr("The engine stopped answering after %1.").arg(PositionName(_index - 1)));
		}
		else if (_engine->GetType() == XBoard && !_useGo)
		{
			// An engine in analysis mode thinks until it is told to stop
			dynamic_cast<WbEngine*>(_engine.get())->SendString("exit");
			if (_index == 0 && !_score.has_value() && _bestMove.isEmpty())
			{
				// Not a word about the opening position: "analyze" went unheard (MaxQi), so ask for a move
				AnalyseWithGo();
				return;
			}
			Done();
		}
		else if (_index + 1 == _history.size())
		{
			Done(); // the last position may be the end of the game, with nothing left to move
		}
		else
		{
			Fail(tr("The engine did not answer within %1 seconds on %2.").arg(ui->timeBox->value() + 10).arg(PositionName(_index)));
		}
	});
}

AnalysisDialog::~AnalysisDialog()
{
	if (_vboard != nullptr) _vboard->PreviewPosition(nullptr); // the game goes back on the board
	Stop();
	delete ui;
}

// Row n is the move that led to position n + 1, and 0 is no position at all: back to the game.
void AnalysisDialog::on_resultTable_itemSelectionChanged()
{
	const int row = ui->resultTable->currentRow();
	ShowPosition(row < 0 ? 0 : row + 1);
}

void AnalysisDialog::ShowPosition(const int index)
{
	_graph->current = index;
	_graph->update();
	if (_vboard == nullptr) return;
	// A position of this game only fits the board this game was played on
	if (index <= 0 || index >= static_cast<int>(_history.size()) || _vboard->GetGameVariant() != _variant)
	{
		_vboard->PreviewPosition(nullptr);
		return;
	}
	_vboard->PreviewPosition(&_history[index]);
}

void AnalysisDialog::SetEngines(const std::vector<std::tuple<QString, GameVariant, EngineProtocol, QString, QString>>& engines)
{
	if (_engine != nullptr) return; // not while one of them is running
	_engines = engines;
	_variant = _vboard->GetGameVariant();
	ui->engineBox->clear();
	for (const auto& engine : _engines)
	{
		ui->engineBox->addItem(std::get<0>(engine));
	}
}

void AnalysisDialog::on_analyseButton_clicked()
{
	if (_engine != nullptr)
	{
		Stop();
	}
	else
	{
		Start();
	}
}

void AnalysisDialog::Start()
{
	if (_vboard->GetGameVariant() != _variant)
	{
		QMessageBox::information(this, windowTitle(), tr("The game variant has changed. Open Game Analysis again to choose an engine for it."));
		return;
	}
	_history = _vboard->GetHistory();
	if (_history.size() < 2)
	{
		QMessageBox::information(this, windowTitle(), tr("There are no moves to analyse yet."));
		return;
	}
	if (ui->engineBox->currentIndex() < 0)
	{
		QMessageBox::information(this, windowTitle(), tr("No engine plays %1. Add one in the Engine Manager.")
			.arg(EngineManager::GameVariantToString(_variant)));
		return;
	}
	const auto& [engineName, gameVariant, engineProtocol, engineExe, engineOptions] = _engines[ui->engineBox->currentIndex()];
	_engine = MainWindow::CreateEngine(engineProtocol);
	_engine->SetTextEdit(ui->engineOutput);
	_engine->UseEngineDepth(false);
	_engine->UseEngineTime(true);
	_engine->SetEngineTime(ui->timeBox->value());
	const QProcess* process = _engine->RunProcess(this, engineExe, engineOptions);
	if (process->processId() <= 0 || process->state() == QProcess::ProcessState::NotRunning)
	{
		const QString error = process->errorString();
		_engine.reset();
		QMessageBox::warning(this, windowTitle(), tr("Error while running engine: ") + error);
		return;
	}
	connect(process, &QProcess::readyReadStandardOutput, this, &AnalysisDialog::readEngineOutput);
	_board.reset(_vboard->GetBoard()->Clone());
	_scores.assign(_history.size(), std::nullopt);
	_bestMoves.assign(_history.size(), QString());
	_buffer.clear();
	_useGo = false; // the XBoard features, which say otherwise if the engine has no analysis mode
	_ping = false;
	ui->resultTable->clearContents();
	ui->resultTable->setRowCount(static_cast<int>(_history.size()) - 1);
	for (size_t index = 1; index < _history.size(); index++)
	{
		SetCell(static_cast<int>(index) - 1, 0, _history[index].move.empty() ? "-" : QString::fromStdString(_history[index].move));
	}
	_graph->scores = &_scores;
	_graph->analysed = 0;
	_graph->current = -1;
	_graph->update();
	ui->analyseButton->setText(tr("Stop"));
	ui->engineBox->setEnabled(false);
	ui->timeBox->setEnabled(false);
	if (engineProtocol == XBoard)
	{
		auto* wb = dynamic_cast<WbEngine*>(_engine.get());
		wb->StartGame(EngineManager::GameVariantToShortString(_variant));
		wb->SendString("post"); // the thinking lines are where the score is
		_startTimer.start(2000); // until the engine says done=1, or has had long enough to have said anything
	}
	else
	{
		_engine->StartGame();
		// A book move comes with the book's opinion of it, not with a search's
		if (engineProtocol != Qianhong)
		{
			_engine->WriteToProcess(engineProtocol == UCCI ? "setoption usebook false\n" :
				engineProtocol == USI ? "setoption name USI_OwnBook value false\n" : "setoption name OwnBook value false\n");
		}
		Begin();
	}
}

void AnalysisDialog::Stop()
{
	_startTimer.stop();
	_watchdog.stop();
	_searching = false;
	_engine.reset();
	ui->analyseButton->setText(tr("Analyse"));
	ui->engineBox->setEnabled(true);
	ui->timeBox->setEnabled(true);
}

// Called from inside the engine's own output signal, where the process must not be deleted yet
void AnalysisDialog::Fail(const QString& message)
{
	_searching = false;
	QMetaObject::invokeMethod(this, [this, message]
	{
		Stop();
		if (!message.isEmpty())
		{
			QMessageBox::warning(this, windowTitle(), message);
		}
	}, Qt::QueuedConnection);
}

void AnalysisDialog::Begin()
{
	_startTimer.stop();
	_index = 0;
	AnalysePosition();
}

void AnalysisDialog::AnalysePosition()
{
	if (_engine == nullptr) return; // stopped in the meantime
	const BoardSnapshot& position = _history[_index];
	_score.reset();
	_bestMove.clear();
	_legs.clear();
	_searching = true;
	ui->engineOutput->clear();
	if (_index > 0)
	{
		ui->resultTable->scrollToItem(ui->resultTable->item(static_cast<int>(_index) - 1, 0));
	}
	if (auto* wb = dynamic_cast<WbEngine*>(_engine.get()))
	{
		// Analysis mode rather than go: the engine only thinks, and never plays a move, resigns or
		// claims a result, all of which leave some engines out of step with the next setboard
		wb->SendString("force");
		if (wb->GetOption("setboard"))
		{
			wb->SetFEN(position.engineFen);
		}
		else
		{
			// What the game does for such engines too (VBoard::SetEditorMode); an engine that knows
			// neither command answers "Illegal move", which HandleLine turns into an error
			EngineOutputHandler::TrySetFenToBoard(_board.get(), QByteArray::fromStdString(position.engineFen), _variant);
			wb->Edit(_board.get());
			wb->SendString(position.sideToMove == White ? "white" : "black");
		}
		if (_useGo)
		{
			AnalyseWithGo();
		}
		else
		{
			wb->SendString("analyze");
			_watchdog.start(ui->timeBox->value() * 1000);
		}
	}
	else
	{
		_engine->SetFEN(position.engineFen);
		_engine->Move();
		_watchdog.start((ui->timeBox->value() + 10) * 1000);
	}
}

// For an XBoard engine without an analysis mode: it plays the position as in a game, "st" long
void AnalysisDialog::AnalyseWithGo()
{
	_useGo = true;
	_engine->Move();
	_watchdog.start((ui->timeBox->value() + 10) * 1000);
}

void AnalysisDialog::readEngineOutput()
{
	if (_engine == nullptr) return;
	_buffer.append(_engine->GetProcess()->readAllStandardOutput());
	qsizetype nl;
	while ((nl = _buffer.indexOf('\n')) != -1)
	{
		const QByteArray line = _buffer.left(nl).trimmed();
		_buffer.remove(0, nl + 1);
		if (line.isEmpty()) continue;
		ui->engineOutput->append(QString::fromLatin1(line));
		HandleLine(line);
	}
}

void AnalysisDialog::HandleLine(const QByteArray& line)
{
	const EngineProtocol engineProtocol = _engine->GetType();
	if (engineProtocol == XBoard && line.startsWith("feature"))
	{
		auto* wb = dynamic_cast<WbEngine*>(_engine.get());
		if (line.contains("setboard=1")) wb->SetOption("setboard", true);
		if (line.contains("setboard=0")) wb->SetOption("setboard", false);
		if (line.contains("analyze=0")) _useGo = true;
		if (line.contains("ping=1")) _ping = true;
		if (line.contains("done=0") && _startTimer.isActive()) _startTimer.start(10000); // more features to come
		if (line.contains("done=1") && _startTimer.isActive()) Begin();
		return;
	}
	if (engineProtocol == XBoard && line == "pong " + QByteArray::number(_index))
	{
		AnalysePosition();
		return;
	}
	if (!_searching) return;
	if (engineProtocol == XBoard)
	{
		// depth, score, time, nodes and the line the engine expects, with the score from the side to move
		static const QRegularExpression thinking(R"(^(\d+)\S*\s+(-?\d+)\s+(\d+)\s+(\d+)\s*(.*)$)");
		// Not "Error (Illegal move or unknown command): easy", which only means a command it does without
		if (line.startsWith("Illegal") || line.contains("Illegal position"))
		{
			Fail(tr("The engine refused %1:\n%2").arg(PositionName(_index)).arg(QString::fromLatin1(line)));
		}
		else if (line.startsWith("Error") && line.endsWith("analyze")) // XQWLight has no analysis mode after all
		{
			AnalyseWithGo();
		}
		else if (_useGo && line.startsWith("move "))
		{
			_legs += QString::fromLatin1(line.mid(5).trimmed());
			if (!_legs.endsWith(',')) // a lion's legs arrive one line each
			{
				_bestMove = _legs;
				Done();
			}
		}
		// "resign" answers the go. A result can also trail the engine's previous move, so only the last
		// position, which may be the end of the game, is allowed to finish on one.
		else if (_useGo && (line.startsWith("resign") || (_index + 1 == _history.size() &&
			(line.startsWith("1-0") || line.startsWith("0-1") || line.startsWith("1/2-1/2")))))
		{
			Done();
		}
		else if (const QRegularExpressionMatch match = thinking.match(QString::fromLatin1(line)); match.hasMatch())
		{
			// The protocol scores a mate in N as 100000 + N
			const int score = match.captured(2).toInt();
			_score = score >= 100000 ? Mate - (score - 100000) : score <= -100000 ? -Mate + (-score - 100000) : score;
			// SjaakII writes the line in SAN with move numbers: "1. ... Qa8 2. Kg1"
			for (const QString& token : match.captured(5).split(' ', Qt::SkipEmptyParts))
			{
				if (token.endsWith('.') && (token.front().isDigit() || token.front() == '.')) continue;
				_bestMove = token;
				break;
			}
		}
	}
	else if (engineProtocol == Qianhong)
	{
		static const QRegularExpression move(R"([A-I][0-9]-[A-I][0-9])");
		if (const QRegularExpressionMatch match = move.match(line); match.hasMatch())
		{
			_bestMove = match.captured(0);
			Done();
		}
	}
	else
	{
		// UCI and USI say "score cp 25" or "score mate -3" (USI also "score mate +"), UCCI "score 25"
		static const QRegularExpression score(R"(\bscore\s+(?:(cp|mate)\s+)?([+-]?\d+|[+-]))");
		if (line.startsWith("info"))
		{
			if (const QRegularExpressionMatch match = score.match(line); match.hasMatch())
			{
				const QString value = match.captured(2);
				if (match.captured(1) == "mate")
				{
					const int distance = std::abs(value.toInt());
					_score = value.startsWith('+') || value.toInt() > 0 ? Mate - distance : -Mate + distance;
				}
				else
				{
					_score = value.toInt();
				}
			}
		}
		else if (line.startsWith("bestmove") || line.startsWith("nobestmove"))
		{
			const QString bestMove = QString::fromLatin1(line).section(' ', 1, 1);
			_bestMove = bestMove == "(none)" || bestMove == "0000" ? "" : bestMove;
			Done();
		}
	}
}

void AnalysisDialog::Done()
{
	_watchdog.stop();
	_searching = false;
	if (_score.has_value())
	{
		_scores[_index] = _history[_index].sideToMove == White ? *_score : -*_score;
	}
	_bestMoves[_index] = _bestMove;
	ShowResult(_index);
	if (++_index == _history.size())
	{
		ui->engineOutput->append(tr("Analysis complete."));
		Fail("");
	}
	else if (_ping)
	{
		// Thinking lines the engine printed before it read "exit" are still on their way; they belong
		// to the last position, so the next one waits until the engine has answered the ping
		dynamic_cast<WbEngine*>(_engine.get())->SendString("ping " + QByteArray::number(_index));
		_watchdog.start(10000);
	}
	else
	{
		// Next time round the event loop, once the rest of what the engine sent has been read and ignored
		QMetaObject::invokeMethod(this, &AnalysisDialog::AnalysePosition, Qt::QueuedConnection);
	}
}

void AnalysisDialog::ShowResult(size_t index)
{
	if (index > 0) // the row of the move that led here
	{
		const int row = static_cast<int>(index) - 1;
		if (_scores[index].has_value())
		{
			SetCell(row, 1, FormatScore(*_scores[index]));
		}
		if (_scores[index - 1].has_value() && _scores[index].has_value())
		{
			const int sign = _history[index - 1].sideToMove == White ? 1 : -1; // the side that moved
			SetCell(row, 3, Judge(WinPercent(sign * *_scores[index - 1]) - WinPercent(sign * *_scores[index])));
		}
	}
	if (index + 1 < _history.size()) // what the engine would have played instead of the next move
	{
		SetCell(static_cast<int>(index), 2, _bestMoves[index]);
	}
	_graph->analysed = static_cast<int>(index) + 1;
	_graph->update();
}

void AnalysisDialog::SetCell(int row, int column, const QString& text) const
{
	auto* item = new QTableWidgetItem(text);
	if (text.startsWith("??"))
	{
		item->setForeground(Qt::red);
	}
	ui->resultTable->setItem(row, column, item);
}
