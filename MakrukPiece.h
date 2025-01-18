#pragma once
#include <unordered_map>
#include "Common.h"
#include "ShatranjPiece.h"

class MakrukPiece : public ShatranjPiece
{
public:
	MakrukPiece(PieceType pieceType, PieceColour pieceColour);
	~MakrukPiece() override;
	std::string StringCode() override;
	PieceType FromStringCode(const std::string& code) override;
};

