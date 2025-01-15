#include "TenjikuShogiBoard.h"

TenjikuShogiBoard::TenjikuShogiBoard()
{
	_width = 16;
	_height = 16;
	TenjikuShogiBoard::Initialize();
}

TenjikuShogiBoard::~TenjikuShogiBoard()
{
}

void TenjikuShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new TenjikuShogiPiece(_initialSetup[j][i], j < 7 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* TenjikuShogiBoard::Clone()
{
	TenjikuShogiBoard* cb = new TenjikuShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	return cb;
}

Piece* TenjikuShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new TenjikuShogiPiece(pieceType, pieceColour);
}

void TenjikuShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	/*case ViceGeneral:
		return "ViceGeneral" + colour + ".png";
	case GreatGeneral:
		return "GreatGeneral" + colour + ".png";
	case BishopGeneral:
		return promo + "BishopGeneral" + colour + ".png";
	case RookGeneral:
		return promo + "RookGeneral" + colour + ".png";
	case MultiGeneral:
		return "Multi-General" + colour + "2.png";*/
	case Dog:
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
	/*case FreeEagle:
		return "FreeEagle" + colour + ".png";
	case LionHawk:
		return "Lion-Hawk" + colour + ".png";
	case SideSoldier:
		return promo + "SideSoldier" + colour + ".png";
	case VerticalSoldier:
		return promo + "VerticalSoldier" + colour + ".png";
	case ChariotSoldier:
		return promo + "ChariotSoldier" + colour + ".png";
	case WaterBuffalo:
		return promo + "WaterBuffalo" + colour + ".png";
	case HeavenlyTetrarch:
		return "Heaven" + colour + ".png";
	case FireDemon:
		return "FireDemon" + colour + ".png";*/
	default:
		DaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
