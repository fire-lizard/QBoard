#pragma once
#include "KyotoShogiBoard.h"
#include "MicroShogiPiece.h"

class MicroShogiBoard : public KyotoShogiBoard
{
public:
    MicroShogiBoard();
    ~MicroShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y) override;

private:

    PieceType _initialSetup[5][4] = {
        { King, Bishop, Gold, Silver },
        { Pawn, None, None, None },
        { None, None, None, None },
        { None, None, None, Pawn },
        { Silver, Gold, Bishop, King }
    };
};
