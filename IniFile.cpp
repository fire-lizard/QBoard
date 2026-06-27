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
    settings.setValue("Engine1Depth", configRecord.whiteEngineDepth);
    settings.setValue("Engine2Depth", configRecord.blackEngineDepth);
    settings.setValue("Engine1Time", configRecord.whiteEngineTime);
    settings.setValue("Engine2Time", configRecord.blackEngineTime);
    settings.endGroup();

	// Sync the changes explicitly (optional)
	settings.sync();
}

QStringList IniFile::readFromIniFile(const QString& filePath) {
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
    int whiteEngineDepth = settings.value("Engine1Depth", 10).toInt();
    int blackEngineDepth = settings.value("Engine2Depth", 10).toInt();
    int whiteEngineTime = settings.value("Engine1Time", 10).toInt();
    int blackEngineTime = settings.value("Engine2Time", 10).toInt();
    settings.endGroup();

    // Return values
    QStringList result;
    result << styleName << gameVariant << pieceStyle << engineOutput << QVariant(highlightMoves).toString();
    result << QVariant(highlightShoots).toString() << QVariant(highlightAttackers).toString();
	result << QVariant(highlightDefenders).toString() << QVariant(highlightLastMoves).toString();
    whiteEngineDepth = std::max(whiteEngineDepth, _minEngineDepth);
    whiteEngineDepth = std::min(whiteEngineDepth, _maxEngineDepth);
    blackEngineDepth = std::max(blackEngineDepth, _minEngineDepth);
    blackEngineDepth = std::min(blackEngineDepth, _maxEngineDepth);
    whiteEngineTime = std::max(whiteEngineTime, _minEngineTime);
    whiteEngineTime = std::min(whiteEngineTime, _maxEngineTime);
    blackEngineTime = std::max(blackEngineTime, _minEngineTime);
    blackEngineTime = std::min(blackEngineTime, _maxEngineTime);
    result << QVariant(timerState).toString();
	result << QVariant(whiteEngineDepth).toString() << QVariant(blackEngineDepth).toString();
    result << QVariant(whiteEngineTime).toString() << QVariant(blackEngineTime).toString();
    return result;
}
