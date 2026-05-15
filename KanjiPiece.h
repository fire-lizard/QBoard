#pragma once
#include "Piece.h"

class KanjiPiece : public Piece
{
public:
	KanjiPiece(PieceType pieceType, PieceColour pieceColour);
	~KanjiPiece() override;
};

