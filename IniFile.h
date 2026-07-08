#pragma once

#include <algorithm>
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
    bool useWhiteEngineDepth;
    int  whiteEngineDepth;
    bool useBlackEngineDepth;
    int  blackEngineDepth;
    bool useWhiteEngineTime;
    int  whiteEngineTime;
    bool useBlackEngineTime;
    int  blackEngineTime;
};

class IniFile {
public:
    static void writeToIniFile(const QString& filePath, const ConfigRecord& configRecord);
    static ConfigRecord readFromIniFile(const QString& filePath);

private:
    static constexpr int _minEngineDepth = 1;
    static constexpr int _maxEngineDepth = 20;
    static constexpr int _minEngineTime = 1;
    static constexpr int _maxEngineTime = 30;
};
