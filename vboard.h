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
#include "ShatranjBoard.h"
#include "MakrukBoard.h"
#include "XiangqiPiece.h"
#include "promotiondialog.h"

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
	void SetStatusBar(QStatusBar *statusBar);
	void SetMainWindow(QMainWindow *window);
	void SetEngine(Engine *engine);

protected:
	void contextMenuEvent(QContextMenuEvent* event) override;

private:
	void paintEvent(QPaintEvent *) override;

	void mousePressEvent(QMouseEvent *event) override;

	bool PossibleMove(int x, int y) const;
	void RemoveMove(int x, int y);
	void CalculateCheck(int oldX, int oldY, int newX, int newY);
	void AddMove(PieceType p, int x1, int y1, int x2, int y2, int x3, int y3) const;
    QByteArray ExtractMove(const QByteArray& buf) const;
	void FinishMove();

	Board *_board;
	PieceColour _currentPlayer = White;
	PieceStyle _pieceStyle = European;
	EngineOutput _engineOutput = Concise;
	Piece *_currentPiece;
	int _oldX = -1;
	int _oldY = -1;
	std::vector<std::pair<int, int>> _moves;
	std::vector<std::tuple<int, int, int, int>> _opponentMoves;
	QStatusBar *_statusBar;
	QTextEdit *_textEdit;
	QMainWindow *_window = nullptr;
	GameVariant _gameVariant = Chess;
	Engine *_engine = nullptr;
    QRegularExpression _nlre;
    QRegularExpression _csre;
    QRegularExpression _qhre;
    QRegularExpression _sgxbre;
    QRegularExpression _sgusre;
	GameVariant _shogiVariants[8] = {Shogi, MiniShogi, JudkinShogi, ChuShogi, DaiShogi, ShoShogi, WaShogi, CrazyWa};
	PieceType _lionPieces[3] = { Lion, Eagle, Unicorn };
	bool _lionMovedOnce = false;
	std::pair<int, int> _lionFirstMove;

signals:

	public slots :

	void readyReadStandardOutput();

	void readyReadStandardError() const;
};
