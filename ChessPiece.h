#pragma once
#include "Piece.h"

class ChessPiece : public Piece
{
public:
	ChessPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	~ChessPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string AsianStringCode() override;

protected:

private:
};
