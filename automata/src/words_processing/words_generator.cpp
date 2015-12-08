//
// Created by dybisz on 11/13/15.
//

#include <logger/log.h>
#include "words_generator.h"

WordsGenerator::WordsGenerator(vector<int> alphabet) : _alphabet(alphabet),
                                                       _omegaS(MIN_LENG_S, MAX_LENG_S),
                                                       _omegaM(MIN_LENG_M, MAX_LENG_M),
                                                       _omegaL(MIN_LENG_L, MAX_LENG_L),
                                                       _testSet(MIN_LENG_S, MAX_LENG_L) {
    try {
        utils::seed();
        //_checkGlobalConditions();
        //_fillBags();
		_fillTestBag(SIZE_S);
        //_createAllWordsUpToLength(R_MAX);
        printAllKLength(_alphabet, R_MAX);
        _generatePairs();
        _generateTestPairs();
        
        
		std::stringstream ss;
		ss << "Words Generated:" << std::endl;
		ss << "All up to length:   " << R_MAX << std::endl;
		ss << "Number of words:    " << _psoWords.size() << endl;
		ss << "Size Test:    	   " << SIZE_S;
		logger::log(File("words.txt"), ss.str());
        
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }
}

// Conditions specified in methodology
void WordsGenerator::_checkGlobalConditions() {

    if (SIZE_S + SIZE_M + SIZE_L > R_MAX) {
        throw invalid_argument("omega_s + omega_m + omega_l > r_max; check your flags.");
    }

    if (MAX_LENG_S >= MIN_LENG_M) {
        throw invalid_argument("MAX_LENG_S > MIN_LENG_M; words from omega_S might be longer than those in omega_M");
    }

    if (MAX_LENG_M >= MIN_LENG_L) {
        throw invalid_argument("MAX_LENG_M > MIN_LENG_L; words from omega_M might be longer than those in omega_L");
    }
}

void WordsGenerator::_fillBags() {
    _fillBagWithWords(_omegaS, SIZE_S);
    _fillBagWithWords(_omegaM, SIZE_M);
    _fillBagWithWords(_omegaL, SIZE_L);
    //_fillTestBag(R_MAX / 3);

    std::stringstream ss;
    ss << "Words Generated:" << std::endl;
    ss << "Size Small:   " << SIZE_S << std::endl;
    ss << "Size Medium:  " << SIZE_M << std::endl;
    ss << "Size Large:   " << SIZE_L << std::endl;
    ss << "Size Test:    " << R_MAX / 3;
    logger::log(File("words.txt"), ss.str());
}

void WordsGenerator::_fillTestBag(int numberOfTestWords) {
    // Produce as many alphabet words as words needed
    for (int i = 0; i < numberOfTestWords; i++) {
        int length = utils::generateRandomNumber(_testSet.getMinWordLength(), _testSet.getMaxWordLength());
        Word word = _generateRandomWordOverAlphabet(length);
        _testSet.addWord(word);
    }
}

void WordsGenerator::_fillBagWithWords(BagOfWords &bag, int numberOfWords) {
    int alphabetSize = _alphabet.size();
    bool moreWordsNeededThanSymbolsInAlphabet = numberOfWords > alphabetSize;

    if (moreWordsNeededThanSymbolsInAlphabet) {

        // Create alphabet based words
        for (unsigned int symbol = 0; symbol <= _alphabet.size()-1; symbol++) {
            int length = utils::generateRandomNumber(bag.getMinWordLength(), bag.getMaxWordLength());
            Word word = _generateWordStartingWith(bag, symbol, length);
            bag.addWord(word);
        }

        // Fill up rest of the space
        int restOfTheSpaceSize = numberOfWords - _alphabet.size();
        for (int i = 0; i < restOfTheSpaceSize; i++) {
            int length = utils::generateRandomNumber(bag.getMinWordLength(), bag.getMaxWordLength());
            Word word = _generateRandomWordOverAlphabet(length);
            bag.addWord(word);
        }

    } else {
        // Produce as many alphabet words as words needed
        for (int symbol = 0; symbol <= numberOfWords-1; symbol++) {
            int length = utils::generateRandomNumber(bag.getMinWordLength(), bag.getMaxWordLength());
            Word word = _generateWordStartingWith(bag, symbol, length);
            bag.addWord(word);
        }
    }
}

int WordsGenerator::hammingDistance(Word w1, Word w2) const {
    int distance = 0;

    if (w1.length() != w2.length()) {
        throw invalid_argument("words have different lengths!");
    }

    for (int i = 0; i < w1.length(); i++) {
        if (w1[i] != w2[i]) {
            distance++;
        }
    }

    return distance;
}

Word WordsGenerator::_generateWordStartingWith(BagOfWords &bag, int startingSymbol, int wordLength) {
    Word word;
    do {
        int length = utils::generateRandomNumber(0, bag.getMaxWordLength());
        word = _generateRandomWordOverAlphabet(length);
        word[0] = startingSymbol;
    } while (!_hammingConditionMet(word));

    return word;
}

Word WordsGenerator::_generateRandomWordOverAlphabet(int length) {
    Word word;

    for (int i = 0; i < length; i++) {
        int randomSymbol = _generateRandomSymbolFromAlphabet();
        word.appendSymbol(randomSymbol);
    }

    return word;
}

int WordsGenerator::_generateRandomSymbolFromAlphabet() {
    unsigned int size = _alphabet.size();

    int firstSymbol = _alphabet[0];
    int lastSymbol = _alphabet[size-1];

    return utils::generateRandomNumber(firstSymbol, lastSymbol);
}

// Check if word meets conditions regarding those already created
bool WordsGenerator::_hammingConditionMet(Word word) {
    vector<Word> wordsInSpecificOmega;
    int wordLength = word.length();

    if (_omegaS.canWordBelongToTheBag(wordLength)) {
        wordsInSpecificOmega = _omegaS.getWordsOfLength(word.length());
    } else if (_omegaM.canWordBelongToTheBag(wordLength)) {
        wordsInSpecificOmega = _omegaS.getWordsOfLength(word.length());
    } else if (_omegaL.canWordBelongToTheBag(wordLength)) {
        wordsInSpecificOmega = _omegaS.getWordsOfLength(word.length());
    } else {
        throw invalid_argument("word: " + word.toString()
                               + " can not belong to any bag, because its length is to big.");
    }

    return _checkHammingCondition(word, wordsInSpecificOmega);
}

bool WordsGenerator::_checkHammingCondition(Word word, vector<Word> wordsToCompare) {

    int acceptableHammingDistance = _calculateAcceptableHammingDistance(word.length());

    if (acceptableHammingDistance < 1) acceptableHammingDistance = 1;

    for (auto i = wordsToCompare.begin(); i != wordsToCompare.end(); ++i) {
        int distance = hammingDistance(word, *i);

        if (distance < acceptableHammingDistance) {
            LOG_DEBUG("word: " + word.toString() + " and " + (*i).toString()
                      + " have wrong hamming distance: " + to_string(distance) +
                      " starting over ...");
            return false;
        }
    }

    return true;
}


int WordsGenerator::_calculateAcceptableHammingDistance(int length) {
    return length / 2;
}

void WordsGenerator::_generatePairs() {
    //vector<Word> allWords = _collectAllWordsFromBags();
    _pairs = _combineIntoPairs(_psoWords);
}

void WordsGenerator::_generateTestPairs() {
    vector<Word> allTestWords = _testSet.getAllWords();
    _testPairs = _combineIntoPairs(allTestWords);
}

vector<Word> WordsGenerator::_collectAllWordsFromBags() {
    vector<Word> wordsOmegaS = _omegaS.getAllWords();
    vector<Word> wordsOmegaM = _omegaM.getAllWords();
    vector<Word> wordsOmegaL = _omegaL.getAllWords();
    vector<Word> allWords = utils::mergeVectors(wordsOmegaS, wordsOmegaM, wordsOmegaL);

    return allWords;
}

vector<PairOfWords> WordsGenerator::_combineIntoPairs(vector<Word> words) {
    vector<PairOfWords> pairs;
    for (unsigned int i = 0; i < words.size() - 1; i++) {
        for (unsigned int j = i; j < words.size(); j++) {
            PairOfWords pairOfWords(words[i], words[j]);
            pairs.push_back(pairOfWords);
        }
    }
    return pairs;
}

vector<PairOfWords> *WordsGenerator::getPairs() {
    return &_pairs;
}

vector<PairOfWords> *WordsGenerator::getTestPairs() {
    return &_testPairs;
}

void WordsGenerator::print() {
    cout << "OMEG_S:\n";
    _omegaS.print();
    cout << "OMEG_M:\n";
    _omegaM.print();
    cout << "OMEG_L:\n";
    _omegaL.print();
}

/////////// NEW SET OF FUNCTIONS //////////////////

void WordsGenerator::_createAllWordsUpToLength(int N) {
	
	// Prepare local copy of the alphabet
	vector<int> local_alph_cp;
	local_alph_cp.reserve(_alphabet.size());
	copy(_alphabet.begin(),_alphabet.end(),back_inserter(local_alph_cp));
	
	// Create consecutive permutations and save them
	sort(local_alph_cp.begin(), local_alph_cp.end());
	do {
		Word _w(local_alph_cp);
		_psoWords.push_back(_w);
	} while (next_permutation(local_alph_cp.begin(), local_alph_cp.end()));	
  	
  	//for(unsigned int i = 0; i < _psoWords.size() ; i++) {
	//	cout << _psoWords[i].toString() << endl;
	//}
	 	
}

void WordsGenerator::printAllKLength(vector<int> alphabet, int k) {
        int n = alphabet.size();  
        Word word;      
        printAllKLengthRec(alphabet, word, n, k);
}
 
// The main recursive method to print all possible strings of length k
void WordsGenerator::printAllKLengthRec(vector<int> alphabet, Word word, int n, int k) {
	 
	// Base case: k is 0, print prefix
	if (k == 0) {
		//cout << word.toString();
		_psoWords.push_back(word);
		return;
	}

	// One by one add all characters from set and recursively 
	// call for k equals to k-1
	for (int i = 0; i < n; ++i) {
		 //cout << i << endl;
		// Next character of input added
		word.appendSymbol(alphabet[i]);
		Word new_prefix(word);
	
		// k is decreased, because we have added a new character
		printAllKLengthRec(alphabet, new_prefix, n, k - 1); 
	}
}




