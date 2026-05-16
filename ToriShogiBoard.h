#pragma once
#include "ShogiBoard.h"

class ToriShogiBoard : public ShogiBoard
{
public:
    ToriShogiBoard();
    ~ToriShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y) override;
    void Promote(int x, int y, PieceType pt) override;
    void Promote(Piece *piece, PieceType pt) override;
    void GetMoves(Piece* piece, int x, int y) override;
    std::string GetStringCode(int x, int y) const override;

private:

    PieceType _initialSetup[7][7] = {
        { RightQuail, Pheasant, Crane, King, Crane, Pheasant, LeftQuail },
        { None, None, None, Falcon, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, Pawn, None, Pawn, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, Falcon, None, None, None },
        { LeftQuail, Pheasant, Crane, King, Crane, Pheasant, RightQuail }
    };
};
