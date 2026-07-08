#include "IniFile.h"

void IniFile::writeToIniFile(const QString& filePath, const ConfigRecord& configRecord) {
	// Create a QSettings object for the INI file
	QSettings settings(filePath, QSettings::IniFormat);

	// Write values
	settings.beginGroup("General");
    settings.setValue("StyleName", configRecord.styleName);
    settings.setValue("GameVariant", configRecord.gameVariant);
    settings.setValue("PieceStyle", configRecord.pieceStyle);
    settings.setValue("EngineOutput", configRecord.engineOutput);
    settings.setValue("HighlightMoves", configRecord.highlightMoves);
    settings.setValue("HighlightShoots", configRecord.highlightShoots);
    settings.setValue("HighlightAttackers", configRecord.highlightAttackers);
    settings.setValue("HighlightDefenders", configRecord.highlightDefenders);
    settings.setValue("HighlightLastMoves", configRecord.highlightLastMoves);
    settings.setValue("TimerState", configRecord.timerState);
    settings.setValue("UseEngine1Depth", configRecord.useWhiteEngineDepth);
    settings.setValue("Engine1Depth", configRecord.whiteEngineDepth);
    settings.setValue("UseEngine2Depth", configRecord.useBlackEngineDepth);
    settings.setValue("Engine2Depth", configRecord.blackEngineDepth);
    settings.setValue("UseEngine1Time", configRecord.useWhiteEngineTime);
    settings.setValue("Engine1Time", configRecord.whiteEngineTime);
    settings.setValue("UseEngine2Time", configRecord.useBlackEngineTime);
    settings.setValue("Engine2Time", configRecord.blackEngineTime);
    settings.endGroup();

	// Sync the changes explicitly (optional)
	settings.sync();
}

ConfigRecord IniFile::readFromIniFile(const QString& filePath) {
    // Create a QSettings object for the INI file
    QSettings settings(filePath, QSettings::IniFormat);

    // Read values from the "General" group
    settings.beginGroup("General");
    const QString styleName = settings.value("StyleName", "").toString();
    const QString gameVariant = settings.value("GameVariant", "Chess").toString();
    const QString pieceStyle = settings.value("PieceStyle", "European").toString();
    const QString engineOutput = settings.value("EngineOutput", "Concise").toString();
    const bool highlightMoves = settings.value("HighlightMoves", true).toBool();
    const bool highlightShoots = settings.value("HighlightShoots", true).toBool();
    const bool highlightAttackers = settings.value("HighlightAttackers", true).toBool();
    const bool highlightDefenders = settings.value("HighlightDefenders", true).toBool();
    const bool highlightLastMoves = settings.value("HighlightLastMoves", true).toBool();
    const bool timerState = settings.value("TimerState", true).toBool();
    const bool useWhiteEngineDepth = settings.value("UseEngine1Depth", false).toBool();
    int  whiteEngineDepth = settings.value("Engine1Depth", 10).toInt();
    const bool useBlackEngineDepth = settings.value("UseEngine2Depth", false).toBool();
    int  blackEngineDepth = settings.value("Engine2Depth", 10).toInt();
    const bool useWhiteEngineTime = settings.value("UseEngine1Time", false).toBool();
    int  whiteEngineTime = settings.value("Engine1Time", 10).toInt();
    const bool useBlackEngineTime = settings.value("UseEngine2Time", false).toBool();
    int  blackEngineTime = settings.value("Engine2Time", 10).toInt();
    settings.endGroup();

    // Return values
    ConfigRecord result;
	result.styleName = styleName;
    result.gameVariant = gameVariant;
    result.pieceStyle = pieceStyle;
    result.engineOutput = engineOutput;
    result.highlightMoves = highlightMoves;
    result.highlightShoots = highlightShoots;
    result.highlightAttackers = highlightAttackers;
    result.highlightDefenders = highlightDefenders;
    result.highlightLastMoves = highlightLastMoves;
    result.timerState = timerState;
    whiteEngineDepth = std::max(whiteEngineDepth, _minEngineDepth);
    whiteEngineDepth = std::min(whiteEngineDepth, _maxEngineDepth);
    blackEngineDepth = std::max(blackEngineDepth, _minEngineDepth);
    blackEngineDepth = std::min(blackEngineDepth, _maxEngineDepth);
    whiteEngineTime = std::max(whiteEngineTime, _minEngineTime);
    whiteEngineTime = std::min(whiteEngineTime, _maxEngineTime);
    blackEngineTime = std::max(blackEngineTime, _minEngineTime);
    blackEngineTime = std::min(blackEngineTime, _maxEngineTime);
    result.useWhiteEngineDepth = useWhiteEngineDepth;
    result.whiteEngineDepth = whiteEngineDepth;
    result.useBlackEngineDepth = useBlackEngineDepth;
    result.blackEngineDepth = blackEngineDepth;
    result.useWhiteEngineTime = useWhiteEngineTime;
    result.whiteEngineTime = whiteEngineTime;
    result.useBlackEngineTime = useBlackEngineTime;
    result.blackEngineTime = blackEngineTime;
    return result;
}
