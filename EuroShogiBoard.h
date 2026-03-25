#pragma once
#include "ShogiBoard.h"

class EuroShogiBoard : public ShogiBoard
{
public:
    EuroShogiBoard();
    ~EuroShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(Piece *piece, int x, int y) override;

private:

    PieceType _initialSetup[8][8] = {
        { None, Knight, Bishop, Gold, King, Gold, Knight, None },
        { None, Rook, None, None, None, None, Bishop, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, Bishop, None, None, None, None, Rook, None },
        { None, Knight, Gold, King, Gold, Bishop, Knight, None }
    };
};
