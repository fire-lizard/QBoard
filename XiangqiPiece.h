#pragma once
#include "Piece.h"

class XiangqiPiece : public Piece
{
public:
	XiangqiPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	~XiangqiPiece() override;
	void Promote(PieceType pieceType = None) override;
	string StringCode() override;
	string AsianStringCode() override;

protected:

private:
};

