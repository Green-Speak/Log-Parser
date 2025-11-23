#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

struct LogHit {
    int lineNumber;
    string content;
};

class LogParser {
public:
    explicit LogParser(const string& path)
        : filePath(path) {}

    // Datei laden
    bool loadFile() {
        ifstream file(filePath);
        if (!file.is_open()) {
            return false;
        }

        lines.clear();
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }

        return true;
    }

    // Filter anwenden
    void applyFilter(const string& filter) {
        countOccurrences(filter);
    }

    // Statistiken ausgeben
    void printStatistics() const {
        cout << "=== Log-Statistiken ===" << endl;

        for (const auto& entry : stats) {
            const string& filter = entry.first;
            const auto& hitLines = entry.second;

            cout << filter << ": " << hitLines.size() << " Treffer" << endl;

            for (const auto& hit : hitLines) {
                cout << "[Line " << hit.lineNumber << "] " << hit.content << endl;
            }

            cout << endl; // Leerzeile zwischen Filtern
        }
    }

    // Zugriff auf die Statistik-Daten
    const unordered_map<string, vector<LogHit>>& getStatisticsMap() const {
        return stats;
    }

    // Statistik zurücksetzen
    void clearStatistics() {
        stats.clear();
    }

private:
    string filePath;  // Pfad zur Logdatei
    vector<string> lines;  // Eingelesene Zeilen
    unordered_map<string, vector<LogHit>> stats; // Filter → Trefferliste

    // Zählt Treffer und speichert Zeilen mit Nummer
    void countOccurrences(const string& filter) {
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
};
