#pragma once
#include "ShatranjBoard.h"
#include "CourierChessPiece.h"

class CourierChessBoard : public ShatranjBoard
{
public:
    CourierChessBoard();
    ~CourierChessBoard() override;
    void Initialize() override;
    Board* Clone() override;
    Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void GetMoves(Piece* piece, int x, int y) override;
    std::string GetStringCode(int x, int y) const override;

private:

    PieceType _initialSetup[8][12] = {
    {Rook, Knight, Bishop, Courier, Sage, King, Queen, Schleich, Courier, Bishop, Knight, Rook},
    {Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None, None, None, None, None},
    {Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
    {Rook, Knight, Bishop, Courier, Sage, King, Queen, Schleich, Courier, Bishop, Knight, Rook}
    };
};
