#include "TaiShogiBoard.h"

TaiShogiBoard::TaiShogiBoard()
{
	_width = 25;
	_height = 25;
	TaiShogiBoard::Initialize();
}

TaiShogiBoard::~TaiShogiBoard()
{
}

Board* TaiShogiBoard::Clone()
{
	TaiShogiBoard* cb = new TaiShogiBoard();
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

void TaiShogiBoard::Initialize()
{
	_moveCount = 0;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
                SetData(i, j, Piece(_initialSetup[j][i], j < 12 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

void TaiShogiBoard::Promote(int x, int y, PieceType pt)
{
	if (GetData(x, y) != std::nullopt)
	{
		_data[x][y]->IsPromoted = true;
		PieceType pieceType = None;
		switch (_data[x][y]->Type)
		{
		case SideDragon:
			pieceType = Gold;
			break;
		default:
			DaiDaiShogiBoard::Promote(x, y, pt);
			break;
		}
		if (pieceType != None)
		{
			_data[x][y]->Type = pieceType;
		}
	}
}

void TaiShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
	{
    case RamsHeadSoldier:
		break;
	case GoldenDeer:
		break;
	case SilverHare:
		break;
	case VermillionSparrow:
		break;
	case TurtleSnake:
		break;
	case Soldier:
		break;
	case Peacock:
		break;
	case FierceEagle:
		break;
	case SideDragon:
		break;
	default:
		DaiDaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
