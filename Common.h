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
	Chess, Xiangqi, Shatranj, Makruk, Shogi, ShoShogi, ChuShogi, DaiShogi, MiniShogi,
	JudkinShogi, WaShogi, CrazyWa, TenjikuShogi, DaiDaiShogi, MakaDaiDaiShogi, KoShogi
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
	None, King, Lion, Queen, DragonKing, DragonHorse, Rook, Bishop, Knight, VerticalMover, SideMover, ReverseChariot, Lance, Kylin, Phoenix,
	Elephant, Prince, Tiger, Gold, Silver, Copper, Leopard, GoBetween, Pawn, Eagle, Unicorn, FlyingOx, FreeBoar, FlyingStag, WhiteHorse, Whale,
	// Promoted Shogi pieces
	PromotedLance, PromotedKnight, PromotedSilver, Tokin,
	// Dai Shogi pieces
	ViolentOx, FlyingDragon, AngryBoar, CatSword, EvilWolf, Iron, Stone,
	// Wa Shogi pieces
	PloddingOx, LiberatedHorse, HeavenlyHorse, SwoopingOwl, CloudEagle, StruttingCrow, FlyingFalcon, FlyingCock, RaidingFalcon, FlyingGoose,
	ClimbingMonkey, Dog, BearEyes, RunningRabbit, TreacherousFox, TenaciousFalcon,
	// Tenjiku Shogi pieces
	ViceGeneral, GreatGeneral, BishopGeneral, RookGeneral, MultiGeneral, FreeEagle, LionHawk, SideSoldier, VerticalSoldier, ChariotSoldier,
	WaterBuffalo, HeavenlyTetrarch, FireDemon,
	// Dai Dai Shogi Pieces
	BlindMonkey, BlueDragon, Dove, EasternBarbarian, WesternBarbarian, SouthernBarbarian, NorthernBarbarian, EnchantedBadger, EnchantedFox,
	FragrantElephant, FreeDemon, FreeDreamEater, FuriousFiend, GoldenBird, GreatElephant, HowlingDog, LeftGeneral, RightGeneral, Tengu,
	NeighboringKing, OldKite, PoisonousSnake, PrancingStag, RacingChariot, RushingBird, SavageTiger, Yaksha, SquareMover, StandardBearer,
	ViolentBear, WhiteElephant, WhiteTiger, Wood, FlyingHorse,
	// Maka Dai Dai Shogi Pieces
	GreatDragon, MountainWitch, WizardStork, LionDog, Deva, DarkSpirit, Tile, Earth, CoiledSerpent, RecliningDragon, ChineseCock, BuddhistDevil,
	OldMonkey, BlindBear, Wrestler, Guardian, BuddhistSpirit, OldRat, Donkey, Capricorn, HookMover, SideFlier, LeftChariot, RightChariot, Emperor,
	TeachingKing, FreeGold, FreeSilver, FreeCopper, FreeIron, FreeTile, FreeStone, FreeEarth, FreeGo, FreeTiger, FreeLeopard, FreeSerpent,
	FreeDragon, FreeWolf, FreeCat, FreeBear, Bat,
	// Ko Shogi Pieces
	MiddleTroop, Drum, Thunderclap, Flag, RoamingAssault, CompanyCommander, ViceCommissioner, PoisonFlame, DoubleKylin, DoublePhoenix, TaoistPriest,
	SpiritualMonk, ExtensiveFog, HolyLight, AdvanceGuard, RearGuard, SkywardNet, EarthwardNet, RisingDragon, Quartermaster, WingedTiger, FlyingHawk,
	Longbow, LongbowKnight, Crossbow, CrossbowKnight, Cannon, CannonCarriage, FrankishCannon, DivineCarriage, KnightCaptain, WingedHorse, ShieldCaptain,
	Chariot, Vanguard
};

enum Direction
{
	NorthWest, North, NorthEast, East, SouthEast, South, SouthWest, West
};

inline GameVariant shogiVariants[] = { Shogi, MiniShogi, JudkinShogi, ChuShogi, DaiShogi, ShoShogi, WaShogi,
									   CrazyWa, TenjikuShogi, DaiDaiShogi, MakaDaiDaiShogi, KoShogi };
inline PieceType lionPieces[] = { Lion, Eagle, Unicorn, LionHawk, FreeEagle, LionDog, TeachingKing, BuddhistSpirit, FuriousFiend, GreatElephant, RoamingAssault };

inline PieceType KoShogiPieces[] = { King, Prince, Queen, Rook, Bishop, Gold, Silver, Copper, FlyingOx, FreeBoar, VerticalMover, DragonHorse, DragonKing, Pawn,
									 CatSword, Leopard, FlyingStag, Tiger, Elephant, Phoenix, Kylin, Knight, MiddleTroop, Drum, Thunderclap, Flag, RoamingAssault,
									 CompanyCommander, ViceCommissioner, PoisonFlame, Lion, DoubleKylin, DoublePhoenix, TaoistPriest, SpiritualMonk,
									 ExtensiveFog, HolyLight, AdvanceGuard, RearGuard, SkywardNet, EarthwardNet, RisingDragon, Quartermaster, WingedTiger,
									 FlyingHawk, Longbow, LongbowKnight, Crossbow, CrossbowKnight, Cannon, CannonCarriage, FrankishCannon, DivineCarriage,
									 KnightCaptain, WingedHorse, ShieldCaptain, Chariot, Vanguard };

inline PieceType MakaDaiDaiShogiPieces[] = { King, Gold, Silver, Copper, Iron, Tile, Stone, Earth, Elephant, Prince, Tiger, Leopard, CatSword, Lion,
											 Phoenix, Kylin, EvilWolf, AngryBoar, Queen, DragonHorse, DragonKing, Lance, ReverseChariot, FlyingDragon,
											 Knight, Bishop, Rook, SideMover, VerticalMover, Pawn, Deva, DarkSpirit, CoiledSerpent, FuriousFiend,
											 RecliningDragon, ChineseCock, OldMonkey, BlindBear, Wrestler, Guardian, BuddhistSpirit, OldRat, Donkey,
											 Capricorn, HookMover, SideFlier, LeftChariot, RightChariot, Emperor, TeachingKing, FreeGold, FreeSilver,
											 FreeCopper, FreeIron, FreeTile, FreeStone, FreeEarth, FreeTiger, FreeLeopard, FreeSerpent, FreeDragon,
											 FreeWolf, FreeCat, FreeBear, FreeGo, Bat, MountainWitch, WizardStork, LionDog, GreatDragon, GoBetween,
											 GoldenBird, ViolentOx, Yaksha };

inline PieceType DaiDaiShogiPieces[] = { King, Lion, WaterBuffalo, Queen, DragonHorse, DragonKing, CatSword, FlyingDragon, Phoenix, Kylin, Bishop, Rook,
										 SideMover, VerticalMover, ReverseChariot, ViolentOx, Lance, AngryBoar, Gold, Silver, Leopard, Copper, Iron,
										 Stone, EvilWolf, Pawn, BlindMonkey, BlueDragon, Dove, EasternBarbarian, WesternBarbarian, SouthernBarbarian,
										 NorthernBarbarian, EnchantedBadger, EnchantedFox, FragrantElephant, FreeDemon, FreeDreamEater, FuriousFiend,
										 GoldenBird, GreatDragon, GreatElephant, HookMover, HowlingDog, LeftChariot, RightChariot, LeftGeneral, RightGeneral,
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