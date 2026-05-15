#include "TenjikuShogiPiece.h"

TenjikuShogiPiece::TenjikuShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

TenjikuShogiPiece::~TenjikuShogiPiece()
{
}

void TenjikuShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case BishopGeneral:
		_pieceType = ViceGeneral;
		break;
	case RookGeneral:
		_pieceType = GreatGeneral;
		break;
	case Dog:
		_pieceType = MultiGeneral;
		break;
	case SideSoldier:
		_pieceType = WaterBuffalo;
		break;
	case VerticalSoldier:
		_pieceType = ChariotSoldier;
		break;
	case ChariotSoldier:
		_pieceType = HeavenlyTetrarch;
		break;
	case WaterBuffalo:
		_pieceType = FireDemon;
		break;
	case Queen:
		_pieceType = FreeEagle;
		break;
	case Iron:
		_pieceType = VerticalSoldier;
		break;
	case Knight:
		_pieceType = SideSoldier;
		break;
	case Lion:
		_pieceType = LionHawk;
		break;
	case Unicorn:
		_pieceType = BishopGeneral;
		break;
	case Eagle:
		_pieceType = RookGeneral;
		break;
	default:
		DaiShogiPiece::Promote(pieceType);
		break;
	}
}
