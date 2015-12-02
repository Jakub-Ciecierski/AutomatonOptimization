//
// Created by dybisz on 11/13/15.
//

#include "bag_of_words.h"

BagOfWords::BagOfWords() { }

BagOfWords::BagOfWords(int minWordLength, int maxWordLength) : _minWordLength(minWordLength),
                                                               _maxWordLength(maxWordLength) {
    // Create empty entries
    for (int i = _minWordLength; i <= _maxWordLength; i++) {
        _bag[i];
    }
}

void BagOfWords::addWord(Word word) {
    _bag[word.length()].push_back(word);
    _numberOfWords++;
}

vector<Word> BagOfWords::getWordsOfLength(int length) {
    std::unordered_map<int, vector<Word>>::const_iterator got;
    got = _bag.find(length);

    if (got == _bag.end()) {
        vector<Word> foo;
        return foo;
    }
    else {
        return got->second;
    }
}

vector<Word> BagOfWords::getAllWords() {
    vector<Word> allWords;
    for (auto kv: _bag) {
        allWords = utils::concatenateVector(allWords, kv.second);
    }
    return allWords;
}


void BagOfWords::print() {
    string stringOut = "";
    std::vector<int> keys;
    keys.reserve(_bag.size());
    std::vector<vector<Word>> vals;
    vals.reserve(_bag.size());

    for (auto kv : _bag) {
        cout << "[" << kv.first << "]: ";
        cout << wordsToString(kv.second);
        cout << endl;
    }
}


string BagOfWords::wordsToString(vector<Word> words) {
    std::string stringOut = "";
    for (auto i = words.begin(); i != words.end(); ++i) {
        stringOut += "{ " + (((Word) *i).toString() + "} ");
    }
    return stringOut;
}

int BagOfWords::size() {
    return _numberOfWords;
}

bool BagOfWords::canWordBelongToTheBag(int length) {
    return (_minWordLength <= length) && (length <= _maxWordLength);
}

int BagOfWords::getMinWordLength() {
    return _minWordLength;
}

int BagOfWords::getMaxWordLength() {
    return _maxWordLength;
}

