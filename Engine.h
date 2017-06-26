#pragma once
#include <QProcess>
#include "Common.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();
	QProcess* RunProcess(QObject *parentObject, QString engineFolder, QString engineExe);
	void Quit() const;
	virtual EngineType GetType() = 0;
	virtual void StartGame(QString variant = "") = 0;
	virtual void Move(int x1, int y1, int x2, int y2, char promotion = ' ') = 0;

protected:
	QProcess *_process = nullptr;

private:
};
