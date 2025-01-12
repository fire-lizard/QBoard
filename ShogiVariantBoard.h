#pragma once
#include <vector>
#include "Common.h"
#include "Board.h"
#include "ShogiPiece.h"

class ShogiVariantBoard : public Board
{
public:
	bool Move(int oldX, int oldY, int newX, int newY) override;
	virtual void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y);
	std::vector<PieceType> GetCapturedPieces(PieceColour pieceColour);
	void RemoveCapturedPiece(PieceType p, PieceColour pieceColour);

protected:
	std::vector<std::pair<PieceColour, PieceType>> _capturedPieces;
};
