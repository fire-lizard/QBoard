#pragma once

enum EngineProtocol
{
	XBoard, UCI, UCCI, Qianhong, USI
};

enum GameFormat
{
	PGN, WXF, PSN, CSA, KIF
};

enum GameVariant
{
	Chess, Xiangqi, Shatranj, Makruk, Shogi, ShoShogi, ChuShogi, DaiShogi, MiniShogi, JudkinShogi, WaShogi, CrazyWa, TenjikuShogi
};

enum PieceColour
{
	White, Black
};

enum PieceStyle
{
	European, Asian, Mnemonic
};

enum EngineOutput
{
	Concise, Verbose
};

enum PieceType
{
	None = 0, King = 1, Lion = 2, Queen = 3, DragonKing = 4, DragonHorse = 5, Rook = 6, Bishop = 7, Knight = 8,
	VerticalMover = 9, SideMover = 10, ReverseChariot = 11, Lance = 12, Kylin = 13, Phoenix = 14, Elephant = 15, Prince = 16,
	Tiger = 17, Gold = 18, Silver = 19, Copper = 20, Leopard = 21, GoBetween = 22, Pawn = 23,
	Eagle = 24, Unicorn = 25, FlyingOx = 26, FreeBoar = 27, FlyingStag = 28, WhiteHorse = 29, Whale = 30,
	// Promoted Shogi pieces
	PromotedLance = 31, PromotedKnight = 32, PromotedSilver = 33, Tokin = 34,
	// Dai Shogi pieces
	ViolentOx = 35, FlyingDragon = 36, AngryBoar = 37, CatSword = 38, EvilWolf = 39, Iron = 40, Stone = 41,
	// Wa Shogi pieces
	PloddingOx = 42, LiberatedHorse = 43, HeavenlyHorse = 44, SwoopingOwl = 45, CloudEagle = 46,
	StruttingCrow = 47, FlyingFalcon = 48, FlyingCock = 49, RaidingFalcon = 50, FlyingGoose = 51,
	ClimbingMonkey = 52, Dog = 53, BearEyes = 54, RunningRabbit = 55, TreacherousFox = 56, TenaciousFalcon = 57,
	// Tenjiku Shogi pieces
	ViceGeneral = 58, GreatGeneral = 59, BishopGeneral = 60, RookGeneral = 61, MultiGeneral = 62,
	FreeEagle = 63, LionHawk = 64, SideSoldier = 65, VerticalSoldier = 66, ChariotSoldier = 67, WaterBuffalo = 68,
	HeavenlyTetrarch = 69, FireDemon = 70,
	// Dai Dai Shogi Pieces
	BlindMonkey = 71, BlueDragon = 72, Dove = 73, EasternBarbarian = 74, WesternBarbarian = 75, SouthernBarbarian = 76, NorthernBarbarian = 77,
	EnchantedBadger = 78, EnchantedFox = 79, FragrantElephant = 80, FreeDemon = 81, FreeDreamEater = 82, FuriousFiend = 83, GoldenBird = 84,
	GreatDragon = 85, GreatElephant = 86, HowlingDog = 87, LeftGeneral = 88, RightGeneral = 89,	Tengu = 90, NeighboringKing = 91, OldKite = 92,
	PoisonousSnake = 93, PrancingStag = 94, RacingChariot = 95, RushingBird = 96, SavageTiger = 97, Yaksha = 98, SquareMover = 99, StandardBearer = 100,
	ViolentBear = 101, WhiteElephant = 102, WhiteTiger = 103, MountainWitch = 104, WizardStork = 105, Wood = 106, LionDog = 107,
	// Maka Dai Dai Shogi Pieces
	Deva = 108, DarkSpirit = 109, Tile = 110, Earth = 111, CoiledSerpent = 112, RecliningDragon = 113, ChineseCock = 114, OldMonkey = 115,
	BlindBear = 116, Wrestler = 117, Guardian = 118, BuddhistDevil = 119, OldRat = 120, Donkey = 121, Capricorn = 122, HookMover = 123,
	SideFlier = 124, LeftChariot = 125, RightChariot = 126, Emperor = 127, TeachingKing = 128, FreeGold = 129, FreeSilver = 130,
	FreeCopper = 131, FreeIron = 132, FreeTile = 133, FreeStone = 134, FreeEarth = 135, FreeTiger = 136, FreeLeopard = 137, FreeSerpent = 138,
	FreeDragon = 139, FreeWolf = 140, FreeCat = 141, FreeBear = 142, Bat = 143,
	// Ko Shogi Pieces
	MiddleTroop = 144, Drum = 145, Thunderclap = 146, Banner = 147, FlagWaver = 148, VillageBrigade = 149,
	ViceCommander = 150, PoisonFlame = 151, SumoWrestler = 152, DoubleKylin = 153, DoublePhoenix = 154, TaoistPriest = 155, SpiritualMonk = 156,
	FiveLiFog = 157, ImmaculateLight = 158, AdvanceGuard = 159, RearGuard = 160, SkywardNet = 161, EarthwardNet = 162, DragonAscending = 163,
	Quartermaster = 164, TigerWing = 165, WarHawk = 166, Longbow = 167, LongbowCavalryman = 168, Crossbow = 169, CrossbowCavalryman = 170,
	Cannon = 171, GunCarriage = 172, FrankishCannon = 173, ChariotOfTheGods = 174, Cavalry = 175, WingedHorse = 176, ShieldUnit = 177,
	Chariot = 178, Vanguard = 179
};

enum Direction
{
	NorthWest, North, NorthEast, East, SouthEast, South, SouthWest, West
};

inline PieceType KoShogiPieces[] = { King, Prince, Queen, Rook, Bishop, Gold, Silver, Copper, FlyingOx, FreeBoar, VerticalMover, DragonHorse, DragonKing,
									 CatSword, Leopard, FlyingStag, Tiger, Elephant, Phoenix, Kylin, Knight, MiddleTroop, Drum, Thunderclap, Banner, FlagWaver,
									 VillageBrigade, ViceCommander, PoisonFlame, SumoWrestler, DoubleKylin, DoublePhoenix, TaoistPriest, SpiritualMonk,
									 FiveLiFog, ImmaculateLight, AdvanceGuard, RearGuard, SkywardNet, EarthwardNet, DragonAscending, Quartermaster, TigerWing,
									 WarHawk, Longbow, LongbowCavalryman, Crossbow, CrossbowCavalryman, Cannon, GunCarriage, FrankishCannon, ChariotOfTheGods,
									 Cavalry, WingedHorse, ShieldUnit, Chariot, Vanguard };

inline PieceType MakaDaiDaiShogiPieces[] = { King, Gold, Silver, Copper, Iron, Tile, Stone, Earth, Elephant, Prince, Tiger, Leopard, CatSword, Lion,
											 Phoenix, Kylin, EvilWolf, AngryBoar, Queen, DragonHorse, DragonKing, Lance, ReverseChariot, FlyingDragon, ViolentOx,
											 Knight, Bishop, Rook, SideMover, VerticalMover, Pawn, Deva, DarkSpirit, Tile, Earth, CoiledSerpent,
											 RecliningDragon, ChineseCock, OldMonkey, BlindBear, Wrestler, Guardian, BuddhistDevil, OldRat, Donkey,
											 Capricorn, HookMover, SideFlier, LeftChariot, RightChariot, Emperor, TeachingKing, FreeGold, FreeSilver,
											 FreeCopper, FreeIron, FreeTile, FreeStone, FreeEarth, FreeTiger, FreeLeopard, FreeSerpent, FreeDragon,
											 FreeWolf, FreeCat, FreeBear, Bat };

inline PieceType DaiDaiShogiPieces[] = { King, Lion, WaterBuffalo, Queen, DragonHorse, DragonKing, CatSword, FlyingDragon, Phoenix, Kylin, Bishop, Rook,
										 SideMover, VerticalMover, ReverseChariot, ViolentOx, Lance, AngryBoar, Gold, Silver, Leopard, Copper, Iron, Stone, EvilWolf,
										 Pawn, BlindMonkey, BlueDragon, Dove, EasternBarbarian, WesternBarbarian, SouthernBarbarian, NorthernBarbarian,
										 EnchantedBadger, EnchantedFox, FragrantElephant, FreeDemon, FreeDreamEater, FuriousFiend, GoldenBird,
										 GreatDragon, GreatElephant, HookMover, HowlingDog, LeftChariot, RightChariot, LeftGeneral, RightGeneral,
										 Tengu, NeighboringKing, OldKite, OldRat, PoisonousSnake, PrancingStag, RacingChariot, RushingBird,
										 SavageTiger, Yaksha, SquareMover, StandardBearer, ViolentBear, WhiteElephant, WhiteTiger,
										 MountainWitch, WizardStork, Wood, LionDog };

inline PieceType WaShogiPieces[] = { Lance, Dog, StruttingCrow, FlyingGoose, Gold, King, Silver, FlyingCock, SwoopingOwl, ClimbingMonkey, LiberatedHorse,
									 FlyingFalcon, SideMover, CloudEagle, TreacherousFox, RunningRabbit, Pawn, Tokin, Rook, PloddingOx, HeavenlyHorse,
									 RaidingFalcon, Elephant, BearEyes, TenaciousFalcon };

inline PieceType ChuShogiPieces[] = { King, Lion, Queen, DragonKing, DragonHorse, Rook, Bishop, VerticalMover, SideMover, ReverseChariot, Lance, Kylin, Phoenix,
									  Elephant, Tiger, Leopard, Gold, Silver, Copper, GoBetween, Pawn, Tokin, Prince, Eagle, Unicorn, FlyingOx, FreeBoar,
									  FlyingStag, WhiteHorse, Whale };

inline PieceType DaiShogiPieces[] = { King, Lion, Queen, DragonKing, DragonHorse, Rook, Bishop, VerticalMover, SideMover, ReverseChariot, Lance, Kylin, Phoenix,
									  Elephant, Tiger, Leopard, Gold, Silver, Copper, GoBetween, Pawn, CatSword, EvilWolf, Iron, Stone, Tokin, Prince,
									  Eagle, Unicorn, FlyingOx, FreeBoar, FlyingStag, WhiteHorse, Whale, Knight, ViolentOx, FlyingDragon, AngryBoar };

inline PieceType TenjikuShogiPieces[] = { King, Lion, Queen, DragonKing, DragonHorse, Rook, Bishop, VerticalMover, SideMover, ReverseChariot, Lance, Kylin, Phoenix,
										  Elephant, Tiger, Leopard, Gold, Silver, Copper, GoBetween, Pawn, Tokin, Prince, Eagle, Unicorn, FlyingOx, FreeBoar,
										  FlyingStag, WhiteHorse, Whale, Dog, Knight, Iron, ViceGeneral, GreatGeneral, BishopGeneral, RookGeneral, MultiGeneral,
										  FreeEagle, LionHawk, SideSoldier, VerticalSoldier, ChariotSoldier, WaterBuffalo, HeavenlyTetrarch, FireDemon };

inline PieceType ChessPieces[] = { King, Queen, Bishop, Knight, Rook, Pawn };

inline PieceType ShatranjPieces[] = { King, Queen, Bishop, Knight, Rook, Pawn };

inline PieceType MakrukPieces[] = { King, Queen, Silver, Knight, Rook, Pawn };

inline PieceType XiangqiPieces[] = { King, Silver, Elephant, Knight, Rook, Cannon, Pawn };

inline PieceType ShogiPieces[] = { King, Gold, Silver, Knight, Lance, Rook, Bishop, Pawn,
								   PromotedLance, PromotedKnight, PromotedSilver, Tokin,
								   DragonHorse, DragonKing };

inline PieceType ShoShogiPieces[] = { King, Gold, Silver, Knight, Lance, Elephant, Rook, Bishop, Pawn,
									  PromotedLance, PromotedKnight, PromotedSilver, Tokin, Prince,
									  DragonHorse, DragonKing };

inline PieceType MiniShogiPieces[] = { King, Gold, Silver, Rook, Bishop, Pawn, PromotedSilver, Tokin, DragonHorse, DragonKing };

inline PieceType JudkinsShogiPieces[] = { King, Gold, Silver, Knight, Rook, Bishop, Pawn, PromotedKnight, PromotedSilver, Tokin, DragonHorse, DragonKing };

inline char CHESSFEN[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

inline char XIANGQIFEN[] = "rheakaehr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RHEAKAEHR w - - 0 1";

inline char SHOGIFEN[] = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL W - 1";

inline char MINISHOGIFEN[] = "rbsgk/4p/5/P4/KGSBR w";

inline char JUDKINSHOGIFEN[] = "rbnsgk/5p/6/6/P5/KGSNBR w";

inline char WASHOGIFEN[] = "hmlcvkwgudo/1e3s3f1/ppprpppxppp/3p3p3/11/11/11/3P3P3/PPPXPPPRPPP/1F3S3E1/ODUGWKVCLMH w";

inline char CHUSHOGIFEN[] = "lfcsgekgscfl/a1b1txot1b1a/mvrhdqndhrvm/pppppppppppp/3i4i3"
"/12/12/"
"3I4I3/PPPPPPPPPPPP/MVRHDNQDHRVM/A1B1TOXT1B1A/LFCSGKEGSCFL";

inline char DAISHOGIFEN[] = "lnuicsgkgsciunl/a1c'1f1tet1f1c'1a/1x'1a'1wxl!ow1a'1x'1/rf'mvbhdqdhbvmf'r/"
"ppppppppppppppp/4p'5p'4/15/15/15/4P'5P'4/PPPPPPPPPPPPPPP/"
"RF'MVBHDQDHBVMF'R/1X'1A'1WOL!XW1A'1X'1/A1C'1F1TET1F1C'1A/LNUICSGKGSCIUNL";

inline char TENJIKUSHOGIFEN[] = "lnficsgekgscifnl/a1c!c!1txql!ot1c!c!1a/s'v'bhdw!d!q'h!d!w!dhbv's'/"
"mvrf!e!b!r!v!q!r!b!e!f!rvm/pppppppppppppppp/4d6d4/"
"16/16/16/16/"
"4D6D4/PPPPPPPPPPPPPPPP/MVRF!E!B!R!Q!V!R!B!E!F!RVM/"
"S'V'BHDW!D!H!Q'D!W!DHBV'S'/A1C!C!1TOL!QXT1C!C!1A/LNFICSGKEGSCIFNL";

inline char SHOSHOGIFEN[] = "lnsgkgsnl/1r2e2b1/ppppppppp/9/9/9/PPPPPPPPP/1B2E2R1/LNSGKGSNL";

inline char SHATRANJFEN[] = "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR";

inline char MAKRUKFEN[] = "rnsmksnr/8/pppppppp/8/8/PPPPPPPP/8/RNSKMSNR";