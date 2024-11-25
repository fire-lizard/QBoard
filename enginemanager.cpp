#include "enginemanager.h"
#include "ui_enginemanager.h"

EngineManager::EngineManager(QWidget *parent) : QDialog(parent), ui(new Ui::EngineManager)
{
	ui->setupUi(this);
	ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate(ui->engineTable);
	ui->engineTable->setItemDelegate(cbid);
	ui->engineTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	readXmlUsingStream("QBoardEngines.xml");
}

EngineManager::~EngineManager()
{
	delete ui;
}

QTableWidget * EngineManager::GetEngineTable() const
{
	return ui->engineTable;
}

EngineProtocol EngineManager::StringToEngineProtocol(const QString& str)
{
	if (str == "UCI")
		return UCI;
	if (str == "UCCI")
		return UCCI;
	if (str == "Qianhong")
		return Qianhong;
	if (str == "USI")
		return USI;
	return WinBoard;
}

void EngineManager::addElementToXmlStream(const QString& fileName, const QString& engineName, const QString& engineProtocol, const QString& enginePath) {
	const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	QFile file(settingsDir + "/" + fileName);
	QFile tempFile(settingsDir + "/temp.xml");

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the file for reading.";
		return;
	}

	if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the temp file for writing.";
		file.close();
		return;
	}

	QXmlStreamReader reader(&file);
	QXmlStreamWriter writer(&tempFile);

	writer.setAutoFormatting(true);
	writer.writeStartDocument();

	while (!reader.atEnd()) {
		reader.readNext();

		if (reader.isStartElement() && reader.name().toString() == "Engines") {
			writer.writeStartElement(reader.name().toString());
			writer.writeAttributes(reader.attributes());

			// Add your new element here
			writer.writeStartElement("Engine");
			writer.writeAttribute("EngineName", engineName);
			writer.writeAttribute("EngineProtocol", engineProtocol);
			writer.writeAttribute("EnginePath", enginePath);
			writer.writeEndElement();
		}
		else if (reader.isStartElement() || reader.isEndElement()) {
			writer.writeCurrentToken(reader);
		}
		else if (reader.isCharacters()) {
			writer.writeCharacters(reader.text().toString());
		}
	}

	file.close();
	tempFile.close();

	if (reader.hasError()) {
		qDebug() << "Error reading XML file.";
	}
	else {
		file.remove();
		tempFile.rename(settingsDir + "/" + fileName);
		qDebug() << "Element added successfully.";
	}
}

void EngineManager::modifyXmlElement(const QString& fileName, const QString& engineName, const QString& engineProtocol, const QString& enginePath) {
	const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	QFile file(settingsDir + "/" + fileName);
	QFile tempFile(settingsDir + "/temp.xml");

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the file for reading.";
		return;
	}

	if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the temporary file for writing.";
		file.close();
		return;
	}

	QXmlStreamReader xmlReader(&file);
	QXmlStreamWriter xmlWriter(&tempFile);

	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();

	while (!xmlReader.atEnd()) {
		xmlReader.readNext();

		// Check if it's a start element
		if (xmlReader.isStartElement()) {
			if (xmlReader.name().toString() == "Engine") {
				// Write the start element
				xmlWriter.writeStartElement(xmlReader.name().toString());

				// Copy attributes if any
				QXmlStreamAttributes attributes = xmlReader.attributes();
				if (!attributes.empty() && attributes[0].name().toString() == "EngineName" && attributes[0].value().toString() == engineName)
				{
					xmlWriter.writeAttribute("EngineName", engineName);
					xmlWriter.writeAttribute("EngineProtocol", engineProtocol);
					xmlWriter.writeAttribute("EnginePath", enginePath);
				}
				else
				{
					foreach(const QXmlStreamAttribute & attr, attributes) {
						xmlWriter.writeAttribute(attr.name().toString(), attr.value().toString());
					}
				}

				// Skip the rest of this element's text
				xmlReader.readNext(); // Move past characters/text
			}
			else {
				// Write the start element as is
				xmlWriter.writeStartElement(xmlReader.name().toString());
				foreach(const QXmlStreamAttribute & attr, xmlReader.attributes()) {
					xmlWriter.writeAttribute(attr.name().toString(), attr.value().toString());
				}
			}
		}
		else if (xmlReader.isEndElement()) {
			// Write the end element
			xmlWriter.writeEndElement();
		}
		else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
			// Write text content
			xmlWriter.writeCharacters(xmlReader.text().toString());
		}
	}

	xmlWriter.writeEndDocument();

	if (xmlReader.hasError()) {
		qDebug() << "Error reading XML:" << xmlReader.errorString();
	}

	file.close();
	tempFile.close();

	// Replace original file with modified content
	if (file.remove() && tempFile.rename(settingsDir + "/" + fileName)) {
		qDebug() << "XML file modified successfully.";
	}
	else {
		qDebug() << "Failed to save changes to the original file.";
	}
}

void EngineManager::readXmlUsingStream(const QString& fileName) const
{
	const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	QFile file(settingsDir + "/" + fileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the file for reading.";
		return;
	}

	QXmlStreamReader xml(&file);

	while (!xml.atEnd() && !xml.hasError()) {
		QXmlStreamReader::TokenType token = xml.readNext();

		if (token == QXmlStreamReader::StartElement) {
			qDebug() << "Element name:" << xml.name().toString();

			// Read attributes
			QString engineName;
			QString engineProtocol;
			QString enginePath;
			foreach(const QXmlStreamAttribute & attr, xml.attributes()) {
				qDebug() << " -" << attr.name().toString() << "=" << attr.value().toString();
				if (attr.name().toString() == "EngineName") engineName = attr.value().toString();
				if (attr.name().toString() == "EngineProtocol") engineProtocol = attr.value().toString();
				if (attr.name().toString() == "EnginePath") enginePath = attr.value().toString();
			}
			if (engineName != "" && enginePath != "")
			{
				ui->engineTable->insertRow(ui->engineTable->rowCount());
				const int currentRow = ui->engineTable->rowCount() - 1;
				ui->engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
				ui->engineTable->setItem(currentRow, 1, new QTableWidgetItem(engineProtocol));
				ui->engineTable->setItem(currentRow, 2, new QTableWidgetItem(enginePath));
			}
		}
		else if (token == QXmlStreamReader::Characters && !xml.isWhitespace()) {
			qDebug() << "Element text:" << xml.text().toString();
		}
	}

	if (xml.hasError()) {
		qDebug() << "Error reading XML:" << xml.errorString();
	}

	file.close();
}

bool EngineManager::hasAttributeWithSpecificValue(const QString& fileName, const QString& attributeName, const QString& attributeValue) {
	const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	QFile file(settingsDir + "/" + fileName);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the file for reading.";
		return false;
	}

	QXmlStreamReader xmlReader(&file);

	while (!xmlReader.atEnd()) {
		xmlReader.readNext();

		// Check if it's a start element
		if (xmlReader.isStartElement()) {
			// Check if the element has the specified attribute
			if (xmlReader.attributes().hasAttribute(attributeName)) {
				QString value = xmlReader.attributes().value(attributeName).toString();
				if (value == attributeValue) {
					file.close();
					return true; // Attribute with the specific value is found
				}
			}
		}
	}

	if (xmlReader.hasError()) {
		qDebug() << "Error reading XML:" << xmlReader.errorString();
	}

	file.close();
	return false; // Attribute with specific value not found
}

void EngineManager::deleteXmlElementByAttribute(const QString& fileName, const QString& attributeName, const QString& attributeValue) {
	const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
	QFile file(settingsDir + "/" + fileName);
	QFile tempFile(settingsDir + "/temp.xml");

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the file for reading.";
		return;
	}

	if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Failed to open the temporary file for writing.";
		file.close();
		return;
	}

	QXmlStreamReader xmlReader(&file);
	QXmlStreamWriter xmlWriter(&tempFile);

	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();

	while (!xmlReader.atEnd()) {
		xmlReader.readNext();

		if (xmlReader.isStartElement()) {
			bool skipElement = false;

			// Check if this element has the target attribute
			if (xmlReader.attributes().hasAttribute(attributeName) &&
				xmlReader.attributes().value(attributeName) == attributeValue) {
				skipElement = true; // Mark this element for skipping
				xmlReader.readNext(); // Move past this element and its children
				while (!(xmlReader.isEndElement() && xmlReader.name() == xmlReader.name())) {
					xmlReader.readNext();
				}
				continue; // Skip writing this element
			}

			if (!skipElement) {
				// Write the start element and copy attributes
				xmlWriter.writeStartElement(xmlReader.name().toString());
				foreach(const QXmlStreamAttribute & attr, xmlReader.attributes()) {
					xmlWriter.writeAttribute(attr.name().toString(), attr.value().toString());
				}
			}
		}
		else if (xmlReader.isEndElement()) {
			xmlWriter.writeEndElement();
		}
		else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
			xmlWriter.writeCharacters(xmlReader.text().toString());
		}
	}

	if (xmlReader.hasError()) {
		qDebug() << "Error reading XML:" << xmlReader.errorString();
	}

	file.close();
	tempFile.close();

	// Replace the original file with the updated content
	if (file.remove() && tempFile.rename(settingsDir + "/" + fileName)) {
		qDebug() << "Element deleted successfully.";
	}
	else {
		qDebug() << "Failed to save changes to the original file.";
	}
}

void EngineManager::on_toolButton_clicked()
{
	AddEngineDialog *addEngineDialog = new AddEngineDialog(this);
	addEngineDialog->exec();
	if (addEngineDialog->result() == QDialog::Accepted)
	{
		const QString engineName = addEngineDialog->GetEngineName()->text();
		if (hasAttributeWithSpecificValue("QBoardEngines.xml", "EngineName", engineName))
		{
			QMessageBox::warning(this, "Warning", "Engine with the same name already exists", QMessageBox::Ok);
			return;
		}
		const QString engineProtocol = addEngineDialog->GetEngineProtocol()->currentText();
		const QString enginePath = addEngineDialog->GetEnginePath()->text();
		if (engineName != "" && enginePath != "")
		{
			ui->engineTable->insertRow(ui->engineTable->rowCount());
			const int currentRow = ui->engineTable->rowCount() - 1;
			ui->engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
			ui->engineTable->setItem(currentRow, 1, new QTableWidgetItem(engineProtocol));
			ui->engineTable->setItem(currentRow, 2, new QTableWidgetItem(enginePath));

			// Writing added engine string to the file
			const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
			if (!QDir(settingsDir).exists())
			{
				QDir().mkdir(settingsDir);
			}
			QFile file(settingsDir + "/QBoardEngines.xml");
			if (!file.exists())
			{
				file.open(QIODevice::WriteOnly);
				QXmlStreamWriter xmlWriter(&file);
				xmlWriter.setAutoFormatting(true);

				// Start the XML document
				xmlWriter.writeStartDocument();

				// Write the root element
				xmlWriter.writeStartElement("Engines");
				xmlWriter.writeEndElement(); // Close the root element

				// End the XML document
				xmlWriter.writeEndDocument();
				file.close();
			}
			addElementToXmlStream("QBoardEngines.xml", engineName, engineProtocol, enginePath);
		}
	}
}

void EngineManager::on_toolButton_2_clicked()
{
	const int currentRow = ui->engineTable->currentRow();
	if (currentRow == -1) return;
	AddEngineDialog *addEngineDialog = new AddEngineDialog(this);
	addEngineDialog->SetEngineName(ui->engineTable->item(currentRow, 0)->text());
	addEngineDialog->SetEngineProtocol(StringToEngineProtocol(ui->engineTable->item(currentRow, 1)->text()));
	addEngineDialog->SetEnginePath(ui->engineTable->item(currentRow, 2)->text());
	addEngineDialog->GetEngineName()->setStyleSheet("QLineEdit { background-color: lightgray; }");
	addEngineDialog->GetEngineName()->setReadOnly(true);
	addEngineDialog->exec();
	if (addEngineDialog->result() == QDialog::Accepted)
	{
		const QString engineName = addEngineDialog->GetEngineName()->text();
		const QString engineProtocol = addEngineDialog->GetEngineProtocol()->currentText();
		const QString enginePath = addEngineDialog->GetEnginePath()->text();
		if (engineName != "" && enginePath != "")
		{
			modifyXmlElement("QBoardEngines.xml", engineName, engineProtocol, enginePath);
			ui->engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
			ui->engineTable->setItem(currentRow, 1, new QTableWidgetItem(engineProtocol));
			ui->engineTable->setItem(currentRow, 2, new QTableWidgetItem(enginePath));
		}
	}
}

void EngineManager::on_toolButton_3_clicked()
{
	QItemSelectionModel *select = ui->engineTable->selectionModel();

	if (select->hasSelection())
	{
		QModelIndexList selectedRows = select->selectedRows();
		QMessageBox mb("Remove warning", "Do you want to remove this entry?",
			QMessageBox::Question,
			QMessageBox::Ok | QMessageBox::Default,
			QMessageBox::Cancel | QMessageBox::Escape,
			QMessageBox::NoButton, this);
		const int response = mb.exec();
		if (response == QMessageBox::Ok)
		{
			int cnt = selectedRows.size();
			for (int index = cnt - 1; index >= 0; index--)
			{
				QString engineName = ui->engineTable->item(selectedRows[index].row(), 0)->text();
				deleteXmlElementByAttribute("QBoardEngines.xml", "EngineName", engineName);
				ui->engineTable->removeRow(selectedRows[index].row());
			}
		}
	}
}

void EngineManager::on_buttonBox_accepted()
{
	accept();
}

void EngineManager::on_buttonBox_rejected()
{
	reject();
}
