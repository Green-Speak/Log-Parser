#include "LogParser.h"
#include <fstream>
#include <iostream>

using namespace std;

LogParser::LogParser(const string& path)
    : filePath(path) {}

bool LogParser::loadFile() {
    ifstream file(filePath);

    // Konnte die Datei nicht geöffnet werden?
    if (!file.is_open()) {
        return false;
    }

    string line;

    // Zeilenweise einlesen
    while (getline(file, line)) {
        lines.push_back(line);
    }

    return true;
}

void LogParser::applyFilter(const string& filter) {
    countOccurrences(filter);
}

void LogParser::countOccurrences(const string& filter) {
    stats.clear();
    vector<LogHit> hits;

    if (filter.empty()) {
        for (size_t i = 0; i < lines.size(); ++i) {
            hits.push_back({ static_cast<int>(i + 1), lines[i] });
        }
        stats["ALL"] = hits;
        return;
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find(filter) != string::npos) {
            hits.push_back({ static_cast<int>(i + 1), lines[i] });
        }
    }

    stats[filter] = hits;
}



void LogParser::printStatistics() const {
    cout << "=== Log-Statistiken ===" << endl;

    for (const auto& entry : stats) {
        const string& filter = entry.first;
        const auto& hitLines = entry.second;

        cout << filter << ": " << hitLines.size() << " Treffer" << endl;

        for (const auto& hit : hitLines) {
            cout << "[Line " << hit.lineNumber << "] " << hit.content << endl;
        }

        cout << endl;
    }
}



