#include "DaiShogiPiece.h"

DaiShogiPiece::DaiShogiPiece(PieceType pieceType, PieceColour pieceColour) : ChuShogiPiece(pieceType, pieceColour)
{
}

DaiShogiPiece::~DaiShogiPiece()
{
}

void DaiShogiPiece::Promote(PieceType pieceType)
{
	IsPromoted = true;
	switch (_pieceType)
	{
	case Iron:
	case Stone:
	case AngryBoar:
	case ViolentOx:
	case FlyingDragon:
	case EvilWolf:
	case CatSword:
	case Knight:
		_pieceType = Gold;
		break;
	default:
		ChuShogiPiece::Promote(pieceType);
		break;
	}
}
