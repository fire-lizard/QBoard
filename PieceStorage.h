#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include "Common.h"
#include "stringmanager.h"

class PieceStorage
{
public:
	std::vector<PieceType> GetCapturedPieces(PieceColour pieceColour);
	void AddCapturedPiece(PieceType p, PieceColour pieceColour);
	void RemoveCapturedPiece(PieceType p, PieceColour pieceColour);
	void ClearCapturedPieces();
	std::string CapturedPieceString(GameVariant gameVariant);

protected:
	std::vector<std::pair<PieceColour, PieceType>> _capturedPieces;

private:
	std::string formatEnumCounts(GameVariant gameVariant, PieceColour pieceColour);
};
