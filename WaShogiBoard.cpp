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
                SetData(i, j, Piece(_initialSetup[j][i], j < 5 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
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
			const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	for (const auto& capturedPiece : _capturedPieces)
	{
		cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

void WaShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (_data[x][y] != std::nullopt)
    {
		_data[x][y]->IsPromoted = true;
        PieceType pieceType = None;
        switch (_data[x][y]->Type)
        {
        case Lance:
            pieceType = PloddingOx;
            break;
        case Pawn:
            pieceType = Tokin;
            break;
        case SideMover:
            pieceType = Rook;
            break;
        case LiberatedHorse:
            pieceType = HeavenlyHorse;
            break;
        case SwoopingOwl:
            pieceType = CloudEagle;
            break;
        case StruttingCrow:
            pieceType = FlyingFalcon;
            break;
        case FlyingFalcon:
            pieceType = TenaciousFalcon;
            break;
        case FlyingCock:
            pieceType = RaidingFalcon;
            break;
        case FlyingGoose:
            pieceType = SideMover;
            break;
        case ClimbingMonkey:
            pieceType = Silver;
            break;
        case Silver:
            pieceType = Elephant;
            break;
        case Dog:
            pieceType = Gold;
            break;
        case Gold:
            pieceType = BearEyes;
            break;
        case RunningRabbit:
            pieceType = TreacherousFox;
            break;
        default:
            break;
        }
        if (pieceType != None)
        {
			_data[x][y]->Type = pieceType;
        }
    }
}

void WaShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
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
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
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
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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
	case RaidingFalcon:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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

std::string WaShogiBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    PieceType basePieceType = GetData(x, y)->BaseType;
    switch (pieceType)
    {
    case King:
        return "K";
    case Rook:
        return "+S";
    case Lance:
        return "O";
    case Tokin:
        return "+P";
    case Pawn:
        return "P";
    case SideMover:
        return basePieceType == FlyingGoose ? "+G" : "S";
    case PloddingOx:
        return "+O";
    case LiberatedHorse:
        return "H";
    case HeavenlyHorse:
        return "+H";
    case SwoopingOwl:
        return "L";
    case CloudEagle:
        return basePieceType == SwoopingOwl ? "+L" : "E";
    case StruttingCrow:
        return "U";
    case FlyingFalcon:
        return basePieceType == StruttingCrow ? "+U" : "F";
    case FlyingCock:
        return "C";
    case RaidingFalcon:
        return "+C";
    case FlyingGoose:
        return "G";
    case ClimbingMonkey:
        return "M";
    case Silver:
        return basePieceType == ClimbingMonkey ? "+M" : "V";
    case Dog:
        return "D";
    case Gold:
        return basePieceType == Dog ? "+D" : "W";
    case Elephant:
        return "+V";
    case BearEyes:
        return "+W";
    case RunningRabbit:
        return "R";
    case TreacherousFox:
        return basePieceType == RunningRabbit ? "+R" : "X";
    case TenaciousFalcon:
        return "+F";
    default:
        return "";
    }
}
