#pragma once
#include "ShatranjPiece.h"

class ChessPiece : public ShatranjPiece
{
public:
	ChessPiece(PieceType pieceType, PieceColour pieceColour);
	~ChessPiece() override;
	void Promote(PieceType pieceType = None) override;
	void Move();
	bool HasMoved() const;

protected:

private:
	bool _hasMoved;
};
