#include "AmazonChessBoard.h"

AmazonChessBoard::AmazonChessBoard()
{
	_width = 8;
	_height = 8;
	AmazonChessBoard::Initialize();
}

AmazonChessBoard::~AmazonChessBoard()
{
}

Board* AmazonChessBoard::Clone()
{
	AmazonChessBoard* cb = new AmazonChessBoard();
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

void AmazonChessBoard::Initialize()
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
void AmazonChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case Queen:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		break;
	default:
		ChessBoard::GetMoves(piece, x, y);
		break;
	}
}
