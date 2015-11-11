//
// Created by dybisz on 11/8/15.
//

#include "transition_table.h"

void TransitionTable::loadFromFile(string url) {
    ifstream file(url);

    if (file.is_open()) {
        _processInputData(file);
        file.close();
    }
    else {
        cout << "[ERROR] Unable to open file\n";
    }

}

void TransitionTable::_processInputData(istream &inputFileStream) {
    try {
        _numberOfStates = _loadOneSymbolFromFile(inputFileStream);
        _numberOfSymbols = _loadOneSymbolFromFile(inputFileStream);
        _defaultTransitionTable = _loadDefaultTransitionTable(inputFileStream);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }
    cout << "\n# states: " << _numberOfStates << " # symbols: " << _numberOfSymbols << endl;
}

int TransitionTable::_loadOneSymbolFromFile(istream &inputFileStream) {
    string mi;
    getline(inputFileStream, mi, ',');
    return stoi(mi);
}

int **TransitionTable::_loadDefaultTransitionTable(istream &inputFileStream) {

    if (_numberOfStates > 1 || _numberOfSymbols < 1) {
        throw invalid_argument("_numberOfStates < 1 || _numberOfSymbols < 1");
    }

//    TODO(dybisz) FINISH LEL
//    while (inputFileStream.good()) {
//        cout << _loadOneSymbolFromFile(inputFileStream) << " ";
//    }

    return NULL;
}

void TransitionTable::_deleteDefaultTransitionTable() {
    // check for errors;
}
