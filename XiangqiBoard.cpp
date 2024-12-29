#include "XiangqiBoard.h"
#include "XiangqiPiece.h"

XiangqiBoard::XiangqiBoard()
{
	_width = 9;
	_height = 10;
	_moveCount = 0;
	_wxf = "";
	XiangqiBoard::Initialize();
}

XiangqiBoard::~XiangqiBoard()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_data[i][j] != nullptr)
			{
				delete _data[i][j];
			}
		}
	}
}

Board* XiangqiBoard::Clone()
{
	XiangqiBoard *cb = new XiangqiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece *p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	return cb;
}

void XiangqiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new XiangqiPiece(_initialSetup[j][i], j < 5 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Piece* XiangqiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new XiangqiPiece(pieceType, pieceColour);
}

void XiangqiBoard::GetMoves(Piece *piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case King:
		if (x < 5)
			CheckMove(piece, x + 1, y);
        if ((piece->GetColour() == Black && y < 2) || piece->GetColour() == White)
			CheckMove(piece, x, y + 1);
        if ((piece->GetColour() == White && y > 7) || piece->GetColour() == Black)
			CheckMove(piece, x, y - 1);
		if (x > 3)
			CheckMove(piece, x - 1, y);
		break;
	case Silver:
        if ((x < 5 && (piece->GetColour() == Black && y < 2)) || piece->GetColour() == White)
			CheckMove(piece, x + 1, y + 1);
        if ((x < 5 && (piece->GetColour() == White && y > 7)) || piece->GetColour() == Black)
			CheckMove(piece, x + 1, y - 1);
        if ((x > 3 && (piece->GetColour() == Black && y < 2)) || piece->GetColour() == White)
			CheckMove(piece, x - 1, y + 1);
        if ((x > 3 && (piece->GetColour() == White && y > 7)) || piece->GetColour() == Black)
			CheckMove(piece, x - 1, y - 1);
		break;
	case Rook:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case Elephant:
        if ((piece->GetColour() == White && y > 5) || piece->GetColour() == Black)
			if (_data[x - 1][y - 1] == nullptr)
				CheckMove(piece, x - 2, y - 2);
        if ((piece->GetColour() == White && y > 5) || piece->GetColour() == Black)
			if (_data[x + 1][y - 1] == nullptr)
				CheckMove(piece, x + 2, y - 2);
        if ((piece->GetColour() == Black && y < 4) || piece->GetColour() == White)
			if (_data[x - 1][y + 1] == nullptr)
				CheckMove(piece, x - 2, y + 2);
        if ((piece->GetColour() == Black && y < 4) || piece->GetColour() == White)
			if (_data[x + 1][y + 1] == nullptr)
				CheckMove(piece, x + 2, y + 2);
		break;
	case Pawn:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
			if (y >= 5)
			{
				CheckMove(piece, x + 1, y);
				CheckMove(piece, x - 1, y);
			}
		}
		else
		{
			CheckMove(piece, x, y - 1);
			if (y <= 4)
			{
				CheckMove(piece, x + 1, y);
				CheckMove(piece, x - 1, y);
			}
		}
		break;
	case WhiteHorse:
		if (_data[x][y + 1] == nullptr)
		{
			CheckMove(piece, x + 1, y + 2);
			CheckMove(piece, x - 1, y + 2);
		}
		if (_data[x + 1][y] == nullptr)
		{
			CheckMove(piece, x + 2, y + 1);
			CheckMove(piece, x + 2, y - 1);
		}
		if (_data[x - 1][y] == nullptr)
		{
			CheckMove(piece, x - 2, y + 1);
			CheckMove(piece, x - 2, y - 1);
		}
		if (_data[x][y - 1] == nullptr)
		{
			CheckMove(piece, x + 1, y - 2);
			CheckMove(piece, x - 1, y - 2);
		}
		break;
	case Cannon:
		CheckCannonDirection(piece, x, y, North);
		CheckCannonDirection(piece, x, y, East);
		CheckCannonDirection(piece, x, y, West);
		CheckCannonDirection(piece, x, y, South);
		break;
	default:
		break;
	}
}

void XiangqiBoard::CheckCannonDirection(const Piece *piece, int x, int y, Direction direction)
{
	do
	{
		CheckDirectionInc(x, y, direction);
		if (_data[x][y] == nullptr)
			CheckMove(piece, x, y);
		else
		{
			do
			{
				CheckDirectionInc(x, y, direction);
			} 
			while (_data[x][y] == nullptr && CheckDirectionAux(x, y, direction));
			if (CheckPosition(x, y) && _data[x][y] != nullptr && _data[x][y]->GetColour() != piece->GetColour())
			{
				CheckMove(piece, x, y);
			}
			break;
		}
	}
	while (CheckDirectionAux(x, y, direction));
}


void XiangqiBoard::WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2)
{
	char direction = '.';
	if (_moveCount % 2 == 0)
	{
		_wxf += std::to_string((_moveCount / 2) + 1) + ". "; // Add move number for red
		_wxf += _pieceToWXF.at(pieceType);
		if (y1 > y2) direction = '+';
		else if (y1 < y2) direction = '-';
		_wxf += std::to_string(9 - x1);
		_wxf.push_back(direction);
		if (direction == '.' || x1 != x2)
		{
			_wxf += std::to_string(9 - x2);
		}
		else
		{
			_wxf += std::to_string(abs(y2 - y1));
		}
	}
	else
	{
		_wxf.push_back(static_cast<char>(std::tolower(_pieceToWXF.at(pieceType)[0])));
		if (y2 > y1) direction = '+';
		else if (y2 < y1) direction = '-';
		_wxf += std::to_string(x1 + 1);
		_wxf.push_back(direction);
		if (direction == '.' || x1 != x2)
		{
			_wxf += std::to_string(x2 + 1);
		}
		else
		{
			_wxf += std::to_string(abs(y2 - y1));
		}
	}
	_wxf += " ";
	_moveCount++;
}

std::string XiangqiBoard::GetWXF()
{
	return _wxf;
}