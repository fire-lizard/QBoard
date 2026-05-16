#pragma once
#include <string>
#include "Common.h"

class Piece
{
public:
	virtual ~Piece();
	virtual void Promote(PieceType pieceType = None) = 0;
	PieceType GetBaseType() const;
	PieceType GetType() const;
	PieceColour GetColour() const;
	bool IsPromoted() const;

protected:
	Piece(PieceType pieceType, PieceColour pieceColour);
	PieceType _basePieceType;
	PieceType _pieceType;
	PieceColour _pieceColour;
	bool _isPromoted;
};
