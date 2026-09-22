#include <algorithm>
#include <sstream>
#include "UsiEngine.h"

UsiEngine::UsiEngine()
{
	_fen = SHOGIFEN;
}

UsiEngine::~UsiEngine()
{
	Quit();
}

// QBoard writes a shogi position the way its XBoard engines read it: the hand in brackets after the
// placement and 'w' for the side that moves first. SFEN has the hand as a field of its own, with
// counts ("S2Pp"), and calls the first mover 'b'. A FEN without brackets is taken to be SFEN already.
static std::string ToSfen(const std::string& fen)
{
	const size_t open = fen.find('[');
	const size_t close = fen.find(']');
	if (open == std::string::npos || close == std::string::npos || close < open) return fen;
	std::istringstream rest(fen.substr(close + 1));
	std::string side, holdings, number;
	rest >> side >> holdings >> number;
	const std::string held = fen.substr(open + 1, close - open - 1);
	std::string hand;
	for (size_t i = 0; i < held.size(); i++)
	{
		if (held.find(held[i]) != i) continue; // counted where it first appears
		const auto count = std::ranges::count(held, held[i]);
		if (count > 1) hand += std::to_string(count);
		hand += held[i];
	}
	return fen.substr(0, open) + (side == "b" ? " w " : " b ") + (hand.empty() ? "-" : hand) + " " +
		(number.empty() ? "1" : number);
}

void UsiEngine::SetFEN(std::string fen)
{
	trimNewline(fen);
	_fen = ToSfen(fen);
    if (_process != nullptr && _process->processId() > 0 && _process->state() != QProcess::ProcessState::NotRunning)
    {
        WriteToProcess("usinewgame\n");
    }
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
    moveStr += "position sfen " + QByteArray::fromStdString(_fen) + " moves ";
    for (const auto& _move : _moves)
	{
		moveStr += _move;
		moveStr += " ";
	}
	moveStr += "\n";
	WriteToProcess(moveStr);
	moveStr = "go";
	if (_useEngineDepth)
	{
		moveStr += " depth " + QByteArray::number(_engineDepth);
	}
	if (_useEngineTime)
	{
		moveStr += " movetime " + QByteArray::number(_engineTime * 1000);
	}
	WriteToProcess(moveStr + "\n");
}

void UsiEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->setText("");
	QByteArray moveStr;
    moveStr += "position sfen " + QByteArray::fromStdString(_fen) + " moves ";
    for (const auto& _move : _moves)
	{
		moveStr += _move;
		moveStr += " ";
	}
	moveStr += AddMove(x1, y1, x2, y2, promotion);
	moveStr += "\n";
	WriteToProcess(moveStr);
	moveStr = "go";
	if (_useEngineDepth)
	{
		moveStr += " depth " + QByteArray::number(_engineDepth);
	}
	if (_useEngineTime)
	{
		moveStr += " movetime " + QByteArray::number(_engineTime * 1000);
	}
	WriteToProcess(moveStr + "\n");
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
