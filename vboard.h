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

private:
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);

    bool PossibleMove(int x, int y);

    //ChuShogiBoard _board;
    ChessBoard _board;
    PieceColour _currentPlayer = White;
    bool _check = false;
    Piece *_currentPiece;
    int _oldX = -1;
    int _oldY = -1;
    vector<pair<int,int>> _moves;
    vector<pair<int,int>> _myMoves;
    vector<pair<int,int>> _opponentMoves;

signals:

public slots:
};

#endif // VBOARD_H
