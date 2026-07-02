#include "MusketeerChessBoard.h"

MusketeerChessBoard::MusketeerChessBoard()
{
	_width = 8;
	_height = 10;
	MusketeerChessBoard::Initialize();
}

MusketeerChessBoard::~MusketeerChessBoard()
{
}

Board* MusketeerChessBoard::Clone()
{
	MusketeerChessBoard* cb = new MusketeerChessBoard();
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

void MusketeerChessBoard::Initialize()
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

bool MusketeerChessBoard::EnemyPawnsAround(int x, int y) const
{
	const std::optional<Piece> fp = x > 0 ? GetData(x - 1, y) : std::nullopt;
	const std::optional<Piece> sp = x < _width - 1 ? GetData(x + 1, y) : std::nullopt;
	const PieceColour pieceColour = y == 4 ? White : Black;
	const bool fpa = (fp != std::nullopt) && (fp->Type == Pawn) && (fp->Colour == pieceColour);
	const bool spa = (sp != std::nullopt) && (sp->Type == Pawn) && (sp->Colour == pieceColour);
	return fpa || spa;
}

void MusketeerChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case King:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		// Check castling
		if (!piece->HasMoved)
		{
			if (GetData(0, y) != std::nullopt)
			{
				const std::optional<Piece> cp = GetData(0, y);
				if (!cp->HasMoved && cp->Type == Rook && GetData(1, y) == std::nullopt && GetData(2, y) == std::nullopt && GetData(3, y) == std::nullopt)
				{
					if ((piece->Colour == White && _wqc == true) || (piece->Colour == Black && _bqc == true))
					{
						_moves.emplace_back(0, y);
					}
				}
			}
			if (GetData(_width - 1, y) != std::nullopt)
			{
				const std::optional<Piece> cp = GetData(_width - 1, y);
				if (!cp->HasMoved && cp->Type == Rook && GetData(5, y) == std::nullopt && GetData(6, y) == std::nullopt)
				{
					if ((piece->Colour == White && _wkc == true) || (piece->Colour == Black && _bkc == true))
					{
						_moves.emplace_back(_width - 1, y);
					}
				}
			}
		}
		break;
	case Leopard:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		CheckDirection(piece, x, y, NorthEast, 2);
		CheckDirection(piece, x, y, SouthEast, 2);
		CheckDirection(piece, x, y, SouthWest, 2);
		CheckDirection(piece, x, y, NorthWest, 2);
		break;
	case Cannon:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);

		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		break;
	case Unicorn:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);

		CheckMove(piece, x + 1, y + 3);
		CheckMove(piece, x - 1, y + 3);
		CheckMove(piece, x + 3, y + 1);
		CheckMove(piece, x + 3, y - 1);
		CheckMove(piece, x - 3, y + 1);
		CheckMove(piece, x - 3, y - 1);
		CheckMove(piece, x + 1, y - 3);
		CheckMove(piece, x - 1, y - 3);
		break;
	case FlyingDragon:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Elephant:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);

		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 2);
		break;
	case Eagle:
		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 2);

		CheckMove(piece, x + 3, y + 3);
		CheckMove(piece, x + 3, y);
		CheckMove(piece, x + 3, y - 3);
		CheckMove(piece, x, y + 3);
		CheckMove(piece, x, y - 3);
		CheckMove(piece, x - 3, y + 3);
		CheckMove(piece, x - 3, y);
		CheckMove(piece, x - 3, y - 3);
		break;
	case Fortress:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y);
		CheckDirection(piece, x, y, NorthEast, 3);
		CheckDirection(piece, x, y, SouthEast, 3);
		CheckDirection(piece, x, y, SouthWest, 3);
		CheckDirection(piece, x, y, NorthWest, 3);
		break;
	case Spider:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckDirection(piece, x, y, NorthEast, 2);
		CheckDirection(piece, x, y, SouthEast, 2);
		CheckDirection(piece, x, y, SouthWest, 2);
		CheckDirection(piece, x, y, NorthWest, 2);
		break;
	case Pawn:
		if (piece->Colour == Black)
		{
			if (y == 2 && GetData(x, y + 1) == std::nullopt && GetData(x, y + 2) == std::nullopt)
			{
				CheckMove(piece, x, y + 2);
			}
			if (y + 1 < _height && GetData(x, y + 1) == std::nullopt)
			{
				CheckMove(piece, x, y + 1);
			}
			if (y + 1 < _height && x + 1 < _width && GetData(x + 1, y + 1) != std::nullopt)
			{
				CheckMove(piece, x + 1, y + 1);
			}
			if (y + 1 < _height && x - 1 >= 0 && GetData(x - 1, y + 1) != std::nullopt)
			{
				CheckMove(piece, x - 1, y + 1);
			}
			// En passant
			if (_ep != "-")
			{
				const int letter = _ep[0] - 97;
				const int number = _ep[1] - 48;
				if (abs(x - letter) == 1 && y == number + 1)
				{
					CheckMove(piece, letter, number + 2);
				}
			}
		}
		else
		{
			if (y == _height - 3 && GetData(x, y - 1) == std::nullopt && GetData(x, y - 2) == std::nullopt)
			{
				CheckMove(piece, x, y - 2);
			}
			if (y - 1 >= 0 && GetData(x, y - 1) == std::nullopt)
			{
				CheckMove(piece, x, y - 1);
			}
			if (y - 1 >= 0 && x + 1 < _width && GetData(x + 1, y - 1) != std::nullopt)
			{
				CheckMove(piece, x + 1, y - 1);
			}
			if (y - 1 >= 0 && x - 1 >= 0 && GetData(x - 1, y - 1) != std::nullopt)
			{
				CheckMove(piece, x - 1, y - 1);
			}
			// En passant
			if (_ep != "-")
			{
				const int letter = _ep[0] - 97;
				const int number = _ep[1] - 48;
				if (abs(x - letter) == 1 && y == number)
				{
					CheckMove(piece, letter, number - 1);
				}
			}
		}
		break;
	default:
		CapablancaChessBoard::GetMoves(piece, x, y);
		break;
	}
	auto moves_to_remove =
		std::ranges::remove_if(_moves, [](const auto& m) { return m.second == 0 || m.second == 9; });
	_moves.erase(moves_to_remove.begin(), moves_to_remove.end());
}

bool MusketeerChessBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	const PieceType pieceType = GetData(oldX, oldY)->Type;
	const PieceColour pieceColour = GetData(oldX, oldY)->Colour;
	const PieceType destPieceType = GetData(newX, newY) != std::nullopt ? GetData(newX, newY)->Type : None;
	const bool result = CapablancaChessBoard::Move(oldX, oldY, newX, newY, cl);
	if (result && GetData(newX, newY) != std::nullopt)
	{
		_data[newX][newY]->HasMoved = true;
		// Castling
		if (pieceType == Rook)
		{
			if (oldX == 0 && oldY == _height - 2)
			{
				_wqc = false;
			}
			else if (oldX == _width - 1 && oldY == _height - 2)
			{
				_wkc = false;
			}
			else if (oldX == 0 && oldY == 1)
			{
				_bqc = false;
			}
			else if (oldX == _width - 1 && oldY == 1)
			{
				_bkc = false;
			}
		}
		else if (pieceType == King)
		{
			if (pieceColour == White)
			{
				_wqc = false;
				_wkc = false;
			}
			else
			{
				_bqc = false;
				_bkc = false;
			}
		}
		if (destPieceType == Rook)
		{
			if (newX == 0 && newY == _height - 2)
			{
				_wqc = false;
			}
			else if (newX == _width - 1 && newY == _height - 2)
			{
				_wkc = false;
			}
			else if (newX == 0 && newY == 1)
			{
				_bqc = false;
			}
			else if (newX == _width - 1 && newY == 1)
			{
				_bkc = false;
			}
		}
		// En passant
		if (pieceType == Pawn && abs(oldY - newY) == 2 && EnemyPawnsAround(newX, newY))
		{
			_ep = "";
			const char letter = newX + 97;
			_ep.push_back(letter);
			_ep.append(oldY == _height - 4 ? "7" : "4");
		}
		else if (pieceType == Pawn && _ep != "-")
		{
			const char letter = newX + 97;
			const int number = _ep[1] - 48;
			if (letter == _ep[0] && ((pieceColour == White && newY == number - 1) || (pieceColour == Black && newY == number + 2)))
			{
				const std::optional<Piece> p = pieceColour == White ? GetData(newX, number) : GetData(newX, number + 1);
				if (p != std::nullopt && p->Type == Pawn && p->Colour != pieceColour)
				{
					if (pieceColour == White)
					{
						SetData(newX, number, std::nullopt);
					}
					else
					{
						SetData(newX, number + 1, std::nullopt);
					}
				}
			}
			_ep = "-";
		}
		else
		{
			_ep = "-";
		}
		if (pieceType == Pawn || destPieceType != None)
		{
			_halfMoveCount = 0;
		}
		else
		{
			_halfMoveCount++;
		}
	}
	return result;
}

std::string MusketeerChessBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	PieceType pieceType = GetData(x, y)->Type;
	switch (pieceType)
	{
	case Leopard:
		return "L";
	case Cannon:
		return "C";
	case Unicorn:
		return "U";
	case FlyingDragon:
		return "D";
	case Chancellor:
		return "M";
	case Archbishop:
		return "A";
	case Elephant:
		return "E";
	case Eagle:
		return "H";
	case Fortress:
		return "F";
	case Spider:
		return "S";
	default:
		return CapablancaChessBoard::GetStringCode(x, y);
	}
}
