#pragma once
#include "ShatranjBoard.h"

class GrandeAcedrexBoard : public ShatranjBoard
{
public:
    GrandeAcedrexBoard();
    ~GrandeAcedrexBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void Promote(int x, int y, PieceType pt) override;
    void Promote(Piece *piece, PieceType pt) override;
    void GetMoves(Piece* piece, int x, int y) override;
    bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
    std::string GetStringCode(int x, int y) const override;

private:

    PieceType _initialSetup[12][12] = {
    {Rook, Lion, Unicorn, Giraffe, Crocodile, Aanca, King, Crocodile, Giraffe, Unicorn, Lion, Rook},
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
    {Rook, Lion, Unicorn, Giraffe, Crocodile, Aanca, King, Crocodile, Giraffe, Unicorn, Lion, Rook}
    };
};
