#pragma once
#include <QWidget>
#include <QMessageBox>
#include <QStatusBar>
#include <QPainter>
#include <QMouseEvent>
#include <QTextEdit>
#include "mainwindow.h"
#include "ChuShogiBoard.h"
#include "ChessBoard.h"
#include "XiangqiBoard.h"
#include "ShogiBoard.h"
#include "MiniShogiBoard.h"

class VBoard : public QWidget
{
	Q_OBJECT
public:
	explicit VBoard(QWidget *parent = nullptr);
	virtual ~VBoard();
	Board* GetBoard() const;
	GameVariant GetGameVariant() const;
	void SetGameVariant(GameVariant gameVariant);
	PieceColour GetCurrentPlayer() const;
	void SetCurrentPlayer(PieceColour currentPlayer);
	void SetTextEdit(QTextEdit *textEdit);
	void SetStatusBar(QStatusBar *statusBar);
	void SetMainWindow(QMainWindow *window);
	void SetEngine(Engine *engine);

private:
	void paintEvent(QPaintEvent *) override;

	void mousePressEvent(QMouseEvent *event) override;

	bool PossibleMove(int x, int y);
	void RemoveMove(int x, int y);
	void CalculateCheck(int oldX, int oldY, int newX, int newY);

	Board *_board;
	PieceColour _currentPlayer = White;
	Piece *_currentPiece;
	int _oldX = -1;
	int _oldY = -1;
	vector<pair<int, int>> _moves;
	vector<tuple<int, int, int, int>> _opponentMoves;
	QStatusBar *_statusBar;
	QTextEdit *_textEdit;
	QMainWindow *_window = nullptr;
	GameVariant _gameVariant = Chess;
	Engine *_engine = nullptr;

signals:

	public slots :

	void readyReadStandardOutput();

	void readyReadStandardError();
};
