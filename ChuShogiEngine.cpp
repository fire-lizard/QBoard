#include "ChuShogiEngine.h"

ChuShogiEngine::ChuShogiEngine()
{
}

ChuShogiEngine::~ChuShogiEngine()
{
}

EngineProtocol ChuShogiEngine::GetType()
{
	return XBoard;
}

void ChuShogiEngine::StartGame(QString variant)
{
	_moves.clear();
	_process->write("xboard\n");
	_process->write("new\n");
	if (variant != "")
	{
		const QString str = "variant " + variant + "\n";
		_process->write(str.toLatin1());
	}
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
	if (y1 == '@')
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(static_cast<char>(x2 + 97));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
	}
	else if (y1 <= 12 || y2 <= 12)
	{
		moveStr.push_back(static_cast<char>(x1 < 30 ? x1 + 97 : x1));
		moveStr.push_back(QString::number(y1)[0].toLatin1());
		if (y1 >= 10) moveStr.push_back(QString::number(y1)[1].toLatin1());
		moveStr.push_back(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
		if (y2 >= 10) moveStr.push_back(QString::number(y2)[1].toLatin1());
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

QByteArray ChuShogiEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3)
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
	if (y1 <= 12 || y2 <= 12)
	{
		moveStr.push_back(static_cast<char>(x1 < 30 ? x1 + 97 : x1));
		moveStr.push_back(QString::number(y1)[0].toLatin1());
		if (y1 >= 10) moveStr.push_back(QString::number(y1)[1].toLatin1());
		moveStr.push_back(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
		if (y2 >= 10) moveStr.push_back(QString::number(y2)[1].toLatin1());
	}
	else
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(x2);
		moveStr.push_back(y2);
	}
	moveStr.push_back(',');
	if (y2 <= 12 || y3 <= 12)
	{
		moveStr.push_back(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
		if (y2 >= 10) moveStr.push_back(QString::number(y2)[1].toLatin1());
		moveStr.push_back(static_cast<char>(x3 < 30 ? x3 + 97 : x3));
		moveStr.push_back(QString::number(y3)[0].toLatin1());
		if (y3 >= 10) moveStr.push_back(QString::number(y3)[1].toLatin1());
	}
	else
	{
		moveStr.push_back(x2);
		moveStr.push_back(y2);
		moveStr.push_back(x3);
		moveStr.push_back(y3);
	}
	_moves.push_back(moveStr);
	return moveStr;
}