#pragma once
#include "Common.h"
#include "ShatranjPiece.h"

class MakrukPiece : public ShatranjPiece
{
public:
	MakrukPiece(PieceType pieceType, PieceColour pieceColour);
	~MakrukPiece() override;
};

