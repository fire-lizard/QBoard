#pragma once
#include "ChessBoard.h"

class CapablancaChessBoard : public ChessBoard
{
public:
    CapablancaChessBoard();
    ~CapablancaChessBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(const std::optional<Piece>& piece, int x, int y) override;

private:

    PieceType _initialSetup[8][10] = {
        { Rook, Knight, Archbishop, Bishop, Queen, King, Bishop, Chancellor, Knight, Rook },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Rook, Knight, Archbishop, Bishop, Queen, King, Bishop, Chancellor, Knight, Rook }
    };
};
