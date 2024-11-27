#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class IniFile {
public:
    IniFile(const std::string& filename);

    // Function to get the value of a key in a section
    std::string get(const std::string& section, const std::string& key, const std::string& defaultValue = "") const;

private:
    std::map<std::string, std::map<std::string, std::string>> data;

    // Helper function to load and parse the INI file
    void load(const std::string& filename);

    // Helper function to trim spaces from both sides of a string
    static std::string trim(const std::string& str);
};
