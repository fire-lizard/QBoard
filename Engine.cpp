#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

QProcess* Engine::RunProcess(QObject *parentObject, QString engineFolder, QString engineExe)
{
	QString fileName = engineFolder + "/" + engineExe;
	_process = new QProcess(parentObject);
	_process->setWorkingDirectory(engineFolder);
	_process->setProgram(fileName);
	_process->start();
	return _process;
}

void Engine::Quit() const
{
	_process->write("quit\n");
	_process->close();
	delete _process;
}
