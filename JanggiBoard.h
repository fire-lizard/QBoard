#pragma once
#include "XiangqiBoard.h"
#include "XiangqiPiece.h"

class JanggiBoard : public XiangqiBoard
{
public:
    JanggiBoard();
    ~JanggiBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(Piece *piece, int x, int y) override;

private:

    PieceType _initialSetup[10][9] = {
        { Rook, Knight, Elephant, Silver, None, Silver, Elephant, Knight, Rook },
        { None, None, None, None, King, None, None, None, None },
        { None, Cannon, None, None, None, None, None, Cannon, None },
        { Pawn, None, Pawn, None, Pawn, None, Pawn, None, Pawn },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { Pawn, None, Pawn, None, Pawn, None, Pawn, None, Pawn },
        { None, Cannon, None, None, None, None, None, Cannon, None },
        { None, None, None, None, King, None, None, None, None },
        { Rook, Knight, Elephant, Silver, None, Silver, Elephant, Knight, Rook }
    };
};
