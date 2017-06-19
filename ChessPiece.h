#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include "Piece.h"

class ChessPiece : public Piece
{
public:
	ChessPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	virtual ~ChessPiece();
	void Promote(PieceType pieceType = None) override;
	string StringCode() override;

protected:

private:
};

#endif // CHESSPIECE_H
