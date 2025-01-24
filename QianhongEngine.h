#pragma once
#include "Engine.h"

class QianhongEngine : public Engine
{
public:
	QianhongEngine();
	~QianhongEngine() override;
	QProcess* RunProcess(QObject* parentObject, const QString& engineExe) override;
	EngineProtocol GetType() override;
	void StartGame(QString variant = "") override;
	void Move() override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;

private:
	bool _fenSet = false;
};

