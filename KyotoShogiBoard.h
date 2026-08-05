#pragma once
#include "MiniShogiBoard.h"

// Every Kyoto piece is a two-sided coin, and both faces are one piece: the face showing flips on
// each move, and a captured coin may be dropped on either face. This maps a face to its other side.
PieceType KyotoFlip(PieceType pieceType);

class KyotoShogiBoard : public MiniShogiBoard
{
public:
    KyotoShogiBoard();
    ~KyotoShogiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void Promote(int x, int y, PieceType pt = None) override;
    std::string GetStringCode(int x, int y) const override;

private:

    PieceType _initialSetup[5][5] = {
        { Pawn, Gold, King, Silver, Tokin },
        { None, None, None, None, None },
        { None, None, None, None, None },
        { None, None, None, None, None },
        { Tokin, Silver, King, Gold, Pawn }
    };
};
