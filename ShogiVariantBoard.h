#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include "Common.h"
#include "Board.h"
#include "CaptureBoard.h"

class ShogiVariantBoard : public Board, public CaptureBoard
{
public:
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
	std::string CapturedPieceString();

protected:
	virtual std::string formatEnumCounts(const std::vector<PieceType>& enumList);
};
