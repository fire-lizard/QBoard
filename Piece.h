#pragma once
#include <string>
#include "Common.h"

class Piece
{
public:
	virtual ~Piece();
	PieceType GetBaseType() const;
	PieceType GetType() const;
    void SetType(PieceType pieceType);
	PieceColour GetColour() const;
    bool IsPromoted;

protected:
	Piece(PieceType pieceType, PieceColour pieceColour);
	PieceType _basePieceType;
	PieceType _pieceType;
	PieceColour _pieceColour;
};
