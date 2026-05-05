#pragma once
#include "CapablancaChessBoard.h"

class JanusChessBoard : public CapablancaChessBoard
{
public:
    JanusChessBoard();
    ~JanusChessBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(Piece *piece, int x, int y) override;

protected:

    PieceType _initialSetup[8][10] = {
        { Rook, Archbishop, Knight, Bishop, King, Queen, Bishop, Knight, Archbishop, Rook },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Rook, Archbishop, Knight, Bishop, King, Queen, Bishop, Knight, Archbishop, Rook }
    };
};
