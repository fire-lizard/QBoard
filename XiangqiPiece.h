#pragma once
#include "Piece.h"

class XiangqiPiece : public Piece
{
public:
	XiangqiPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	~XiangqiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string AsianStringCode() override;
	static std::string GetChineseImageFileName(PieceType pieceType, PieceColour pieceColour);

protected:

private:
};

