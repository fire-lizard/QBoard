#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <tuple>
#include <vector>
#include <QDialog>
#include <QPointer>
#include <QTimer>
#include "Engine.h"
#include "Board.h"
#include "PieceStorage.h"

namespace Ui {
	class AnalysisDialog;
}

class VBoard;

// The scores so far as a curve: the game read left to right, White's chances filled from the bottom.
// Clicking it picks a position, the same as clicking the row.
class EvalGraph : public QWidget
{
	Q_OBJECT

public:
	using QWidget::QWidget;
	const std::vector<std::optional<int>>* scores = nullptr; // centipawns from White's side, one per position
	int analysed = 0; // how many of them have been searched, the graph growing as the analysis runs
	int current = -1; // the position on show, or -1
	std::function<void(int)> onPick;

protected:
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;
};

// Runs an engine over every position of the game played so far and shows, move by move, the
// score, what the engine would have played instead, and how much the move played gave away.
class AnalysisDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AnalysisDialog(VBoard* vboard, QWidget* parent = nullptr);
	~AnalysisDialog() override;
	void SetEngines(const std::vector<std::tuple<QString, GameVariant, EngineProtocol, QString, QString>>& engines);

private slots:
	void on_analyseButton_clicked();

	void on_resultTable_itemSelectionChanged();

	void readEngineOutput();

private:
	void ShowPosition(int index);
	void Start();
	void Stop();
	void Fail(const QString& message);
	void Begin();
	void AnalysePosition();
	void AnalyseWithGo();
	void HandleLine(const QByteArray& line);
	void Done();
	void ShowResult(size_t index);
	void SetCell(int row, int column, const QString& text) const;

	Ui::AnalysisDialog* ui;
	QPointer<VBoard> _vboard; // the board may be torn down first when the main window closes
	EvalGraph* _graph = nullptr;
	std::vector<std::tuple<QString, GameVariant, EngineProtocol, QString, QString>> _engines;
	GameVariant _variant = Chess;
	std::shared_ptr<Engine> _engine;
	std::unique_ptr<Board> _board; // an edit-mode engine is handed the position one piece at a time
	std::vector<BoardSnapshot> _history;
	std::vector<std::optional<int>> _scores; // centipawns from White's side, one per position
	std::vector<QString> _bestMoves;
	size_t _index = 0;
	bool _searching = false;
	bool _useGo = false; // an XBoard engine without an analysis mode
	bool _ping = false;
	std::optional<int> _score; // from the side to move, for the position being searched
	QString _bestMove;
	QString _legs; // of the move an XBoard engine is sending
	QByteArray _buffer;
	QTimer _startTimer;
	QTimer _watchdog;
};
