#pragma once
#include "ShatranjPiece.h"

class ChessPiece : public ShatranjPiece
{
public:
	ChessPiece(PieceType pieceType, PieceColour pieceColour);
	~ChessPiece() override;
	void Move();
	bool HasMoved() const;

protected:
	bool _hasMoved;
};
