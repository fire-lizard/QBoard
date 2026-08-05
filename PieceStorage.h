#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include "Common.h"
#include "stringmanager.h"

struct BoardSnapshot
{
	std::string fen;
	std::vector<std::pair<PieceColour, PieceType>> pieces;
};

class PieceStorage
{
public:
	std::vector<PieceType> GetCapturedPieces(PieceColour pieceColour);
	void AddCapturedPiece(PieceType p, PieceColour pieceColour);
	// False when the hand did not hold it - Kyoto needs to retry with the coin's other face.
	bool RemoveCapturedPiece(PieceType p, PieceColour pieceColour);
	void ClearCapturedPieces();
	std::string CapturedPieceString(GameVariant gameVariant);
	const std::vector<std::pair<PieceColour, PieceType>>& CapturedPieces() const;
	void SetCapturedPieces(std::vector<std::pair<PieceColour, PieceType>> pieces);

protected:
	std::vector<std::pair<PieceColour, PieceType>> _capturedPieces;

private:
	std::string formatEnumCounts(GameVariant gameVariant, PieceColour pieceColour);
};
