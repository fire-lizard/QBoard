#pragma once
#include "ShogiBoard.h"

class YariShogiBoard : public ShogiBoard
{
public:
    YariShogiBoard();
    ~YariShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void Promote(int x, int y, PieceType pt) override;
    void Promote(Piece *piece, PieceType pt) override;
    void GetMoves(Piece *piece, int x, int y) override;

protected:
    std::string formatEnumCounts(const std::vector<PieceType>& enumList) override;

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
