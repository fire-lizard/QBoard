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
	case KnightCaptain:
		_pieceType = WingedHorse;
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
	default:
		break;
	}
}

std::string KoShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case MiddleTroop:
		return "M";
	case Prince:
		return "+M";
	case Drum:
		return "U";
	case Thunderclap:
		return "+U";
	case Flag:
		return "L";
	case RoamingAssault:
		return "+L";
	case Tiger:
		return "T";
	case DragonHorse:
		return _basePieceType == Tiger ? "+T" : "H";
	case Elephant:
		return "E";
	case DragonKing:
		return _basePieceType == Elephant ? "+E" : "D";
	case Gold:
		return "G";
	case FlyingStag:
		return "+G";
	case Silver:
		return "S";
	case CompanyCommander:
		return "+S";
	case Leopard:
		return "F";
	case ViceCommissioner:
		return "+F";
	case Copper:
		return "C";
	case PoisonFlame:
		return "+C";
	case Lion:
		return "N";
	case Kylin:
		return "O";
	case DoubleKylin:
		return "+O";
	case Phoenix:
		return "X";
	case DoublePhoenix:
		return "+X";
	case TaoistPriest:
		return "T'";
	case SpiritualMonk:
		return "S'";
	case ExtensiveFog:
		return "+T'";
	case HolyLight:
		return "+S'";
	case AdvanceGuard:
		return "A'";
	case RearGuard:
		return "R'";
	case SkywardNet:
		return "+A'";
	case EarthwardNet:
		return "+R'";
	case Queen:
		return _basePieceType == Rook ? "+R" : "Q";
	case RisingDragon:
		return "+Q";
	case WingedTiger:
		return "+D";
	case FlyingHawk:
		return "+H";
	case Bishop:
		return "B";
	case Longbow:
		return "L'";
	case LongbowKnight:
		return "+L'";
	case Crossbow:
		return "C'";
	case CrossbowKnight:
		return "+C'";
	case Cannon:
		return "I";
	case CannonCarriage:
		return "+I";
	case FrankishCannon:
		return "J";
	case DivineCarriage:
		return "+J";
	case Knight:
		return "Y";
	case KnightCaptain:
		return _basePieceType == Knight ? "+Y" : "W";
	case WingedHorse:
		return "+W";
	case Pawn:
		return "P";
	case VerticalMover:
		return _basePieceType == Pawn ? "+P" : "V";
	case FlyingOx:
		return "+V";
	case CatSword:
		return "Z";
	case ShieldCaptain:
		return _basePieceType == CatSword ? "+Z": "U'";
	case FreeBoar:
		return "F'";
	case Chariot:
		return "A";
	case Rook:
		return _basePieceType == Chariot ? "+A" : "R";
	case Vanguard:
		return "V'";
	default:
		return "";
	}
}

PieceType KoShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"K",   King},
		{"M",   MiddleTroop},
		{"+M",  Prince},
		{"U",   Drum},
		{"+U",  Thunderclap},
		{"L",   Flag},
		{"+L",  RoamingAssault},
		{"T",   Tiger},
		{"+T",   Tiger},
		{"H",   DragonHorse},
		{"E",   Elephant},
		{"+E",   Elephant},
		{"D",   DragonKing},
		{"G",   Gold},
		{"+G",  FlyingStag},
		{"S",   Silver},
		{"+S",  CompanyCommander},
		{"F",   Leopard},
		{"+F",  ViceCommissioner},
		{"C",   Copper},
		{"+C",  PoisonFlame},
		{"N",   Lion},
		{"O",   Kylin},
		{"+O",  DoubleKylin},
		{"X",   Phoenix},
		{"+X",  DoublePhoenix},
		{"T'",  TaoistPriest},
		{"S'",  SpiritualMonk},
		{"+T'", ExtensiveFog},
		{"+S'", HolyLight},
		{"A'",  AdvanceGuard},
		{"R'",  RearGuard},
		{"+A'", SkywardNet},
		{"+R'", EarthwardNet},
		{"Q",   Queen},
		{"+Q",  RisingDragon},
		{"+D",  WingedTiger},
		{"+H",  FlyingHawk},
		{"B",   Bishop},
		{"L'",  Longbow},
		{"+L'", LongbowKnight},
		{"C'",  Crossbow},
		{"+C'", CrossbowKnight},
		{"I",   Cannon},
		{"+I",  CannonCarriage},
		{"J",   FrankishCannon},
		{"+J",  DivineCarriage},
		{"Y",   Knight},
		{"+Y",   Knight},
		{"W",   KnightCaptain},
		{"+W",  WingedHorse},
		{"P",   Pawn},
		{"+P",   Pawn},
		{"V",   VerticalMover},
		{"+V",  FlyingOx},
		{"Z",   CatSword},
		{"+Z",   CatSword},
		{"U'",  ShieldCaptain},
		{"F'",  FreeBoar},
		{"A",   Chariot},
		{"+A",   Chariot},
		{"R",   Rook},
		{"+R",   Rook},
		{"V'",  Vanguard}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : None;
}

std::string KoShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case King:
		return "将";
	case MiddleTroop:
		return "中軍";
	case Prince:
		return "帥";
	case Drum:
		return "鼓";
	case Thunderclap:
		return "霹靂";
	case Flag:
		return "旗";
	case RoamingAssault:
		return "招揺";
	case Tiger:
		return "護兵";
	case DragonHorse:
		return "百総";
	case Elephant:
		return "親兵";
	case DragonKing:
		return "把総";
	case Gold:
		return "舎人";
	case FlyingStag:
		return "千戸";
	case Silver:
		return "舎餘";
	case CompanyCommander:
		return "百戸";
	case Leopard:
		return "軍吏";
	case ViceCommissioner:
		return "副司";
	case Copper:
		return "軍匠";
	case PoisonFlame:
		return "毒火";
	case Lion:
		return "力士";
	case Kylin:
		return "記室";
	case DoubleKylin:
		return "軍師";
	case Phoenix:
		return "参謀";
	case DoublePhoenix:
		return "旗鼓";
	case TaoistPriest:
		return "高道";
	case SpiritualMonk:
		return "神僧";
	case ExtensiveFog:
		return "五里霧";
	case HolyLight:
		return "聖燈";
	case AdvanceGuard:
		return "前衝";
	case RearGuard:
		return "後衝";
	case SkywardNet:
		return "天網";
	case EarthwardNet:
		return "地網";
	case Queen:
		return "千総";
	case RisingDragon:
		return "龍驤";
	case WingedTiger:
		return "虎翼";
	case FlyingHawk:
		return "鷹揚";
	case Bishop:
		return "象";
	case Longbow:
		return "弓";
	case LongbowKnight:
		return "彍騎";
	case Crossbow:
		return "弩";
	case CrossbowKnight:
		return "弩騎";
	case Cannon:
		return "砲";
	case CannonCarriage:
		return "砲車";
	case FrankishCannon:
		return "佛狼機";
	case DivineCarriage:
		return "神機車";
	case Knight:
		return "馬兵";
	case KnightCaptain:
		return "騎総";
	case WingedHorse:
		return "天馬";
	case Pawn:
		return "歩兵";
	case VerticalMover:
		return "歩総";
	case FlyingOx:
		return "都司";
	case CatSword:
		return "牌";
	case ShieldCaptain:
		return "牌総";
	case FreeBoar:
		return "天塁";
	case Chariot:
		return "車";
	case Rook:
		return "車総";
	case Vanguard:
		return "先鋒";
	default:
		return "";
	}
}

std::string KoShogiPiece::GetKanjiImageFileName()
{
	std::string colour = _pieceColour == White ? "F" : "";
	if (_isPromoted && _pieceType != King && _pieceType != Lion && _pieceType != Bishop)
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
	case Lion:
		return "Wrestler" + colour + ".png";
	default:
		std::string desc = PieceType2Description(_pieceType);
		replaceSubstring(desc, " ", "");
		return desc + colour + ".png";
	}
}

std::string KoShogiPiece::GetKanjiImageFileName2()
{
	const std::string colour = _pieceColour == White ? "kw" : "kb";
	switch (_pieceType)
	{
	case King:           return colour + "g" + ".png";
	case Prince:         return colour + "go" + ".png";
	case Queen:          return colour + (_isPromoted ? "mm" : "m") + ".png";
	case Rook:           return colour + (_isPromoted ? "cc" : "cu") + ".png";
	case Bishop:         return colour + "e" + ".png";
	case Gold:           return colour + "a" + ".png";
	case Silver:         return colour + "s" + ".png";
	case Copper:         return colour + "en" + ".png";
	case FlyingOx:       return colour + "co" + ".png";
	case FreeBoar:       return colour + "ib" + ".png";
	case VerticalMover:  return colour + (_isPromoted ? "pp" : "pu") + ".png";
	case DragonHorse:    return colour + (_isPromoted ? "ss" : "cr") + ".png";
	case DragonKing:     return colour + (_isPromoted ? "aa" : "q") + ".png";
	case CatSword:       return colour + "sh" + ".png";
	case Leopard:        return colour + "cs" + ".png";
	case FlyingStag:     return colour + "tb" + ".png";
	case Tiger:          return colour + "sn" + ".png";
	case Elephant:       return colour + "ac" + ".png";
	case Phoenix:        return colour + "so" + ".png";
	case Kylin:          return colour + "cl" + ".png";
	case Knight:         return colour + "hs" + ".png";
	case Pawn:           return colour + "p" + ".png";
	case MiddleTroop:          return colour + "mt" + ".png";
	case Drum:                 return colour + "d" + ".png";
	case Thunderclap:          return colour + "tc" + ".png";
	case Flag:                 return colour + "b" + ".png";
	case RoamingAssault:       return colour + "ra" + ".png";
	case CompanyCommander:     return colour + "vb" + ".png";
	case ViceCommissioner:     return colour + "vc" + ".png";
	case PoisonFlame:          return colour + "pf" + ".png";
	case Lion:                 return colour + "wr" + ".png";
	case DoubleKylin:          return colour + "ma" + ".png";
	case DoublePhoenix:        return colour + "bd" + ".png";
	case TaoistPriest:         return colour + "tp" + ".png";
	case SpiritualMonk:        return colour + "sm" + ".png";
	case ExtensiveFog:         return colour + "tf" + ".png";
	case HolyLight:			   return colour + "il" + ".png";
	case AdvanceGuard:         return colour + "ag" + ".png";
	case RearGuard:            return colour + "rg" + ".png";
	case SkywardNet:           return colour + "hv" + ".png";
	case EarthwardNet:         return colour + "ev" + ".png";
	case RisingDragon:         return colour + "da" + ".png";
	case WingedTiger:          return colour + "tw" + ".png";
	case FlyingHawk:           return colour + "wh" + ".png";
	case Longbow:              return colour + "lb" + ".png";
	case LongbowKnight:        return colour + "lc" + ".png";
	case Crossbow:             return colour + "sb" + ".png";
	case CrossbowKnight:       return colour + "sc" + ".png";
	case Cannon:               return colour + "c" + ".png";
	case CannonCarriage:       return colour + "gc" + ".png";
	case FrankishCannon:       return colour + "ec" + ".png";
	case DivineCarriage:       return colour + "cg" + ".png";
	case KnightCaptain:        return colour + (_isPromoted ? "hh" : "ca") + ".png";
	case WingedHorse:          return colour + "wg" + ".png";
	case ShieldCaptain:        return colour + (_isPromoted ? "uu" : "su") + ".png";
	case Chariot:              return colour + "ch" + ".png";
	case Vanguard:             return colour + "v" + ".png";
	default: return "";
	}
}

std::string KoShogiPiece::GetMnemonicImageFileName() const
{
	const std::string colour = _pieceColour == White ? "w" : "b";
	switch (_pieceType)
	{
	case King:           return colour + "g" + ".png";
	case Prince:         return colour + "go" + ".png";
	case Queen:          return colour + "m" + ".png";
	case Rook:           return colour + "cu" + ".png";
	case Bishop:         return colour + "e" + ".png";
	case Gold:           return colour + "a" + ".png";
	case Silver:         return colour + "s" + ".png";
	case Copper:         return colour + "en" + ".png";
	case FlyingOx:       return colour + "co" + ".png";
	case FreeBoar:       return colour + "ib" + ".png";
	case VerticalMover:  return colour + "pu" + ".png";
	case DragonHorse:    return colour + "cr" + ".png";
	case DragonKing:     return colour + "q" + ".png";
	case CatSword:       return colour + "sh" + ".png";
	case Leopard:        return colour + "cs" + ".png";
	case FlyingStag:     return colour + "tb" + ".png";
	case Tiger:          return colour + "sn" + ".png";
	case Elephant:       return colour + "ac" + ".png";
	case Phoenix:        return colour + "so" + ".png";
	case Kylin:          return colour + "cl" + ".png";
	case Knight:         return colour + "hs" + ".png";
	case Pawn:           return colour + "p" + ".png";
	case MiddleTroop:          return colour + "mt" + ".png";
	case Drum:                 return colour + "d" + ".png";
	case Thunderclap:          return colour + "tc" + ".png";
	case Flag:                 return colour + "b" + ".png";
	case RoamingAssault:       return colour + "ra" + ".png";
	case CompanyCommander:     return colour + "vb" + ".png";
	case ViceCommissioner:     return colour + "vc" + ".png";
	case PoisonFlame:          return colour + "pf" + ".png";
	case Lion:                 return colour + "wr" + ".png";
	case DoubleKylin:          return colour + "ma" + ".png";
	case DoublePhoenix:        return colour + "bd" + ".png";
	case TaoistPriest:         return colour + "tp" + ".png";
	case SpiritualMonk:        return colour + "sm" + ".png";
	case ExtensiveFog:         return colour + "tf" + ".png";
	case HolyLight:			   return colour + "il" + ".png";
	case AdvanceGuard:         return colour + "ag" + ".png";
	case RearGuard:            return colour + "rg" + ".png";
	case SkywardNet:           return colour + "hv" + ".png";
	case EarthwardNet:         return colour + "ev" + ".png";
	case RisingDragon:         return colour + "da" + ".png";
	case WingedTiger:          return colour + "tw" + ".png";
	case FlyingHawk:           return colour + "wh" + ".png";
	case Longbow:              return colour + "lb" + ".png";
	case LongbowKnight:        return colour + "lc" + ".png";
	case Crossbow:             return colour + "sb" + ".png";
	case CrossbowKnight:       return colour + "sc" + ".png";
	case Cannon:               return colour + "c" + ".png";
	case CannonCarriage:       return colour + "gc" + ".png";
	case FrankishCannon:       return colour + "ec" + ".png";
	case DivineCarriage:       return colour + "cg" + ".png";
	case KnightCaptain:        return colour + "ca" + ".png";
	case WingedHorse:          return colour + "wg" + ".png";
	case ShieldCaptain:        return colour + "su" + ".png";
	case Chariot:              return colour + "ch" + ".png";
	case Vanguard:             return colour + "v" + ".png";
	default: return "";
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
	case Flag:                 return "Flag";
	case RoamingAssault:       return "Roaming Assault";
	case CompanyCommander:     return "Company Commander";
	case ViceCommissioner:     return "Vice Commissioner";
	case PoisonFlame:          return "Poison Flame";
	case Lion:                 return "Wrestler";
	case DoubleKylin:          return "Master at Arms";
	case DoublePhoenix:        return "Flag and Drum";
	case TaoistPriest:         return "Taoist Priest";
	case SpiritualMonk:        return "Spiritual Monk";
	case ExtensiveFog:         return "Extensive Fog";
	case HolyLight:			   return "Holy Light";
	case AdvanceGuard:         return "Advance Guard";
	case RearGuard:            return "Rear Guard";
	case SkywardNet:           return "Skyward Net";
	case EarthwardNet:         return "Earthward Net";
	case RisingDragon:         return "Rising Dragon";
	case WingedTiger:          return "Winged Tiger";
	case FlyingHawk:           return "Flying Hawk";
	case Longbow:              return "Longbow";
	case LongbowKnight:        return "Longbow Knight";
	case Crossbow:             return "Crossbow";
	case CrossbowKnight:       return "Crossbow Knight";
	case Cannon:               return "Cannon";
	case CannonCarriage:       return "Cannon Carriage";
	case FrankishCannon:       return "Frankish Cannon";
	case DivineCarriage:       return "Divine Carriage";
	case KnightCaptain:        return "Knight Captain";
	case WingedHorse:          return "Winged Horse";
	case ShieldCaptain:        return "Shield Captain";
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
	if (description == "Middle Troop")  return MiddleTroop;
	if (description == "Drum")          return Drum;
	if (description == "Thunderclap")   return Thunderclap;
	if (description == "Flag")          return Flag;
	if (description == "Roaming Assault")     return RoamingAssault;
	if (description == "Company Commander")   return CompanyCommander;
	if (description == "Vice Commissioner")   return ViceCommissioner;
	if (description == "Poison Flame")        return PoisonFlame;
	if (description == "Wrestler")			  return Lion;
	if (description == "Master at Arms")      return DoubleKylin;
	if (description == "Flag and Drum")       return DoublePhoenix;
	if (description == "Taoist Priest")       return TaoistPriest;
	if (description == "Spiritual Monk")      return SpiritualMonk;
	if (description == "Extensive Fog")       return ExtensiveFog;
	if (description == "Holy Light")		  return HolyLight;
	if (description == "Advance Guard")       return AdvanceGuard;
	if (description == "Rear Guard")          return RearGuard;
	if (description == "Skyward Net")         return SkywardNet;
	if (description == "Earthward Net")       return EarthwardNet;
	if (description == "Rising Dragon")       return RisingDragon;
	if (description == "Winged Tiger")        return WingedTiger;
	if (description == "Flying Hawk")         return FlyingHawk;
	if (description == "Longbow")             return Longbow;
	if (description == "Longbow Knight")      return LongbowKnight;
	if (description == "Crossbow")            return Crossbow;
	if (description == "Crossbow Knight")     return CrossbowKnight;
	if (description == "Cannon")              return Cannon;
	if (description == "Cannon Carriage")     return CannonCarriage;
	if (description == "Frankish Cannon")     return FrankishCannon;
	if (description == "Divine Carriage")     return DivineCarriage;
	if (description == "Knight Captain")      return KnightCaptain;
	if (description == "Winged Horse")        return WingedHorse;
	if (description == "Shield Captain")      return ShieldCaptain;
	if (description == "Chariot")             return Chariot;
	if (description == "Vanguard")            return Vanguard;

	return None;
}

void KoShogiPiece::Demote()
{
	if (_isPromoted)
	{
		_isPromoted = false;
		_pieceType = _basePieceType;
	}
}