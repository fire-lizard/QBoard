#ifndef VBOARD_H
#define VBOARD_H

#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include "ChuShogiBoard.h"
#include "ChessBoard.h"

class VBoard : public QWidget
{
	Q_OBJECT
public:
	explicit VBoard(QWidget *parent = nullptr);
	virtual ~VBoard();

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

signals:

	public slots :
};

#endif // VBOARD_H
