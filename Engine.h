#pragma once
#include <utility>
#include <QProcess>
#include <QFileInfo>
#include <QTextEdit>
#include "Common.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();
    virtual QProcess* RunProcess(QObject *parentObject, const QString& engineExe, const QString& engineOptions);
	void Quit() const;
	bool IsActive() const;
	void SetActive(bool val);
	QTextEdit* GetTextEdit() const;
	void SetTextEdit(QTextEdit* textEdit);
	void UseEngineDepth(bool useEngineDepth);
	void UseEngineTime(bool useEngineTime);
	int  GetEngineDepth() const;
	int  GetEngineTime() const;
	QProcess* GetProcess() const;
	void WriteToProcess(QByteArray buf) const;
	std::vector<QByteArray> Moves() const;
	virtual QByteArray AddMove(QByteArray moveStr);
	virtual void Move(QByteArray moveStr);
	virtual void SetEngineDepth(int engineDepth);
	virtual void SetEngineTime(int engineTime);
	virtual void SetFEN(std::string fen) = 0;
	virtual EngineProtocol GetType() = 0;
	virtual void StartGame(QString variant = "") = 0;
	virtual void Move() = 0;
	virtual void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') = 0;
	virtual QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') = 0;

protected:
	mutable std::unique_ptr<QProcess> _process = nullptr;
	QTextEdit *_textEdit;
	bool _useEngineDepth = false;
	int  _engineDepth = 10;
	bool _useEngineTime = false;
	int  _engineTime = 10;
	bool _isActive = false;
	std::vector<QByteArray> _moves;
	std::string _fen;
};
