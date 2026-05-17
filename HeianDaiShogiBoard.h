#pragma once
#include "DaiShogiBoard.h"

class HeianDaiShogiBoard : public DaiShogiBoard
{
public:
    HeianDaiShogiBoard();
    ~HeianDaiShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void Promote(int x, int y, PieceType pt) override;
    void Promote(Piece *piece, PieceType pt) override;
    void GetMoves(Piece* piece, int x, int y) override;

private:

    PieceType _initialSetup[13][13] = {
        { Lance, Knight, Iron, Copper, Silver, Gold, King, Gold, Silver, Copper, Iron, Knight, Lance },
        { ReverseChariot, FlyingDragon, None, None, Tiger, None, SideMover, None, Tiger, None, None, FlyingDragon, ReverseChariot },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, GoBetween, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, GoBetween, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { ReverseChariot, FlyingDragon, None, None, Tiger, None, SideMover, None, Tiger, None, None, FlyingDragon, ReverseChariot },
        { Lance, Knight, Iron, Copper, Silver, Gold, King, Gold, Silver, Copper, Iron, Knight, Lance }
    };
};
