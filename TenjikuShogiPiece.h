#pragma once
#include <unordered_map>
#include "Common.h"
#include "DaiShogiPiece.h"

class TenjikuShogiPiece : public DaiShogiPiece
{
public:
	TenjikuShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~TenjikuShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
};

