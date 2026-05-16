#pragma once
#include "Common.h"
#include "DaiShogiPiece.h"

class KoShogiPiece : public DaiShogiPiece
{
public:
	KoShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~KoShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	void Demote();
};

