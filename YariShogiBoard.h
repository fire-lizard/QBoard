#pragma once
#include "ShogiBoard.h"
#include "YariShogiPiece.h"

class YariShogiBoard : public ShogiBoard
{
public:
    YariShogiBoard();
    ~YariShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y) override;
    void GetMoves(Piece *piece, int x, int y) override;

private:

    PieceType _initialSetup[9][7] = {
        { YariRook, YariKnight, YariKnight, King, YariBishop, YariBishop, YariRook },
        { None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None },
        { YariRook, YariBishop, YariBishop, King, YariKnight, YariKnight, YariRook }
    };
};
