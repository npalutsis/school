/* Author: Nick Palutsis
	Date: April 20, 2016
	CSE 20212
	Lab 10 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

int main (void) {

	map <string, int> english;
	map <string, int> french;
	string word;
	string FILE;
	string ENGLISH = "english.txt";		// list of unique english words
	string FRENCH = "french.txt";		// list of unique french words
	int englishSum = 0;
	int frenchSum = 0;

	ifstream infile;
	infile.open( ENGLISH.c_str() );
	if( !infile )
		cout << "Error opening english dictionary!" << endl;

	// Load english dictionary
	while( infile >> word ) {
		word.erase( remove_if( word.begin(), word.end(), ::ispunct ), word.end() );
		transform( word.begin(), word.end(), word.begin(), ::tolower );
		english[word];
	}
	infile.close();

	infile.open( FRENCH.c_str() );
	if( !infile )
		cout << "Error opening french dictionary!" << endl;

	// Load french dictionary
	while( infile >> word ) {
		word.erase( remove_if( word.begin(), word.end(), ::ispunct ), word.end() );
		transform( word.begin(), word.end(), word.begin(), ::tolower );
		french[word];
	}
	infile.close();

	cout << "Please enter the name of a file: " << endl;
	cin >> FILE;

	infile.open(FILE.c_str());
	if( !infile )
		cout << "Error opening file " << FILE << "!" << endl;

	// Count the word matches with each dictionary
	while (infile >> word){
		word.erase( remove_if( word.begin(), word.end(), ::ispunct ), word.end() );
		transform( word.begin(), word.end(), word.begin(), ::tolower );
		if( english.find( word ) != english.end() )
			english[word]++;
		if( french.find( word ) != french.end() )
			french[word]++;
	}
	infile.close();

	// Find the total number of matches
	for( map<string, int>::const_iterator iter = english.begin(); iter != english.end(); ++iter )
		englishSum += iter->second;
	for( map<string, int>::const_iterator iter = french.begin(); iter != french.end(); ++iter )
		frenchSum += iter->second;

	// Determine the language
	if( englishSum >= frenchSum )
		cout << "The file is in english." << endl;
	else
		cout << "The file is in french." << endl;
	return 0;
}
