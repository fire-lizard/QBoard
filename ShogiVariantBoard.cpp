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

std::string ShogiVariantBoard::formatEnumCounts(const std::vector<PieceType>& enumList) 
{
	// Define the required order of pieces
	std::vector<PieceType> order = { Rook, Bishop, Gold, Silver, Knight, Lance, Pawn };

	// Count occurrences of each piece
	std::unordered_map<PieceType, int> counts;
	for (const auto& piece : enumList) 
	{
		counts[piece]++;
	}

	std::ostringstream result;

	// Construct the output string based on the order
	for (const auto& piece : order) {
		if (counts[piece] > 1) {
			result << counts[piece] << ShogiPiece::ToStringCode(piece); // Add count + first letter
		}
		else if (counts[piece] == 1) {
			result << ShogiPiece::ToStringCode(piece); // Add just the first letter
		}
	}

	return result.str();
}

std::string ShogiVariantBoard::CapturedPieceString()
{
	if (_capturedPieces.empty())
	{
		return "-";
	}
	else
	{
		// The pieces are always listed in the order rook, bishop, gold, silver, knight, lance, pawn
		std::string wstr = formatEnumCounts(GetCapturedPieces(White));
		std::string bstr = formatEnumCounts(GetCapturedPieces(Black));
		std::transform(bstr.begin(), bstr.end(), bstr.begin(), [](const char v) { return static_cast<char>(std::tolower(v)); });
		return wstr + bstr;
	}
}

bool ShogiVariantBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	if (_data[oldX][oldY] != nullptr)
	{
		PieceColour pieceColour = _data[oldX][oldY]->GetColour();
		PieceType pt = _data[newX][newY] != nullptr && _data[newX][newY]->GetColour() != _data[oldX][oldY]->GetColour() ? _data[newX][newY]->GetBaseType() : None;
		const bool result = Board::Move(oldX, oldY, newX, newY, cl);
		if (result && pt != None)
		{
			_capturedPieces.emplace_back(pieceColour, pt);
		}
		return result;
	}
	return false;
}