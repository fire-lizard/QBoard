#pragma once
#include <unordered_map>
#include "KanjiPiece.h"

class XiangqiPiece : public KanjiPiece
{
public:
	XiangqiPiece(PieceType pieceType, PieceColour pieceColour);
	~XiangqiPiece() override;
	void Promote(PieceType pieceType = None) override;
};

