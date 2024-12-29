#pragma once
#include <vector>
#include "Common.h"
#include "Board.h"
#include "ShogiPiece.h"

class ShogiVariantBoard : public Board
{
public:
	bool Move(int oldX, int oldY, int newX, int newY) override;
	void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y);
	std::vector<PieceType> GetCapturedPieces();
	void RemoveCapturedPiece(PieceType p);

protected:
	std::vector<PieceType> _capturedPieces;
};
