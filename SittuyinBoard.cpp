#include "SittuyinBoard.h"

SittuyinBoard::SittuyinBoard()
{
	_width = 8;
	_height = 8;
	SittuyinBoard::Initialize();
}

SittuyinBoard::~SittuyinBoard()
{
}

Board* SittuyinBoard::Clone()
{
	SittuyinBoard* cb = new SittuyinBoard();
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

void SittuyinBoard::Initialize()
{
	_moveCount = 0;
	_pgn = "";
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				SetData(i, j, Piece(_initialSetup[j][i], j < 4 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
	_capturedPieces = {
		{White, Rook},
		{White, Rook},
		{Black, Rook},
		{Black, Rook},
		{White, Knight},
		{White, Knight},
		{Black, Knight},
		{Black, Knight},
		{White, Bishop},
		{White, Bishop},
		{Black, Bishop},
		{Black, Bishop},
		{White, Queen},
		{Black, Queen},
		{White, King},
		{Black, King}
	};
}

void SittuyinBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case Bishop:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case Pawn:
		ShatranjBoard::GetMoves(piece, x, y);
		// Promoting is a move of its own: the General either replaces the pawn where it stands or
		// appears one step diagonally away. Whether it may actually be played also depends on the
		// check it would give, which PromotionGivesCheck answers - the caller prunes those.
		if (IsPromotionMove(x, y, x, y))
		{
			_moves.emplace_back(x, y);
		}
		for (int dx = -1; dx <= 1; dx += 2)
		{
			for (int dy = -1; dy <= 1; dy += 2)
			{
				if (IsPromotionMove(x, y, x + dx, y + dy))
				{
					_moves.emplace_back(x + dx, y + dy);
				}
			}
		}
		break;
	default:
		ShatranjBoard::GetMoves(piece, x, y);
		break;
	}
}

// The promotion squares are the two long diagonals of the board, but only the half of each that
// lies in enemy territory: a8, b7, c6, d5, e5, f6, g7 and h8 for white, mirrored for black.
bool SittuyinBoard::IsPromotionSquare(int x, int y, PieceColour pieceColour) const
{
	if (x != y && x + y != _height - 1) return false;
	return pieceColour == White ? y < _height / 2 : y >= _height / 2;
}

// A promotion move stands still or steps one square diagonally onto an empty square, and it never
// captures. It is the square the pawn STANDS on that has to be a promotion square, not the one the
// General lands on - a pawn on d5 may put its General on e6 or c4 just as well. A side may never
// own two Generals, so its own General has to be gone first, and a side down to its last pawn may
// promote it wherever it stands.
bool SittuyinBoard::IsPromotionMove(int fromX, int fromY, int toX, int toY) const
{
	if (!CheckPosition(toX, toY)) return false;
	const std::optional<Piece> p = GetData(fromX, fromY);
	if (p == std::nullopt || p->Type != Pawn || HasPiece(Queen, p->Colour)) return false;
	const int dx = toX > fromX ? toX - fromX : fromX - toX;
	const int dy = toY > fromY ? toY - fromY : fromY - toY;
	if (dx != dy || dx > 1) return false;
	if (dx == 1 && GetData(toX, toY) != std::nullopt) return false;
	return IsPromotionSquare(fromX, fromY, p->Colour) || PawnCount(p->Colour) == 1;
}

int SittuyinBoard::PawnCount(PieceColour pieceColour) const
{
	int count = 0;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			const std::optional<Piece> p = GetData(i, j);
			if (p != std::nullopt && p->Type == Pawn && p->Colour == pieceColour) count++;
		}
	}
	return count;
}

// A promotion may not threaten anything. The new General may not end up next to an enemy piece -
// the four diagonal neighbours are exactly what a General attacks - and the move may not leave the
// opponent in check, not even by uncovering a line. Ordinary moves attack and check as they like;
// this restriction belongs to the promotion alone, and it is what an engine rejects a promotion for.
bool SittuyinBoard::PromotionThreatens(int fromX, int fromY, int toX, int toY)
{
	const std::optional<Piece> p = GetData(fromX, fromY);
	if (p == std::nullopt) return false;
	const PieceColour enemy = p->Colour == White ? Black : White;
	for (int dx = -1; dx <= 1; dx += 2)
	{
		for (int dy = -1; dy <= 1; dy += 2)
		{
			if (!CheckPosition(toX + dx, toY + dy)) continue;
			const std::optional<Piece> n = GetData(toX + dx, toY + dy);
			if (n != std::nullopt && n->Colour == enemy) return true;
		}
	}
	const std::pair<int, int> king = GetPieceLocation(King, enemy);
	if (king.first < 0) return false;
	Board* brd = Clone();
	brd->SetData(fromX, fromY, std::nullopt);
	brd->SetData(toX, toY, Piece(Queen, p->Colour));
	const bool check = brd->IsSquareUnderAttack(king.first, king.second, enemy);
	delete brd;
	return check;
}

std::string SittuyinBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	PieceType pieceType = GetData(x, y)->Type;
	switch (pieceType)
	{
	case Queen:
		return "F";
	case Bishop:
		return "S";
	default:
		return ShatranjBoard::GetStringCode(x, y);
	}
}
