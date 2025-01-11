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
				_data[i][j] = new DaiShogiPiece(_initialSetup[j][i], j < 7 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
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
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	return cb;
}

Piece* DaiShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new DaiShogiPiece(pieceType, pieceColour);
}

void DaiShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Knight:
		if (piece->GetColour() == Black)
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
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y);
		break;
	case FlyingDragon:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y - 2);
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
		if (piece->GetColour() == Black)
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
		if (piece->GetColour() == Black)
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
	default:
		ChuShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
