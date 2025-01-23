#include "ShogiVariantBoard.h"

void ShogiVariantBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
	_data[x][y] = new ShogiPiece(pieceType, pieceColour);
}

std::vector<PieceType> ShogiVariantBoard::GetCapturedPieces(PieceColour pieceColour)
{
	std::vector<PieceType> result;
	for (auto& capturedPiece : _capturedPieces)
	{
		if (capturedPiece.first == pieceColour)
		{
			result.emplace_back(capturedPiece.second);
		}
	}
	return result;
}

void ShogiVariantBoard::AddCapturedPiece(PieceType p, PieceColour pieceColour)
{
	_capturedPieces.emplace_back(pieceColour, p);
}

void ShogiVariantBoard::RemoveCapturedPiece(PieceType p, PieceColour pieceColour)
{
	for (size_t index = 0; index < _capturedPieces.size(); index++)
	{
		if (_capturedPieces[index].first == pieceColour && _capturedPieces[index].second == p)
		{
			_capturedPieces.erase(_capturedPieces.begin() + index);
			break;
		}
	}
}

bool ShogiVariantBoard::Move(int oldX, int oldY, int newX, int newY)
{
	if (_data[oldX][oldY] != nullptr)
	{
		PieceColour pieceColour = _data[oldX][oldY]->GetColour();
		PieceType pt = _data[newX][newY] != nullptr && _data[newX][newY]->GetColour() != _data[oldX][oldY]->GetColour() ? _data[newX][newY]->GetBaseType() : None;
		const bool result = Board::Move(oldX, oldY, newX, newY);
		if (result && pt != None)
		{
			_capturedPieces.emplace_back(pieceColour, pt);
		}
		return result;
	}
	return false;
}