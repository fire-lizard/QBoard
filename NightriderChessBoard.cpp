#include "NightriderChessBoard.h"

NightriderChessBoard::NightriderChessBoard()
{
	_width = 8;
	_height = 8;
	NightriderChessBoard::Initialize();
}

NightriderChessBoard::~NightriderChessBoard()
{
}

Board* NightriderChessBoard::Clone()
{
	NightriderChessBoard* cb = new NightriderChessBoard();
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

void NightriderChessBoard::Initialize()
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

void NightriderChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case Nightrider:
		CheckKnightDirection(piece, x, y, North);
		CheckKnightDirection(piece, x, y, NorthEast);
		CheckKnightDirection(piece, x, y, East);
		CheckKnightDirection(piece, x, y, SouthEast);
		CheckKnightDirection(piece, x, y, South);
		CheckKnightDirection(piece, x, y, SouthWest);
		CheckKnightDirection(piece, x, y, West);
		CheckKnightDirection(piece, x, y, NorthWest);
		break;
	default:
		ChessBoard::GetMoves(piece, x, y);
		break;
	}
}

void NightriderChessBoard::CheckKnightDirection(const std::optional<Piece>& piece, int x, int y, Direction direction)
{
	while (CheckPosition(x, y))
	{
		CheckKnightDirectionInc(x, y, direction);
		CheckMove(piece, x, y);
		if (GetData(x, y) != std::nullopt)
		{
			break;
		}
	}
}

void NightriderChessBoard::CheckKnightDirectionInc(int& x, int& y, Direction direction)
{
	switch (direction)
	{
	case North:
		x++; y -= 2;
		break;
	case South:
		x--; y += 2;
		break;
	case East:
		x += 2; y++;
		break;
	case West:
		x -= 2; y--;
		break;
	case NorthWest:
		x--; y -= 2;
		break;
	case NorthEast:
		x += 2; y--;
		break;
	case SouthWest:
		x -= 2; y++;
		break;
	case SouthEast:
		x++; y += 2;
		break;
	}
}

std::string NightriderChessBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	PieceType pieceType = GetData(x, y)->Type;
	switch (pieceType)
	{
	case Nightrider:
		return "N";
	default:
		return ChessBoard::GetStringCode(x, y);
	}
}
