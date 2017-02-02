// Project 3: Turing Machine
// Author: Nick Palutsis
// Class: CSE 30151
// Date: December 1, 2016

#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>

using namespace std;

struct Rule {
	Rule(int, string, char, string, char, char);
	friend ostream &operator<<(ostream &os, const Rule &n);

	int number;
	string currentState;
	char tapeSymbol;
	string nextState;
	char newTapeSymbol;
	char direction;
};

ostream &operator<<(ostream &os, const Rule &r);
Rule *readRule(istream &s, int num, unordered_set<string> tmStates, unordered_set<char> alphabet);
bool isValidState(string state, unordered_set<string> allStates);
bool isValidInput(char input, unordered_set<char> alphabet);

//================================================================================
//================================ Main Execution ================================
//================================================================================

int main(int argc, char *argv[]) {
	string line;
	vector<Rule> tmRules;
	string tmFILE;
	string startState;
	string acceptState;
	string rejectState;
	unordered_set<char> inputAlphabet;
	unordered_set<char> tapeAlphabet;
	unordered_set<string> tmStates;
	string currentState, nextState;

	cout << "Enter the name of a textfile with the rule set for a turing machine: ";
	cin >> tmFILE;

	ifstream tm;
	tm.open(tmFILE.c_str());

	if (!getline(tm, line)) {										// Title
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	cout << "\n   SOURCE: " << line << endl;


	if (!getline(tm, line)) {										// Input alphabet
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream alphabetStream(line);
	// Parse alphabet
	while (alphabetStream.peek() != '\n' && alphabetStream.peek() > 0) {
		while (alphabetStream.peek() != ',' && alphabetStream.peek() != '\n' && alphabetStream.peek() >= ' ') {
			inputAlphabet.insert(alphabetStream.peek());
			tapeAlphabet.insert(alphabetStream.get());
		}
		alphabetStream.get();
	}
	cout << " ALPHABET: " << line << endl;

	if (!getline(tm, line)) {										// Tape alphabet
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream tapeStream(line);
	// Parse stack
	while (tapeStream.peek() != '\n' && tapeStream.peek() >= ' ') {
		while (tapeStream.peek() != ','&& tapeStream.peek() != '\n' && tapeStream.peek() >= ' ')
			tapeAlphabet.insert(tapeStream.get());
		tapeStream.get();
	}
	tapeAlphabet.insert('_');
	cout << "     TAPE: " << line << endl;

	if (!getline(tm, line)) {										// All states
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream statesStream(line);
	string temp = "";
	// Parse string to find separate states and push to vector
	while (statesStream.peek() != '\n' && statesStream.peek() > 0) {
		while (statesStream.peek() != '.'  && statesStream.peek() != '\n' && statesStream.peek() > 0)
			temp.push_back(statesStream.get());
		tmStates.insert(temp);
		statesStream.get();
		temp = "";
	}
	cout << "   STATES: " << line << endl;

	if (!getline(tm, line)) {										// START STATE
		cout << "Error: Improper file format." << endl;
		return 0;
	}

	startState = "";
	stringstream startStream(line);
	// Parse string for starting states
	while (startStream.peek() != '\n' && startStream.peek() != 13 && startStream.peek() > 0)
		startState.push_back(startStream.get());
	startStream.get();
	cout << "    START: " << startState << endl;

	if (!getline(tm, line)) {										// Accept STATE
		cout << "Error: Improper file format." << endl;
		return 0;
	}

	acceptState = "";
	stringstream acceptStream(line);
	// Parse string for accepting states
	while (acceptStream.peek() != '\n' && acceptStream.peek() != 13 && acceptStream.peek() > 0)
		acceptState.push_back(acceptStream.get());
	acceptStream.get();
	cout << "   ACCEPT: " << acceptState << endl;

	if (!getline(tm, line)) {										// reject STATE
		cout << "Error: Improper file format." << endl;
		return 0;
	}

	rejectState = "";
	stringstream rejectStream(line);
	// Parse string for rejecting states
	while (rejectStream.peek() != '\n' && rejectStream.peek() != 13 && rejectStream.peek() > 0)
		rejectState.push_back(rejectStream.get());
	rejectStream.get();
	cout << "   REJECT: " << rejectState << endl;

	// Read in transition rules
	int ruleNum = 1;		// Assign numeric value to rules
	while(!tm.eof())
	{
		if (!getline(tm, line)) {
			break;
		} else if (line.length() <= 1)
			break;
		// make stringstream
		stringstream s(line);
		// pass into function to make rule object
		Rule *r = readRule(s, ruleNum, tmStates, tapeAlphabet);
		tmRules.push_back(*r);
		ruleNum++;
		delete r;
	}
	tm.close();


	cout << "\nRULES:" << endl;						// Print out rules
	for(size_t i = 0; i < tmRules.size(); i++) {
		if (tmRules[i].number < 10)
			cout << " ";
		cout << tmRules[i] << endl;
	}

	string testFILE;
	cout << "\nEnter the name of an input test file: ";
	cin >> testFILE;

	ifstream test;
	test.open(testFILE.c_str());

	while(!test.eof())
	{
		string tape;
		int head = 0;
		int step = 1;
		currentState = startState;		// Initialize at start state

		if (!getline(test, line)) {
			break;
		}

		tape = "";
		stringstream tapeStream(line);
		// Create the tape for tm
		while (tapeStream.peek() != '\n' && tapeStream.peek() != 13 && tapeStream.peek() > ' ')
			tape.push_back(tapeStream.get());
		tapeStream.get();

		cout << "\nTape: " << tape << endl;

		for (size_t i = 0; i < tape.size(); i++) {	// Verify string matches the input alphabet
			if (!isValidInput(tape[i], inputAlphabet) && tape != "_") {
				printf("Error: The input \"%c\" is not part of the input alphabet.\n", tape[i]);
				startState = rejectState;
				break;
			}
		}
		tape.push_back('_');

		// Parse through input string
		while (currentState != acceptState && currentState != rejectState && step <= 200) {		// Quit if accepts, rejects, or loops
			if (!isValidInput(tape[head], tapeAlphabet)) {
				printf("Error: The input \"%c\" is not part of the tape alphabet.\n", tape[head]);
				break;
			}

			bool ruleFound = false;
			for (size_t i = 0; i < tmRules.size(); i++) {			// Find matching rule
				if (currentState == tmRules[i].currentState) {
					if (tape[head] == tmRules[i].tapeSymbol) {
						currentState = tmRules[i].nextState;
						tape[head] = tmRules[i].newTapeSymbol;

						// Print out matching in rule in specific format:
						// <Step#>@<Current_Tape_Head_Index>#<Rule_Number>:<Initial_State_Name>,<Current_Tape_Symbol>, | <New_State_Name>,<New_tape_symbol>,<New_tape_index>
						cout << step << "@" << head << "#" << tmRules[i].number << ":" << tmRules[i].currentState << "," << tmRules[i].tapeSymbol; 
						if (tmRules[i].direction == 'R') {
							if (tape[head] == '_')
								tape.push_back('_');
							head++;
						}
						else if (tmRules[i].direction == 'L' && head > 0)
							head--;
						cout << "|" << tmRules[i].nextState << "," << tmRules[i].newTapeSymbol << "," << head << endl;
						ruleFound = true;
						break;
					}
				}
			}
			if (!ruleFound){
				cout << "Error: No rule matching current state and input." << endl;
				break;
			}
			step++;
		}
		if (currentState == acceptState)
			cout << "Accepted: ";
		else if (currentState == rejectState)
			cout << "Rejected: ";
		else {
			cout << "Error: ";
		}
		for (size_t i = 0; i < tape.size(); i++) {
			if (tape[i] != '_')
				cout << tape[i];
			else
				break;
		}
		cout << endl;
	}
	test.close();

	return 0;
}


//================================================================================
//================================ Functions =====================================
//================================================================================

Rule::Rule(int num, string curr, char ts, string next, char nts, char d){
	number = num;
	currentState = curr;
	tapeSymbol = ts;
	nextState = next;
	newTapeSymbol = nts;
	direction = d;
}

ostream &operator<<(ostream &os, const Rule &r) {
	os << r.number << ": " << r.currentState << "," << r.tapeSymbol << "|" << r.nextState << "," << r.newTapeSymbol << "," << r.direction;
	return os;
}

Rule *readRule(istream &s, int num, unordered_set<string> tmStates, unordered_set<char> alphabet) {
	string currentState = "";
	char tapeSymbol;
	string nextState = "";
	char newTapeSymbol;
	char direction;

	while (s.peek() != ',' && s.peek() != '.' && s.peek() != '\n' && s.peek() > ' ')			// Start state
		currentState.push_back(s.get());
	s.get();
	if (isValidInput(s.peek(), alphabet))				// Current tape character
		tapeSymbol = s.get();
	else {
		cout << "Error: Invalid tape symbol \"" << s.peek() <<"\"" << endl;
		tapeSymbol = s.get();
	}

	if (s.peek() == '|') 
		s.get();

	while (s.peek() != ',' && s.peek() != '.' && s.peek() != '\n' && s.peek() > ' ') 	// Next state
		nextState.push_back(s.get());
	s.get();
	if (isValidInput(s.peek(), alphabet))				// Replacement tape character
		newTapeSymbol = s.get();
	else {
		cout << "Error: Invalid new tape symbol \"" << s.peek() <<"\"" << endl;
		newTapeSymbol = s.get();
	}
	s.get();
	if (s.peek() == 'L' || s.peek() == 'R')				// Input for direction
		direction = s.get();
	else {
		cout << "Error: Invalid direction \"" << s.peek() <<"\"" << endl;
		direction = s.get();
	}

	return new Rule(num, currentState, tapeSymbol, nextState, newTapeSymbol, direction);
}

bool isValidState(string state, unordered_set<string> allStates) {
	auto found = allStates.find(state);
	if (found == allStates.end())
		return false;
	else
		return true;
}

bool isValidInput(char input, unordered_set<char> alphabet) {
	auto found = alphabet.find(input);
	if (found == alphabet.end())
		return false;
	else
		return true;
}