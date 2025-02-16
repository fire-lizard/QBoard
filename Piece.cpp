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
	case ReverseChariot:
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
	case ReverseChariot: return "ReverseChariot";
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
	case BlindMonkey:          return "Blind Monkey";
	case BlueDragon:           return "Blue Dragon";
	case Dove:                 return "Dove";
	case EasternBarbarian:     return "Eastern Barbarian";
	case WesternBarbarian:     return "Western Barbarian";
	case SouthernBarbarian:    return "Southern Barbarian";
	case NorthernBarbarian:    return "Northern Barbarian";
	case EnchantedBadger:      return "Enchanted Badger";
	case EnchantedFox:         return "Enchanted Fox";
	case FragrantElephant:     return "Fragrant Elephant";
	case FreeDemon:            return "Free Demon";
	case FreeDreamEater:       return "Free Dream Eater";
	case FuriousFiend:         return "Furious Fiend";
	case GoldenBird:           return "Golden Bird";
	case GreatElephant:        return "Great Elephant";
	case HowlingDog:           return "Howling Dog";
	case LeftGeneral:          return "Left General";
	case RightGeneral:         return "Right General";
	case Tengu:                return "Tengu";
	case NeighboringKing:      return "Neighboring King";
	case OldKite:              return "Old Kite";
	case PoisonousSnake:       return "Poisonous Snake";
	case PrancingStag:         return "Prancing Stag";
	case RacingChariot:        return "Racing Chariot";
	case RushingBird:          return "Rushing Bird";
	case SavageTiger:          return "Savage Tiger";
	case Yaksha:               return "Yaksha";
	case SquareMover:          return "Square Mover";
	case StandardBearer:       return "Standard Bearer";
	case ViolentBear:          return "Violent Bear";
	case WhiteElephant:        return "White Elephant";
	case WhiteTiger:           return "White Tiger";
	case Wood:                 return "Wood";
	case FlyingHorse:          return "Flying Horse";
	case GreatDragon:          return "Great Dragon";
	case MountainWitch:        return "Mountain Witch";
	case WizardStork:          return "Wizard Stork";
	case LionDog:              return "Lion Dog";
	case Deva:                 return "Deva";
	case DarkSpirit:           return "Dark Spirit";
	case Tile:                 return "Tile";
	case Earth:                return "Earth";
	case CoiledSerpent:        return "Coiled Serpent";
	case RecliningDragon:      return "Reclining Dragon";
	case ChineseCock:          return "Chinese Cock";
	case OldMonkey:            return "Old Monkey";
	case BlindBear:            return "Blind Bear";
	case Wrestler:             return "Wrestler";
	case Guardian:             return "Guardian";
	case BuddhistSpirit:        return "Buddhist Spirit";
	case OldRat:               return "OldRat";
	case Donkey:               return "Donkey";
	case Capricorn:            return "Capricorn";
	case HookMover:            return "Hook Mover";
	case SideFlier:            return "Side Flier";
	case LeftChariot:          return "Left Chariot";
	case RightChariot:         return "Right Chariot";
	case Emperor:              return "Emperor";
	case TeachingKing:         return "Teaching King";
	case FreeGold:             return "Free Gold";
	case FreeSilver:           return "Free Silver";
	case FreeCopper:           return "Free Copper";
	case FreeIron:             return "Free Iron";
	case FreeTile:             return "Free Tile";
	case FreeStone:            return "Free Stone";
	case FreeEarth:            return "Free Earth";
	case FreeGo:               return "Free Go";
	case FreeTiger:            return "Free Tiger";
	case FreeLeopard:          return "Free Leopard";
	case FreeSerpent:          return "Free Serpent";
	case FreeDragon:           return "Free Dragon";
	case FreeWolf:             return "Free Wolf";
	case FreeCat:              return "Free Cat";
	case FreeBear:             return "Free Bear";
	case Bat:                  return "Bat";
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
	if (description == "ReverseChariot")    return ReverseChariot;
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
	if (description == "Blind Monkey")       return BlindMonkey;
	if (description == "Blue Dragon")		return BlueDragon;
	if (description == "Dove")				return Dove;
	if (description == "Eastern Barbarian")  return EasternBarbarian;
	if (description == "Western Barbarian")  return WesternBarbarian;
	if (description == "Southern Barbarian") return SouthernBarbarian;
	if (description == "Northern Barbarian") return NorthernBarbarian;
	if (description == "Enchanted Badger")   return EnchantedBadger;
	if (description == "Enchanted Fox")      return EnchantedFox;
	if (description == "Fragrant Elephant")  return FragrantElephant;
	if (description == "Free Demon")         return FreeDemon;
	if (description == "Free Dream Eater")    return FreeDreamEater;
	if (description == "Furious Fiend")      return FuriousFiend;
	if (description == "Golden Bird")        return GoldenBird;
	if (description == "Great Elephant")     return GreatElephant;
	if (description == "Howling Dog")        return HowlingDog;
	if (description == "Left General")       return LeftGeneral;
	if (description == "Right General")      return RightGeneral;
	if (description == "Tengu")             return Tengu;
	if (description == "Neighboring King")   return NeighboringKing;
	if (description == "Old Kite")           return OldKite;
	if (description == "Poisonous Snake")    return PoisonousSnake;
	if (description == "Prancing Stag")      return PrancingStag;
	if (description == "Racing Chariot")     return RacingChariot;
	if (description == "Rushing Bird")       return RushingBird;
	if (description == "Savage Tiger")       return SavageTiger;
	if (description == "Yaksha")            return Yaksha;
	if (description == "Square Mover")       return SquareMover;
	if (description == "Standard Bearer")    return StandardBearer;
	if (description == "Violent Bear")       return ViolentBear;
	if (description == "White Elephant")     return WhiteElephant;
	if (description == "White Tiger")        return WhiteTiger;
	if (description == "Wood")              return Wood;
	if (description == "Flying Horse")       return FlyingHorse;
	if (description == "Great Dragon")       return GreatDragon;
	if (description == "Mountain Witch")     return MountainWitch;
	if (description == "Wizard Stork")       return WizardStork;
	if (description == "Lion Dog")           return LionDog;
	if (description == "Deva")              return Deva;
	if (description == "Dark Spirit")        return DarkSpirit;
	if (description == "Tile")              return Tile;
	if (description == "Earth")             return Earth;
	if (description == "Coiled Serpent")     return CoiledSerpent;
	if (description == "Reclining Dragon")   return RecliningDragon;
	if (description == "Chinese Cock")       return ChineseCock;
	if (description == "Old Monkey")         return OldMonkey;
	if (description == "Blind Bear")         return BlindBear;
	if (description == "Wrestler")          return Wrestler;
	if (description == "Guardian")          return Guardian;
	if (description == "Buddhist Spirit")     return BuddhistSpirit;
	if (description == "Old Rat")            return OldRat;
	if (description == "Donkey")            return Donkey;
	if (description == "Capricorn")         return Capricorn;
	if (description == "Hook Mover")         return HookMover;
	if (description == "Side Flier")         return SideFlier;
	if (description == "Left Chariot")       return LeftChariot;
	if (description == "Right Chariot")      return RightChariot;
	if (description == "Emperor")           return Emperor;
	if (description == "Teaching King")      return TeachingKing;
	if (description == "Free Gold")          return FreeGold;
	if (description == "Free Silver")        return FreeSilver;
	if (description == "Free Copper")        return FreeCopper;
	if (description == "Free Iron")          return FreeIron;
	if (description == "Free Tile")          return FreeTile;
	if (description == "Free Stone")         return FreeStone;
	if (description == "Free Earth")         return FreeEarth;
	if (description == "Free Go")            return FreeGo;
	if (description == "Free Tiger")         return FreeTiger;
	if (description == "Free Leopard")       return FreeLeopard;
	if (description == "Free Serpent")       return FreeSerpent;
	if (description == "Free Dragon")        return FreeDragon;
	if (description == "Free Wolf")          return FreeWolf;
	if (description == "Free Cat")           return FreeCat;
	if (description == "Free Bear")          return FreeBear;
	if (description == "Bat")               return Bat;

	// Fallback for unrecognized description.
	return None;
}
