#include "CrazyHouseBoard.h"

CrazyHouseBoard::CrazyHouseBoard()
{
	_width = 8;
	_height = 8;
	CrazyHouseBoard::Initialize();
}

CrazyHouseBoard::~CrazyHouseBoard()
{
}

Board* CrazyHouseBoard::Clone()
{
	CrazyHouseBoard* cb = new CrazyHouseBoard();
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
	cb->SetCapturedPieces(_capturedPieces);
	return cb;
}

void CrazyHouseBoard::Initialize()
{
	ChessBoard::Initialize();
	ClearCapturedPieces();
}

bool CrazyHouseBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	const std::optional<Piece> mover = GetData(oldX, oldY);
	if (mover == std::nullopt) return false;
	const std::optional<Piece> victim = GetData(newX, newY);
	PieceType captured = victim != std::nullopt && victim->Colour != mover->Colour ? victim->BaseType : None;
	if (captured == None && mover->Type == Pawn && oldX != newX && victim == std::nullopt)
	{
		captured = Pawn;
	}
	const bool result = ChessBoard::Move(oldX, oldY, newX, newY, cl);
	if (result && captured != None)
	{
		_capturedPieces.emplace_back(mover->Colour, captured);
	}
	return result;
}
