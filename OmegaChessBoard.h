#pragma once
#include "ChessBoard.h"
#include "OmegaChessPiece.h"

class OmegaChessBoard : public ChessBoard
{
public:
    OmegaChessBoard();
    ~OmegaChessBoard() override;
    void Initialize() override;
    Board* Clone() override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void GetMoves(Piece* piece, int x, int y) override;

private:

    PieceType _initialSetup[12][12] = {
    {Wizard, None, None, None, None, None, None, None, None, None, None, Wizard},
    {None, Champion, Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook, Champion, None},
    {None, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, None},
    {None, Champion, Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook, Champion, None},
    {Wizard, None, None, None, None, None, None, None, None, None, None, Wizard}
    };
};
