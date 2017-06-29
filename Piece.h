#pragma once
#include <string>
#include "Common.h"

using namespace std;

class Piece
{
public:
	virtual ~Piece();
	static string GetImageFileName(PieceType pieceType, PieceColour pieceColour);
	virtual void Promote(PieceType pieceType = None) = 0;
	virtual string StringCode() = 0;
	PieceType GetBaseType() const;
	PieceType GetType() const;
	PieceColour GetColour() const;
	bool IsPromoted() const;

protected:
	Piece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	PieceType _basePieceType;
	PieceType _pieceType;
	PieceColour _pieceColour;
	bool _isPromoted;

private:
};
