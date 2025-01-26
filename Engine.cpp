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

void Engine::SetFEN(std::string fen)
{
	_fen = std::move(fen);
}
