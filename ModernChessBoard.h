#pragma once
#include "ChancellorChessBoard.h"

class ModernChessBoard : public ChancellorChessBoard
{
public:
    ModernChessBoard();
    ~ModernChessBoard() override;
    void Initialize() override;
    Board* Clone() override;

private:

    PieceType _initialSetup[9][9] = {
        { Rook, Knight, Bishop, Queen, King, Archbishop, Bishop, Knight, Rook },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Rook, Knight, Bishop, Archbishop, King, Queen, Bishop, Knight, Rook }
    };
};
