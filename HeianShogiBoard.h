#pragma once
#include "HeianDaiShogiBoard.h"

class HeianShogiBoard : public HeianDaiShogiBoard
{
public:
    HeianShogiBoard();
    ~HeianShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;

private:

    PieceType _initialSetup[8][9] = {
        { Lance, Knight, Silver, Gold, King, Gold, Silver, Knight, Lance },
        { None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None },
        { Lance, Knight, Silver, Gold, King, Gold, Silver, Knight, Lance }
    };
};
