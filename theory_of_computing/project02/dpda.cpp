// Project 1: dpda
// Author: Nick Palutsis
// Class: CSE 30151
// Date: October 31, 2016

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <typeinfo>

using namespace std;

struct Rule {
	Rule(string, char, char, string, char, int num);
	friend ostream &operator<<(ostream &os, const Rule &n);

	string currentState;
	char input;
	char currTop;
	string nextState;
	char newTop;
	int number;
};

ostream &operator<<(ostream &os, const Rule &r);
Rule *readRule(istream &s, int num, vector<string> dpdaStates, vector<char> alphabet, vector<char> stackAlphabet);
bool isValidState(string state, vector<string> allStates);
bool isValidInput(char input, vector<char> alphabet);
bool isAccepted(string currentState, vector<string> acceptStates);

//================================================================================
//================================ Main Execution ================================
//================================================================================

int main(int argc, char *argv[]) {
	string line;
	vector<Rule> dpdaRules;
	string dpdaFILE;
	string startState;
	vector<char> alphabet;
	vector<char> stackAlphabet;
	stack<char> dpdaStack;
	vector<string> dpdaStates;
	vector<string> acceptStates;
	string currentState, nextState;

	cout << "Enter the name of a textfile with the rule set for a dpda: ";
	cin >> dpdaFILE;

	ifstream dpda;
	dpda.open(dpdaFILE.c_str());

	if (!getline(dpda, line)) {										// TITLE
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	cout << "\n   SOURCE: " << line << endl;


	if (!getline(dpda, line)) {										// ALPHABET
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

	if (!getline(dpda, line)) {										// STACK
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream stackStream(line);
	// Parse stack
	while (stackStream.peek() != '\n' && stackStream.peek() > 0) {
		while (stackStream.peek() != ',' && stackStream.peek() != '\n' && stackStream.peek() > 0)
			stackAlphabet.push_back(stackStream.get());
		stackStream.get();
	}
	cout << "    STACK: " << line << endl;


	if (!getline(dpda, line)) {										// ALL STATES
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream statesStream(line);
	string temp = "";
	// Parse string to find separate states and push to vector
	while (statesStream.peek() != '\n' && statesStream.peek() > 0) {
		while (statesStream.peek() != ',' && statesStream.peek() != '\n' && statesStream.peek() > 0)
			temp.push_back(statesStream.get());
		dpdaStates.push_back(temp);
		statesStream.get();
		temp = "";
	}
	cout << "   STATES: " << line << endl;
	// parse line to add states

	//
	if (!getline(dpda, line)) {										// START STATE
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	// startState = line;

	startState = "";
	stringstream startStream(line);
	// Parse string for starting states
	while (startStream.peek() != ',' && startStream.peek() != '\n' && startStream.peek() != 13 && startStream.peek() > 0)
		startState.push_back(startStream.get());
	startStream.get();
	// Check that start state is valid state
	if (!isValidState(startState, dpdaStates)) {
		cout << "Error: Invalid start state." << endl;
		return 0;
	}
	if (startState.empty()) cout << "Empty" << endl;
	cout << "    START: " << startState << endl;


	if (!getline(dpda, line)) {										// ACCEPT STATES
		cout << "Error: Improper file format." << endl;
		return 0;
	}
	stringstream acceptStream(line);
	// Parse string for accepting states
	while (acceptStream.peek() != '\n' && acceptStream.peek() > 0) {
		while (acceptStream.peek() != ',' && acceptStream.peek() != '\n' && acceptStream.peek() != 13 && acceptStream.peek() > 0)
			temp.push_back(acceptStream.get());
		acceptStates.push_back(temp);
		acceptStream.get();
		temp = "";
	}
	// Check that accepting states are valid
	bool match = false;
	for (size_t i = 0; i < acceptStates.size(); i++) {
		for (size_t j = 0; j < dpdaStates.size(); j++) {
			if (acceptStates[i] == dpdaStates[j])
				match = true;
		}
		if (!match) {
			cout << "Accepting states are not valid states" << endl;
			cout << "Size: " << acceptStates[i].length() << endl;
			return 0;
		}
		match = false;
	}
	cout << "ACCEPTING: " << line << endl;

	int ruleNum = 1;		// Assign numeric value to rules
	while(!dpda.eof())		// Read in Transition Rules
	{
		if (!getline(dpda, line)) {
			break;
		}
		// make stringstream
		stringstream s(line);

		// pass into function to make rule object
		Rule *r = readRule(s, ruleNum, dpdaStates, alphabet, stackAlphabet);
		dpdaRules.push_back(*r);
		ruleNum++;
		delete r;
	}
	dpda.close();

	cout << "\nRULES:" << endl;						// Print out rules
	for(size_t i = 0; i < dpdaRules.size(); i++) {
		if (dpdaRules[i].number < 10)
			cout << " ";
		cout << dpdaRules[i] << endl;
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
		bool ruleFound = false;
		while (s.peek() != '\n' && s.peek() > 0 && s.peek() != 13) {
			char input;
			if (isValidInput(s.peek(), alphabet))
				input = s.get();
			else {
				printf("Error: The input \"%c\" is not part of the alphabet.\n", s.peek());
				break;
			}
			ruleFound = false;
			for (size_t i = 0; i < dpdaRules.size(); i++) {			// Find matching rule

				if (currentState == dpdaRules[i].currentState) {	// Matches current state

					if (dpdaRules[i].input == '~') {	// Epsilon rule
						if (dpdaStack.top() == dpdaRules[i].currTop) {	// top of stack matches value to pop
							dpdaStack.pop();
							if (dpdaRules[i].newTop != '~')
								dpdaStack.push(dpdaRules[i].newTop);
							nextState = dpdaRules[i].nextState;
							if (step < 10)
								cout << " ";
							cout << step << "#" << dpdaRules[i] << endl;			// <Step#>#<Rule_Number>: <Initial_State_Name>,<Input_Symbol>,<top_of_stack>|<New_State_Name>,<New_stack>
							currentState = nextState;
							ruleFound = true;
							i = 0;
							step++;
						} else if (dpdaRules[i].currTop == '~') {
							// cout << "Stack matches" << endl;
							if (dpdaRules[i].newTop != '~')
								dpdaStack.push(dpdaRules[i].newTop);
							nextState = dpdaRules[i].nextState;
							if (step < 10)
								cout << " ";
							cout << step << "#" << dpdaRules[i] << endl;			// <Step#>#<Rule_Number>: <Initial_State_Name>,<Input_Symbol>,<top_of_stack>|<New_State_Name>,<New_stack>
							currentState = nextState;
							ruleFound = true;
							i = 0;
							step++;
						}
					}


					if (input == dpdaRules[i].input) {		// Rule with matching input
						if (dpdaStack.top() == dpdaRules[i].currTop) {		// top of stack matches value to pop
							dpdaStack.pop();
							if (dpdaRules[i].newTop != '~')
								dpdaStack.push(dpdaRules[i].newTop);
							nextState = dpdaRules[i].nextState;
							if (step < 10)
								cout << " ";
							cout << step << "#" << dpdaRules[i] << endl;			// <Step#>#<Rule_Number>: <Initial_State_Name>,<Input_Symbol>,<top_of_stack>|<New_State_Name>,<New_stack>
							currentState = nextState;
							ruleFound = true;
							break;
						} else if (dpdaRules[i].currTop == '~') {		// epsilon rule
							// cout << "Stack matches" << endl;
							if (dpdaRules[i].newTop != '~')
								dpdaStack.push(dpdaRules[i].newTop);
							nextState = dpdaRules[i].nextState;
							if (step < 10)
								cout << " ";
							cout << step << "#" << dpdaRules[i] << endl;			// <Step#>#<Rule_Number>: <Initial_State_Name>,<Input_Symbol>,<top_of_stack>|<New_State_Name>,<New_stack>
							currentState = nextState;
							ruleFound = true;
							break;
						}
					}
				}
			}
			if (!ruleFound){
				cout << "Error: No matching rule." << endl;
				break;
			}
			step++;
		}
		if (isAccepted(currentState, acceptStates) && ruleFound)
			cout << "Accepted" << endl;
		else
			cout << "Rejected" << endl;
		while (!dpdaStack.empty())
			dpdaStack.pop();
	}
	test.close();

	return 0;
}


//================================================================================
//================================ Functions =====================================
//================================================================================

Rule::Rule(string curr, char i, char ct, string next, char nt, int num){
	currentState = curr;
	input = i;
	currTop = ct;
	nextState = next;
	newTop = nt;
	number = num;
}

ostream &operator<<(ostream &os, const Rule &r) {
	os << r.number << ": " << r.currentState << "," << r.input << "," << r.currTop << "|" << r.nextState << "," << r.newTop;
	return os;
}

Rule *readRule(istream &s, int num, vector<string> dpdaStates, vector<char> alphabet, vector<char> stackAlphabet) {
	string current = "";
	char input, currTop, newTop;
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

	if (isValidInput(s.peek(), stackAlphabet))				// Value to pop
		currTop = s.get();
	else {
		cout << "Error: Invalid stack input \"" << s.peek() <<"\"" << endl;
		currTop = s.get();
	}

	if (s.peek() == ',' || s.peek() == '|')
		s.get();

	while (s.peek() != ',' && s.peek() != '\n' && s.peek() > 0) 	// Next state
		next.push_back(s.get());

	if (s.peek() == ',')
		s.get();

	if (isValidInput(s.peek(), stackAlphabet))				// Value to push
		newTop = s.get();
	else {
		cout << "Error: Invalid stack input \"" << s.peek() <<"\"" << endl;
		newTop = s.get();
	}

	return new Rule(current, input, currTop, next, newTop, num);
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
		if (input == alphabet[i] || input == '~')
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
