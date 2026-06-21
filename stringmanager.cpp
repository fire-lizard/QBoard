#include "stringmanager.h"

std::string StringManager::PieceType2Description(GameVariant gameVariant, PieceType pieceType)
{
    if (gameVariant == KoShogi)
    {
        return KoShogiPieceType2Description(pieceType);
    }
    if (gameVariant == WaShogi || gameVariant == CrazyWa)
    {
        return WaShogiPieceType2Description(pieceType);
    }
    else if (gameVariant == ToriShogi)
    {
        return ToriShogiPieceType2Description(pieceType);
    }
    else if (gameVariant == WhaleShogi)
    {
        return WhaleShogiPieceType2Description(pieceType);
    }
    else
    {
        return PieceType2Description(pieceType);
    }
}

PieceType StringManager::Description2PieceType(GameVariant gameVariant, const std::string& description)
{
    if (gameVariant == KoShogi)
    {
        return KoShogiDescription2PieceType(description);
    }
    else if (gameVariant == WaShogi || gameVariant == CrazyWa)
    {
        return WaShogiDescription2PieceType(description);
    }
    else if (gameVariant == ToriShogi)
    {
        return ToriShogiDescription2PieceType(description);
    }
    else if (gameVariant == WhaleShogi)
    {
        return WhaleShogiDescription2PieceType(description);
    }
    else
    {
        return Description2PieceType(description);
    }
}

std::string StringManager::PieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case None:                 return "None";
    case King:                 return "King";
    case Lion:                 return "Lion";
    case Queen:                return "Queen";
    case DragonKing:           return "Dragon King";
    case DragonHorse:          return "Dragon Horse";
    case Rook:                 return "Rook";
    case Bishop:               return "Bishop";
    case Knight:               return "Knight";
    case VerticalMover:        return "Vertical Mover";
    case SideMover:            return "Side Mover";
    case Cannon:               return "Cannon";
    case ReverseChariot:       return "Reverse Chariot";
    case Lance:                return "Lance";
    case Kylin:                return "Kylin";
    case Phoenix:              return "Phoenix";
    case Elephant:             return "Elephant";
    case Prince:               return "Prince";
    case Tiger:                return "Tiger";
    case Gold:                 return "Gold";
    case Silver:               return "Silver";
    case Copper:               return "Copper";
    case Leopard:              return "Leopard";
    case GoBetween:            return "Go Between";
    case Pawn:                 return "Pawn";
    case Eagle:                return "Eagle";
    case Unicorn:              return "Unicorn";
    case FlyingOx:             return "Flying Ox";
    case FreeBoar:             return "Free Boar";
    case FlyingStag:           return "Flying Stag";
    case WhiteHorse:           return "White Horse";
    case Whale:                return "Whale";
    case PromotedLance:        return "Promoted Lance";
    case PromotedKnight:       return "Promoted Knight";
    case PromotedSilver:       return "Promoted Silver";
    case Tokin:                return "Tokin";
    case ViolentOx:            return "Violent Ox";
    case FlyingDragon:         return "Flying Dragon";
    case AngryBoar:            return "Angry Boar";
    case CatSword:             return "Cat Sword";
    case EvilWolf:             return "Evil Wolf";
    case Iron:                 return "Iron";
    case Stone:                return "Stone";
    case Dog:                  return "Dog";
    case ViceGeneral:          return "Vice General";
    case GreatGeneral:         return "Great General";
    case BishopGeneral:        return "Bishop General";
    case RookGeneral:          return "Rook General";
    case MultiGeneral:         return "Multi General";
    case FreeEagle:            return "Free Eagle";
    case LionHawk:             return "Lion Hawk";
    case SideSoldier:          return "Side Soldier";
    case VerticalSoldier:      return "Vertical Soldier";
    case ChariotSoldier:       return "Chariot Soldier";
    case WaterBuffalo:         return "Water Buffalo";
    case HeavenlyTetrarch:     return "Heavenly Tetrarch";
    case FireDemon:            return "Fire Demon";
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
    case BuddhistDevil:        return "Buddhist Devil";
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
    case BuddhistSpirit:       return "Buddhist Spirit";
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
    case Archbishop:           return "Archbishop";
    case Chancellor:           return "Chancellor";
    case Champion:             return "Champion";
    case Wizard:               return "Wizard";
    case Nightrider:           return "Nightrider";
    case Aanca:                return "Aanca";
    case Crocodile:            return "Crocodile";
    case Giraffe:              return "Giraffe";
    case Sage:                 return "Sage";
    case Schleich:             return "Schleich";
    case Courier:              return "Courier";
    case YariKnight:           return "Yari Knight";
    case YariRook:             return "Yari Rook";
    case YariBishop:           return "Yari Bishop";
    case YariGold:             return "Yari Gold";
    case YariSilver:           return "Yari Silver";
    default: return "";
    }
}

std::string StringManager::KoShogiPieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case King:                 return "General";
    case Prince:               return "Governor";
    case Queen:                return "Millenary";
    case Rook:                 return "Chariot Unit";
    case Bishop:               return "Elephant";
    case Gold:                 return "Aide";
    case Silver:               return "Staff";
    case Copper:               return "Engineer";
    case FlyingOx:             return "Commissar";
    case FreeBoar:             return "Heavenly Fortress";
    case VerticalMover:        return "Patrol Unit";
    case DragonHorse:          return "Centuria";
    case DragonKing:           return "Quartermaster";
    case CatSword:             return "Shield";
    case Leopard:              return "Chief of Staff";
    case FlyingStag:           return "Town Brigade";
    case Tiger:                return "Sentry";
    case Elephant:             return "Aide de Camp";
    case Phoenix:              return "Staff Officer";
    case Kylin:                return "Clerk";
    case Knight:               return "Cavalryman";
    case Pawn:                 return "Pawn";
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

std::string StringManager::ToriShogiPieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case King: return "Phoenix";
    case Falcon: return "Falcon";
    case Eagle: return "Eagle";
    case Crane: return "Crane";
    case Pheasant: return "Pheasant";
    case LeftQuail: return "Left Quail";
    case RightQuail: return "Right Quail";
    case Pawn: return "Swallow";
    case Goose: return "Goose";
    default: return "";
    }
}

std::string StringManager::WaShogiPieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case King: return "Crane King";
    case Rook: return "Gliding Swallow";
    case SideMover: return "Swallow's Wings";
    case Lance: return "Ox Cart";
    case Elephant: return "Roaming Boar";
    case Gold: return "Violent Wolf";
    case Silver: return "Violent Stag";
    case Pawn: return "Sparrow Pawn";
    case Tokin: return "Golden Bird";
    case PloddingOx: return "Plodding Ox";
    case LiberatedHorse: return "Liberated Horse";
    case HeavenlyHorse: return "Heavenly Horse";
    case SwoopingOwl: return "Swooping Owl";
    case CloudEagle: return "Cloud Eagle";
    case StruttingCrow: return "Strutting Crow";
    case FlyingFalcon: return "Flying Falcon";
    case FlyingCock: return "Flying Cock";
    case RaidingFalcon: return "Raiding Falcon";
    case FlyingGoose: return "Flying Goose";
    case ClimbingMonkey: return "Climbing Monkey";
    case Dog: return "Blind Dog";
    case BearEyes: return "Bear Eyes";
    case RunningRabbit: return "Running Rabbit";
    case TreacherousFox: return "Treacherous Fox";
    case TenaciousFalcon: return "Tenacious Falcon";
    default: return "";
    }
}

std::string StringManager::WhaleShogiPieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case King: return "White Whale";
    case GreyWhale: return "Grey Whale";
    case Porpoise: return "Porpoise";
    case DragonKing: return "Killer Whale";
    case Narwhal: return "Narwhal";
    case Humpback: return "Humpback";
    case BlueWhale: return "Blue Whale";
    case Pawn: return "Dolphin";
    default: return "";
    }
}

PieceType StringManager::Description2PieceType(const std::string& description)
{
    if (description == "None")               return None;
    if (description == "King")               return King;
    if (description == "Lion")               return Lion;
    if (description == "Queen")              return Queen;
    if (description == "Dragon King")        return DragonKing;
    if (description == "Dragon Horse")       return DragonHorse;
    if (description == "Rook")               return Rook;
    if (description == "Bishop")             return Bishop;
    if (description == "Knight")             return Knight;
    if (description == "Vertical Mover")     return VerticalMover;
    if (description == "Side Mover")         return SideMover;
    if (description == "Cannon")             return Cannon;
    if (description == "Reverse Chariot")    return ReverseChariot;
    if (description == "Lance")              return Lance;
    if (description == "Kylin")              return Kylin;
    if (description == "Phoenix")            return Phoenix;
    if (description == "Elephant")           return Elephant;
    if (description == "Prince")             return Prince;
    if (description == "Tiger")              return Tiger;
    if (description == "Gold")               return Gold;
    if (description == "Silver")             return Silver;
    if (description == "Copper")             return Copper;
    if (description == "Leopard")            return Leopard;
    if (description == "Go Between")         return GoBetween;
    if (description == "Pawn")               return Pawn;
    if (description == "Eagle")              return Eagle;
    if (description == "Unicorn")            return Unicorn;
    if (description == "Flying Ox")          return FlyingOx;
    if (description == "Free Boar")          return FreeBoar;
    if (description == "Flying Stag")        return FlyingStag;
    if (description == "White Horse")        return WhiteHorse;
    if (description == "Whale")              return Whale;
    if (description == "Promoted Lance")     return PromotedLance;
    if (description == "Promoted Knight")    return PromotedKnight;
    if (description == "Promoted Silver")    return PromotedSilver;
    if (description == "Tokin")              return Tokin;
    if (description == "Violent Ox")         return ViolentOx;
    if (description == "Flying Dragon")      return FlyingDragon;
    if (description == "Angry Boar")         return AngryBoar;
    if (description == "Cat Sword")          return CatSword;
    if (description == "Evil Wolf")          return EvilWolf;
    if (description == "Iron")               return Iron;
    if (description == "Stone")              return Stone;
    if (description == "Dog")                return Dog;
    if (description == "Vice General")       return ViceGeneral;
    if (description == "Great General")      return GreatGeneral;
    if (description == "Bishop General")     return BishopGeneral;
    if (description == "Rook General")       return RookGeneral;
    if (description == "Multi General")      return MultiGeneral;
    if (description == "Free Eagle")         return FreeEagle;
    if (description == "Lion Hawk")          return LionHawk;
    if (description == "Side Soldier")       return SideSoldier;
    if (description == "Vertical Soldier")   return VerticalSoldier;
    if (description == "Chariot Soldier")    return ChariotSoldier;
    if (description == "Water Buffalo")      return WaterBuffalo;
    if (description == "Heavenly Tetrarch")  return HeavenlyTetrarch;
    if (description == "Fire Demon")         return FireDemon;
    if (description == "Blind Monkey")       return BlindMonkey;
    if (description == "Blue Dragon")		 return BlueDragon;
    if (description == "Dove")				 return Dove;
    if (description == "Eastern Barbarian")  return EasternBarbarian;
    if (description == "Western Barbarian")  return WesternBarbarian;
    if (description == "Southern Barbarian") return SouthernBarbarian;
    if (description == "Northern Barbarian") return NorthernBarbarian;
    if (description == "Enchanted Badger")   return EnchantedBadger;
    if (description == "Enchanted Fox")      return EnchantedFox;
    if (description == "Fragrant Elephant")  return FragrantElephant;
    if (description == "Free Demon")         return FreeDemon;
    if (description == "Free Dream Eater")   return FreeDreamEater;
    if (description == "Furious Fiend")      return FuriousFiend;
    if (description == "Golden Bird")        return GoldenBird;
    if (description == "Great Elephant")     return GreatElephant;
    if (description == "Howling Dog")        return HowlingDog;
    if (description == "Left General")       return LeftGeneral;
    if (description == "Right General")      return RightGeneral;
    if (description == "Tengu")              return Tengu;
    if (description == "Neighboring King")   return NeighboringKing;
    if (description == "Old Kite")           return OldKite;
    if (description == "Poisonous Snake")    return PoisonousSnake;
    if (description == "Prancing Stag")      return PrancingStag;
    if (description == "Racing Chariot")     return RacingChariot;
    if (description == "Rushing Bird")       return RushingBird;
    if (description == "Savage Tiger")       return SavageTiger;
    if (description == "Buddhist Devil")     return BuddhistDevil;
    if (description == "Yaksha")             return Yaksha;
    if (description == "Square Mover")       return SquareMover;
    if (description == "Standard Bearer")    return StandardBearer;
    if (description == "Violent Bear")       return ViolentBear;
    if (description == "White Elephant")     return WhiteElephant;
    if (description == "White Tiger")        return WhiteTiger;
    if (description == "Wood")               return Wood;
    if (description == "Flying Horse")       return FlyingHorse;
    if (description == "Great Dragon")       return GreatDragon;
    if (description == "Mountain Witch")     return MountainWitch;
    if (description == "Wizard Stork")       return WizardStork;
    if (description == "Lion Dog")           return LionDog;
    if (description == "Deva")               return Deva;
    if (description == "Dark Spirit")        return DarkSpirit;
    if (description == "Tile")               return Tile;
    if (description == "Earth")              return Earth;
    if (description == "Coiled Serpent")     return CoiledSerpent;
    if (description == "Reclining Dragon")   return RecliningDragon;
    if (description == "Chinese Cock")       return ChineseCock;
    if (description == "Old Monkey")         return OldMonkey;
    if (description == "Blind Bear")         return BlindBear;
    if (description == "Wrestler")           return Wrestler;
    if (description == "Guardian")           return Guardian;
    if (description == "Buddhist Spirit")    return BuddhistSpirit;
    if (description == "Old Rat")            return OldRat;
    if (description == "Donkey")             return Donkey;
    if (description == "Capricorn")          return Capricorn;
    if (description == "Hook Mover")         return HookMover;
    if (description == "Side Flier")         return SideFlier;
    if (description == "Left Chariot")       return LeftChariot;
    if (description == "Right Chariot")      return RightChariot;
    if (description == "Emperor")            return Emperor;
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
    if (description == "Bat")                return Bat;
    if (description == "Archbishop")         return Archbishop;
    if (description == "Chancellor")         return Chancellor;
    if (description == "Champion")           return Champion;
    if (description == "Wizard")             return Wizard;
    if (description == "Nightrider")         return Nightrider;
    if (description == "Aanca")              return Aanca;
    if (description == "Crocodile")          return Crocodile;
    if (description == "Giraffe")            return Giraffe;
    if (description == "Sage")               return Sage;
    if (description == "Schleich")           return Schleich;
    if (description == "Courier")            return Courier;
    if (description == "Yari Knight")        return YariKnight;
    if (description == "Yari Rook")          return YariRook;
    if (description == "Yari Bishop")        return YariBishop;
    if (description == "Yari Gold")          return YariGold;
    if (description == "Yari Silver")        return YariSilver;

    // Fallback for unrecognized description.
    return None;
}

PieceType StringManager::KoShogiDescription2PieceType(const std::string& description)
{
    if (description == "General")             return King;
    if (description == "Governor")            return Prince;
    if (description == "Millenary")           return Queen;
    if (description == "Chariot Unit")        return Rook;
    if (description == "Elephant")            return Bishop;
    if (description == "Aide")                return Gold;
    if (description == "Staff")               return Silver;
    if (description == "Engineer")            return Copper;
    if (description == "Commissar")           return FlyingOx;
    if (description == "Heavenly Fortress")   return FreeBoar;
    if (description == "Patrol Unit")         return VerticalMover;
    if (description == "Centuria")            return DragonHorse;
    if (description == "Quartermaster")       return DragonKing;
    if (description == "Shield")              return CatSword;
    if (description == "Chief of Staff")      return Leopard;
    if (description == "Town Brigade")        return FlyingStag;
    if (description == "Sentry")              return Tiger;
    if (description == "Aide de Camp")        return Elephant;
    if (description == "Staff Officer")       return Phoenix;
    if (description == "Clerk")               return Kylin;
    if (description == "Cavalryman")          return Knight;
    if (description == "Pawn")                return Pawn;
    if (description == "Middle Troop")        return MiddleTroop;
    if (description == "Drum")                return Drum;
    if (description == "Thunderclap")         return Thunderclap;
    if (description == "Flag")                return Flag;
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

PieceType StringManager::ToriShogiDescription2PieceType(const std::string& description)
{
    if (description == "Phoenix")     return King;
    if (description == "Falcon")      return Falcon;
    if (description == "Eagle")       return Eagle;
    if (description == "Crane")       return Crane;
    if (description == "Pheasant")    return Pheasant;
    if (description == "Left Quail")  return LeftQuail;
    if (description == "Right Quail") return RightQuail;
    if (description == "Swallow")     return Pawn;
    if (description == "Goose")       return Goose;
    return None;
}

PieceType StringManager::WaShogiDescription2PieceType(const std::string& description)
{
    if (description == "Crane King")        return King;
    if (description == "Gliding Swallow")   return Rook;
    if (description == "Swallow's Wings")   return SideMover;
    if (description == "Ox Cart")           return Lance;
    if (description == "Roaming Boar")      return Elephant;
    if (description == "Violent Wolf")      return Gold;
    if (description == "Violent Stag")      return Silver;
    if (description == "Sparrow Pawn")      return Pawn;
    if (description == "Golden Bird")       return Tokin;
    if (description == "Plodding Ox")       return PloddingOx;
    if (description == "Liberated Horse")   return LiberatedHorse;
    if (description == "Heavenly Horse")    return HeavenlyHorse;
    if (description == "Swooping Owl")      return SwoopingOwl;
    if (description == "Cloud Eagle")       return CloudEagle;
    if (description == "Strutting Crow")    return StruttingCrow;
    if (description == "Flying Falcon")     return FlyingFalcon;
    if (description == "Flying Cock")       return FlyingCock;
    if (description == "Raiding Falcon")    return RaidingFalcon;
    if (description == "Flying Goose")      return FlyingGoose;
    if (description == "Climbing Monkey")   return ClimbingMonkey;
    if (description == "Blind Dog")         return Dog;
    if (description == "Bear Eyes")         return BearEyes;
    if (description == "Running Rabbit")    return RunningRabbit;
    if (description == "Treacherous Fox")   return TreacherousFox;
    if (description == "Tenacious Falcon")  return TenaciousFalcon;
    return None;
}

PieceType StringManager::WhaleShogiDescription2PieceType(const std::string& description)
{
    if (description == "White Whale")  return King;
    if (description == "Grey Whale")   return GreyWhale;
    if (description == "Porpoise")     return Porpoise;
    if (description == "Killer Whale") return DragonKing;
    if (description == "Narwhal")      return Narwhal;
    if (description == "Humpback")     return Humpback;
    if (description == "Blue Whale")   return BlueWhale;
    if (description == "Dolphin")      return Pawn;
    return None;
}

PieceType StringManager::StringCode2PieceType(GameVariant gameVariant, const std::string& stringCode)
{
    if (gameVariant == Xiangqi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"K", King},
            {"A", Silver},
            {"R", Rook},
            {"C", Cannon},
            {"N", Knight},
            {"H", Knight},
            {"B", Elephant},
            {"E", Elephant},
            {"P", Pawn}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : None;
    }
    else if (gameVariant == KoShogi)
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

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : None;
    }
    else if (gameVariant == WaShogi || gameVariant == CrazyWa)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"K", King},
        	{"O", Lance},
            {"+O", PloddingOx},
            {"P", Pawn},
            {"+P", Tokin},
            {"S", SideMover},
            {"+S", Rook},
            {"H", LiberatedHorse},
            {"+H", HeavenlyHorse},
            {"L", SwoopingOwl},
            {"+L", CloudEagle},
            {"E", CloudEagle},
            {"U", StruttingCrow},
            {"+U", FlyingFalcon},
            {"F", FlyingFalcon},
            {"+F", TenaciousFalcon},
            {"C", FlyingCock},
            {"+C", RaidingFalcon},
            {"G", FlyingGoose},
            {"+G", SideMover},
            {"M", ClimbingMonkey},
            {"+M", Silver},
            {"V", Silver},
            {"+V", Elephant},
            {"D", Dog},
            {"+D", Gold},
            {"W", Gold},
            {"+W", BearEyes},
            {"R", RunningRabbit},
            {"+R", TreacherousFox},
            {"X", TreacherousFox}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : None;
    }
    else if (gameVariant == ToriShogi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"K", King},
            {"F", Falcon},
            {"+F", Eagle},
            {"C", Crane},
            {"P", Pheasant},
            {"L", LeftQuail},
            {"R", RightQuail},
            {"S", Pawn},
            {"+S", Goose}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : None;
    }
    else if (gameVariant == WhaleShogi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"W", King},
            {"G", GreyWhale},
            {"P", Porpoise},
            {"K", DragonKing},
            {"N", Narwhal},
            {"H", Humpback},
            {"B", BlueWhale},
            {"D", Pawn}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : None;
    }
    else if (gameVariant == YariShogi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"N",     YariKnight},
            {"Y",     YariRook},
            {"B",     YariBishop},
            {"G",     YariGold},
            {"S",     YariSilver},
            {"R",     Rook},
            {"P",     Pawn},
            {"K",     King}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : None;
    }
    else if (gameVariant == ChuShogi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"K", King},
            {"N", Lion},
            {"Q", Queen},
            {"D", DragonKing},
            {"H", DragonHorse},
            {"R", Rook},
            {"+R", Rook},
            {"B", Bishop},
            {"+B", Bishop},
            {"V", VerticalMover},
            {"M", SideMover},
            {"A", ReverseChariot},
            {"L", Lance},
            {"O", Kylin},
            {"+O", Kylin},
            {"X", Phoenix},
            {"+X", Phoenix},
            {"E", Elephant},
            {"T", Tiger},
            {"G", Gold},
            {"+G", Gold},
            {"S", Silver},
            {"+S", Silver},
            {"C", Copper},
            {"+C", Copper},
            {"F", Leopard},
            {"+F", Leopard},
            {"I", GoBetween},
            {"+I", GoBetween},
            {"P", Pawn},
            {"+P", Tokin},
            {"+D", Eagle},
            {"+H", Unicorn},
            {"+V", FlyingOx},
            {"+M", FreeBoar},
            {"+T", FlyingStag},
            {"+L", WhiteHorse},
            {"+A", Whale},
            {"+E", Prince}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : None;
    }
    else if (gameVariant == DaiShogi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"J", Iron},
            {"U", Stone},
            {"A'", AngryBoar},
            {"V'", ViolentOx},
            {"F'", FlyingDragon},
            {"W", EvilWolf},
            {"Z", CatSword},
            {"Y", Knight},
            {"W!", WaterBuffalo},
            {"+J", Iron},
            {"+U", Stone},
            {"+A'", AngryBoar},
            {"+V'", ViolentOx},
            {"+F'", FlyingDragon},
            {"+W", EvilWolf},
            {"+Z", CatSword},
            {"+Y", Knight},
            {"+W!", WaterBuffalo},
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : StringCode2PieceType(ChuShogi, stringCode);
    }
    else if (gameVariant == TenjikuShogi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"D'", Dog},
            {"+D'", MultiGeneral},
            {"V!", ViceGeneral},
            {"Q!", GreatGeneral},
            {"B!", BishopGeneral},
            {"+B!", BishopGeneral},
            {"R!", RookGeneral},
            {"+R!", RookGeneral},
            {"Q'", FreeEagle},
            {"H!", LionHawk},
            {"S'", SideSoldier},
            {"+S'", SideSoldier},
            {"V'", VerticalSoldier},
            {"+V'", VerticalSoldier},
            {"C!", ChariotSoldier},
            {"+C!", HeavenlyTetrarch},
            {"D!", FireDemon},
            {"F!", Unicorn},
            {"+F!", Unicorn},
            {"E!", Eagle},
            {"+E!", Eagle},
            {"+Q", Queen},
            {"+N", Lion}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : StringCode2PieceType(DaiShogi, stringCode);
    }
    else if (gameVariant == DaiDaiShogi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            { "J'",   Tengu },
            { "K'",   OldKite },
            { "+K'",  OldKite },
            { "M'",   PoisonousSnake },
            { "+M'",  PoisonousSnake },
            { "B'",   WesternBarbarian },
            { "+B'",  WesternBarbarian },
            { "C'",   EasternBarbarian },
            { "+C'",  EasternBarbarian },
            { "G'",   SouthernBarbarian },
            { "+G'",  SouthernBarbarian },
            { "H'",   NorthernBarbarian },
            { "+H'",  NorthernBarbarian },
            { "N'",   FragrantElephant },
            { "O'",   WhiteElephant },
            { "P'",   FreeDreamEater },
            { "U'",   FreeDemon },
            { "X'",   RushingBird },
            { "+X'",  RushingBird },
            { "Y'",   StandardBearer },
            { "A~",   FlyingHorse },
            { "+A~",  FlyingHorse },
            { "B~",   NeighboringKing },
            { "+B~",  NeighboringKing },
            { "C~",   BlindMonkey },
            { "D~",   Dove },
            { "E~",   EnchantedBadger },
            { "+E~",  EnchantedBadger },
            { "F~",   EnchantedFox },
            { "+F~",  EnchantedFox },
            { "G~",   RacingChariot },
            { "H~",   SquareMover },
            { "I~",   PrancingStag },
            { "+I~",  PrancingStag },
            { "J~",   WhiteTiger },
            { "K~",   BlueDragon },
            { "M~",   HowlingDog },
            { "N~",   ViolentBear },
            { "L~",   LeftGeneral },
            { "R~",   RightGeneral },
            { "O~",   SavageTiger },
            { "P~",   GoldenBird },
            { "Q~",   GreatDragon },
            { "W'",   Wood }
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : StringCode2PieceType(MakaDaiDaiShogi, stringCode);
    }
    else if (gameVariant == MakaDaiDaiShogi)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            { "+P",   Pawn },
            { "+Z!",  SideFlier },
            { "+R'",  RightChariot },
            { "+L'",  LeftChariot },
            { "+Y!",  HookMover },
            { "+X!",  Capricorn },
            { "+U!",  Donkey },
            { "+T!",  Yaksha },
            { "+S!",  BuddhistDevil },
            { "+R!",  Guardian },
            { "+P!",  Wrestler },
            { "+N!",  GreatElephant },
            { "+A",   ReverseChariot },
            { "+L",   Lance },
            { "+M",   SideMover },
            { "+V",   VerticalMover },
            { "+K",   Emperor },
            { "A!",   Deva },
            { "G!",   DarkSpirit },
            { "+A!",  TeachingKing },
            { "+G!",  BuddhistSpirit },
            { "+G",   FreeGold },
            { "+S",   FreeSilver },
            { "+C",   FreeCopper },
            { "+J",   FreeIron },
            { "+T'",  FreeTile },
            { "+U",   FreeStone },
            { "+E'",  FreeEarth },
            { "+I",   FreeGo },
            { "+T",   FreeTiger },
            { "+F",   FreeLeopard },
            { "I!",   CoiledSerpent },
            { "J!",   RecliningDragon },
            { "+I!",  FreeSerpent },
            { "+J!",  FreeDragon },
            { "M!",   OldMonkey },
            { "+M!",  MountainWitch },
            { "K!",   ChineseCock },
            { "+K!",  WizardStork },
            { "+Z",   FreeCat },
            { "+N",   FuriousFiend },
            { "+X",   GoldenBird },
            { "+O",   GreatDragon },
            { "+W",   FreeWolf },
            { "L!",   BlindBear },
            { "+L!",  FreeBear },
            { "O!",   OldRat },
            { "+O!",  Bat },
            { "N!",   LionDog },
            { "P!",   Wrestler },
            { "R!",   Guardian },
            { "S!",   BuddhistDevil },
            { "T!",   Yaksha },
            { "U!",   Donkey },
            { "X!",   Capricorn },
            { "Y!",   HookMover },
            { "L'",   LeftChariot },
            { "R'",   RightChariot },
            { "Z!",   SideFlier },
            { "T'",   Tile },
            { "E'",   Earth }
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : StringCode2PieceType(DaiShogi, stringCode);
    }
    else if (gameVariant == Makruk)
    {
        if (stringCode == "M") return Queen;
        return StringCode2PieceType(Shatranj, stringCode);
    }
    else if (gameVariant == GrandeAcedrex)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"A", Aanca},
            {"C", Crocodile},
            {"G", Giraffe},
            {"U", Unicorn},
            {"L", Lion}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : StringCode2PieceType(Shatranj, stringCode);
    }
    else if (gameVariant == CourierChess)
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"E", Bishop},
            {"B", Courier},
            {"W", Schleich},
            {"M", Sage},
            {"F", Queen}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : StringCode2PieceType(Shatranj, stringCode);
    }
    else if (gameVariant == OmegaChess)
    {
        if (stringCode == "C") return Champion;
        if (stringCode == "W") return Wizard;
        return StringCode2PieceType(Shatranj, stringCode);
    }
    else if (gameVariant == NightriderChess)
    {
        if (stringCode == "N") return Nightrider;
        return StringCode2PieceType(Shatranj, stringCode);
    }
    else if (gameVariant == Shatar)
    {
        if (stringCode == "J") return Queen;
        return StringCode2PieceType(Shatranj, stringCode);
    }
    else if (gameVariant == Sittuyin)
    {
        if (stringCode == "S") return Bishop;
        if (stringCode == "F") return Queen;
        return StringCode2PieceType(Shatranj, stringCode);
    }
    else
    {
        static const std::unordered_map<std::string, PieceType> codeToPieceType = {
            {"K", King},
            {"Q", Queen},
            {"R", Rook},
            {"B", Bishop},
            {"N", Knight},
            {"A", Archbishop},
            {"C", Chancellor},
            {"P", Pawn},
            {"+L", PromotedLance},
            {"+S", PromotedSilver},
            {"+N", PromotedKnight},
            {"+R", DragonKing},
            {"+B", DragonHorse},
            {"L", Lance},
            {"E", Elephant},
            {"G", Gold},
            {"S", Silver},
            {"+P", Tokin},
            {"+E", Prince}
        };

        const auto it = codeToPieceType.find(stringCode);
        return it != codeToPieceType.end() ? it->second : None;
    }
}

std::string StringManager::PieceType2KanjiCode(GameVariant gameVariant, PieceType pieceType, PieceColour pieceColour)
{
    if (gameVariant == Xiangqi)
    {
        switch (pieceType)
        {
        case King:
            return pieceColour == Black ? "將" : "帥";
        case Silver:
            return pieceColour == Black ? "士" : "仕";
        case Rook:
            return pieceColour == Black ? "車" : "俥";
        case Cannon:
            return pieceColour == Black ? "砲" : "炮";
        case Knight:
            return pieceColour == Black ? "馬" : "傌";
        case Elephant:
            return pieceColour == Black ? "象" : "相";
        case Pawn:
            return pieceColour == Black ? "卒" : "兵";
        default:
            return "";
        }
    }
    else if (gameVariant == KoShogi)
    {
        switch (pieceType)
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
    if (gameVariant == WaShogi || gameVariant == CrazyWa)
    {
        switch (pieceType)
        {
        case King:
            return "靏玉";
        case Rook:
            return "燕行";
        case Lance:
            return "牛車";
        case Tokin:
            return "金鳥";
        case Pawn:
            return "萑歩";
        case SideMover:
            return "燕羽";
        case PloddingOx:
            return "歬牛";
        case LiberatedHorse:
            return "風馬";
        case HeavenlyHorse:
            return "天馬";
        case SwoopingOwl:
            return "鴟行";
        case CloudEagle:
            return "雲鷲";
        case StruttingCrow:
            return "烏行";
        case FlyingFalcon:
            return "飛鷹";
        case FlyingCock:
            return "鶏飛";
        case RaidingFalcon:
            return "延鷹";
        case FlyingGoose:
            return "鳫飛";
        case ClimbingMonkey:
            return "登猿";
        case Silver:
            return "猛鹿";
        case Dog:
            return "盲犬";
        case Gold:
            return "猛狼";
        case Elephant:
            return "行猪";
        case BearEyes:
            return "熊眼";
        case RunningRabbit:
            return "走兎";
        case TreacherousFox:
            return "隠狐";
        case TenaciousFalcon:
            return "奚力 鷹";
        default:
            return "";
        }
    }
    else if (gameVariant == ToriShogi)
    {
        switch (pieceType)
        {
        case King:
            return "鵬";
        case Falcon:
            return "鷹";
        case Eagle:
            return "鵰";
        case Crane:
            return "鶴";
        case Pheasant:
            return "雉";
        case LeftQuail:
        case RightQuail:
            return "鶉";
        case Pawn:
            return "燕";
        case Goose:
            return "鴈";
        default:
            return "";
        }
    }
    else
    {
        switch (pieceType)
        {
        case King:
            return pieceColour == White ? "王" : "玉";
        case Prince:
            return "太";
        case Lion:
            return "獅";
        case Queen:
            return "奔";
        case DragonKing:
            return "竜";
        case DragonHorse:
            return "馬";
        case Rook:
            return "飛";
        case Bishop:
            return "角";
        case VerticalMover:
            return "竪";
        case SideMover:
            return "横";
        case ReverseChariot:
            return "反";
        case Lance:
            return "香";
        case Kylin:
            return "麒";
        case Phoenix:
            return "鳳";
        case Elephant:
            return "酔";
        case Tiger:
            return "虎";
        case Gold:
            return "金";
        case Tokin:
            return "と";
        case Silver:
            return "銀";
        case Copper:
            return "銅";
        case Leopard:
            return "豹";
        case GoBetween:
            return "仲";
        case Pawn:
            return "歩";
        case Eagle:
            return "鷲";
        case Unicorn:
            return "鷹";
        case FlyingOx:
            return "牛";
        case FreeBoar:
            return "猪";
        case FlyingStag:
            return "鹿";
        case WhiteHorse:
            return "駒";
        case Whale:
            return "鯨";
        case PromotedLance:
            return "杏";
        case PromotedKnight:
            return "圭";
        case PromotedSilver:
            return "全";
        case Iron:
            return "鉄";
        case Stone:
            return "石";
        case AngryBoar:
            return "猪";
        case ViolentOx:
            return "牛";
        case FlyingDragon:
            return "龍";
        case EvilWolf:
            return "狼";
        case CatSword:
            return "猫";
        case Knight:
            return "桂";
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
        case Tengu:
            return "天狗";
        case OldKite:
            return "古鵄";
        case PoisonousSnake:
            return "毒蛇";
        case GreatElephant:
            return "大象";
        case WesternBarbarian:
            return "西戎";
        case EasternBarbarian:
            return "東夷";
        case SouthernBarbarian:
            return "南蛮";
        case NorthernBarbarian:
            return "北狄";
        case FragrantElephant:
            return "香象";
        case WhiteElephant:
            return "白象";
        case FreeDreamEater:
            return "奔獏";
        case FreeDemon:
            return "奔鬼";
        case WaterBuffalo:
            return "水";
        case RushingBird:
            return "行鳥";
        case StandardBearer:
            return "前旗";
        case FlyingHorse:
            return "馬麟";
        case NeighboringKing:
            return "近王";
        case BlindMonkey:
            return "盲猿";
        case Dove:
            return "鳩槃";
        case EnchantedBadger:
            return "変狸";
        case EnchantedFox:
            return "変狐";
        case RacingChariot:
            return "走車";
        case SquareMover:
            return "方行";
        case PrancingStag:
            return "踊鹿";
        case WhiteTiger:
            return "白虎";
        case BlueDragon:
            return "青龍";
        case HowlingDog:
            return "𠵇犬";
        case ViolentBear:
            return "猛熊";
        case LeftGeneral:
            return "左将";
        case RightGeneral:
            return "右将";
        case SavageTiger:
            return "猛虎";
        case Wood:
            return "木";
        case ViceGeneral:
            return "副";
        case GreatGeneral:
            return "大";
        case BishopGeneral:
            return "用";
        case RookGeneral:
            return "升";
        case MultiGeneral:
            return "雜";
        case Dog:
            return "犬";
        case FreeEagle:
            return "就";
        case LionHawk:
            return "師";
        case SideSoldier:
            return "黄";
        case VerticalSoldier:
            return "立";
        case ChariotSoldier:
            return "車";
        case HeavenlyTetrarch:
            return "天";
        case FireDemon:
            return "火";
        default:
            return "";
        }
    }
}

std::string StringManager::PieceType2GHCode(GameVariant gameVariant, PieceType pieceType, PieceType basePieceType)
{
    switch (pieceType)
    {
    case King:
        return "CK";
    case Rook:
        return "+SW";
    case Lance:
        return "OC";
    case Tokin:
        return "+SP";
    case Pawn:
        return "SP";
    case SideMover:
        return basePieceType == FlyingGoose ? "+FG" : "SW";
    case PloddingOx:
        return "+OC";
    case LiberatedHorse:
        return "LH";
    case HeavenlyHorse:
        return "+LH";
    case SwoopingOwl:
        return "SO";
    case CloudEagle:
        return basePieceType == SwoopingOwl ? "+SO" : "CE";
    case StruttingCrow:
        return "SC";
    case FlyingFalcon:
        return basePieceType == StruttingCrow ? "+SC" : "FF";
    case FlyingCock:
        return "FC";
    case RaidingFalcon:
        return "+FC";
    case FlyingGoose:
        return "FG";
    case ClimbingMonkey:
        return "CM";
    case Silver:
        return basePieceType == ClimbingMonkey ? "+CM" : "VS";
    case Dog:
        return "BD";
    case Gold:
        return basePieceType == Dog ? "+BD" : "VW";
    case Elephant:
        return "+VS";
    case BearEyes:
        return "+VW";
    case RunningRabbit:
        return "RR";
    case TreacherousFox:
        return basePieceType == RunningRabbit ? "+RR" : "TF";
    case TenaciousFalcon:
        return "+FF";
    default:
        return "";
    }
}
