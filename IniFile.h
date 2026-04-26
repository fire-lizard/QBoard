#pragma once

#include <QSettings>
#include <QApplication>
#include <qstyle.h>

class ConfigRecord {
public:
    QString styleName;
    QString gameVariant;
    QString pieceStyle;
    QString engineOutput;
    bool highlightMoves;
    bool highlightShoots;
    bool highlightAttackers;
    bool highlightDefenders;
    bool highlightLastMoves;
    bool timerState;
    int  whiteEngineDepth;
    int  blackEngineDepth;
};

class IniFile {
public:
    static void writeToIniFile(const QString& filePath, const ConfigRecord& configRecord);
    static QStringList readFromIniFile(const QString& filePath);

private:
    static const int _minEngineDepth = 1;
    static const int _maxEngineDepth = 20;
};
