#include "ShogiVariantBoard.h"

void ShogiVariantBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
	_data[x][y] = new ShogiPiece(pieceType, pieceColour);
}

std::vector<PieceType> ShogiVariantBoard::GetCapturedPieces()
{
	return _capturedPieces;
}

void ShogiVariantBoard::RemoveCapturedPiece(PieceType p)
{
	for (size_t index = 0; index < _capturedPieces.size(); index++)
	{
		if (_capturedPieces[index] == p)
		{
			_capturedPieces.erase(_capturedPieces.begin() + index);
			break;
		}
	}
}

bool ShogiVariantBoard::Move(int oldX, int oldY, int newX, int newY)
{
	PieceType pt = _data[newX][newY] != nullptr && _data[newX][newY]->GetColour() == Black ? _data[newX][newY]->GetBaseType() : None;
	const bool result = Board::Move(oldX, oldY, newX, newY);
	if (result && pt != None)
	{
		_capturedPieces.emplace_back(pt);
	}
	return result;
}