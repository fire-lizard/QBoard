#pragma once
#include "CapablancaChessBoard.h"
#include "PieceStorage.h"

class SeirawanChessBoard : public CapablancaChessBoard, public PieceStorage
{
public:
	SeirawanChessBoard();
	~SeirawanChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	void GetMoves(const std::optional<Piece>& piece, int x, int y) override;
	std::string GetStringCode(int x, int y) const override;

	int BackRank(PieceColour pieceColour) const;
	bool Gate(int x, int y, PieceType pieceType, PieceColour pieceColour);
	std::string GatingRights() const;
};
