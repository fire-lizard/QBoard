#pragma once
#include "ChessBoard.h"
#include "PieceStorage.h"

class CrazyHouseBoard : public ChessBoard, public PieceStorage
{
public:
	CrazyHouseBoard();
	~CrazyHouseBoard() override;
	void Initialize() override;
	Board* Clone() override;
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
};
