//
// Created by dybisz on 11/8/15.
//

#include "transition_table.h"

TransitionTable::TransitionTable() { }

TransitionTable::TransitionTable(string url) {
    ifstream file(url);

    if (file.is_open()) {
        _processInputData(file);
        file.close();
    }
    else {
        LOG_ERROR("Unable to open file " + url)
    }
}

void TransitionTable::_processInputData(istream &inputFileStream) {
    try {
        _loadAndLogNumberOfStates(inputFileStream);
        _loadAndLogNumberOfSymbols(inputFileStream);
        _loadAndLogDefaultTransitionTable(inputFileStream);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }
}

void TransitionTable::_loadAndLogNumberOfStates(istream &inputFileStream) {
    _numberOfStates = _loadOneSymbolFromFile(inputFileStream);
    LOG_DEBUG("_numberOfStates loaded; value: " + to_string(_numberOfStates))
}

void TransitionTable::_loadAndLogNumberOfSymbols(istream &inputFileStream) {
    _numberOfSymbols = _loadOneSymbolFromFile(inputFileStream);
    LOG_DEBUG("_numberOfSymbols loaded; value: " + to_string(_numberOfSymbols))
}

void TransitionTable::_loadAndLogDefaultTransitionTable(istream &inputFileStream) {
    if (_numberOfStates < 1 || _numberOfSymbols < 1) {
        throw invalid_argument("_numberOfStates < 1 || _numberOfSymbols < 1");
    }

    _loadEntries(inputFileStream);

    LOG_DEBUG("_entries loaded: " + _entriesToString());
}

int TransitionTable::_loadOneSymbolFromFile(istream &inputFileStream) {
    string mi;
    getline(inputFileStream, mi, ',');
    return stoi(mi);
}

void TransitionTable::_loadEntries(istream &inputFileStream) {
    int val;

    while (inputFileStream.good()) {
        val = _loadOneSymbolFromFile(inputFileStream);
        _entries.push_back(val);
    }
}

void TransitionTable::print() {
    _printSpecifications();
    _printEntries();
}

void TransitionTable::_printSpecifications() {
    cout << "states:  " << _numberOfStates << endl;
    cout << "symbols: " << _numberOfSymbols << endl;
}

string TransitionTable::_entriesToString() {
    string entries = "";
    for (auto i = _entries.begin(); i != _entries.end(); ++i) {
        entries += (to_string(*i) + " ");
    }
    return entries;
}

void TransitionTable::_printEntries() {
    cout << "entries: ";
    for (auto i = _entries.begin(); i != _entries.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;
}

int TransitionTable::getNumberOfSymbols() {
    return _numberOfSymbols;
}
