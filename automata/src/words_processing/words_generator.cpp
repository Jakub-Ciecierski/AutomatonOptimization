//
// Created by dybisz on 11/13/15.
//

#include <logger/log.h>
#include "words_generator.h"
WordsGenerator::WordsGenerator(vector<int> alphabet) {}
WordsGenerator::WordsGenerator(string url) {
  _loadWordsFromFile(url);
}
WordsGenerator::WordsGenerator(vector<int> alphabet,
                               int c, int trainSetCount,
                               int trainSetMaxLength,
                               int testSetCount,
                               int testSetMaxLength) :
        _alphabet(alphabet),
        _C(c),
        _wordsInTrainingSet(trainSetCount),
        _maxWordLengthTraining(c + trainSetMaxLength),
        _wordsInTestingSet(testSetCount),
        _maxWordLengthTesting(c + testSetMaxLength) {
    try {
        utils::seed();
        _calculateNumberOfWords();
        _checkGlobalConditions();
        _generateWords();
        _saveWordsToFIle();
        _printInfo();
    }
        catch (std::exception &e) {
        LOG_ERROR(e.what())
    }
}

WordsGenerator::~WordsGenerator(){
    for(unsigned int i = 0; i < _trainingAllSet.size(); i++){
        delete _trainingAllSet[i];
    }
    for(unsigned int i = 0; i < _testSet.size(); i++){
        delete _testSet[i];
    }
}

const vector<Word*>* WordsGenerator::getTrainingAllSet() const{
    return &_trainingAllSet;
}
const vector<Word*>* WordsGenerator::getTrainingShortSet() const{
    return &_trainingShortSet;
}

const vector<Word*>* WordsGenerator::getTrainingLongSet() const{
    return &_trainingLongSet;
}

const vector<Word*>* WordsGenerator::getTestSet() const{
    return &_testSet;
}

void WordsGenerator::_loadWordsFromFile(string url) {
    cout << "Opening file: " << url << endl;
    std::ifstream infile(url);
    string line;

    // HEADER PART
    _loadHeader(infile);

    //ALPHABET
    std::getline(infile, line);
    istringstream iss(line);
    int alphabet;
    iss >> alphabet;
    _createAlphabet(alphabet);

    // SKIP shit
    _loadHeader(infile);

    // FIRST subset
    _trainingShortSet = _parseWords(infile);

    // SECOND subset
    _trainingLongSet = _parseWords(infile);

    // TESTING set
    _testSet = _parseWords(infile);

    // Append Training All with both subsets
    for(unsigned int i = 0; i < _trainingShortSet.size();i++){
        _trainingAllSet.push_back(_trainingShortSet[i]);
    }
    for(unsigned int i = 0; i < _trainingLongSet.size();i++){
        _trainingAllSet.push_back(_trainingLongSet[i]);
    }

}
void WordsGenerator::_loadHeader(ifstream & infile) {
  string line;
  while (std::getline(infile, line))
  {
    istringstream iss(line);
    char  firstSymbol;
    if (!(iss >> firstSymbol)) { break; } // error
    if(firstSymbol == '[') break;
  }
  std::getline(infile, line);
}
void WordsGenerator::_createAlphabet(int n) {
    for(int i = 0; i < n ; i++) {
      _alphabet.push_back(i);
    }
    cout << "Alphabet loaded: " << utils::vectorToString(_alphabet) << endl;
}

vector<Word*> WordsGenerator::_parseWords(ifstream & infile) {
  string line;
  vector<Word*> words;


  while (infile)
  {
    string s;
    if (!getline( infile, s )) break;
    if(s[0] == '[') break;

    istringstream ss( s );
    vector <string> record;
    Word* _word = new Word();
    while (ss)
    {
      string s;
      if (!getline( ss, s, ',' )) break;
      _word->appendSymbol(stoi(s));
    }

    if(_word->length() !=0) words.push_back(_word);
  }

  // for(int i = 0 ; i < words.size(); i++) {
  //   if(words[i].length() == 0) cout << "{}" << endl;
  //   else
  //   cout << words[i].toString() << endl;
  // }
  cout << "SET SIZE:" << words.size() << endl;

  return words;
}

void WordsGenerator::_saveWordsToFIle() {
  fstream file;
    std::stringstream ss;
    ss << "./res/words_C" << this->_C
        << "_Train" << this->_wordsInTrainingSet
        << "_Test" << this->_wordsInTestingSet
        << ".txt";

  file.open(ss.str() ,fstream::out);

  //INFO
  file << "#TRAINING SET CONST: " << _firstSubset.size() << endl;
  file << "#TRAINING SET RAND: " << _secondSubset.size() <<endl;
  file << "#TESTING SET: " << _testingSet.size() << endl << endl;

  // Alphabet
  file << "[ALPHABET]" << endl;
  file << _alphabet.size() << endl << endl;

  // First subset
  file << "[TRAINING SET CONST]" << endl;
  for(auto iter = _firstSubset.begin() ; iter != _firstSubset.end() ; ++iter) {
    file << iter->toString() << endl;
  }
  file << endl;

  // Second subset
  file << "[TRAINING SET RAND]" << endl;
  for(auto iter = _secondSubset.begin() ; iter != _secondSubset.end() ; ++iter) {
    file << iter->toString() << endl;
  }
  file << endl;

  // Testing subset
  file << "[TESTING SET]" << endl;
  for(auto iter = _testingSet.begin() ; iter != _testingSet.end() ; ++iter) {
    file << iter->toString() << endl;
  }

  file.close();
}

void WordsGenerator::_calculateNumberOfWords() {
  _wordsInFirstSubset = 0;
    for(int i = 1; i <= _C; i++) {
        _wordsInFirstSubset += pow(_alphabet.size(), i);
        cout << _wordsInFirstSubset << endl;
    }
    _wordsInSecondSubset = _wordsInTrainingSet - _wordsInFirstSubset;
}

// Conditions specified in methodology
void WordsGenerator::_checkGlobalConditions() {
  if (_wordsInSecondSubset < _wordsInFirstSubset) {
      throw invalid_argument("Too few words in training set.");
  }

  if(_wordsInTestingSet < _wordsInTrainingSet) {
      throw invalid_argument("Less words in testing set than in training one");
  }
}

void WordsGenerator::_generateWords() {
  _firstSubset = _createAllWordsUpToLength(_C);
  cout << "firstSubset created\n";
  _secondSubset = _createRandomWordsOfLengthInInterval(_C+1, _maxWordLengthTraining, _wordsInSecondSubset);
  cout << "secondSubset created\n";
  _trainingSet = utils::concatenateVector(_firstSubset, _secondSubset);
  cout << "trainingSet created\n";
  _testingSet = _createRandomWordsOfLengthInInterval(_maxWordLengthTraining+1, _maxWordLengthTesting, _wordsInTestingSet);
  cout << "testingSet created\n";
}

// Creates all possible words of length from interval <0,N>.
vector<Word> WordsGenerator::_createAllWordsUpToLength(int N) {
  int alphabet_size = _alphabet.size();
  vector<Word> _wordsList;

	if(N == 0) return _wordsList;

  _wordsList = _initBaseWords();

	for(int n = 1; n < N; n++) {
		vector<Word> _wordsOfSizeN = _getWordsOfSizeN(_wordsList, n);
		for(unsigned int i = 0; i < _wordsOfSizeN.size(); i++) {
				for(int a = 0; a < alphabet_size; a++) {
						Word w = _wordsOfSizeN[i];
						w.appendSymbol(a);
						_wordsList.push_back(w);
				}
			}
	}

	return _wordsList;
}

vector<Word> WordsGenerator::_initBaseWords() {
  vector<Word> output;
  int alphabet_size = _alphabet.size();
	for(int symbol = 0; symbol < alphabet_size; ++symbol) {
		Word _base;
		_base.appendSymbol(symbol);
		output.push_back(_base);
	}
  return output;
}

vector<Word> WordsGenerator::_getWordsOfSizeN(vector<Word> _wordsList, int n) {
    vector<Word> wordsOfSizeN;
    for(unsigned int word = 0; word < _wordsList.size(); word++) {
        Word w = _wordsList[word];
        if(w.length() == n) {
            wordsOfSizeN.push_back(w);
        }
    }
    return wordsOfSizeN;
}

vector<Word> WordsGenerator::_createRandomWordsOfLengthInInterval(int min, int max, int count) {
    vector<Word> randomWords;
    for(int w = 0; w < count; w++) {
      int length = utils::generateRandomNumber(min, max+1);
      Word word = _generateRandomWordOverAlphabet(length);
      randomWords.push_back(word);
    }

    return randomWords;

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

Word WordsGenerator::_generateRandomWordOverAlphabet(int length) {
    Word word;

    for (int i = 0; i < length; i++) {
        int randomSymbol = _generateRandomSymbolFromAlphabet();
        word.appendSymbol(randomSymbol);
    }

    return word;
}

int WordsGenerator::_generateRandomSymbolFromAlphabet() {
    int firstSymbol = _alphabet[0];
    int lastSymbol = _alphabet.size();

    return utils::generateRandomNumber(firstSymbol, lastSymbol);
}

vector<PairOfWords> WordsGenerator::_combineIntoPairs(vector<Word> words) {
    vector<PairOfWords> pairs;
    // for (unsigned int i = 0; i < words.size() - 1; i++) {
    //     for (unsigned int j = i; j < words.size(); j++) {
    //         PairOfWords pairOfWords(words[i], words[j]);
    //         pairs.push_back(pairOfWords);
    //     }
    // }
    return pairs;
}

vector<PairOfWords>* WordsGenerator::getPairs() {
    return NULL;
}

vector<PairOfWords>* WordsGenerator::getTestPairs() {
    return NULL;
}

void WordsGenerator::print() {
  cout << "[TRAINING SET]" << endl;

  for(auto iter = _trainingSet.begin(); iter != _trainingSet.end(); ++iter) {
    cout << (*iter).toString() << endl;
  }


  cout << "[TESTING SET]" << endl;

  for(auto iter = _testingSet.begin(); iter != _testingSet.end(); ++iter) {
    cout << (*iter).toString() << endl;
  }
}


void WordsGenerator::_printInfo() {
  std::stringstream ss;
  // ss << "Words Generated:" << std::endl;
  // ss << "All up to length:   " << R_MAX << std::endl;
  // ss << "Number of words:    " << _psoWords.size() << endl;
  // ss << "Size Test:    	   " << SIZE_S;
  logger::log(File("words.txt"), ss.str());
}
