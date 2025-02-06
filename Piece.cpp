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

void Piece::SetPromoted(bool isPromoted)
{
	_isPromoted = isPromoted;
}

std::string Piece::GetImageFileName() const
{
	const std::string colour = _pieceColour == White ? "White" : "Black";
	const std::string promo = _isPromoted ? "Promo" : "";
	switch (_pieceType)
	{
	case King:
	case Prince:
		return colour + "King.png";
	case Lion:
		return colour + "Lion.png";
	case Queen:
		return colour + "Queen.png";
	case DragonKing:
		return colour + promo + "CrownedRook.png";
	case DragonHorse:
		return colour + promo + "CrownedBishop.png";
	case Rook:
		return colour + promo + "Rook.png";
	case Bishop:
		return colour + promo + "Bishop.png";
	case VerticalMover:
		return colour + promo + "Sword.png";
	case SideMover:
		return colour + promo + "HSword.png";
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
		return colour + "Commoner.png";
	case AngryBoar:
		return colour + "LShield.png";
	case ViolentOx:
		return colour + "Gnu.png";
	case FlyingDragon:
		return colour + "Dragon.png";
	case EvilWolf:
		return colour + "Wolf.png";
	case CatSword:
		return colour + "RShield.png";
	default:
		return "";
	}
}

std::string Piece::PieceType2Description(PieceType pieceType)
{
	switch (pieceType)
	{
	case None: return "None";
	case King: return "King";
	case Lion: return "Lion";
	case Queen: return "Queen";
	case DragonKing: return "Dragon King";
	case DragonHorse: return "Dragon Horse";
	case Rook: return "Rook";
	case Bishop: return "Bishop";
	case Knight: return "Knight";
	case VerticalMover: return "Vertical Mover";
	case SideMover: return "Side Mover";
	case Cannon: return "Cannon";
	case Lance: return "Lance";
	case Kylin: return "Kylin";
	case Phoenix: return "Phoenix";
	case Elephant: return "Elephant";
	case Prince: return "Prince";
	case Tiger: return "Tiger";
	case Gold: return "Gold";
	case Silver: return "Silver";
	case Copper: return "Copper";
	case Leopard: return "Leopard";
	case GoBetween: return "Go Between";
	case Pawn: return "Pawn";
	case Eagle: return "Eagle";
	case Unicorn: return "Unicorn";
	case FlyingOx: return "Flying Ox";
	case FreeBoar: return "Free Boar";
	case FlyingStag: return "Flying Stag";
	case WhiteHorse: return "White Horse";
	case Whale: return "Whale";
	case PromotedLance: return "Promoted Lance";
	case PromotedKnight: return "Promoted Knight";
	case PromotedSilver: return "Promoted Silver";
	case Tokin: return "Tokin";
	case ViolentOx: return "Violent Ox";
	case FlyingDragon: return "Flying Dragon";
	case AngryBoar: return "Angry Boar";
	case CatSword: return "Cat Sword";
	case EvilWolf: return "Evil Wolf";
	case Iron: return "Iron";
	case Stone: return "Stone";
	case Dog: return "Dog";
	case ViceGeneral: return "Vice General";
	case GreatGeneral: return "Great General";
	case BishopGeneral: return "Bishop General";
	case RookGeneral: return "Rook General";
	case MultiGeneral: return "Multi General";
	case FreeEagle: return "Free Eagle";
	case LionHawk: return "Lion Hawk";
	case SideSoldier: return "Side Soldier";
	case VerticalSoldier: return "Vertical Soldier";
	case ChariotSoldier: return "Chariot Soldier";
	case WaterBuffalo: return "Water Buffalo";
	case HeavenlyTetrarch: return "Heavenly Tetrarch";
	case FireDemon: return "Fire Demon";
	default: return "";
	}
}

PieceType Piece::Description2PieceType(const std::string& description)
{
	if (description == "None")              return None;
	if (description == "King")              return King;
	if (description == "Lion")              return Lion;
	if (description == "Queen")             return Queen;
	if (description == "Dragon King")       return DragonKing;
	if (description == "Dragon Horse")      return DragonHorse;
	if (description == "Rook")              return Rook;
	if (description == "Bishop")            return Bishop;
	if (description == "Knight")            return Knight;
	if (description == "Vertical Mover")    return VerticalMover;
	if (description == "Side Mover")        return SideMover;
	if (description == "Cannon")            return Cannon;
	if (description == "Lance")             return Lance;
	if (description == "Kylin")             return Kylin;
	if (description == "Phoenix")           return Phoenix;
	if (description == "Elephant")          return Elephant;
	if (description == "Prince")            return Prince;
	if (description == "Tiger")             return Tiger;
	if (description == "Gold")              return Gold;
	if (description == "Silver")            return Silver;
	if (description == "Copper")            return Copper;
	if (description == "Leopard")           return Leopard;
	if (description == "Go Between")        return GoBetween;
	if (description == "Pawn")              return Pawn;
	if (description == "Eagle")             return Eagle;
	if (description == "Unicorn")           return Unicorn;
	if (description == "Flying Ox")         return FlyingOx;
	if (description == "Free Boar")         return FreeBoar;
	if (description == "Flying Stag")       return FlyingStag;
	if (description == "White Horse")       return WhiteHorse;
	if (description == "Whale")             return Whale;
	if (description == "Promoted Lance")    return PromotedLance;
	if (description == "Promoted Knight")   return PromotedKnight;
	if (description == "Promoted Silver")   return PromotedSilver;
	if (description == "Tokin")             return Tokin;
	if (description == "Violent Ox")        return ViolentOx;
	if (description == "Flying Dragon")     return FlyingDragon;
	if (description == "Angry Boar")        return AngryBoar;
	if (description == "Cat Sword")         return CatSword;
	if (description == "Evil Wolf")         return EvilWolf;
	if (description == "Iron")              return Iron;
	if (description == "Stone")             return Stone;
	if (description == "Dog")               return Dog;
	if (description == "Vice General")      return ViceGeneral;
	if (description == "Great General")     return GreatGeneral;
	if (description == "Bishop General")    return BishopGeneral;
	if (description == "Rook General")      return RookGeneral;
	if (description == "Multi General")     return MultiGeneral;
	if (description == "Free Eagle")        return FreeEagle;
	if (description == "Lion Hawk")         return LionHawk;
	if (description == "Side Soldier")      return SideSoldier;
	if (description == "Vertical Soldier")  return VerticalSoldier;
	if (description == "Chariot Soldier")   return ChariotSoldier;
	if (description == "Water Buffalo")     return WaterBuffalo;
	if (description == "Heavenly Tetrarch") return HeavenlyTetrarch;
	if (description == "Fire Demon")        return FireDemon;

	// Fallback for unrecognized description.
	return None;
}
