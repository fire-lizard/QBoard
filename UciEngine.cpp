#include "UciEngine.h"

UciEngine::UciEngine()
{
}

UciEngine::~UciEngine()
{
}

EngineType UciEngine::GetType()
{
	return UCI;
}

void UciEngine::StartGame(QString variant)
{
	_process->write("uci\n");
	_process->write("ucinewgame\n");
}

void UciEngine::Move(int x1, int y1, int x2, int y2, char promotion)
{
	char moveStr[6];
	moveStr[0] = char(x1 + 97);
	moveStr[1] = QString::number(y1)[0].toLatin1();
	moveStr[2] = char(x2 + 97);
	moveStr[3] = QString::number(y2)[0].toLatin1();
	moveStr[4] = promotion != ' ' ? promotion : '\n';
	moveStr[5] = '\n';
	_process->write(moveStr, promotion != ' ' ? 6 : 5);
}
