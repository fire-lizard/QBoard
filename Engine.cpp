#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

QProcess* Engine::RunProcess(QObject *parentObject, const QString& engineExe, const QStringList& engineArguments)
{
	_process = new QProcess(parentObject);
	_process->setWorkingDirectory(QFileInfo(engineExe).absolutePath());
	_process->setProgram(engineExe);
	_process->setArguments(engineArguments);
	_process->start();
	return _process;
}

void Engine::Quit() const
{
	_process->write("quit\n");
	_process->close();
	delete _process;
}
