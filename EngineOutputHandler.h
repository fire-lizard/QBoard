#pragma once
#include <QRegularExpression>
#include "Common.h"
#include "WbEngine.h"
#include "ChessBoard.h"
#include "XiangqiBoard.h"
#include "ShogiBoard.h"
#include "MakrukBoard.h"
#include "XiangqiPiece.h"
#include "WaShogiPiece.h"
#include "ChuShogiPiece.h"

struct Move
{
	int x1, y1, x2, y2;
};

class EngineOutputHandler
{
public:
	static std::pair<int, int> GetPieceLocation(const Board* board, PieceType pieceType, PieceColour pieceColour);
	static QByteArray ExtractMove(const QByteArray& buf, EngineProtocol engineProtocol, GameVariant gameVariant);
	static Move ByteArrayToMove(QByteArray moveArray, EngineProtocol engineProtocol, GameVariant gameVariant, int width, int height);
	static QByteArray MoveToByteArray(Move m, EngineProtocol engineProtocol, GameVariant gameVariant, int width, int height);
	static void ReadStandardOutput(const QByteArray& buf, const std::shared_ptr<Engine>& engine, Board* board, QTextEdit* textEdit,
		GameVariant gameVariant, EngineOutput engineOutput, PieceColour currentPlayer);
	static void ReadStandardError(const QByteArray& buf, QTextEdit* textEdit);
	static void AddMove(Board* board, GameVariant gameVariant, PieceType p, int x1, int y1, int x2, int y2, int x3, int y3);
	static QString SetFenToBoard(Board* board, const QByteArray& str, GameVariant gameVariant);
};

