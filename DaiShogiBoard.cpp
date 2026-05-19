#include "DaiShogiBoard.h"

DaiShogiBoard::DaiShogiBoard()
{
	_width = 15;
	_height = 15;
	DaiShogiBoard::Initialize();
}

DaiShogiBoard::~DaiShogiBoard()
{
}

void DaiShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
                SetData(i, j, Piece(_initialSetup[j][i], j < 7 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

Board* DaiShogiBoard::Clone()
{
	DaiShogiBoard* cb = new DaiShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? cb->CreatePiece(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

void DaiShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (_data[x][y] != std::nullopt)
    {
		_data[x][y]->IsPromoted = true;
        PieceType pieceType = None;
        switch (_data[x][y]->Type)
        {
        case Iron:
        case Stone:
        case AngryBoar:
        case ViolentOx:
        case FlyingDragon:
        case EvilWolf:
        case CatSword:
        case Knight:
            pieceType = Gold;
            break;
        default:
            ChuShogiBoard::Promote(x, y, pt);
            break;
        }
        if (pieceType != None)
        {
			_data[x][y]->Type = pieceType;
        }
    }
}

void DaiShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
	{
	case Knight:
        if (piece->Colour == Black)
		{
			CheckMove(piece, x - 1, y + 2);
			CheckMove(piece, x + 1, y + 2);
		}
		else
		{
			CheckMove(piece, x - 1, y - 2);
			CheckMove(piece, x + 1, y - 2);
		}
		break;
	case ViolentOx:
		CheckDirection(piece, x, y, South, 2);
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
		break;
	case FlyingDragon:
		CheckDirection(piece, x, y, SouthWest, 2);
		CheckDirection(piece, x, y, NorthWest, 2);
		CheckDirection(piece, x, y, SouthEast, 2);
		CheckDirection(piece, x, y, NorthEast, 2);
		break;
	case AngryBoar:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		break;
	case CatSword:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case EvilWolf:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case Iron:
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case Stone:
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
	case WaterBuffalo:
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
		break;
	default:
		ChuShogiBoard::GetMoves(piece, x, y);
		break;
	}
}

void DaiShogiBoard::CheckLionDirection(const std::optional<Piece>& piece, int x, int y, Direction direction, int count)
{
	int i = 0;
	while (InBounds(x, y, direction) && i < count)
	{
		CheckDirectionInc(x, y, direction);
		CheckMove(piece, x, y);
        if (GetData(x, y) != std::nullopt && GetData(x, y)->Colour == piece->Colour)
		{
			break;
		}
		i++;
	}
}

std::vector<std::pair<int, int>> DaiShogiBoard::GetEnemyPiecesAround(int x, int y, PieceColour pieceColour) const
{
	std::vector<std::pair<int, int>> result;
	constexpr int directions[8][2] =
	{
		{0, 1}, {1, 0}, {0, -1}, {-1, 0}, // Right, Down, Left, Up
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1} // NW, NE, SW, SE
	};
	for (const auto direction : directions)
	{
		int i = x + direction[0];
		int j = y + direction[1];
        if (i < 0 || i > _width - 1 || j < 0 || j > _height - 1 || GetData(i, j) == std::nullopt || GetData(i, j)->Colour == pieceColour)
		{
			continue;
		}
        if (GetData(i, j)->Colour != pieceColour)
		{
			result.emplace_back(i, j);
		}
	}
	return result;
}
