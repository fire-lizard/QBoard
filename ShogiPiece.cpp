#include "ShogiPiece.h"

ShogiPiece::ShogiPiece(PieceType pieceType, PieceColour pieceColour) : ChuShogiPiece(pieceType, pieceColour)
{
}

ShogiPiece::~ShogiPiece()
{
}

void ShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case Rook:
		_pieceType = DragonKing;
		break;
	case Bishop:
		_pieceType = DragonHorse;
		break;
	case Elephant:
		_pieceType = King;
		break;
	case Lance:
	case Silver:
	case WhiteHorse:
	case Pawn:
		_pieceType = Gold;
		break;
	default:
		break;
	}
}

std::string ShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case DragonKing:
		return "D";
	case DragonHorse:
		return "H";
	case Rook:
		return "R";
	case Bishop:
		return "B";
	case Lance:
		return "L";
	case Silver:
		return "S";
	case Gold:
		return "G";
	case WhiteHorse:
		return "N";
	case Pawn:
		return "P";
	case Elephant:
		return "E";
	default:
		return "";
	}
}


std::string ShogiPiece::LongStringCode() const
{
	switch (_pieceType)
	{
	case Rook:
		return "Rook";
	case Bishop:
		return "Bishop";
	case Lance:
		return "Lance";
	case Silver:
		return "Silver";
	case Gold:
		return "Gold";
	case WhiteHorse:
		return "Knight";
	case Pawn:
		return "Pawn";
	default:
		return "";
	}
}

PieceType ShogiPiece::LongStringCode2PieceType(const std::string& longStringCode)
{
	if (longStringCode == "Rook") return Rook;
	if (longStringCode == "Bishop") return Bishop;
	if (longStringCode == "Lance") return Lance;
	if (longStringCode == "Silver") return Silver;
	if (longStringCode == "Gold") return Gold;
	if (longStringCode == "Knight") return WhiteHorse;
	if (longStringCode == "Pawn") return Pawn;
	return None;
}

std::string ShogiPiece::AsianStringCode()
{
	switch (_pieceType)
	{
	case King:
		return _basePieceType == Elephant ? "太" : _pieceColour == Black ? "王" : "玉";
	case DragonKing:
		return "竜";
	case DragonHorse:
		return "馬";
	case Rook:
		return "飛";
	case Bishop:
		return "角";
	case Lance:
		return "香";
	case Silver:
		return "銀";
	case Gold:
		switch (_basePieceType)
		{
		case Lance:
			return "杏";
		case Silver:
			return "全";
		case WhiteHorse:
			return "圭";
		case Pawn:
			return "と";
		default:
			return "金";
		}
	case WhiteHorse:
		return "桂";
	case Pawn:
		return "歩";
	case Elephant:
		return "酔";
	default:
		return "";
	}
}

std::string ShogiPiece::GetJapaneseImageFileName()
{
	std::string imageFileName = GetImageFileName();
	if (_isPromoted)
	{
		const std::string colour = _pieceColour == White ? "White" : "Black";
		if (_pieceType == Gold)
		{
			constexpr PieceType pieces[] = { Pawn, WhiteHorse, Lance, Silver };

			if (std::find(std::begin(pieces), std::end(pieces), _basePieceType) != std::end(pieces))
			{
				switch (_basePieceType)
				{
				case WhiteHorse:
					imageFileName = colour + "GoldKnight.png";
					break;
				case Lance:
					imageFileName = colour + "GoldLance.png";
					break;
				case Silver:
					imageFileName = colour + "GoldSilver.png";
					break;
				case Pawn:
					imageFileName = colour + "Tokin.png";
					break;
				}
			}
		}
		else if (_pieceType == King)
		{
			imageFileName = colour + "King.png";
		}
	}
	return imageFileName;
}
