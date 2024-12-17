#pragma once
#include <string>
#include "Common.h"

class Piece
{
public:
	virtual ~Piece();
	std::string GetImageFileName() const;
	virtual void Promote(PieceType pieceType = None) = 0;
	virtual std::string StringCode() = 0;
	virtual std::string AsianStringCode() = 0;
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

private:
};
