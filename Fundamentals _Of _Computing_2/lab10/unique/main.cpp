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

	map <string, int> wordCount1;
	map <string, int> wordCount2;
	string word;
	string FILE1;
	string FILE2;

	cout << "Please enter the name of a file: " << endl;
	cin >> FILE1;

	ifstream infile1;
	infile1.open(FILE1.c_str());
	if( !infile1 )
		cout << "Error opening file " << FILE1 << "!" << endl;

	while (infile1 >> word){
		word.erase( remove_if(word.begin(), word.end(), ::ispunct ), word.end());
		transform( word.begin(), word.end(), word.begin(), ::tolower);
		wordCount1[word]++;
	}
	infile1.close();

	cout << "Please enter the name of another file: " << endl;
	cin >> FILE2;

	ifstream infile2;
	infile2.open(FILE2.c_str());
	if( !infile2 )
		cout << "Error opening file " << FILE2 << "!" << endl;

	while (infile2 >> word){
		word.erase( remove_if( word.begin(), word.end(), ::ispunct ), word.end() );
		transform( word.begin(), word.end(), word.begin(), ::tolower );
		wordCount2[word]++;
	}
	infile2.close();

	cout << "There are " << wordCount1.size() << " unique words in the first file." << endl;
	cout << "Unique words in the second file and their counts:" << endl;
	cout << "Count\tWord\n=====\t====" << endl;
	for( map<string, int>::const_iterator iter = wordCount2.begin(); iter != wordCount2.end(); ++iter )
		cout << iter->second << "\t" << iter->first << endl;

	return 0;
}
