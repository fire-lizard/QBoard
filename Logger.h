#pragma once
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDateTime>
#include <QDebug>

enum LogLevel {Info, Warning, Error};

class Logger
{
public:
	static void writeToLog(const QString& message, const LogLevel level = Info);
};

