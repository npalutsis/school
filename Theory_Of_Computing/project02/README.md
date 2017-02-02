Project 1: Finite Automaton
===========================

Author: Nick Palutsis
Class: CSE 30131
Date: October 31, 2016

The C++ program **dpda.cpp** computes the states for a **deterministic pushdown automaton (DPDA)**. The program asks for two files as inputs from the user: one which provides the alphabets, states, and transition rules for the DPDA, and the other with test strings. It parses through the first file using stringstreams with `,` as the delimiter between lines. The alphabet, states, and accepting states are each stored in separate arrays, and the start state is stored as a string. The transition rules are stored in an array of Rule objects where each object stores the current state, input, next state, and number for the rule. These objects are then stored in their own vector.  

When the second file is opened, it is read in character by character. The program sets the initial state to the start state, and then searches for the rule that matches the current state, input read in, and the top of the stack to pop. If the input does not match a character in the alphabet or no matching rule can be found then an error will be displayed and the program will move on to the next test string. If one is found, then it prints the information to stdout and then sets the new current state to `nextState` for the rule. A rule may also match if the input or stack variable is `~` which represents *epsilon*. If this occurs, the machine will follow the transition without wasting the initial input which was read in. When it reaches the end of a line it will compare the current state to the vector of accepting states. If it matches any of them it will print "Accepted". Otherwise, it will print "Rejected." The program will then reset the state machine to its start state and read in the next test string. It will repeat this process until the end of the file.

To compile the program a simple Makefile is included which uses standard debugging flags and creates an executable **dpda**. There is also a file **dpda.txt** which is a custom DPDA, and another **test.txt** which contains a series of test strings. test.txt includes scenarios which are both accepted and rejected, and it also checks to ensure errors are thrown when there is no transition rule for the given state and input. The file `results.txt` holds the dumped outputs after running each test case.
