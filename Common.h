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
	VerticalMover = 9, SideMover = 10, Cannon = 11, Lance = 12, Kylin = 13, Phoenix = 14, Elephant = 15,
	Tiger = 16, Gold = 17, Silver = 18, Copper = 19, Leopard = 20, GoBetween = 21, Pawn = 22,
	Eagle = 23, Unicorn = 24, FlyingOx = 25, FreeBoar = 26, FlyingStag = 27, WhiteHorse = 28, Whale = 29,
	// Promoted Shogi pieces
	PromotedLance = 30, PromotedKnight = 31, PromotedSilver = 32, Tokin = 33,
	// Dai Shogi pieces
	ViolentOx = 34, FlyingDragon = 35, AngryBoar = 36, CatSword = 37, EvilWolf = 38, Iron = 39, Stone = 40,
	// Wa Shogi pieces
	PloddingOx = 41, LiberatedHorse = 42, HeavenlyHorse = 43, SwoopingOwl = 44, CloudEagle = 45,
	StruttingCrow = 46, FlyingFalcon = 47, FlyingCock = 48, RaidingFalcon = 49, FlyingGoose = 50,
	ClimbingMonkey = 51, Dog = 52, BearEyes = 53, RunningRabbit = 54, TreacherousFox = 55, TenaciousFalcon = 56,
	// Tenjiku Shogi pieces
	ViceGeneral = 57, GreatGeneral = 58, BishopGeneral = 59, RookGeneral = 60, MultiGeneral = 61,
	FreeEagle = 62, LionHawk = 63, SideSoldier = 64, VerticalSoldier = 65, ChariotSoldier = 66, WaterBuffalo = 67,
	HeavenlyTetrarch = 68, FireDemon = 69
};

enum Direction
{
	NorthWest, North, NorthEast, East, SouthEast, South, SouthWest, West
};

inline char CHESSFEN[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

inline char XIANGQIFEN[] = "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1";

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