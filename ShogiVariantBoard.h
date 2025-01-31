#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include "Common.h"
#include "Board.h"
#include "ShogiPiece.h"

class ShogiVariantBoard : public Board
{
public:
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
	virtual void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y);
	std::vector<PieceType> GetCapturedPieces(PieceColour pieceColour);
	void AddCapturedPiece(PieceType p, PieceColour pieceColour);
	void RemoveCapturedPiece(PieceType p, PieceColour pieceColour);
	std::string CapturedPieceString();

protected:
	std::vector<std::pair<PieceColour, PieceType>> _capturedPieces;

private:
	static std::string formatEnumCounts(const std::vector<PieceType>& enumList);
};
