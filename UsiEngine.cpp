#include "UsiEngine.h"

UsiEngine::UsiEngine()
{
}

UsiEngine::~UsiEngine()
{
}

EngineType UsiEngine::GetType()
{
	return USI;
}

void UsiEngine::StartGame(QString variant)
{
	_process->write("usi\n");
	_process->write("usinewgame\n");
}

void UsiEngine::Move(int x1, int y1, int x2, int y2, char promotion)
{
	char moveStr[6];
	moveStr[0] = char(x1 + 97);
	moveStr[1] = QString::number(y1)[0].toLatin1();
	moveStr[2] = char(x2 + 97);
	moveStr[3] = QString::number(y2)[0].toLatin1();
	moveStr[4] = promotion != ' ' ? promotion : '\n';
	moveStr[5] = '\n';
	_process->write("position moves ", 15);
	_process->write(moveStr, promotion != ' ' ? 6 : 5);
	_process->write("go movetime 1000\n", 17);
}
