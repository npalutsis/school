/* Author: Nick Palutsis
Date: April 20, 2016
CSE 20212
Lab 10 */

#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

int main() {

	string FILE;
	vector<string> doc;
	map<string, int> wordCount1;
	map<string, int> wordCount2;
	vector<set<string> > uniq;    //set storing vector for both docs

	// read in the 2 files to be word counted
	for ( int i = 0; i < 2; i++ ) {
		ifstream input_file;
		do {
			cout << "Enter file " << i+1 << "'s name: "; //prompt the user for names of files
			cin >> FILE; //reads file name user entered into FILE variable
			input_file.open( FILE.c_str() );
			if (!input_file )
				cout << "Error opening file " << FILE << "! Try again." << endl;
		} while ( !input_file );
		doc.push_back( FILE );
	}

	for ( int i = 0; i < 2; i++ ) {
		set<string> uniqueWords;
		uniq.push_back( uniqueWords );

		string word;
		char letter;                // the char read in from file
		ifstream input_file(doc[i].c_str()); // opens file

		while( !input_file.eof() ) {
			input_file.get( letter );   // read next character
			if( isalpha( letter ) )		// if it is a letter
				word.push_back( tolower( letter ) );  // convert to lowercase
			else if ( isspace( letter ) ) {       // if it is a space
				if( word != "" ) {        // make sure word was stored
					uniq[i].insert( word ); // add word to vector
					if ( i == 0 )		// add to first map
						wordCount1[word]++;
					else    // add to second map
						wordCount2[word]++;
					word = "";            //reset word
				}
			}
		}

		// print out the count of unique words
		cout << "\nNumber of unique words in file " << i+1 << ": " << uniq[i].size() << endl;
		cout << "Set of unique words in file " << i+1 << ":" << endl;

		int count = 0;
		cout << "Count\tWord\n=====\t====" << endl;
		for( set<string>::iterator it = uniq[i].begin(); it != uniq[i].end(); it++ ) {
			if (i == 0)
				cout  << wordCount1[*it] << "\t" << *it << endl;
			else
				cout  << wordCount2[*it] << "\t" << *it << endl;
			count++;
		}
	}

	set<string> intersection;
	set_intersection( uniq[0].begin(), uniq[0].end(), uniq[1].begin(),uniq[1].end(), inserter( intersection, intersection.begin() ) );

	set<string> unionSet = uniq[0];
	for( set<string>::iterator it = uniq[1].begin(); it != uniq[1].end(); it++ )
		unionSet.insert(*it);

	cout << "\nThe Jaccard similarity between the two files is " << (double) intersection.size() / unionSet.size() << endl;

	return 0;
}