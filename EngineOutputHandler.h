#pragma once
#include <QRegularExpression>
#include "Common.h"
#include "WbEngine.h"
#include "stringmanager.h"
#include "ChessBoard.h"
#include "XiangqiBoard.h"
#include "ShogiBoard.h"
#include "MakrukBoard.h"
#include "SittuyinBoard.h"
#include "TenjikuShogiBoard.h"

struct Move
{
	int x1, y1, x2, y2;
};

class EngineOutputHandler
{
public:
	static QByteArray ExtractMove(const QByteArray& buf, EngineProtocol engineProtocol, GameVariant gameVariant);
    static Move ByteArrayToMove(QByteArray moveArray, EngineProtocol engineProtocol, int width, int height);
	static QByteArray MoveToByteArray(Move m, EngineProtocol engineProtocol, int width, int height);
	static QByteArray KoShogiShootToText(const QByteArray& moveArray);
	static void ReadStandardOutput(const QByteArray& buf, const std::shared_ptr<Engine>& engine, Board* board, QTextEdit* textEdit,
		GameVariant gameVariant, EngineOutput engineOutput, PieceColour currentPlayer);
	static void ReadStandardError(const QByteArray& buf, QTextEdit* textEdit);
	static void AddMove(Board* board, GameVariant gameVariant, PieceType p, int x1, int y1, int x2, int y2, int x3, int y3);
	static PieceType PieceTypeAt(const Board* board, int x, int y);
	static QString SetFenToBoard(Board* board, const QByteArray& str, GameVariant gameVariant);
	static QString GetFenFromBoard(Board* board, GameVariant gameVariant, PieceColour sideToMove);
	static bool HasHoldingsField(GameVariant gameVariant);
	static void CalculateCheck(Board* board, PieceColour pieceColour, std::vector<std::pair<int, int>>& moves, int oldX, int oldY, int newX, int newY);
    static void CalculateXiangqiCheck(Board* board, std::vector<std::pair<int, int>>& moves, int oldX, int oldY, int newX, int newY);
    static std::vector<std::pair<int, int>> GetPieceLocations(const Board* board, PieceType pieceType, PieceColour pieceColour);
	static bool IsInsidePromotionZone(GameVariant gameVariant, PieceColour pieceColour, int y);
	static bool CanBePromoted(const std::optional<Piece>& piece, GameVariant gameVariant, int oldY, int newY);
	static bool IsLionMove(const std::optional<Piece>& piece, int x1, int y1, int x2, int y2);
    static void RollbackIllegalMove(GameVariant gameVariant, Board *board, std::vector<BoardSnapshot>& history);
	static void RemoveMove(std::vector<std::pair<int, int>>& moves, int x, int y);
	static int  GetEnPassantRank(GameVariant gameVariant, PieceColour pieceColour, char y);
	static char ChessPieceChar(PieceType chessPiece);
	static char MusketeerPieceChar(PieceType musketeerPiece);
	static qsizetype CutAtLastCompleteMove(const QByteArray& buffer);
	static Move CastlingToMove(const QByteArray& c, const Board* board, PieceColour currentPlayer);
	static bool IsCastling(const QByteArray& moveArray, const Board* board, GameVariant gameVariant,
		int x1, int y1, int x2, int y2);
	static void PromoteIfUnmarked(Board* board, GameVariant gameVariant, int x2, int y2);
	static bool HasPromotion(const std::optional<Piece>& piece, GameVariant gameVariant);
	static bool RelayMove(const std::shared_ptr<Engine>& to, const QByteArray& moveArray, const Move& castling,
		const Board* board, GameVariant gameVariant);
	static std::pair<int, int> CastlingTargets(GameVariant gameVariant, int kingX, int rookX);
	static int EngineRank(GameVariant gameVariant, int height, int y);

private:
	static int ApplyCastling(Board* board, GameVariant gameVariant, int x1, int y1, int x2);
	template <typename T> static std::basic_string<T> lowercase(const std::basic_string<T>& s);
	template <typename T> static std::basic_string<T> uppercase(const std::basic_string<T>& s);
};
