#pragma once
#include <queue>
#include <set>
#include "Common.h"
#include "TenjikuShogiBoard.h"
#include "KoShogiPiece.h"
#include "EngineOutputHandler.h"

inline PieceType StepMovers[15] = { King,Gold,Elephant,Silver,Leopard,Copper,MiddleTroop,Drum,Flag,Tiger,FrankishCannon,Longbow,Crossbow,CatSword,Pawn };
inline PieceType ShootingPieces[12] = { FrankishCannon,DivineCarriage,Longbow,LongbowKnight,Crossbow,CrossbowKnight,
									   Cannon,CannonCarriage,TaoistPriest,SpiritualMonk,ExtensiveFog,HolyLight};

class KoShogiBoard : public DaiShogiBoard
{
public:
	KoShogiBoard();
	~KoShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
	std::vector<std::pair<int, int>> GetShoots(const Piece* piece, int x, int y);
	bool IsShootPossible(int x, int y);
	void Shoot(int x, int y);
	void RemoveShoot(int x, int y);
	bool IsTaoistPlayerCaptured() const;

private:
	void CheckShoot(const Piece* piece, int x, int y);
	void CheckShootingDirection(const Piece* piece, int x, int y, Direction direction, int count, bool shootOver);
	void GetPossibleMoves(int x, int y);
	void getAll5StepPaths(int startR, int startC, PieceColour pieceColour);
	void dfsFiveSteps(int r, int c, int step, PieceColour pieceColour, std::vector<std::pair<int, int>>& currentPath);
	std::vector<std::pair<int, int>> getSinglePieceMoves(int r, int c, const std::vector<std::pair<int, int>>& offsets, PieceColour pieceColour) const;
	void getAllPiece2MoveDestinations(int startR, int startC, const std::vector<std::pair<int, int>>& offsets, PieceColour pieceColour);

	std::vector<std::pair<int, int>> _shoots;
	bool _taoistPriestCaptured = false;

	inline static const std::vector<std::pair<int, int>> _knightOffsets =
	{
		{+2, +1}, {+2, -1}, {-2, +1}, {-2, -1},
		{+1, +2}, {+1, -2}, {-1, +2}, {-1, -2}
	};

	inline static const std::vector<std::pair<int, int>> _kylynOffsets =
	{
		{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1},
		{+0, +2}, {+0, -2}, {-2, +0}, {+2, +0}
	};

	inline static const std::vector<std::pair<int, int>> _phoenixOffsets =
	{
		{-1, +0}, {+1, +0}, {+0, -1}, {+0, +1},
		{+2, +2}, {+2, -2}, {-2, +2}, {-2, -2}
	};

	PieceType _initialSetup[19][19] = {
	{AdvanceGuard, TaoistPriest, Copper, Leopard, Silver, Gold, Lion, Elephant, Phoenix, King, Kylin, Elephant, Lion, Gold, Silver, Leopard, Copper, SpiritualMonk, AdvanceGuard},
	{RearGuard, DragonHorse, None, DragonKing, None, Queen, None, Tiger, Flag, MiddleTroop, Drum, Tiger, None, Queen, None, DragonKing, None, DragonHorse, RearGuard},
	{Bishop, Cannon, Crossbow, Longbow, Bishop, Cannon, Crossbow, Longbow, Bishop, FrankishCannon, Bishop, Longbow, Crossbow, Cannon, Bishop, Longbow, Crossbow, Cannon, Bishop},
	{KnightCaptain, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, KnightCaptain},
	{None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None},
	{Rook, ShieldCaptain, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldCaptain, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldCaptain, Rook},
	{None, None, None, None, None, None, None, None, None, Vanguard, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, Vanguard, None, None, None, None, None, None, None, None, None},
	{Rook, ShieldCaptain, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldCaptain, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldCaptain, Rook},
	{None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None},
	{KnightCaptain, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, KnightCaptain},
	{Bishop, Cannon, Crossbow, Longbow, Bishop, Cannon, Crossbow, Longbow, Bishop, FrankishCannon, Bishop, Longbow, Crossbow, Cannon, Bishop, Longbow, Crossbow, Cannon, Bishop},
	{RearGuard, DragonHorse, None, DragonKing, None, Queen, None, Tiger, Drum, MiddleTroop, Flag, Tiger, None, Queen, None, DragonKing, None, DragonHorse, RearGuard},
	{AdvanceGuard, SpiritualMonk, Copper, Leopard, Silver, Gold, Lion, Elephant, Kylin, King, Phoenix, Elephant, Lion, Gold, Silver, Leopard, Copper, TaoistPriest, AdvanceGuard},
	};
};

