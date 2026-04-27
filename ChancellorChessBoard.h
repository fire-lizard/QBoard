#pragma once
#include "CapablancaChessBoard.h"

class ChancellorChessBoard : public CapablancaChessBoard
{
public:
    ChancellorChessBoard();
    ~ChancellorChessBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(Piece *piece, int x, int y) override;

private:

    PieceType _initialSetup[9][9] = {
        { Rook, Knight, Bishop, Queen, King, Chancellor, Bishop, Knight, Rook },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Rook, Knight, Bishop, Queen, King, Chancellor, Bishop, Knight, Rook }
    };
};
