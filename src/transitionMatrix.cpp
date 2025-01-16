#include "headers/transitionMatrix.hpp"

using namespace std;

// increases the state count and returns the new state
int transitionMatrix::addState()
{
    _stateCount++;
    return _stateCount - 1;
}

void transitionMatrix::addAlpha(char alpha)
{
    isSymbolExistsErr(alpha, false);

    int nextIndex = _alphabetToIndex.size();
    _alphabetToIndex[alpha] = nextIndex;
}

void transitionMatrix::initMatrix()
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

// Initialize the matrix as a 2D array of integers
transitionMatrix::transitionMatrix(vector<int> *states, vector<char> *alphabet)
{
    _mat = nullptr;

    for (int state : *states)
    {
        addState();
    }

    for (char alpha : *alphabet)
    {
        addAlpha(alpha);
    }

    initMatrix();
}

void transitionMatrix::insertTransition(int from, char alpha, int to)
{
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

void transitionMatrix::insertTransitionString(string &transition)
{
    int from;
    char alpha;
    int to;

    stringstream ss(transition);

    if (!(ss >> from >> alpha >> to))
    {
        throw runtime_error("Invalid transition format. Expected format: <from> <alpha> <to>");
    }

    insertTransition(from, alpha, to);
}

int transitionMatrix::getState(int state, char alpha) const
{
    // check if the state exists
    isStateExistsWErr(state, true);

    // check if alpha exists in alphabet go to trap state
    if (!isSymbolExists(alpha))
        return -1;

    int res = _mat[state][_alphabetToIndex.at(alpha)];

    return res;
}

transitionMatrix::transitionMatrix()
{
    _stateCount = 0;
    _mat = nullptr;
}

// Helper function to check if the state exists, returns an error message if not
bool transitionMatrix::isStateExsists(int state) const
{
    return state < _stateCount;
}

// Helper function to check if the symbol exists, returns an error message if not
bool transitionMatrix::isSymbolExists(char alpha) const
{
    auto alphabetIt = _alphabetToIndex.find(alpha);
    return (alphabetIt != _alphabetToIndex.end());
}

// same as the checkState() method but instad of returning a bool its throwing an error if the state is invalid
void transitionMatrix::isStateExistsWErr(int state, bool wantedResult) const
{
    if (isStateExsists(state) != wantedResult)
    {
        stringstream ss;
        ss << "state " << state << " does not exist!";
        throw runtime_error(ss.str());
    }
}

// same as the checkSymbol() method but instad of returning a bool its throwing an error if the state is invalid
//
void transitionMatrix::isSymbolExistsErr(char alpha, bool wantedResult) const
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

void transitionMatrix::printMatrix() const
{
    unordered_map<int, char> indexToAlphabet;
    for (const auto& pair : _alphabetToIndex) {
        indexToAlphabet[pair.second] = pair.first; // Reverse key-value
    }

    // Print the alphabet (column headers)
    cout << "Symbols: ";
    for (int i = 0; i < indexToAlphabet.size(); i++)
    {
        cout << indexToAlphabet.at(i) << " ";
    }
    cout << endl;

    int length = _stateCount;
    int width = _alphabetToIndex.size();
    // Print each row (transition for each state)
    for (int i = 0; i < length; i++)
    {
        cout << "State " << i << ": "; // Print the state index at the start of the row
        for (int j = 0; j < width; j++)
        {
            // Print transitions, replacing -1 (trap states) with 'T'
            if(_mat[i][j] == -1)
            {
                cout << 'T';
            }else{
                cout << _mat[i][j]; 
            }
            cout << " ";
        }
        cout << endl;
    }
}
