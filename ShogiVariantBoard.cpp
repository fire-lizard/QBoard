#include "ShogiVariantBoard.h"

void ShogiVariantBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
    SetData(x, y, Piece(pieceType, pieceColour));
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
    static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
        {Rook, "R"},
        {Bishop, "B"},
        {Lance, "L"},
        {Silver, "S"},
        {Gold, "G"},
        {Knight, "N"},
        {Pawn, "P"}
    };

    // Define the required order of pieces
    const std::vector order = { Rook, Bishop, Gold, Silver, Knight, Lance, Pawn };

	// Count occurrences of each piece
	std::unordered_map<PieceType, int> counts;
	for (const auto& piece : enumList) 
	{
		counts[piece]++;
	}

	std::ostringstream result;

	// Construct the output string based on the order
	for (const auto& piece : order) {
        const auto it = pieceTypeToCode.find(piece);
        if (it != pieceTypeToCode.end())
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

std::string ShogiVariantBoard::CapturedPieceString()
{
	if (_capturedPieces.empty())
	{
		return "-";
	}
	// The pieces are always listed in the order rook, bishop, gold, silver, knight, lance, pawn
	const std::string wstr = formatEnumCounts(GetCapturedPieces(White));
	std::string bstr = formatEnumCounts(GetCapturedPieces(Black));
	std::ranges::transform(bstr, bstr.begin(), [](const char v) { return static_cast<char>(std::tolower(v)); });
	return wstr + bstr;
}

bool ShogiVariantBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	if (GetData(oldX, oldY) != std::nullopt)
	{
        PieceColour pieceColour = GetData(oldX, oldY)->Colour;
        PieceType pt = GetData(newX, newY) != std::nullopt && GetData(newX, newY)->Colour != GetData(oldX, oldY)->Colour ? GetData(newX, newY)->BaseType : None;
		const bool result = Board::Move(oldX, oldY, newX, newY, cl);
        if (result && pt != None && pt != Porpoise)
		{
			_capturedPieces.emplace_back(pieceColour, pt);
		}
        else if (result && pt == Porpoise)
        {
            _capturedPieces.emplace_back(pieceColour, DragonKing);
        }
        return result;
	}
	return false;
}
