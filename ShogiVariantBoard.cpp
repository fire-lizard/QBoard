#include "ShogiVariantBoard.h"

void ShogiVariantBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
	_data[x][y] = new ShogiPiece(pieceType, pieceColour);
}
