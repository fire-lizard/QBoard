#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include "Piece.h"

class ChessPiece : public Piece
{
    public:
        ChessPiece(PieceType pieceType, PieceColour pieceColour);
        virtual ~ChessPiece();
		void Promote() override;

    protected:

    private:
};

#endif // CHESSPIECE_H
