#pragma once
#include "ShogiBoard.h"
#include "ShogiPiece.h"

class HeianDaiShogiBoard : public ShogiBoard
{
public:
    HeianDaiShogiBoard();
    //~MiniShogiBoard() override;
    //void Initialize() override;
    //Board* Clone() override;

private:

    PieceType _initialSetup[5][5] = {
        { Rook, Bishop, Silver, Gold, King },
        { None, None, None, None, Pawn },
        { None, None, None, None, None },
        { Pawn, None, None, None, None },
        { King, Gold, Silver, Bishop, Rook }
    };
};
