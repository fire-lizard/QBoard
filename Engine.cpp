#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
	Quit();
}

QProcess* Engine::RunProcess(QObject *parentObject, const QString& engineExe, const QString& engineOptions)
{
	_process = std::make_unique<QProcess>(parentObject);
	_process->setWorkingDirectory(QFileInfo(engineExe).absolutePath());
	_process->setProgram(engineExe);
    if (!engineOptions.trimmed().isEmpty())
    {
        QStringList engineArguments;
        engineArguments << engineOptions;
        _process->setArguments(engineArguments);
    }
    _process->start();
	return _process.get();
}

void Engine::Quit() const
{
	if (_process)
	{
		_process->write("quit\n");
		_process->close();
		_process.reset();
	}
}

bool Engine::IsActive() const
{
	return _isActive;
}

void Engine::SetActive(bool val)
{
	_isActive = val;
}

QTextEdit* Engine::GetTextEdit() const
{
	return _textEdit;
}

void Engine::SetTextEdit(QTextEdit* textEdit)
{
	_textEdit = textEdit;
}

void Engine::UseEngineDepth(bool useEngineDepth)
{
	_useEngineDepth = useEngineDepth;
}

void Engine::UseEngineTime(bool useEngineTime)
{
	_useEngineTime = useEngineTime;
}

int Engine::GetEngineDepth() const
{
    return _engineDepth;
}

void Engine::SetEngineDepth(int engineDepth)
{
    _engineDepth = engineDepth;
}

int Engine::GetEngineTime() const
{
	return _engineTime;
}

void Engine::SetEngineTime(int engineTime)
{
	_engineTime = engineTime;
}

QProcess* Engine::GetProcess() const
{
	return _process.get();
}

void Engine::WriteToProcess(QByteArray buf) const
{
    if (std::ranges::any_of(buf, [=](char t) {return isprint(t);}))
    {
        _textEdit->append(buf);
        _process->write(buf);
    }
}

std::vector<QByteArray> Engine::Moves() const
{
	return _moves;
}

QByteArray Engine::AddMove(QByteArray moveStr)
{
	_moves.push_back(moveStr);
	return moveStr;
}

void Engine::Move(QByteArray moveStr)
{
	_textEdit->setText("");
	WriteToProcess(AddMove(std::move(moveStr)) + "\n");
}
