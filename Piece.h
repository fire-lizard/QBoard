#ifndef PIECE_H
#define PIECE_H
#include <string>
#include "Common.h"

using namespace std;

class Piece
{
public:
	virtual ~Piece();
	static string GetImageFileName(PieceType pieceType, PieceColour pieceColour);
	virtual void Promote() = 0;
	PieceType GetType() const;
	PieceColour GetColour() const;
	bool IsPromoted() const;

protected:
	Piece(PieceType pieceType, PieceColour pieceColour);
	PieceType _pieceType;
	PieceColour _pieceColour;
	bool _isPromoted;

private:
};

#endif // PIECE_H
