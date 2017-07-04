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
	_process->write(AddMove(x1, y1, x2, y2, promotion));
	_process->write("\n", 1);
}

QByteArray WbEngine::AddMove(int x1, int y1, int x2, int y2, char promotion)
{
	QByteArray moveStr;
	moveStr.push_back(char(x1 + 97));
	moveStr.push_back(QString::number(y1)[0].toLatin1());
	moveStr.push_back(char(x2 + 97));
	moveStr.push_back(QString::number(y2)[0].toLatin1());
	if (promotion == 'n' || promotion == 'b' || promotion == 'r' || promotion == 'q' || promotion == '+')
	{
		moveStr.push_back(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
