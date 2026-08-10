#include "Engine.h"

#ifdef Q_OS_WIN
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

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
	_process->setProgram(QFileInfo(engineExe).absoluteFilePath());
    if (!engineOptions.trimmed().isEmpty())
    {
        _process->setArguments(QProcess::splitCommand(engineOptions));
    }
	StartProcess();
	return _process.get();
}

//	Anonymous pipes cannot do async I/O, so QProcess builds a named pipe and opens
//	the child's end with FILE_FLAG_OVERLAPPED.  .NET's Console reader hands out
//	whatever is already buffered on such a handle and then never returns from the
//	first read that has to wait - so a .NET engine (ChessV) took our startup burst
//	and went permanently deaf to every move afterwards, while our write() kept
//	reporting success.  Hand the engine a plain synchronous pipe instead, the way
//	WinBoard and Arena do, and write to that handle ourselves.  Engine output is
//	untouched: QProcess keeps its stdout/stderr channels and its signals.
void Engine::StartProcess() const
{
#ifdef Q_OS_WIN
	if (_stdinWrite)   // restarted without a Quit() in between
	{
		CloseHandle(_stdinWrite);
		_stdinWrite = nullptr;
	}
	SECURITY_ATTRIBUTES sa{ sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE };
	HANDLE readEnd = nullptr, writeEnd = nullptr;
	//	64K of buffer: WriteFile below runs on the GUI thread and blocks once the
	//	pipe is full, and an engine busy thinking may not be reading just now
	if (CreatePipe(&readEnd, &writeEnd, &sa, 64 * 1024) && SetHandleInformation(writeEnd, HANDLE_FLAG_INHERIT, 0))
	{
		_stdinWrite = writeEnd;
		//	the modifier runs immediately before CreateProcess, so this wins over
		//	the stdin handle QProcess put in the STARTUPINFO
		_process->setCreateProcessArgumentsModifier([readEnd](QProcess::CreateProcessArguments *args)
		{
			args->inheritHandles = true;
			args->startupInfo->dwFlags |= STARTF_USESTDHANDLES;
			args->startupInfo->hStdInput = readEnd;
		});
	}
	else
	{
		//	no pipe - fall back to QProcess's own stdin rather than starting mute
		if (readEnd) CloseHandle(readEnd);
		if (writeEnd) CloseHandle(writeEnd);
		readEnd = nullptr;
		_stdinWrite = nullptr;
	}
	_process->start();
	if (readEnd)
	{
		CloseHandle(readEnd);
	}
#else
	_process->start();
#endif
}

void Engine::Quit() const
{
	if (_process)
	{
#ifdef Q_OS_WIN
		if (_stdinWrite)
		{
			DWORD written = 0;
			WriteFile(_stdinWrite, "quit\n", 5, &written, nullptr);
			//	closing our end is the EOF that gets rid of engines ignoring "quit"
			CloseHandle(_stdinWrite);
			_stdinWrite = nullptr;
		}
		else
#endif
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
#ifdef Q_OS_WIN
        if (_stdinWrite)
        {
            const char *p = buf.constData();
            qint64 left = buf.size();
            DWORD written = 0;
            while (left > 0 && WriteFile(_stdinWrite, p, static_cast<DWORD>(left), &written, nullptr) && written > 0)
            {
                p += written;
                left -= written;
            }
            return;
        }
#endif
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
