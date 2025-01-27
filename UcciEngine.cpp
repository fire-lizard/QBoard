#include "UcciEngine.h"

UcciEngine::UcciEngine()
{
	_fen = XIANGQIFEN;
}

UcciEngine::~UcciEngine()
{
	Quit();
}

void UcciEngine::SetFEN(std::string fen)
{
	_fen = std::move(fen);
	WriteToProcess("uccinewgame\n");
}

EngineProtocol UcciEngine::GetType()
{
	return UCCI;
}

void UcciEngine::StartGame(QString variant)
{
	_moves.clear();
	WriteToProcess("ucci\n");
	WriteToProcess("isready\n");
	WriteToProcess("uccinewgame\n");
}

QByteArray UcciEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
	if (x1 < 10)
	{
		moveStr.push_back(static_cast<char>(x1 + 97));
		moveStr.push_back(QString::number(y1)[0].toLatin1());
		moveStr.push_back(static_cast<char>(x2 + 97));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
	}
	else
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(x2);
		moveStr.push_back(y2);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
