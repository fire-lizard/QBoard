#include "ChuShogiEngine.h"

ChuShogiEngine::ChuShogiEngine()
{
}

ChuShogiEngine::~ChuShogiEngine()
{
}

EngineProtocol ChuShogiEngine::GetType()
{
	return WinBoard;
}

void ChuShogiEngine::StartGame(QString variant)
{
	_moves.clear();
	_process->write("xboard\n");
	if (variant != "")
	{
		const QString str = "variant " + variant + "\n";
		_process->write(str.toLatin1());
	}
	_process->write("new\n");
    _process->write("memory 80\n");
}

void ChuShogiEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_process->write(AddMove(x1, y1, x2, y2, promotion));
	_process->write("\n");
}

QByteArray ChuShogiEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
    moveStr.push_back('u');
    moveStr.push_back('s');
    moveStr.push_back('e');
    moveStr.push_back('r');
    moveStr.push_back('m');
    moveStr.push_back('o');
    moveStr.push_back('v');
    moveStr.push_back('e');
    moveStr.push_back(' ');
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
	if (promotion == '+')
	{
		moveStr.push_back(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
