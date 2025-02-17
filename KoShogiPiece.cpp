﻿#include "KoShogiPiece.h"

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
	case Kylin:
		_pieceType = DoubleKylin;
		break;
	case Phoenix:
		_pieceType = DoublePhoenix;
		break;
	case Elephant:
		_pieceType = DragonKing;
		break;
	case Gold:
		_pieceType = FlyingStag;
		break;
	case Silver:
		_pieceType = CompanyCommander;
		break;
	case Leopard:
		_pieceType = ViceCommissioner;
		break;
	case Copper:
		_pieceType = PoisonFlame;
		break;
	case TaoistPriest:
		_pieceType = ExtensiveFog;
		break;
	case SpiritualMonk:
		_pieceType = HolyLight;
		break;
	case AdvanceGuard:
		_pieceType = SkywardNet;
		break;
	case MiddleTroop:
		_pieceType = Prince;
		break;
	case Drum:
		_pieceType = Thunderclap;
		break;
	case Flag:
		_pieceType = RoamingAssault;
		break;
	case Tiger:
		_pieceType = DragonHorse;
		break;
	case Queen:
		_pieceType = RisingDragon;
		break;
	case DragonKing:
		_pieceType = WingedTiger;
		break;
	case DragonHorse:
		_pieceType = FlyingHawk;
		break;
	case RearGuard:
		_pieceType = EarthwardNet;
		break;
	case FrankishCannon:
		_pieceType = DivineCarriage;
		break;
	case Longbow:
		_pieceType = LongbowKnight;
		break;
	case Crossbow:
		_pieceType = CrossbowKnight;
		break;
	case Cannon:
		_pieceType = CannonCarriage;
		break;
	case Knight:
		_pieceType = KnightCaptain;
		break;
	case Pawn:
		_pieceType = VerticalMover;
		break;
	case CatSword:
		_pieceType = ShieldCaptain;
		break;
	case ShieldCaptain:
		_pieceType = FreeBoar;
		break;
	case Chariot:
		_pieceType = Rook;
		break;
	case Rook:
		_pieceType = Queen;
		break;
	case VerticalMover:
	case Vanguard:
		_pieceType = FlyingOx;
		break;
	case Wrestler:
		_isPromoted = false;
		break;
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
	std::string colour = _pieceColour == White ? "F" : "";
	if (_isPromoted && _pieceType != King)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	case Rook:
		return "ChariotCaptain" + colour + ".png";
	case VerticalMover:
		return "PawnCaptain" + colour + ".png";
	case Knight:
		return "Knight" + colour + ".png";
	case FrankishCannon:
		return "EuropeanCannon" + colour + ".png";
	case Copper:
		return "MilitaryEngineer" + colour + ".png";
	case Queen:
		return "Chiliarch" + colour + ".png";
	case Leopard:
		return "MilitaryOfficer" + colour + ".png";
	case DragonKing:
		return "Optio" + colour + ".png";
	case Elephant:
		return "Guard" + colour + ".png";
	case SkywardNet:
		return "SkyNet" + colour + ".png";
	case EarthwardNet:
		return "EarthNet" + colour + ".png";
	case FlyingStag:
		return "BattalionCommander" + colour + ".png";
	case DoubleKylin:
		return "Strategist" + colour + ".png";
	case DoublePhoenix:
		return "Flag-Drum" + colour + ".png";
	case FlyingOx:
		return "MilitaryCommissioner" + colour + ".png";
	case FreeBoar:
		return "ImperialBase" + colour + ".png";
	case Prince:
		return "Marshal" + colour + ".png";
	default:
		std::string desc = PieceType2Description(_pieceType);
		replaceSubstring(desc, " ", "");
		return desc + colour + ".png";
	}
}

std::string KoShogiPiece::PieceType2Description(PieceType pieceType)
{
	switch (pieceType)
	{
	case King:           return "General";
	case Prince:         return "Governor";
	case Queen:          return "Millenary";
	case Rook:           return "Chariot Unit";
	case Bishop:         return "Elephant";
	case Gold:           return "Aide";
	case Silver:         return "Staff";
	case Copper:         return "Engineer";
	case FlyingOx:       return "Commissar";
	case FreeBoar:       return "Heavenly Fortress";
	case VerticalMover:  return "Patrol Unit";
	case DragonHorse:    return "Centuria";
	case DragonKing:     return "Quartermaster";
	case CatSword:       return "Shield";
	case Leopard:        return "Chief of Staff";
	case FlyingStag:     return "Town Brigade";
	case Tiger:          return "Sentry";
	case Elephant:       return "Aide de Camp";
	case Phoenix:        return "Staff Officer";
	case Kylin:          return "Clerk";
	case Knight:         return "Cavalryman";
	case Pawn:           return "Pawn";
	case MiddleTroop:          return "Middle Troop";
	case Drum:                 return "Drum";
	case Thunderclap:          return "Thunderclap";
	case Flag:               return "Flag";
	case RoamingAssault:            return "Roaming Assault";
	case CompanyCommander:       return "Company Commander";
	case ViceCommissioner:        return "Vice Commissioner";
	case PoisonFlame:          return "Poison Flame";
	case Wrestler:             return "Wrestler";
	case DoubleKylin:          return "Master at Arms";
	case DoublePhoenix:        return "Flag and Drum";
	case TaoistPriest:         return "Taoist Priest";
	case SpiritualMonk:        return "Spiritual Monk";
	case ExtensiveFog:            return "Extensive Fog";
	case HolyLight:      return "Holy Light";
	case AdvanceGuard:         return "Advance Guard";
	case RearGuard:            return "Rear Guard";
	case SkywardNet:           return "Skyward Net";
	case EarthwardNet:         return "Earthward Net";
	case RisingDragon:      return "Rising Dragon";
	case Quartermaster:        return "Quartermaster";
	case WingedTiger:            return "Winged Tiger";
	case FlyingHawk:              return "Flying Hawk";
	case Longbow:              return "Longbow";
	case LongbowKnight:    return "Longbow Knight";
	case Crossbow:             return "Crossbow";
	case CrossbowKnight:   return "Crossbow Knight";
	case Cannon:               return "Cannon";
	case CannonCarriage:          return "Cannon Carriage";
	case FrankishCannon:       return "Frankish Cannon";
	case DivineCarriage:     return "Divine Carriage";
	case KnightCaptain:              return "Knight Captain";
	case WingedHorse:          return "Winged Horse";
	case ShieldCaptain:           return "Shield Captain";
	case Chariot:              return "Chariot";
	case Vanguard:             return "Vanguard";
	default: return "";
	}
}

PieceType KoShogiPiece::Description2PieceType(const std::string& description)
{
	if (description == "General")       return King;
	if (description == "Governor")      return Prince;
	if (description == "Millenary")     return Queen;
	if (description == "Chariot Unit")  return Rook;
	if (description == "Elephant")      return Bishop;
	if (description == "Aide")          return Gold;
	if (description == "Staff")         return Silver;
	if (description == "Engineer")      return Copper;
	if (description == "Commissar")     return FlyingOx;
	if (description == "Heavenly Fortress") return FreeBoar;
	if (description == "Patrol Unit")   return VerticalMover;
	if (description == "Centuria")      return DragonHorse;
	if (description == "Quartermaster") return DragonKing;
	if (description == "Shield")        return CatSword;
	if (description == "Chief of Staff")return Leopard;
	if (description == "Town Brigade")  return FlyingStag;
	if (description == "Sentry")        return Tiger;
	if (description == "Aide de Camp")  return Elephant;
	if (description == "Staff Officer") return Phoenix;
	if (description == "Clerk")         return Kylin;
	if (description == "Cavalryman")    return Knight;
	if (description == "Pawn")			return Pawn;
	if (description == "Middle Troop")        return MiddleTroop;
	if (description == "Drum")               return Drum;
	if (description == "Thunderclap")        return Thunderclap;
	if (description == "Flag")             return Flag;
	if (description == "Roaming Assault")          return RoamingAssault;
	if (description == "Company Commander")     return CompanyCommander;
	if (description == "Vice Commissioner")      return ViceCommissioner;
	if (description == "Poison Flame")        return PoisonFlame;
	if (description == "Wrestler")			  return Wrestler;
	if (description == "Master at Arms")        return DoubleKylin;
	if (description == "Flag and Drum")      return DoublePhoenix;
	if (description == "Taoist Priest")       return TaoistPriest;
	if (description == "Spiritual Monk")      return SpiritualMonk;
	if (description == "Extensive Fog")          return ExtensiveFog;
	if (description == "Holy Light")    return HolyLight;
	if (description == "Advance Guard")       return AdvanceGuard;
	if (description == "Rear Guard")          return RearGuard;
	if (description == "Skyward Net")         return SkywardNet;
	if (description == "Earthward Net")       return EarthwardNet;
	if (description == "Rising Dragon")    return RisingDragon;
	if (description == "Quartermaster")      return Quartermaster;
	if (description == "Winged Tiger")          return WingedTiger;
	if (description == "Flying Hawk")            return FlyingHawk;
	if (description == "Longbow")            return Longbow;
	if (description == "Longbow Knight")  return LongbowKnight;
	if (description == "Crossbow")           return Crossbow;
	if (description == "Crossbow Knight") return CrossbowKnight;
	if (description == "Cannon")             return Cannon;
	if (description == "Cannon Carriage")        return CannonCarriage;
	if (description == "Frankish Cannon")     return FrankishCannon;
	if (description == "Divine Carriage")   return DivineCarriage;
	if (description == "Knight Captain")            return KnightCaptain;
	if (description == "Winged Horse")        return WingedHorse;
	if (description == "Shield Captain")         return ShieldCaptain;
	if (description == "Chariot")            return Chariot;
	if (description == "Vanguard")           return Vanguard;

	return None;
}
