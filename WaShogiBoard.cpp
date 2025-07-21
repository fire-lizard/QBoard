#include "WaShogiBoard.h"

WaShogiBoard::WaShogiBoard()
{
	_hasDrops = true;
	_width = 11;
	_height = 11;
	WaShogiBoard::Initialize();
}

WaShogiBoard::~WaShogiBoard()
{
}

void WaShogiBoard::Initialize()
{
	_moveCount = 0;
	_capturedPieces.clear();
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new WaShogiPiece(_initialSetup[j][i], j < 5 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* WaShogiBoard::Clone()
{
	WaShogiBoard* cb = new WaShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	for (const auto& capturedPiece : _capturedPieces)
	{
		cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

Piece* WaShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new WaShogiPiece(pieceType, pieceColour);
}

void WaShogiBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
	_data[x][y] = new WaShogiPiece(pieceType, pieceColour);
}

std::string WaShogiBoard::formatEnumCounts(const std::vector<PieceType>& enumList)
{
    const std::vector<PieceType> order = { Rook, SideMover, Gold, Silver, LiberatedHorse, Lance, Pawn, SwoopingOwl, CloudEagle, StruttingCrow, FlyingFalcon,
								FlyingCock, FlyingGoose, ClimbingMonkey, Dog, RunningRabbit, TreacherousFox };

	// Count occurrences of each piece
	std::unordered_map<PieceType, int> counts;
	for (const auto& piece : enumList)
	{
		counts[piece]++;
	}

	std::ostringstream result;

	for (const auto& piece : order) {
		if (counts[piece] > 1) {
			result << counts[piece] << WaShogiPiece::ToStringCode(piece); // Add count + first letter
		}
		else if (counts[piece] == 1) {
			result << WaShogiPiece::ToStringCode(piece); // Add just the first letter
		}
	}

	return result.str();
}

void WaShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case PloddingOx:
	case BearEyes:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	case SideMover:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		break;
	case LiberatedHorse:
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, South, 2);
			CheckMove(piece, x, y - 1);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, North, 2);
		}
		break;
	case HeavenlyHorse:
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x + 1, y - 2);
		break;
	case SwoopingOwl:
	case StruttingCrow:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case CloudEagle:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckMove(piece, x - 1, y - 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y + 1);
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, NorthWest, 3);
			CheckDirection(piece, x, y, NorthEast, 3);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest, 3);
			CheckDirection(piece, x, y, SouthEast, 3);
		}
		break;
	case FlyingFalcon:
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 1);
		}
		else
		{
			CheckMove(piece, x, y + 1);
		}
		break;
	case FlyingCock:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		break;
	case RaidingFalcon:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		break;
	case FlyingGoose:
	case ClimbingMonkey:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case Dog:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case RunningRabbit:
		CheckMove(piece, x - 1, y - 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x + 1, y + 1);
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckMove(piece, x, y - 1);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckMove(piece, x, y + 1);
		}
		break;
	case TreacherousFox:
		CheckMove(piece, x - 1, y - 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 2, y - 2);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x, y + 2);
		break;
	case TenaciousFalcon:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		break;
	default:
		ShogiBoard::GetMoves(piece, x, y);
		break;
	}
}

void WaShogiBoard::SetDrops(bool hasDrops)
{
	_hasDrops = hasDrops;
}

void WaShogiBoard::WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2, char promotion, bool capture)
{
	if (_moveCount % 2 == 0)
	{
		_pgn += std::to_string((_moveCount / 2) + 1) + ". "; // Add move number for white
	}
	if (pieceType != Pawn)
	{
		//_pgn += _pieceToPGN.at(pieceType);
	}
	_pgn.push_back(static_cast<char>(x1 + 97));
	_pgn += std::to_string(_height - y1);
	if (capture)
	{
		_pgn += "x";
	}
	_pgn.push_back(static_cast<char>(x2 + 97));
	_pgn += std::to_string(y2);
	if (promotion != ' ')
	{
		_pgn += "=";
		_pgn += static_cast<char>(std::toupper(promotion));
	}
	_pgn += " ";
	_moveCount++;
}

std::string WaShogiBoard::GetPGN()
{
	return _pgn;
}
