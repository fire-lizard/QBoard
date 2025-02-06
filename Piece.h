#pragma once
#include <string>
#include "Common.h"

class Piece
{
public:
	virtual ~Piece();
	virtual std::string GetImageFileName() const;
	virtual void Promote(PieceType pieceType = None) = 0;
	virtual std::string StringCode() = 0;
	PieceType GetBaseType() const;
	PieceType GetType() const;
	PieceColour GetColour() const;
	bool IsPromoted() const;
	void SetPromoted(bool isPromoted);
	static std::string PieceType2Description(PieceType pieceType);
	static PieceType Description2PieceType(const std::string& description);

protected:
	Piece(PieceType pieceType, PieceColour pieceColour);
	PieceType _basePieceType;
	PieceType _pieceType;
	PieceColour _pieceColour;
	bool _isPromoted;

private:
};
