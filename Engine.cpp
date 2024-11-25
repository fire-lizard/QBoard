#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

QProcess* Engine::RunProcess(QObject *parentObject, const QString& engineExe)
{
	_process = new QProcess(parentObject);
	_process->setWorkingDirectory(QFileInfo(engineExe).absolutePath());
	_process->setProgram(engineExe);
	_process->start();
	return _process;
}

void Engine::Quit() const
{
	_process->write("quit\n");
	_process->close();
	delete _process;
}
