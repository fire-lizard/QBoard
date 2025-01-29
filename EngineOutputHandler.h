#pragma once
#include <QRegularExpression>
#include "Common.h"
#include "WbEngine.h"
#include "ChessBoard.h"
#include "XiangqiBoard.h"
#include "ShogiBoard.h"
#include "MakrukBoard.h"

class EngineOutputHandler
{
public:
    static QByteArray ExtractMove(const QByteArray& buf, EngineProtocol engineProtocol, GameVariant gameVariant);
	static void ReadStandardOutput(const QByteArray& buf, std::shared_ptr<Engine> engine, Board* board, QTextEdit* textEdit,
		GameVariant gameVariant, EngineOutput engineOutput, PieceColour currentPlayer);
	static void ReadStandardError(const QByteArray& buf, QTextEdit* textEdit);
	static void AddMove(Board* board, GameVariant gameVariant, PieceType p, int x1, int y1, int x2, int y2, int x3, int y3);
};

