#include "XiangqiBoard.h"

XiangqiBoard::XiangqiBoard()
{
	_width = 9;
	_height = 10;
	XiangqiBoard::Initialize();
}

XiangqiBoard::~XiangqiBoard()
{
}

Board* XiangqiBoard::Clone()
{
	XiangqiBoard *cb = new XiangqiBoard();
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

void XiangqiBoard::Initialize()
{
	_moveCount = 0;
	_wxf = "";
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

void XiangqiBoard::Promote(int x, int y, PieceType pt)
{
}

void XiangqiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
	{
	case King:
		if (x < 5)
			CheckMove(piece, x + 1, y);
        if ((piece->Colour == Black && y < 2) || piece->Colour == White)
			CheckMove(piece, x, y + 1);
        if ((piece->Colour == White && y > 7) || piece->Colour == Black)
			CheckMove(piece, x, y - 1);
		if (x > 3)
			CheckMove(piece, x - 1, y);
		break;
	case Silver:
        if (x < 5 && (piece->Colour == Black && y < 2 || piece->Colour == White))
			CheckMove(piece, x + 1, y + 1);
        if (x < 5 && (piece->Colour == White && y > 7 || piece->Colour == Black))
			CheckMove(piece, x + 1, y - 1);
        if (x > 3 && (piece->Colour == Black && y < 2 || piece->Colour == White))
			CheckMove(piece, x - 1, y + 1);
        if (x > 3 && (piece->Colour == White && y > 7 || piece->Colour == Black))
            CheckMove(piece, x - 1, y - 1);
        break;
	case Rook:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case Elephant:
        if ((piece->Colour == White && y > 5) || piece->Colour == Black)
		{
			if (GetData(x - 1, y - 1) == std::nullopt)
				CheckMove(piece, x - 2, y - 2);
			if (GetData(x + 1, y - 1) == std::nullopt)
				CheckMove(piece, x + 2, y - 2);
		}
        if ((piece->Colour == Black && y < 4) || piece->Colour == White)
		{
			if (GetData(x - 1, y + 1) == std::nullopt)
				CheckMove(piece, x - 2, y + 2);
			if (GetData(x + 1, y + 1) == std::nullopt)
				CheckMove(piece, x + 2, y + 2);
		}
		break;
	case Pawn:
        if (piece->Colour == Black)
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
	case Knight:
		if (GetData(x, y + 1) == std::nullopt)
		{
			CheckMove(piece, x + 1, y + 2);
			CheckMove(piece, x - 1, y + 2);
		}
		if (GetData(x + 1, y) == std::nullopt)
		{
			CheckMove(piece, x + 2, y + 1);
			CheckMove(piece, x + 2, y - 1);
		}
		if (GetData(x - 1, y) == std::nullopt)
		{
			CheckMove(piece, x - 2, y + 1);
			CheckMove(piece, x - 2, y - 1);
		}
		if (GetData(x, y - 1) == std::nullopt)
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

void XiangqiBoard::CheckCannonDirection(const std::optional<Piece>& piece, int x, int y, Direction direction)
{
	do
	{
		CheckDirectionInc(x, y, direction);
		if (GetData(x, y) == std::nullopt)
        {
			CheckMove(piece, x, y);
        }
		else
		{
			do
			{
				CheckDirectionInc(x, y, direction);
			} 
			while (GetData(x, y) == std::nullopt && InBounds(x, y, direction));
            if (CheckPosition(x, y) && GetData(x, y) != std::nullopt && GetData(x, y)->Colour != piece->Colour)
			{
				CheckMove(piece, x, y);
			}
			break;
		}
	}
	while (InBounds(x, y, direction));
}

bool XiangqiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	for (int& _pieceFile : _pieceFiles) _pieceFile = -1;
    const PieceColour pieceColour = GetData(oldX, oldY)->Colour;
    const PieceType pieceType = GetData(oldX, oldY)->Type;
	int pieceCount = 0;
	for (int index = 0; index < _height; index++)
	{
		const std::optional<Piece> p = GetData(oldX, index);
        if (p != std::nullopt && p->Colour == pieceColour && p->Type == pieceType)
		{
			_pieceFiles[pieceCount] = index;
			pieceCount++;
		}
	}
	return Board::Move(oldX, oldY, newX, newY, cl);
}

void XiangqiBoard::WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2)
{
	char direction = '.';
	if (_moveCount % 2 == 0)
	{
		_wxf += std::to_string((_moveCount / 2) + 1) + ". "; // Add move number for red
		// single-letter piece abbreviation
		_wxf += _pieceToWXF.at(pieceType);
		// former file
		if (_pieceFiles[1] != -1 && _pieceFiles[2] == -1)
		{
			_wxf += y1 < _pieceFiles[1] ? "+" : "-";
		}
		else if (_pieceFiles[1] != -1 && _pieceFiles[2] != -1)
		{
			for (int index = 0; index < 5; index++) 
			{
				if (_pieceFiles[index] == y1) 
				{
					_wxf += std::to_string(index + 1);
					break;
				}
			}
		}
		else
		{
			_wxf += std::to_string(_width - x1);
		}
		// operator indicating direction of movement
		if (y1 > y2) direction = '+';
		else if (y1 < y2) direction = '-';
		_wxf.push_back(direction);
		// new file, or in the case of purely vertical movement, number of ranks traversed
		if (direction == '.' || x1 != x2)
		{
			_wxf += std::to_string(_width - x2);
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
		if (_pieceFiles[1] != -1 && _pieceFiles[2] == -1)
		{
			_wxf += y1 >= _pieceFiles[1] ? "+" : "-";
		}
		else if (_pieceFiles[1] != -1 && _pieceFiles[2] != -1)
		{
			for (int index = 0; index < 5; index++)
			{
				if (_pieceFiles[index] == y1)
				{
					_wxf += std::to_string(5 - index);
					break;
				}
			}
		}
		else
		{
			_wxf += std::to_string(x1 + 1);
		}
		_wxf.push_back(direction);
		if (direction == '.' || x1 != x2)
		{
			_wxf += std::to_string(x2 + 1);
		}
		else
		{
			_wxf += std::to_string(abs(y2 - y1));
		}
		if (_moveCount > 0 && _moveCount % 3 == 0)
		{
			_wxf.push_back('\n');
		}
	}
	_wxf += " ";
	_moveCount++;
}

std::string XiangqiBoard::GetWXF()
{
	return _wxf;
}

bool XiangqiBoard::AreTwoKingsLookingOnEachOther() const
{
    const auto loc1 = GetPieceLocation(King, Black);
    const auto loc2 = GetPieceLocation(King, White);
    if (loc1.first == loc2.first)
    {
        int step = loc1.second > loc2.second ? -1 : 1;
        for (int index = loc1.second + step; index != loc2.second; index += step)
        {
            if (GetData(loc1.first, index) != std::nullopt)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

std::string XiangqiBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    switch (pieceType)
    {
    case King:
        return "K";
    case Silver:
        return "A";
    case Rook:
        return "R";
    case Cannon:
        return "C";
    case Knight:
        return "H";
    case Elephant:
        return "E";
    case Pawn:
        return "P";
    default:
        return "";
    }
}
