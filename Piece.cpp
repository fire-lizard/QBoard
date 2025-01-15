#include "Piece.h"

Piece::Piece(PieceType pieceType, PieceColour pieceColour)
{
	_basePieceType = pieceType;
	_pieceType = pieceType;
	_pieceColour = pieceColour;
	_isPromoted = false;
}

Piece::~Piece()
{
}

PieceType Piece::GetBaseType() const
{
	return _basePieceType;
}

PieceType Piece::GetType() const
{
	return _pieceType;
}

PieceColour Piece::GetColour() const
{
	return _pieceColour;
}

bool Piece::IsPromoted() const
{
	return _isPromoted;
}

std::string Piece::GetImageFileName() const
{
	const std::string colour = _pieceColour == White ? "White" : "Black";
	switch (_pieceType)
	{
	case King:
		return colour + "King.png";
	case Lion:
		return colour + "Lion.png";
	case Queen:
		return colour + "Queen.png";
	case DragonKing:
		return colour + "CrownedRook.png";
	case DragonHorse:
		return colour + "CrownedBishop.png";
	case Rook:
		return colour + "Rook.png";
	case Bishop:
		return colour + "Bishop.png";
	case VerticalMover:
		return colour + "Sword.png";
	case SideMover:
		return colour + "HSword.png";
	case Cannon:
		return colour + "Canon.png";
	case Lance:
		return colour + "Lance.png";
	case Kylin:
		return colour + "Marshall.png";
	case Phoenix:
		return colour + "Archbishop.png";
	case Elephant:
		return colour + "Elephant.png";
	case Tiger:
		return colour + "Claw.png";
	case Gold:
		return colour + "Gold.png";
	case Tokin:
		return colour + "GoldPawn.png";
	case PromotedLance:
		return colour + "GoldLance.png";
	case PromotedKnight:
		return colour + "GoldKnight.png";
	case PromotedSilver:
		return colour + "GoldSilver.png";
	case Silver:
		return colour + "Advisor.png";
	case Copper:
		return colour + "Copper.png";
	case Leopard:
		return colour + "Leopard.png";
	case GoBetween:
		return colour + "Cobra.png";
	case Pawn:
		return colour + "Pawn.png";
	case Eagle:
		return colour + "Hawk.png";
	case Unicorn:
		return colour + "Unicorn.png";
	case FlyingOx:
		return colour + "Princess.png";
	case FreeBoar:
		return colour + "HCrown.png";
	case FlyingStag:
		return colour + "Chancellor.png";
	case Knight:
	case WhiteHorse:
		return colour + "Knight.png";
	case Whale:
		return colour + "Dolphin.png";
	case Iron:
		return colour + "Iron.png";
	case Stone:
		return colour + "Tower.png";
	case AngryBoar:
		return colour + "PromoHSword.png";
	case ViolentOx:
		return colour + "Gnu.png";
	case FlyingDragon:
		return colour + "Dragon.png";
	case EvilWolf:
		return colour + "Wolf.png";
	case CatSword:
		return colour + "PromoSword.png";
	default:
		return "";
	}
}
