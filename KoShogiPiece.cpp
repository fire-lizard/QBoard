#include "KoShogiPiece.h"

KoShogiPiece::KoShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

KoShogiPiece::~KoShogiPiece()
{
}

void KoShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	default:
		DaiShogiPiece::Promote(pieceType);
		break;
	}
}

std::string KoShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	default:
		return DaiShogiPiece::StringCode();
	}
}

PieceType KoShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : DaiShogiPiece::FromStringCode(code);
}

std::string KoShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	default:
		return DaiShogiPiece::KanjiStringCode();
	}
}

std::string KoShogiPiece::GetKanjiImageFileName()
{
	std::string colour = _pieceColour == White ? "" : "Flip";
	if (_isPromoted && _pieceType != King)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	default:
		return DaiShogiPiece::GetKanjiImageFileName();
	}
}

std::string KoShogiPiece::PieceType2Description(PieceType pieceType)
{
	switch (pieceType)
	{
	case MiddleTroop:          return "MiddleTroop";
	case Drum:                 return "Drum";
	case Thunderclap:          return "Thunderclap";
	case Banner:               return "Banner";
	case FlagWaver:            return "FlagWaver";
	case VillageBrigade:       return "VillageBrigade";
	case ViceCommander:        return "ViceCommander";
	case PoisonFlame:          return "PoisonFlame";
	case SumoWrestler:         return "SumoWrestler";
	case DoubleKylin:          return "DoubleKylin";
	case DoublePhoenix:        return "DoublePhoenix";
	case TaoistPriest:         return "TaoistPriest";
	case SpiritualMonk:        return "SpiritualMonk";
	case FiveLiFog:            return "FiveLiFog";
	case ImmaculateLight:      return "ImmaculateLight";
	case AdvanceGuard:         return "AdvanceGuard";
	case RearGuard:            return "RearGuard";
	case SkywardNet:           return "SkywardNet";
	case EarthwardNet:         return "EarthwardNet";
	case DragonAscending:      return "DragonAscending";
	case Quartermaster:        return "Quartermaster";
	case TigerWing:            return "TigerWing";
	case WarHawk:              return "WarHawk";
	case Longbow:              return "Longbow";
	case LongbowCavalryman:    return "LongbowCavalryman";
	case Crossbow:             return "Crossbow";
	case CrossbowCavalryman:   return "CrossbowCavalryman";
	case Cannon:               return "Cannon";
	case GunCarriage:          return "GunCarriage";
	case FrankishCannon:       return "FrankishCannon";
	case ChariotOfTheGods:     return "ChariotOfTheGods";
	case Cavalry:              return "Cavalry";
	case WingedHorse:          return "WingedHorse";
	case ShieldUnit:           return "ShieldUnit";
	case Chariot:              return "Chariot";
	case Vanguard:             return "Vanguard";
	default: return "";
	}
}

PieceType KoShogiPiece::Description2PieceType(const std::string& description)
{
	if (description == "MiddleTroop")        return MiddleTroop;
	if (description == "Drum")               return Drum;
	if (description == "Thunderclap")        return Thunderclap;
	if (description == "Banner")             return Banner;
	if (description == "FlagWaver")          return FlagWaver;
	if (description == "VillageBrigade")     return VillageBrigade;
	if (description == "ViceCommander")      return ViceCommander;
	if (description == "PoisonFlame")        return PoisonFlame;
	if (description == "SumoWrestler")       return SumoWrestler;
	if (description == "DoubleKylin")        return DoubleKylin;
	if (description == "DoublePhoenix")      return DoublePhoenix;
	if (description == "TaoistPriest")       return TaoistPriest;
	if (description == "SpiritualMonk")      return SpiritualMonk;
	if (description == "FiveLiFog")          return FiveLiFog;
	if (description == "ImmaculateLight")    return ImmaculateLight;
	if (description == "AdvanceGuard")       return AdvanceGuard;
	if (description == "RearGuard")          return RearGuard;
	if (description == "SkywardNet")         return SkywardNet;
	if (description == "EarthwardNet")       return EarthwardNet;
	if (description == "DragonAscending")    return DragonAscending;
	if (description == "Quartermaster")      return Quartermaster;
	if (description == "TigerWing")          return TigerWing;
	if (description == "WarHawk")            return WarHawk;
	if (description == "Longbow")            return Longbow;
	if (description == "LongbowCavalryman")  return LongbowCavalryman;
	if (description == "Crossbow")           return Crossbow;
	if (description == "CrossbowCavalryman") return CrossbowCavalryman;
	if (description == "Cannon")             return Cannon;
	if (description == "GunCarriage")        return GunCarriage;
	if (description == "FrankishCannon")     return FrankishCannon;
	if (description == "ChariotOfTheGods")   return ChariotOfTheGods;
	if (description == "Cavalry")            return Cavalry;
	if (description == "WingedHorse")        return WingedHorse;
	if (description == "ShieldUnit")         return ShieldUnit;
	if (description == "Chariot")            return Chariot;
	if (description == "Vanguard")           return Vanguard;

	return None;
}
