#pragma once
#include "Common.h"
#include "DaiDaiShogiBoard.h"
#include "MakaDaiDaiShogiPiece.h"

class DaiDaiShogiPiece : public MakaDaiDaiShogiPiece
{
public:
	DaiDaiShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~DaiDaiShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
};

