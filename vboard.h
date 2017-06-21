#pragma once
#include <QWidget>
#include <QMessageBox>
#include <QStatusBar>
#include <QPainter>
#include <QMouseEvent>
#include "mainwindow.h"
#include "ChuShogiBoard.h"
#include "ChessBoard.h"
#include "XiangqiBoard.h"
#include "ShogiBoard.h"
#include "TrueChessBoard.h"

class VBoard : public QWidget
{
	Q_OBJECT
public:
	explicit VBoard(QWidget *parent = nullptr);
	virtual ~VBoard();
	Board* GetBoard() const;
	PieceColour GetCurrentPlayer() const;
	void SetCurrentPlayer(PieceColour currentPlayer);
	void SetGameVariant(GameVariant gameVariant);
	void SetStatusBar(QStatusBar *statusBar);
	void SetMainWindow(QMainWindow *window);

private:
	void paintEvent(QPaintEvent *);

	void mousePressEvent(QMouseEvent *event);

	bool PossibleMove(int x, int y);
	void RemoveMove(int x, int y);
	void CalculateCheck(int oldX, int oldY, int newX, int newY);

	Board *_board;
	PieceColour _currentPlayer = White;
	Piece *_currentPiece;
	int _oldX = -1;
	int _oldY = -1;
	vector<pair<int, int>> _moves;
	vector<tuple<int, int, int, int>> _myMoves;
	vector<tuple<int, int, int, int>> _opponentMoves;
	QStatusBar *_statusBar;
	QMainWindow *_window;
	GameVariant _gameVariant;

signals:

	public slots :
};
