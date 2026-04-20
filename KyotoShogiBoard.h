#pragma once
#include "MiniShogiBoard.h"
#include "KyotoShogiPiece.h"

class KyotoShogiBoard : public MiniShogiBoard
{
public:
    KyotoShogiBoard();
    ~KyotoShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y) override;

private:

    PieceType _initialSetup[5][5] = {
        { Pawn, Gold, King, Silver, Tokin },
        { None, None, None, None, None },
        { None, None, None, None, None },
        { None, None, None, None, None },
        { Tokin, Silver, King, Gold, Pawn }
    };
};
