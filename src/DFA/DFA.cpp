#include "../DFA/DFA.hpp"
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

DFA::DFA(string DFAConfigFile)
{
    _stateCount = 0;

    ifstream file(DFAConfigFile);
    string currLine;
    char TransitionLine[13];
    stringstream ss;
    int currentNum;
    int from;
    char currSymbol[2];
    int to;

    if (!file.is_open())
    {
        throw runtime_error("Failed to open file " + DFAConfigFile);
    }

    // initialising states
    getline(file, currLine);
    ss.clear();
    ss.str(currLine);
    ss >> _stateCount;

    // initialising start state
    getline(file, currLine);
    ss.clear();
    ss.str(currLine);
    ss >> currentNum;
    _startState = currentNum;

    // initialising end states
    getline(file, currLine);
    ss.clear();
    ss.str(currLine);

    while (ss >> currentNum)
    {
        _endStates.push_back(currentNum);
    }

    // initialising alphabet
    int newLineCount = 0;
    while (file.read(currSymbol, 2) && !(currSymbol[0] == '$' && currSymbol[1] == '$'))
    {
        addAlpha(currSymbol[0]);
    }

    getline(file, currLine);

    // initialising matrix
    initMatrix();

    // initialising transitions
    while (file.read(TransitionLine, 12))
    {
        TransitionLine[12] = '\0';
        currLine.assign(TransitionLine);
        insertTransitionString(currLine);
    }
}

DFA::DFA(int stateCount, vector<char> *alphabet)
{
    _stateCount = stateCount;

    for (char alpha : *alphabet)
    {
        addAlpha(alpha);
    }

    initMatrix();
}

DFA::DFA() : _mat(nullptr), _stateCount(0), _startState(0) {}

// adding new symbol to alphabet
void DFA::addAlpha(char alpha)
{
    isSymbolExistsErr(alpha, false);

    int nextIndex = _alphabetToIndex.size();
    _alphabetToIndex[alpha] = nextIndex;
}

void DFA::setStateCount(int numOfStates)
{
    if (numOfStates > 0)
    {
        _stateCount = numOfStates;
    }
    else
    {
        throw runtime_error("invalid number of states!");
    }
}

// sets a start state
// if the state dosent exists the function throws an error
void DFA::setStartState(int state)
{
    isStateExistsWErr(state, true);

    _startState = state;
}

// returns start state
int DFA::getStartState() const
{
    return _startState;
}

// adding an end state
// if the state dosent exists the function throws an error
void DFA::addEndState(int state)
{
    //if the number is not a state return an error
    isStateExistsWErr(state, true);
    
    _endStates.push_back(state);
}

//returns a read only vector of end states
const vector<int> &DFA::getEndStates() const
{
    return _endStates;
}

//returns a vector of the alphabet
vector<char> DFA::getAlphabet() const
{
    vector<char> alphabet;

    for (const auto& pair : _alphabetToIndex) {
        alphabet.push_back(pair.first);
    }

    return alphabet;
}

// initialising an empty dfa sized according to alphabet and number of states
void DFA::initMatrix()
{
    int length = _stateCount;
    int width = _alphabetToIndex.size();
    if (length > 0 && width > 0)
    {
        _mat = new int *[length];
        for (int i = 0; i < length; i++)
        {
            _mat[i] = new int[width];
        }

        // initing all transitions to -1 (trap state)
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < width; j++)
            {
                _mat[i][j] = -1;
            }
        }
    }
}

//inserts a new transition to the table
//if the transition with (from,alpha) allready exists it overrides it   
void DFA::insertTransition(int from, char alpha, int to)
{   
    // std::cout << "Inserting transition: "
    //       << "from = " << from
    //       << ", alpha = " << alpha
    //       << ", to = " << to << std::endl;
    // check if the state exists
    isStateExistsWErr(from, true);

    // check if alpha exists in alphabet
    isSymbolExistsErr(alpha, true);

    // check if the state exists
    isStateExistsWErr(to, true);

    // adding to the transition matrix
    int alphaIndex = _alphabetToIndex[alpha];

    _mat[from][alphaIndex] = to;
}

void DFA::insertTransitionString(string &transition)
{
    int from;
    char alpha;
    int to;

    from = stoi(transition.substr(0, 4)); // convert ascii to int
    alpha = transition[5];
    to = stoi(transition.substr(7, 4)); // convert ascii to int

    insertTransition(from, alpha, to);
}

int DFA::getState(int state, char alpha) const
{
    // check if the state exists
    isStateExistsWErr(state, true);

    // check if alpha exists in alphabet go to trap state
    if (!isSymbolExists(alpha))
        return -1;

    int res = _mat[state][_alphabetToIndex.at(alpha)];

    return res;
}

// Helper function to check if the state exists, returns an error message if not
bool DFA::isStateExsists(int state) const
{
    return state < _stateCount;
}

// Helper function to check if the symbol exists, returns an error message if not
bool DFA::isSymbolExists(char alpha) const
{
    auto alphabetIt = _alphabetToIndex.find(alpha);
    return (alphabetIt != _alphabetToIndex.end());
}

// checks if the state exists and compare the result with the wantedResult
// if there is no matching it prints an corresponding error
void DFA::isStateExistsWErr(int state, bool wantedResult) const
{
    if (isStateExsists(state) != wantedResult)
    {
        stringstream ss;
        ss << "state " << state << " does not exist!";
        throw runtime_error(ss.str());
    }
}

// checks if the symbol exists and compare the result with the wantedResult
// if there is no matching it prints an corresponding error
void DFA::isSymbolExistsErr(char alpha, bool wantedResult) const
{
    if (isSymbolExists(alpha) != wantedResult)
    {
        stringstream ss;
        ss << "Symbol " << alpha
           << (wantedResult ? "does not" : "allready exists")
           << " in the alphabet!";
        throw runtime_error(ss.str());
    }
}

void DFA::printMatrix() const
{
    unordered_map<int, char> indexToAlphabet;
    for (const auto &pair : _alphabetToIndex)
    {
        indexToAlphabet[pair.second] = pair.first; // Reverse key-value
    }

    // Print the alphabet (column headers)
    cout << "Symbols: ";
    for (int i = 0; i < indexToAlphabet.size(); i++)
    {
        cout << indexToAlphabet.at(i) <<'\t'<< " ";
    }
    cout << endl;

    int length = _stateCount;
    int width = _alphabetToIndex.size();
    // Print each row (transition for each state)
    for (int i = 0; i < length; i++)
    {
        cout << " State " << i << ": "; // Print the state index at the start of the row
        for (int j = 0; j < width; j++)
        {
            // Print transitions, replacing -1 (trap states) with 'T'
            if (_mat[i][j] == -1)
            {
                cout << '\t' <<'T';
            }
            else
            {
                cout << '\t' <<_mat[i][j];
            }
            cout << " ";
        }
        cout << endl;
    }
}

void DFA::writeDFAToFile(string dstFile)
{
    ofstream destf(dstFile);

    if (!destf)
    {
        std::cerr << "Error opening file: " << dstFile << std::endl;
        return;
    }

    destf << _stateCount << endl; // write state count

    destf << _startState << endl; // write start state

    // write end states
    for (int i = 0; i < _endStates.size(); i++)
    {
        destf << _endStates[i] << " ";
    }

    destf << endl;

    // write alphabet
    unordered_map<int, char> indexToAlphabet;
    for (const auto &pair : _alphabetToIndex)
    {
        indexToAlphabet[pair.second] = pair.first; // Reverse key-value
    }

    for (int i = 0; i < indexToAlphabet.size(); i++)
    {
        destf << indexToAlphabet.at(i) << " ";
    }
    destf << "$$" << endl;

    // write transitions
    for (int i = 0; i < _stateCount; i++)
    {
        for (int j = 0; j < indexToAlphabet.size(); j++)
        {
            int from = i;
            char alpha = indexToAlphabet.at(j);
            int to = getState(from, alpha);

            if (to != -1)
            {
                destf << left << setw(4) << setfill(' ') << i << " "
                      << alpha << " "
                      << left << setw(4) << setfill(' ') << getState(i, alpha) << endl;
            }
        }
    }

    destf.close();
}

// checks if a certain word is in the language
// returns a pair of values
// val 1-> is the word in the language
// val 2-> ending state
pair<bool, int> DFA::inLanguage(string &word) const
{
    int currState = _startState;
    int i = 0;

    while (currState != -1 && i < word.length())
    {
        currState = getState(currState, word[i]);
        i++;
    }

    bool isInLang = find(_endStates.begin(), _endStates.end(), currState) != _endStates.end();
    return make_pair(isInLang, currState);
}
