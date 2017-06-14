#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Board.h"
#include "ChessPiece.h"

class ChessBoard : public Board
{
    public:
        ChessBoard();
        virtual ~ChessBoard();
		void GetMoves(Piece *piece, int x, int y) override;

    protected:

    private:

        PieceType _initialSetup[8][8] = {
        {Rook, WhiteHorse, Bishop, King, Queen, Bishop, WhiteHorse, Rook},
        {Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
        {None, None, None, None, None, None, None, None},
        {None, None, None, None, None, None, None, None},
        {None, None, None, None, None, None, None, None},
        {None, None, None, None, None, None, None, None},
        {Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
        {Rook, WhiteHorse, Bishop, King, Queen, Bishop, WhiteHorse, Rook}
    };
};

#endif // CHESSBOARD_H
