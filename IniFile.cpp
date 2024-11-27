#include "IniFile.h"

IniFile::IniFile(const std::string& filename) {
	load(filename);
}

// Function to get the value of a key in a section
std::string IniFile::get(const std::string& section, const std::string& key, const std::string& defaultValue) const {
	const auto sectionIter = data.find(section);
	if (sectionIter != data.end()) {
		const auto keyIter = sectionIter->second.find(key);
		if (keyIter != sectionIter->second.end()) {
			return keyIter->second;
		}
	}
	return defaultValue;
}

// Helper function to load and parse the INI file
void IniFile::load(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Could not open the file: " << filename << std::endl;
		return;
	}

	std::string line, currentSection;
	while (getline(file, line)) {
		line = trim(line); // Trim spaces from the line

		if (line.empty() || line[0] == ';' || line[0] == '#') {
			// Ignore comments or empty lines
			continue;
		}

		if (line[0] == '[' && line.back() == ']') {
			// Section line
			currentSection = line.substr(1, line.size() - 2);
		}
		else {
			// Key-value line
			const size_t equalPos = line.find('=');
			if (equalPos != std::string::npos) {
				std::string key = trim(line.substr(0, equalPos));
				const std::string value = trim(line.substr(equalPos + 1));
				data[currentSection][key] = value;
			}
		}
	}

	file.close();
}

// Helper function to trim spaces from both sides of a std::string
std::string IniFile::trim(const std::string& str)
{
	const char* whitespace = " \t\n\r\f\v";
	const size_t start = str.find_first_not_of(whitespace);
	const size_t end = str.find_last_not_of(whitespace);
	return start == std::string::npos ? "" : str.substr(start, end - start + 1);
}
