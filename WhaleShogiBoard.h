#pragma once
#include "ShogiBoard.h"
#include "WhaleShogiPiece.h"

class WhaleShogiBoard : public ShogiBoard
{
public:
    WhaleShogiBoard();
    ~WhaleShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y) override;
    void GetMoves(Piece* piece, int x, int y) override;

private:

    PieceType _initialSetup[6][6] = {
        { BlueWhale, Narwhal, Porpoise, King, GreyWhale, Humpback },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None },
        { None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Humpback, GreyWhale, King, Porpoise, Narwhal, BlueWhale }
    };
};
