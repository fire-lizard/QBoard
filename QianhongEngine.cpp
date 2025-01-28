#include "QianhongEngine.h"

QianhongEngine::QianhongEngine()
{
	_fen = XIANGQIFEN;
}

QianhongEngine::~QianhongEngine()
{
	Quit();
}

QProcess* QianhongEngine::RunProcess(QObject* parentObject, const QString& engineExe)
{
	_process = std::make_unique<QProcess>(parentObject);
	_process->setWorkingDirectory(QFileInfo(engineExe).absolutePath());
	_process->setProgram(engineExe);
	QStringList engineArguments;
	engineArguments << "-plugin";
	_process->setArguments(engineArguments);
	_process->start();
	return _process.get();
}

void QianhongEngine::SetFEN(std::string fen)
{
	_fen = std::move(fen);
	WriteToProcess(QByteArray::fromStdString("FEN " + _fen + "\n"));
	_moves.clear();
}

EngineProtocol QianhongEngine::GetType()
{
	return Qianhong;
}

void QianhongEngine::StartGame(QString variant)
{
	_moves.clear();
}

void QianhongEngine::Move()
{
	WriteToProcess("ai\n");
}

void QianhongEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->setText("");
	WriteToProcess(AddMove(x1, y1, x2, y2, promotion) + "\n");
	WriteToProcess("ai\n");
}

QByteArray QianhongEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
	moveStr.push_back('P');
	moveStr.push_back('L');
	moveStr.push_back('A');
	moveStr.push_back('Y');
	moveStr.push_back(' ');
	moveStr.push_back(x1 + 65);
	moveStr.push_back(y1 + '0');
	moveStr.push_back('-');
	moveStr.push_back(x2 + 65);
	moveStr.push_back(y2 + '0');
	_moves.push_back(moveStr);
	return moveStr;
}
