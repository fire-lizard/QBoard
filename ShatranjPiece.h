#pragma once
#include <unordered_map>
#include "Common.h"
#include "Piece.h"

class ShatranjPiece : public Piece
{
public:
	ShatranjPiece(PieceType pieceType, PieceColour pieceColour);
	~ShatranjPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	static PieceType FromStringCode(const std::string& code);
};

