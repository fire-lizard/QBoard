#pragma once
#include "MiniShogiBoard.h"

class KyotoShogiBoard : public MiniShogiBoard
{
public:
    KyotoShogiBoard();
    ~KyotoShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void Promote(int x, int y, PieceType pt) override;
    void Promote(Piece *piece, PieceType pt) override;

private:

    PieceType _initialSetup[5][5] = {
        { Pawn, Gold, King, Silver, Tokin },
        { None, None, None, None, None },
        { None, None, None, None, None },
        { None, None, None, None, None },
        { Tokin, Silver, King, Gold, Pawn }
    };
};
