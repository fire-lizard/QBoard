#pragma once
#include "KanjiPiece.h"

class XiangqiPiece : public KanjiPiece
{
public:
	XiangqiPiece(PieceType pieceType, PieceColour pieceColour);
	~XiangqiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetKanjiImageFileName() override;

protected:

private:
};

