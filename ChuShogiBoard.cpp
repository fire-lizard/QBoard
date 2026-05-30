#include "ChuShogiBoard.h"

ChuShogiBoard::ChuShogiBoard()
{
	_width = 12;
	_height = 12;
	ChuShogiBoard::Initialize();
}

ChuShogiBoard::~ChuShogiBoard()
{
}

void ChuShogiBoard::Initialize()
{
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

Board* ChuShogiBoard::Clone()
{
	ChuShogiBoard *cb = new ChuShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

void ChuShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (_data[x][y] != std::nullopt)
    {
		_data[x][y]->IsPromoted = true;
        PieceType pieceType = None;
        switch (_data[x][y]->Type)
        {
        case DragonKing:
            pieceType = Eagle;
            break;
        case DragonHorse:
            pieceType = Unicorn;
            break;
        case Rook:
            pieceType = DragonKing;
            break;
        case Bishop:
            pieceType = DragonHorse;
            break;
        case VerticalMover:
            pieceType = FlyingOx;
            break;
        case SideMover:
            pieceType = FreeBoar;
            break;
        case ReverseChariot:
            pieceType = Whale;
            break;
        case Lance:
            pieceType = WhiteHorse;
            break;
        case Kylin:
            pieceType = Lion;
            break;
        case Phoenix:
            pieceType = Queen;
            break;
        case Elephant:
            pieceType = Prince;
            break;
        case Tiger:
            pieceType = FlyingStag;
            break;
        case Gold:
            pieceType = Rook;
            break;
        case Silver:
            pieceType = VerticalMover;
            break;
        case Copper:
            pieceType = SideMover;
            break;
        case Leopard:
            pieceType = Bishop;
            break;
        case GoBetween:
            pieceType = Elephant;
            break;
        case Pawn:
            pieceType = Tokin;
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

bool ChuShogiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	// Lion capture rule #2
	const std::optional<Piece> ap = GetData(oldX, oldY);
	const std::optional<Piece> dp = GetData(newX, newY);
	if (_wasLionCapturedByNonLion)
	{
        if (ap != std::nullopt && ap->Type != Lion && dp != std::nullopt && dp->Type == Lion)
		{
			return false;
		}
	}
    _wasLionCapturedByNonLion = ap != std::nullopt && ap->Type != Lion && dp != std::nullopt && dp->Type == Lion;
	return Board::Move(oldX, oldY, newX, newY, cl);
}

void ChuShogiBoard::CheckNullMove(int x, int y)
{
	if (IsMovePossible(x + 1, y + 1) || IsMovePossible(x + 1, y) || IsMovePossible(x + 1, y - 1) || IsMovePossible(x, y + 1) ||
		IsMovePossible(x, y - 1) || IsMovePossible(x - 1, y + 1) || IsMovePossible(x - 1, y) || IsMovePossible(x - 1, y - 1))
	{
		_moves.emplace_back(x, y);
	}
}

void ChuShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
	{
	case King:
	case Prince:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	case Lion:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);

		CheckNullMove(x, y);

		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x - 1, y + 2);

		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x - 2, y - 2);
		break;
	case Queen:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case DragonKing:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case DragonHorse:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Rook:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case Bishop:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case VerticalMover:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		break;
	case SideMover:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		break;
	case ReverseChariot:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		break;
	case Lance:
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, North);
		}
		else
		{
			CheckDirection(piece, x, y, South);
		}
		break;
	case Kylin:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);

		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y);
		break;
	case Phoenix:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);

		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y - 2);
		break;
	case Elephant:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case Tiger:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y - 1);
		}
		else
		{
			CheckMove(piece, x, y + 1);
		}
		break;
	case Gold:
	case Tokin:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
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
	case Silver:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case Copper:
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
	case Leopard:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case GoBetween:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		break;
	case Pawn:
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case Eagle:
		_moves.emplace_back(x, y);

		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, West);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 2, y + 2);
			CheckMove(piece, x - 2, y + 2);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		else
		{
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 2, y - 2);
			CheckMove(piece, x - 2, y - 2);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		break;
	case Unicorn:
		_moves.emplace_back(x, y);

		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x, y + 2);
			CheckDirection(piece, x, y, South);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x, y - 2);
			CheckDirection(piece, x, y, North);
		}
		break;
	case FlyingOx:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case FreeBoar:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case FlyingStag:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		break;
	case WhiteHorse:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, NorthWest);
		}
		else
		{
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		break;
	case Whale:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		else
		{
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, NorthWest);
		}
		break;
	default:
		break;
	}
}

bool ChuShogiBoard::DoubleMove(int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (x1 == x3 && y1 == y3 || std::any_of(_moves.begin(), _moves.end(), [=](std::pair<int, int> t) {return t.first == x3 && t.second == y3;}))
	{
		// Lion capture rule #1
        if ((abs(x1 - x3) == 2 || abs(y1 - y3) == 2) && GetData(x3, y3) != std::nullopt && GetData(x3, y3)->Type == Lion)
		{
			const std::vector<std::pair<int, int>> lionDefenders = GetDefenders(x3, y3);
			if (!lionDefenders.empty())
			{
                if (GetData(x2, y2) == std::nullopt || GetData(x2, y2)->Type != Pawn && GetData(x2, y2)->Type != GoBetween)
				{
					return false;
				}
			}
		}
		if (GetData(x2, y2) != std::nullopt)
		{
			SetData(x2, y2, std::nullopt);
		}
		if (x1 != x3 || y1 != y3)
		{
			SetData(x3, y3, GetData(x1, y1));
			SetData(x1, y1, std::nullopt);
		}
		return true;
	}
	return false;
}
