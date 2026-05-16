#pragma once
#include "ChessBoard.h"

class OmegaChessBoard : public ChessBoard
{
public:
    OmegaChessBoard();
    ~OmegaChessBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(Piece* piece, int x, int y) override;
    bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
    std::string GetStringCode(int x, int y) const override;

protected:
    bool EnemyPawnsAround(int x, int y) const override;

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
