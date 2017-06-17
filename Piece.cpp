#include "Piece.h"

Piece::Piece(PieceType pieceType, PieceColour pieceColour)
{
	_pieceType = pieceType;
	_pieceColour = pieceColour;
	_isPromoted = false;
}

Piece::~Piece()
{
	//dtor
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

string Piece::GetImageFileName(PieceType pieceType, PieceColour pieceColour)
{
	string colour = pieceColour == White ? "White" : "Black";
	switch (pieceType)
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
	case BlindTiger:
		return colour + "Claw.png";
	case Gold:
		return colour + "Gold.png";
	case Silver:
		return colour + "Advisor.png";
	case Copper:
		return colour + "Commoner.png";
	case FerociousLeopard:
		return colour + "Leopard.png";
	case Cobra:
		return colour + "Cobra.png";
	case Pawn:
		return colour + "Pawn.png";
	case Eagle:
		return colour + "Hawk.png";
	case Unicorn:
		return colour + "Unicorn.png";
	case NarrowQueen:
		return colour + "Princess.png";
	case SleepingQueen:
		return colour + "HCrown.png";
	case FlyingStag:
		return colour + "Chancellor.png";
	case WhiteHorse:
		return colour + "Knight.png";
	case Whale:
		return colour + "Dolphin.png";
	default:
		return "";
	}
}
