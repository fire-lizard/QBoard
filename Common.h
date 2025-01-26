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
	VerticalMover = 9, SideMover = 10, Cannon = 11, Lance = 12, Kylin = 13, Phoenix = 14, Elephant = 15, Prince = 16,
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
	HeavenlyTetrarch = 69, FireDemon = 70
};

enum Direction
{
	NorthWest, North, NorthEast, East, SouthEast, South, SouthWest, West
};

inline char CHESSFEN[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

inline char XIANGQIFEN[] = "rheakaehr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RHEAKAEHR w - - 0 1";

inline char SHOGIFEN[] = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL w - 1";

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