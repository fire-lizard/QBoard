#pragma once
#include "ShatranjBoard.h"

class ShatarBoard : public ShatranjBoard
{
public:
    ShatarBoard();
    ~ShatarBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(Piece* piece, int x, int y) override;

protected:

    PieceType _initialSetup[8][8] = {
        { Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Rook, Knight, Bishop, King, Queen, Bishop, Knight, Rook }
    };
};
