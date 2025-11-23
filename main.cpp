#include <iostream>
#include <string>
#include "LogParser.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Prüfen, ob mindestens ein Logdatei-Pfad übergeben wurde
    if (argc < 2) {
        cout << "Usage: logparser <logfile> [filter]" << endl;
        return 1;
    }

    string logfile = argv[1];
    string filter = "";

    // Optional: Filter als zweites Argument
    if (argc >= 3) {
        filter = argv[2];
    }

    LogParser parser(logfile);

    // Datei laden
    if (!parser.loadFile()) {
        cerr << "Fehler: Die Logdatei konnte nicht geoffnet werden." << endl;
        return 1;
    }

    // Filter anwenden
    parser.applyFilter(filter);

    // Ergebnisse ausgeben
    parser.printStatistics();

    return 0;
}
