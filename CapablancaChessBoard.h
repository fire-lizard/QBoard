#pragma once
#include "ChessBoard.h"
#include "GothicChessPiece.h"

class CapablancaChessBoard : public ChessBoard
{
public:
    CapablancaChessBoard();
    ~CapablancaChessBoard() override;
    void Initialize() override;
    Board* Clone() override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void GetMoves(Piece *piece, int x, int y) override;

protected:

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
