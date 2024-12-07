#include "WbEngine.h"

WbEngine::WbEngine()
{
}

WbEngine::~WbEngine()
{
}

EngineProtocol WbEngine::GetType()
{
	return XBoard;
}

void WbEngine::StartGame(QString variant)
{
	_moves.clear();
	_process->write("xboard\n");
	if (variant != "")
	{
		const QString str = "variant " + variant + "\n";
		_process->write(str.toLatin1());
	}
	_process->write("new\n");
}

void WbEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_process->write(AddMove(x1, y1, x2, y2, promotion));
	_process->write("\n");
}

QByteArray WbEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
	if (y1 < 10)
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
	if (promotion == 'n' || promotion == 'b' || promotion == 'r' || promotion == 'q' || promotion == '+')
	{
		moveStr.push_back(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
