#pragma once
#include "Piece.h"

class ChessPiece : public Piece
{
public:
	ChessPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	virtual ~ChessPiece();
	void Promote(PieceType pieceType = None) override;
	string StringCode() override;
	string AsianStringCode() override;

protected:

private:
};
