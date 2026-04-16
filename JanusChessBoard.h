#pragma once
#include "CapablancaChessBoard.h"

class JanusChessBoard : public CapablancaChessBoard
{
public:
    JanusChessBoard();
    ~JanusChessBoard() override;
    void Initialize() override;
    Board* Clone() override;

protected:

    PieceType _initialSetup[8][10] = {
        { Rook, Archbishop, Knight, Bishop, Queen, King, Bishop, Knight, Archbishop, Rook },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Rook, Archbishop, Knight, Bishop, Queen, King, Bishop, Knight, Archbishop, Rook }
    };
};
