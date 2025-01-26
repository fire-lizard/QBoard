#include "Engine.h"

#include <utility>

Engine::Engine()
{
}

Engine::~Engine()
{
	Quit();
}

QProcess* Engine::RunProcess(QObject *parentObject, const QString& engineExe)
{
	_process = std::make_unique<QProcess>(parentObject);
	_process->setWorkingDirectory(QFileInfo(engineExe).absolutePath());
	_process->setProgram(engineExe);
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

void Engine::WriteToProcess(QByteArray buf)
{
	_process->write(buf);
}

void Engine::SetFEN(std::string fen)
{
	_fen = std::move(fen);
}
