#include "DaiDaiShogiBoard.h"

DaiDaiShogiBoard::DaiDaiShogiBoard()
{
	_width = 17;
	_height = 17;
	DaiDaiShogiBoard::Initialize();
}

DaiDaiShogiBoard::~DaiDaiShogiBoard()
{
}

void DaiDaiShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new DaiDaiShogiPiece(_initialSetup[j][i], j < 8 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* DaiDaiShogiBoard::Clone()
{
	DaiDaiShogiBoard* cb = new DaiDaiShogiBoard();
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

Piece* DaiDaiShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new DaiDaiShogiPiece(pieceType, pieceColour);
}

void DaiDaiShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Tile:
		break;
	case Earth:
		break;
	default:
		DaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
