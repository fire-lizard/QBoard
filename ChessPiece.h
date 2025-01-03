#pragma once
#include "Piece.h"

class ChessPiece : public Piece
{
public:
	ChessPiece(PieceType pieceType, PieceColour pieceColour);
	~ChessPiece() override;
	void Promote(PieceType pieceType = None) override;
	void Move();
	bool HasMoved() const;
	std::string StringCode() override;

protected:

private:
	bool _hasMoved;
};
