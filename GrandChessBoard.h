#pragma once
#include "CapablancaChessBoard.h"

class GrandChessBoard : public CapablancaChessBoard
{
public:
    GrandChessBoard();
    ~GrandChessBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(Piece *piece, int x, int y) override;
    bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;

protected:

    PieceType _initialSetup[10][10] = {
        { Rook, None, None, None, None, None, None, None, None, Rook },
        { None, Knight, Bishop, Queen, King, Chancellor, Archbishop, Bishop, Knight, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, Knight, Bishop, Queen, King, Chancellor, Archbishop, Bishop, Knight, None },
        { Rook, None, None, None, None, None, None, None, None, Rook },
    };

    bool EnemyPawnsAround(int x, int y) const override;
};
