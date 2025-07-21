#include "UsiEngine.h"

UsiEngine::UsiEngine()
{
	_fen = SHOGIFEN;
}

UsiEngine::~UsiEngine()
{
	Quit();
}

void UsiEngine::SetFEN(std::string fen)
{
	trimNewline(fen);
	_fen = std::move(fen);
	WriteToProcess("usinewgame\n");
	_moves.clear();
}

EngineProtocol UsiEngine::GetType()
{
	return USI;
}

void UsiEngine::StartGame(QString variant)
{
	_moves.clear();
	WriteToProcess("usi\n");
	WriteToProcess("isready\n");
	WriteToProcess("usinewgame\n");
}

void UsiEngine::Move()
{
	_textEdit->setText("");
	QByteArray moveStr;
    moveStr += "position sfen " + QByteArray::fromStdString(_fen.substr(0, _fen.size() - 5)) + " moves ";
	for (const auto& _move : _moves)
	{
		moveStr += _move;
		moveStr += " ";
	}
	moveStr += "\n";
	WriteToProcess(moveStr);
	WriteToProcess("go depth 10\n");
}

void UsiEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->setText("");
	QByteArray moveStr;
    moveStr += "position sfen " + QByteArray::fromStdString(_fen.substr(0, _fen.size() - 5)) + " moves ";
	for (const auto& _move : _moves)
	{
		moveStr += _move;
		moveStr += " ";
	}
	moveStr += AddMove(x1, y1, x2, y2, promotion);
	moveStr += "\n";
	WriteToProcess(moveStr);
	WriteToProcess("go depth 10\n");
}

QByteArray UsiEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
	if (y1 == '*')
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(QString::number(x2)[0].toLatin1());
		moveStr.push_back(static_cast<char>(y2 + 97));
	}
	else if (x1 < 10)
	{
		moveStr.push_back(QString::number(x1)[0].toLatin1());
		moveStr.push_back(static_cast<char>(y1 + 97));
		moveStr.push_back(QString::number(x2)[0].toLatin1());
		moveStr.push_back(static_cast<char>(y2 + 97));
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
