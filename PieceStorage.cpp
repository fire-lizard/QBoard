#include "PieceStorage.h"

std::vector<PieceType> PieceStorage::GetCapturedPieces(PieceColour pieceColour)
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

void PieceStorage::AddCapturedPiece(PieceType p, PieceColour pieceColour)
{
	_capturedPieces.emplace_back(pieceColour, p);
}

bool PieceStorage::RemoveCapturedPiece(PieceType p, PieceColour pieceColour)
{
	for (size_t index = 0; index < _capturedPieces.size(); index++)
	{
		if (_capturedPieces[index].first == pieceColour && _capturedPieces[index].second == p)
		{
			_capturedPieces.erase(_capturedPieces.begin() + index);
			return true;
		}
	}
	return false;
}

void PieceStorage::ClearCapturedPieces()
{
	_capturedPieces.clear();
}

const std::vector<std::pair<PieceColour, PieceType>>& PieceStorage::CapturedPieces() const
{
	return _capturedPieces;
}

void PieceStorage::SetCapturedPieces(std::vector<std::pair<PieceColour, PieceType>> pieces)
{
	_capturedPieces = std::move(pieces);
}
