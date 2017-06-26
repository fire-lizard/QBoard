#include "WbEngine.h"

WbEngine::WbEngine()
{
}

WbEngine::~WbEngine()
{
}

EngineType WbEngine::GetType()
{
	return WinBoard;
}

void WbEngine::StartGame(QString variant)
{
	_process->write("xboard\n");
	_process->write("new\n");
	if (variant != "")
	{
		QString str = "variant " + variant + "\n";
		_process->write(str.toLatin1());
	}
}

void WbEngine::Move(int x1, int y1, int x2, int y2, char promotion)
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
