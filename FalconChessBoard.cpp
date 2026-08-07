#include "FalconChessBoard.h"

FalconChessBoard::FalconChessBoard()
{
	_width = 10;
	_height = 8;
	FalconChessBoard::Initialize();
}

FalconChessBoard::~FalconChessBoard()
{
}

Board* FalconChessBoard::Clone()
{
	FalconChessBoard* cb = new FalconChessBoard();
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

void FalconChessBoard::Initialize()
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

// One of the Falcon's sixteen destinations. It is not a leaper: it has to walk one of the three
// shortest King paths there, and only when all three are blocked is the destination out of reach.
// Every path is three King steps, the long axis stepping each time and the short axis stepping on
// as many of the three as it has ground to cover - so the three differ only in which step is the
// odd one out. Only the two squares walked through have to be empty; the destination itself is an
// ordinary move-or-capture. A path never leaves the board if its destination is on it, which is
// why the bounds check up front is the only one needed.
void FalconChessBoard::CheckFalconMove(const std::optional<Piece>& piece, int x, int y, int dx, int dy)
{
	if (!CheckPosition(x + dx, y + dy)) return;
	const bool longIsX = abs(dx) == 3;
	const int shortSteps = longIsX ? abs(dy) : abs(dx);
	const int sx = dx > 0 ? 1 : -1;
	const int sy = dy > 0 ? 1 : -1;
	for (int odd = 0; odd < 3; odd++)
	{
		int cx = x, cy = y;
		bool clear = true;
		for (int i = 0; i < 2 && clear; i++)
		{
			const bool shortStep = shortSteps == 1 ? i == odd : i != odd;
			cx += longIsX || shortStep ? sx : 0;
			cy += longIsX ? (shortStep ? sy : 0) : sy;
			clear = GetData(cx, cy) == std::nullopt;
		}
		if (clear)
		{
			CheckMove(piece, x + dx, y + dy);
			return;
		}
	}
}

void FalconChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case Falcon:
		// Every square three King steps away that no Rook, Bishop or Knight reaches in one.
		for (const auto& [dx, dy] : { std::pair(1, 3), std::pair(3, 1), std::pair(2, 3), std::pair(3, 2) })
		{
			CheckFalconMove(piece, x, y,  dx,  dy);
			CheckFalconMove(piece, x, y,  dx, -dy);
			CheckFalconMove(piece, x, y, -dx,  dy);
			CheckFalconMove(piece, x, y, -dx, -dy);
		}
		break;
	default:
		CapablancaChessBoard::GetMoves(piece, x, y);
		break;
	}
}

std::string FalconChessBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	return GetData(x, y)->Type == Falcon ? "F" : CapablancaChessBoard::GetStringCode(x, y);
}
