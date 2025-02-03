#pragma once
#include <QWidget>
#include <QMenu>
#include <QMessageBox>
#include <QStatusBar>
#include <QPainter>
#include <QMouseEvent>
#include <QTextEdit>
#include "mainwindow.h"
#include "ChuShogiBoard.h"
#include "DaiShogiBoard.h"
#include "ChessBoard.h"
#include "XiangqiBoard.h"
#include "ShogiVariantBoard.h"
#include "ShogiBoard.h"
#include "MiniShogiBoard.h"
#include "JudkinShogiBoard.h"
#include "WaShogiBoard.h"
#include "TenjikuShogiBoard.h"
#include "ShatranjBoard.h"
#include "MakrukBoard.h"
#include "XiangqiPiece.h"
#include "promotiondialog.h"
#include "EngineOutputHandler.h"
#include "Logger.h"

class VBoard : public QWidget
{
	Q_OBJECT
public:
	explicit VBoard(QWidget *parent = nullptr);
	~VBoard() override;
	Board* GetBoard() const;
	GameVariant GetGameVariant() const;
	void SetGameVariant(GameVariant gameVariant);
	PieceStyle GetPieceStyle() const;
	void SetPieceStyle(PieceStyle pieceStyle);
	EngineOutput GetEngineOutput() const;
	void SetEngineOutput(EngineOutput engineOutput);
	PieceColour GetCurrentPlayer() const;
	void SetCurrentPlayer(PieceColour currentPlayer);
	void SetTextEdit(QTextEdit *textEdit);
	void SetTextEdit2(QTextEdit* textEdit);
	void SetStatusBar(QStatusBar *statusBar);
	void SetMainWindow(QMainWindow *window);
	void SetWhiteEngine(std::shared_ptr<Engine> engine);
	void SetBlackEngine(std::shared_ptr<Engine> engine);

protected:
	void contextMenuEvent(QContextMenuEvent* event) override;

	bool event(QEvent* event) override;

private:
	void paintEvent(QPaintEvent *) override;

	void mousePressEvent(QMouseEvent *event) override;

	bool CheckRepetition(int oldX, int oldY, int newX, int newY);
	bool PossibleMove(int x, int y) const;
	void FinishMove();

	Board *_board;
	PieceColour _currentPlayer = White;
	PieceStyle _pieceStyle = European;
	EngineOutput _engineOutput = Concise;
	Piece *_currentPiece;
	int _oldX = -1;
	int _oldY = -1;
	int _px = -1;
	int _py = -1;
	std::vector<std::pair<int, int>> _moves;
	std::vector<std::pair<int, int>> _attackers;
	std::vector<std::pair<int, int>> _defenders;
	std::vector<std::tuple<int, int, int, int>> _opponentMoves;
	std::vector<std::string> _whiteMoves;
	std::vector<std::string> _blackMoves;
	QStatusBar *_statusBar;
	QTextEdit *_textEdit;
	QTextEdit *_textEdit2;
	QMainWindow *_window = nullptr;
	GameVariant _gameVariant = Chess;
	std::shared_ptr<Engine> _whiteEngine = nullptr;
	std::shared_ptr<Engine> _blackEngine = nullptr;
	GameVariant _shogiVariants[9] = {Shogi, MiniShogi, JudkinShogi, ChuShogi, DaiShogi, ShoShogi, WaShogi, CrazyWa, TenjikuShogi};
	PieceType _lionPieces[4] = { Lion, Eagle, Unicorn, LionHawk };
	bool _lionMovedOnce = false;
	std::pair<int, int> _lionFirstMove;

signals:

	public slots :

	void whiteEngineReadyReadStandardOutput();

	void whiteEngineReadyReadStandardError() const;

	void blackEngineReadyReadStandardOutput();

	void blackEngineReadyReadStandardError() const;
};
