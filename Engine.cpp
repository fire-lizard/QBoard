#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

QProcess* Engine::RunProcess(QObject *parentObject, QString engineFolder, QString engineExe)
{
	_process = new QProcess(parentObject);
	_process->setWorkingDirectory(engineFolder);
	_process->start(engineFolder + "/" + engineExe);
	return _process;
}

void Engine::Quit() const
{
	_process->write("quit\n");
	delete _process;
}
