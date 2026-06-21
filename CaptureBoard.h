#pragma once
#include <vector>
#include "Common.h"

class CaptureBoard
{
public:
	std::vector<PieceType> GetCapturedPieces(PieceColour pieceColour);
	void AddCapturedPiece(PieceType p, PieceColour pieceColour);
	void RemoveCapturedPiece(PieceType p, PieceColour pieceColour);

protected:
	std::vector<std::pair<PieceColour, PieceType>> _capturedPieces;
};
