#include "AtomicChessBoard.h"

AtomicChessBoard::AtomicChessBoard()
{
	_width = 8;
	_height = 8;
	AtomicChessBoard::Initialize();
}

AtomicChessBoard::~AtomicChessBoard()
{
}

Board* AtomicChessBoard::Clone()
{
	AtomicChessBoard* cb = new AtomicChessBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const std::optional<Piece> p = GetData(i, j);
			cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
	cb->SetHalfMoveCount(_halfMoveCount);
	cb->SetCastling(GetCastling());
	cb->SetEnPassant(_ep);
	return cb;
}

void AtomicChessBoard::Initialize()
{
	_moveCount = 0;
	_halfMoveCount = 0;
	_pgn = "";
	_wkc = true;
	_wqc = true;
	_bkc = true;
	_bqc = true;
	_ep = "-";
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

bool AtomicChessBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	const PieceType destPieceType = GetData(newX, newY) != std::nullopt ? GetData(newX, newY)->Type : None;
	const bool result = ChessBoard::Move(oldX, oldY, newX, newY, cl);
	if (result && GetData(newX, newY) != std::nullopt)
	{
		_data[newX][newY]->HasMoved = true;
		if (destPieceType != None)
		{
			Explode(newX, newY);
		}
	}
	return result;
}

void AtomicChessBoard::Explode(int x, int y)
{
    constexpr int directions[8][2] =
    {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, // Right, Down, Left, Up
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // NW, NE, SW, SE
    };
    for (const auto direction : directions)
    {
        int i = x + direction[0];
        int j = y + direction[1];
        SetData(i, j, std::nullopt);
    }
}
