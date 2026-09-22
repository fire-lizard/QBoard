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
	// For the game analysis: the whole position the way the engines are handed it, and the move that
	// led here — as text for the move list, and as the squares it went through for the arrow
	std::string engineFen;
	std::string move;
	std::vector<std::pair<int, int>> path;
	std::vector<std::pair<int, int>> shoots;
	PieceColour sideToMove = White;
};

class PieceStorage
{
public:
	std::vector<PieceType> GetCapturedPieces(PieceColour pieceColour);
	void AddCapturedPiece(PieceType p, PieceColour pieceColour);
	bool RemoveCapturedPiece(PieceType p, PieceColour pieceColour);
	void ClearCapturedPieces();
	const std::vector<std::pair<PieceColour, PieceType>>& CapturedPieces() const;
	void SetCapturedPieces(std::vector<std::pair<PieceColour, PieceType>> pieces);

protected:
	std::vector<std::pair<PieceColour, PieceType>> _capturedPieces;
};
