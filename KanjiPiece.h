#pragma once
#include "Piece.h"

class KanjiPiece : public Piece
{
public:
	KanjiPiece(PieceType pieceType, PieceColour pieceColour);
	~KanjiPiece() override;
	virtual std::string KanjiStringCode() = 0;
	virtual std::string GetKanjiImageFileName() = 0;
};

