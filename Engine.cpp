#include "Engine.h"

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

QTextEdit* Engine::GetTextEdit() const
{
	return _textEdit;
}

void Engine::SetTextEdit(QTextEdit* textEdit)
{
	_textEdit = textEdit;
}

QProcess* Engine::GetProcess() const
{
	return _process.get();
}

void Engine::WriteToProcess(QByteArray buf) const
{
	if (std::any_of(buf.begin(), buf.end(), [=](char t) {return isprint(t);}))
	{
		_textEdit->append(buf);
	}
	_process->write(buf);
}

std::vector<QByteArray> Engine::Moves() const
{
	return _moves;
}