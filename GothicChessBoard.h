#pragma once
#include "CapablancaChessBoard.h"

class GothicChessBoard : public CapablancaChessBoard
{
public:
    GothicChessBoard();
    ~GothicChessBoard() override;
    void Initialize() override;
    Board* Clone() override;

protected:

    PieceType _initialSetup[8][10] = {
        { Rook, Knight, Bishop, Queen, Chancellor, King, Archbishop, Bishop, Knight, Rook },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Rook, Knight, Bishop, Queen, Chancellor, King, Archbishop, Bishop, Knight, Rook }
    };
};
