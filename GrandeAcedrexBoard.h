#pragma once
#include "ShatranjBoard.h"
#include "GrandeAcedrexPiece.h"

class GrandeAcedrexBoard : public ShatranjBoard
{
public:
    GrandeAcedrexBoard();
    ~GrandeAcedrexBoard() override;
    void Initialize() override;
    Board* Clone() override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void GetMoves(Piece* piece, int x, int y) override;
    bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;

private:

    PieceType _initialSetup[12][12] = {
    {Rook, Lion, Unicorn, Giraffe, Bishop, Aanca, King, Bishop, Giraffe, Unicorn, Lion, Rook},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {Rook, Lion, Unicorn, Giraffe, Bishop, Aanca, King, Bishop, Giraffe, Unicorn, Lion, Rook}
    };
};
