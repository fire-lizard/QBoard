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

void PieceStorage::RemoveCapturedPiece(PieceType p, PieceColour pieceColour)
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

void PieceStorage::ClearCapturedPieces()
{
	_capturedPieces.clear();
}

std::string PieceStorage::CapturedPieceString(GameVariant gameVariant)
{
	if (_capturedPieces.empty())
	{
		return "-";
	}
	// The pieces are always listed in the order rook, bishop, gold, silver, knight, lance, pawn
	const std::string wstr = formatEnumCounts(gameVariant, White);
	std::string bstr = formatEnumCounts(gameVariant, Black);
	std::ranges::transform(bstr, bstr.begin(), [](const char v) { return static_cast<char>(std::tolower(v)); });
	return wstr + bstr;
}

std::string PieceStorage::formatEnumCounts(GameVariant gameVariant, PieceColour pieceColour)
{
	auto orderData = StringManager::GetOrderData(gameVariant);
	auto enumList = GetCapturedPieces(pieceColour);

	// Count occurrences of each piece
	std::unordered_map<PieceType, int> counts;
	for (const auto& piece : enumList)
	{
		counts[piece]++;
	}

	std::ostringstream result;

	// Construct the output string based on the order
	for (const auto& piece : orderData.second) {
		const auto it = orderData.first.find(piece);
		if (it != orderData.first.end())
		{
			if (counts[piece] > 1) {
				result << counts[piece] << it->second; // Add count + first letter
			}
			else if (counts[piece] == 1) {
				result << it->second; // Add just the first letter
			}
		}
	}

	return result.str();
}
