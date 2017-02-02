// Project 1: DFA
// Author: Nick Palutsis
// Class: CSE 30151
// Date: September 26, 2016

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Rule {
	Rule(string, char, string, int num);
	friend ostream &operator<<(ostream &os, const Rule &n);

	string currentState;
	char input;
	string nextState;
	int number;
};

ostream &operator<<(ostream &os, const Rule &r);
Rule *readRule(istream &s, int num, vector<string> dfaStates, vector<char> alphabet);
bool isValidState(string state, vector<string> allStates);
bool isValidInput(char input, vector<char> alphabet);
bool isAccepted(string currentState, vector<string> acceptStates);

//================================================================================
//================================ Main Execution ================================
//================================================================================

int main(int argc, char *argv[]) {
	string line;
	vector<Rule> dfaRules;
	string dfaFILE;
	string startState;
	vector<char> alphabet;
	vector<string> dfaStates;
	vector<string> acceptStates;
	string currentState, nextState;

	cout << "Enter the name of a textfile with the rule set for a DFA: ";
	cin >> dfaFILE;

	ifstream dfa;
	dfa.open(dfaFILE.c_str());

	if (!getline(dfa, line)) {										// TITLE
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	cout << "\n   SOURCE: " << line << endl;


	if (!getline(dfa, line)) {										// ALPHABET
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream alphabetStream(line);
	// Parse alphabet
	while (alphabetStream.peek() != '\n' && alphabetStream.peek() > 0) {
		while (alphabetStream.peek() != ',' && alphabetStream.peek() != '\n' && alphabetStream.peek() > 0)
			alphabet.push_back(alphabetStream.get());
		alphabetStream.get();
	}
	cout << " ALPHABET: " << line << endl;


	if (!getline(dfa, line)) {										// ALL STATES
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream statesStream(line);
	string temp = "";
	// Parse string to find separate states and push to vector
	while (statesStream.peek() != '\n' && statesStream.peek() > 0) {
		while (statesStream.peek() != ',' && statesStream.peek() != '\n' && statesStream.peek() > 0)
			temp.push_back(statesStream.get());
		dfaStates.push_back(temp);
		statesStream.get();
		temp = "";
	}
	cout << "   STATES: " << line << endl;
	// parse line to add states


	if (!getline(dfa, line)) {										// START STATE
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	// Check that start state is valid state
	if (isValidState(line, dfaStates)) {
		// cout << "Start State is Valid" << endl;
		startState = line;
	}
	cout << "    START: " << startState << endl;


	if (!getline(dfa, line)) {										// ACCEPT STATES
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream acceptStream(line);
	// Parse string for accepting states
	while (acceptStream.peek() != '\n' && acceptStream.peek() > 0) {
		while (acceptStream.peek() != ',' && acceptStream.peek() != '\n' && acceptStream.peek() > 0)
			temp.push_back(acceptStream.get());
		acceptStates.push_back(temp);
		acceptStream.get();
		temp = "";
	}
	// Check that accepting states are valid
	bool match = false;
	for (size_t i = 0; i < acceptStates.size(); i++) {
		for (size_t j = 0; j < dfaStates.size(); j++) {
			if (acceptStates[i] == dfaStates[j])
				match = true;
		}
		if (!match) {
			cout << "Accepting states are not valid states" << endl;
			return 0;
		}
		match = false;
	}
	cout << "ACCEPTING: " << line << endl;


	int ruleNum = 1;		// Assign numeric value to rules
	while(!dfa.eof())		// Read in Transition Rules
	{
		if (!getline(dfa, line)) {
			break;
		}
		// make stringstream
		stringstream s(line);

		// pass into function to make rule object
		Rule *r = readRule(s, ruleNum, dfaStates, alphabet);
		dfaRules.push_back(*r);
		ruleNum++;
		delete r;
	}
	dfa.close();
	
	cout << "\nRULES:" << endl;						// Print out rules
	for(size_t i = 0; i < dfaRules.size(); i++) {
		if (dfaRules[i].number < 10)
			cout << " ";
		cout << dfaRules[i] << endl;
	}

	string testFILE;
	cout << "\nEnter the name of an input test file: ";
	cin >> testFILE;

	ifstream test;
	test.open(testFILE.c_str());

	while(!test.eof())
	{
		if (!getline(test, line)) {
			break;
		}
		// make stringstream
		stringstream s(line);
		cout << "\nString: " << line << endl;

		int step = 1;
		currentState = startState;		// Initialize at start state

		// Parse through input string
		while (s.peek() != '\n' && s.peek() > 0) {
			char input;
			if (isValidInput(s.peek(), alphabet))
				input = s.get();
			else {
				printf("Error: The input \"%c\" is not part of the alphabet.\n", s.peek());
				break;
			}
			bool ruleFound = false;
			for (size_t i = 0; i < dfaRules.size(); i++) {			// Find matching rule
				if (currentState == dfaRules[i].currentState) {
					if (input == dfaRules[i].input) {
						nextState = dfaRules[i].nextState;
						cout << step << "#" << dfaRules[i] << endl;			// <Step#>#<Rule_Number>: <Initial_State_Name>,<Input_Symbol>,<New_State_Name>
						currentState = nextState;
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
		if (isAccepted(currentState, acceptStates))
			cout << "Accepted" << endl;
		else
			cout << "Rejected" << endl;
	}
	test.close();

	return 0;
}


//================================================================================
//================================ Functions =====================================
//================================================================================

Rule::Rule(string curr, char i, string next, int num){
	currentState = curr;
	input = i;
	nextState = next;
	number = num;
}

ostream &operator<<(ostream &os, const Rule &r) {
	os << r.number << ": " << r.currentState << "," << r.input << "," << r.nextState;
	return os;
}

Rule *readRule(istream &s, int num, vector<string> dfaStates, vector<char> alphabet) {
	string current = "";
	char input;
	string next = "";

	while (s.peek() != ',' && s.peek() != '\n')			// Start state
		current.push_back(s.get());

	if (s.peek() == ',')
		s.get();

	if (isValidInput(s.peek(), alphabet))				// Input for transition
		input = s.get();
	else {
		cout << "Error: Invalid transition input \"" << s.peek() <<"\"" << endl;
		input = s.get();
	}
	if (s.peek() == ',') 
		s.get();

	while (s.peek() != ',' && s.peek() != '\n' && s.peek() > 0) 	// Next state
		next.push_back(s.get());

	return new Rule(current, input, next, num);
}

bool isValidState(string state, vector<string> allStates) {
	for(size_t i = 0; i < allStates.size(); i++) {
    	if (state == allStates[i])
    		return true;
	}
	return false;
}

bool isValidInput(char input, vector<char> alphabet) {
	for (size_t i = 0; i < alphabet.size(); i++) {
		if (input == alphabet[i])
			return true;
	}
	return false;
}

bool isAccepted(string currentState, vector<string> acceptStates) {
	for (size_t i = 0; i < acceptStates.size(); i++) {
		if (currentState == acceptStates[i])
			return true;
	}
	return false;
}