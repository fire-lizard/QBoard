#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted) : Piece(pieceType, pieceColour, isPromoted)
{
	//ctor
}

ChessPiece::~ChessPiece()
{
	//dtor
}

void ChessPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	_pieceType = pieceType;
}

string ChessPiece::StringCode()
{
	return "";
}
