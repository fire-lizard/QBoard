#include "MakaDaiDaiShogiBoard.h"

MakaDaiDaiShogiBoard::MakaDaiDaiShogiBoard()
{
	_width = 19;
	_height = 19;
	MakaDaiDaiShogiBoard::Initialize();
}

MakaDaiDaiShogiBoard::~MakaDaiDaiShogiBoard()
{
}

void MakaDaiDaiShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new MakaDaiDaiShogiPiece(_initialSetup[j][i], j < 8 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* MakaDaiDaiShogiBoard::Clone()
{
	MakaDaiDaiShogiBoard* cb = new MakaDaiDaiShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

Piece* MakaDaiDaiShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new MakaDaiDaiShogiPiece(pieceType, pieceColour);
}

void MakaDaiDaiShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Deva:
		if (piece->GetColour() == White)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x + 1, y - 1);
		}
		CheckMove(piece, x - 1, y);
		break;
	case DarkSpirit:
		if (piece->GetColour() == White)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y - 1);
		}
		CheckMove(piece, x + 1, y);
		break;
	default:
		DaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
