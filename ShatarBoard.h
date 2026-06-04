#pragma once
#include "ShatranjBoard.h"

class ShatarBoard : public ShatranjBoard
{
public:
    ShatarBoard();
    ~ShatarBoard() override;
    void Initialize() override;
    Board* Clone() override;
    void GetMoves(const std::optional<Piece>& piece, int x, int y) override;
    void SetEvalMode(bool evalMode);

private:
    void CheckKnightMove(const std::optional<Piece>& piece, int x, int y);
    bool IsCheckmate(int oldX, int oldY, int newX, int newY);

    bool _evalMode = false;

    PieceType _initialSetup[8][8] = {
        { Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None },
        { None, None, None, None, None, None, None, None },
        { Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
        { Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook }
    };
};
