#include "MakaDaiDaiShogiPiece.h"

MakaDaiDaiShogiPiece::MakaDaiDaiShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

MakaDaiDaiShogiPiece::~MakaDaiDaiShogiPiece()
{
}

void MakaDaiDaiShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	if (pieceType != None)
	{
		_pieceType = pieceType;
		return;
	}
	switch (_pieceType)
	{
	case King:
		_pieceType = Emperor;
		break;
	case Elephant:
		_pieceType = King;
		break;
	case Deva:
		_pieceType = TeachingKing;
		break;
	case DarkSpirit:
		_pieceType = BuddhistSpirit;
		break;
	case Gold:
		_pieceType = FreeGold;
		break;
	case Silver:
		_pieceType = FreeSilver;
		break;
	case Copper:
		_pieceType = FreeCopper;
		break;
	case Iron:
		_pieceType = FreeIron;
		break;
	case Tile:
		_pieceType = FreeTile;
		break;
	case Stone:
		_pieceType = FreeStone;
		break;
	case GoBetween:
		_pieceType = FreeGo;
		break;
	case Earth:
		_pieceType = FreeEarth;
		break;
	case Tiger:
		_pieceType = FreeTiger;
		break;
	case Leopard:
		_pieceType = FreeLeopard;
		break;
	case CoiledSerpent:
		_pieceType = FreeSerpent;
		break;
	case RecliningDragon:
		_pieceType = FreeDragon;
		break;
	case OldMonkey:
		_pieceType = MountainWitch;
		break;
	case ChineseCock:
		_pieceType = WizardStork;
		break;
	case CatSword:
		_pieceType = FreeCat;
		break;
	case Lion:
		_pieceType = FuriousFiend;
		break;
	case Phoenix:
		_pieceType = GoldenBird;
		break;
	case Kylin:
		_pieceType = GreatDragon;
		break;
	case EvilWolf:
		_pieceType = FreeWolf;
		break;
	case BlindBear:
		_pieceType = FreeBear;
		break;
	case AngryBoar:
		_pieceType = FreeBoar;
		break;
	case OldRat:
		_pieceType = Bat;
		break;
	case Lance:
	case ReverseChariot:
	case LionDog:
	case Wrestler:
	case Guardian:
	case BuddhistDevil:
	case Yaksha:
	case FlyingDragon:
	case ViolentOx:
	case Knight:
	case Donkey:
	case Capricorn:
	case HookMover:
	case Bishop:
	case Rook:
	case VerticalMover:
	case SideMover:
	case LeftChariot:
	case RightChariot:
	case SideFlier:
	case Pawn:
		_pieceType = Gold;
		break;
	default:
		break;
	}
}

std::string MakaDaiDaiShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case Emperor:
		return "+K";
	case Deva:
		return "A!";
	case DarkSpirit:
		return "G!";
	case TeachingKing:
		return "+A!";
	case BuddhistSpirit:
		return "+G!";
	case FreeGold:
		return "+G";
	case FreeSilver:
		return "+S";
	case FreeCopper:
		return "+C";
	case FreeIron:
		return "+J";
	case FreeTile:
		return "+T'";
	case FreeStone:
		return "+U";
	case FreeEarth:
		return "+E'";
	case FreeGo:
		return "+I";
	case FreeTiger:
		return "+T";
	case FreeLeopard:
		return "+F";
	case CoiledSerpent:
		return "I!";
	case RecliningDragon:
		return "J!";
	case FreeSerpent:
		return "+I!";
	case FreeDragon:
		return "+J!";
	case OldMonkey:
		return "M!";
	case MountainWitch:
		return "+M!";
	case ChineseCock:
		return "K!";
	case WizardStork:
		return "+K!";
	case FreeCat:
		return "+Z";
	case FuriousFiend:
		return "+N";
	case GoldenBird:
		return "+X";
	case GreatDragon:
		return "+O";
	case FreeWolf:
		return "+W";
	case BlindBear:
		return "L!";
	case FreeBear:
		return "+L!";
	case OldRat:
		return "O!";
	case Bat:
		return "+O!";
	case LionDog:
		return "N!";
	case Wrestler:
		return "P!";
	case Guardian:
		return "R!";
	case BuddhistDevil:
		return "S!";
	case Yaksha:
		return "T!";
	case Donkey:
		return "U!";
	case Capricorn:
		return "X!";
	case HookMover:
		return "Y!";
	case LeftChariot:
		return "L'";
	case RightChariot:
		return "R'";
	case SideFlier:
		return "Z!";
	case Tile:
		return "T'";
	case Earth:
		return "E'";
	default:
		return DaiShogiPiece::StringCode();
	}
}

PieceType MakaDaiDaiShogiPiece::FromStringCode(const std::string& code)
{
	if (code == "+K")    return Emperor;
	if (code == "A!")    return Deva;
	if (code == "G!")    return DarkSpirit;
	if (code == "+A!")   return TeachingKing;
	if (code == "+G!")   return BuddhistSpirit;
	if (code == "+G")    return FreeGold;
	if (code == "+S")    return FreeSilver;
	if (code == "+C")    return FreeCopper;
	if (code == "+J")    return FreeIron;
	if (code == "+T'")   return FreeTile;
	if (code == "+U")    return FreeStone;
	if (code == "+E'")   return FreeEarth;
	if (code == "+I")    return FreeGo;
	if (code == "+T")    return FreeTiger;
	if (code == "+F")    return FreeLeopard;
	if (code == "I!")    return CoiledSerpent;
	if (code == "J!")    return RecliningDragon;
	if (code == "+I!")   return FreeSerpent;
	if (code == "+J!")   return FreeDragon;
	if (code == "M!")    return OldMonkey;
	if (code == "+M!")   return MountainWitch;
	if (code == "K!")    return ChineseCock;
	if (code == "+K!")   return WizardStork;
	if (code == "+Z")    return FreeCat;
	if (code == "+N")    return FuriousFiend;
	if (code == "+X")    return GoldenBird;
	if (code == "+O")    return GreatDragon;
	if (code == "+W")    return FreeWolf;
	if (code == "L!")    return BlindBear;
	if (code == "+L!")   return FreeBear;
	if (code == "O!")    return OldRat;
	if (code == "+O!")   return Bat;
	if (code == "N!")    return LionDog;
	if (code == "P!")    return Wrestler;
	if (code == "R!")    return Guardian;
	if (code == "S!")    return BuddhistDevil;
	if (code == "T!")    return Yaksha;
	if (code == "U!")    return Donkey;
	if (code == "X!")    return Capricorn;
	if (code == "Y!")    return HookMover;
	if (code == "L'")    return LeftChariot;
	if (code == "R'")    return RightChariot;
	if (code == "Z!")    return SideFlier;
	if (code == "T'")    return Tile;
	if (code == "E'")    return Earth;

	return DaiShogiPiece::FromStringCode(code);
}

std::string MakaDaiDaiShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case Emperor:
		return "自在天王";
	case Deva:
		return "提婆";
	case DarkSpirit:
		return "無明";
	case TeachingKing:
		return "教王";
	case BuddhistSpirit:
		return "法性";
	case FreeGold:
		return "奔金";
	case FreeSilver:
		return "奔銀";
	case FreeCopper:
		return "奔銅";
	case FreeIron:
		return "奔鉄";
	case FreeTile:
		return "奔瓦";
	case FreeStone:
		return "奔石";
	case FreeEarth:
		return "奔土";
	case FreeGo:
		return "奔人";
	case FreeTiger:
		return "奔虎";
	case FreeLeopard:
		return "奔豹";
	case CoiledSerpent:
		return "蟠蛇";
	case RecliningDragon:
		return "臥龍";
	case FreeSerpent:
		return "奔蛇";
	case FreeDragon:
		return "奔龍";
	case OldMonkey:
		return "古猿";
	case MountainWitch:
		return "山母";
	case ChineseCock:
		return "淮鶏";
	case WizardStork:
		return "仙鶴";
	case FreeCat:
		return "奔猫";
	case FuriousFiend:
		return "奮迅";
	case GoldenBird:
		return "金翅";
	case GreatDragon:
		return "大龍";
	case FreeWolf:
		return "奔狼";
	case FreeBear:
		return "奔熊";
	case OldRat:
		return "老鼠";
	case Bat:
		return "蝙蝠";
	case LionDog:
		return "狛犬";
	case Wrestler:
		return "力士";
	case Guardian:
		return "金剛";
	case BuddhistDevil:
		return "羅刹";
	case Yaksha:
		return "夜叉";
	case Donkey:
		return "驢馬";
	case Capricorn:
		return "摩𩹄";
	case HookMover:
		return "鉤行";
	case LeftChariot:
		return "左車";
	case RightChariot:
		return "右車";
	case SideFlier:
		return "横飛";
	case BlindBear:
		return "盲熊";
	case Tile:
		return "瓦";
	case Earth:
		return "土";
	default:
		return DaiShogiPiece::KanjiStringCode();
	}
}

std::string MakaDaiDaiShogiPiece::GetKanjiImageFileName()
{
	std::string colour = _pieceColour == White ? "" : "Flip";
	if (_isPromoted && _pieceType != King && _pieceType != Queen && _pieceType != DragonKing && _pieceType != DragonHorse)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	case Gold:
	case Silver:
	case Copper:
	case Iron:
	case Tile:
	case Stone:
	case Earth:
		return PieceType2Description(_pieceType) + "General" + colour + ".png";
	case Leopard:
		return "FerociousLeopard" + colour + ".png";
	case Tiger:
		return "BlindTiger" + colour + ".png";
	case Elephant:
		return "DrunkElephant" + colour + ".png";
	case Kylin:
		return "Kirin" + colour + ".png";
	case Guardian:
		return "GuardianGod" + colour + ".png";
	case Yaksha:
		return "SheDevil" + colour + ".png";
	case FreeSerpent:
		return "FreeSnake" + colour + ".png";
	case FreeGo:
		return "FreeGoBetween" + colour + ".png";
	default:
		std::string desc = PieceType2Description(_pieceType);
		replaceSubstring(desc, " ", "");
		return desc + colour + ".png";
	}
}

std::string MakaDaiDaiShogiPiece::GetKanjiImageFileName2()
{
	std::string colour = _pieceColour == White ? "_piece_B_" : "_piece_W_";
	colour += _isPromoted && _pieceType != King && _pieceType != Queen && _pieceType != DragonKing && _pieceType != DragonHorse ? "prom" : "norm";
	switch (_pieceType)
	{
	case King:
		return "Korol" + colour + ".png";
	case Queen:
		return "Ferz" + colour + ".png";
	case DragonKing:
		return "Car_Drakon" + colour + ".png";
	case DragonHorse:
		return "Loshad" + colour + ".png";
	case Tile:
		return "Plitochnyj_general" + colour + ".png";
	case Earth:
		return "Zemljanoj_general" + colour + ".png";
	case Guardian:
		return "Almaz" + colour + ".png";
	case Yaksha:
		return "Djavolica" + colour + ".png";
	case FreeSerpent:
		return "Svobodnaja_zmeja" + colour + ".png";
	case FreeGo:
		return "Svobodnyj_hodok" + colour + ".png";
	case Emperor:
		return "Imperator" + colour + ".png";
	case Deva:
		return "Deva" + colour + ".png";
	case DarkSpirit:
		return "Duh_nevezhestva" + colour + ".png";
	case TeachingKing:
		return "Uchebnyj_korol" + colour + ".png";
	case BuddhistSpirit:
		return "Buddijskij_duh" + colour + ".png";
	case FreeGold:
		return "Svobodnoe_zoloto" + colour + ".png";
	case FreeSilver:
		return "Svobodnoe_serebro" + colour + ".png";
	case FreeCopper:
		return "Svobodnaja_med" + colour + ".png";
	case FreeIron:
		return "Svobodnoe_zhelezo" + colour + ".png";
	case FreeTile:
		return "Svobodnaja_plitka" + colour + ".png";
	case FreeStone:
		return "Svobodnyj_kamen" + colour + ".png";
	case FreeEarth:
		return "Svobodnaja_zemlja" + colour + ".png";
	case FreeTiger:
		return "Svobodnyj_tigr" + colour + ".png";
	case FreeLeopard:
		return "Svobodnyj_leopard" + colour + ".png";
	case CoiledSerpent:
		return "Svernuvshajasja_zmeja" + colour + ".png";
	case RecliningDragon:
		return "Lezhashij_drakon" + colour + ".png";
	case FreeDragon:
		return "Svobodnyj_drakon" + colour + ".png";
	case OldMonkey:
		return "Staraja_obezjana" + colour + ".png";
	case MountainWitch:
		return "Gornaja_vedma" + colour + ".png";
	case ChineseCock:
		return "Kitajskij_petuh" + colour + ".png";
	case WizardStork:
		return "Volshebnyj_aist" + colour + ".png";
	case FreeCat:
		return "Svobodnaja_koshka" + colour + ".png";
	case FuriousFiend:
		return "JArostnoe_porozhdenie" + colour + ".png";
	case GoldenBird:
		return "Zolotoe_krylo" + colour + ".png";
	case GreatDragon:
		return "Velikij_drakon" + colour + ".png";
	case FreeWolf:
		return "Svobodnyj_volk" + colour + ".png";
	case FreeBear:
		return "Svobodnyj_medved" + colour + ".png";
	case OldRat:
		return "Staraja_krysa" + colour + ".png";
	case Bat:
		return "Letuchaja_mysh" + colour + ".png";
	case LionDog:
		return "Lvinaja_sobaka" + colour + ".png";
	case Wrestler:
		return "Borec" + colour + ".png";
	case BuddhistDevil:
		return "Demon" + colour + ".png";
	case Donkey:
		return "Osjol" + colour + ".png";
	case Capricorn:
		return "Kozerog" + colour + ".png";
	case HookMover:
		return "Krjukovoj_hodok" + colour + ".png";
	case LeftChariot:
		return "Levaja_kolesnica" + colour + ".png";
	case RightChariot:
		return "Pravaja_kolesnica" + colour + ".png";
	case SideFlier:
		return "Gorizontalnyj_letun" + colour + ".png";
	case BlindBear:
		return "Slepoj_medved" + colour + ".png";
	default:
		return DaiShogiPiece::GetKanjiImageFileName2();
	}
}