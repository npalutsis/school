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

  int fcount = 2; //counter for the number of files we are coparing
  vector<string> doc;
  map<string, int> wordcounter1;
  map<string, int> wordcounter2;
  vector<set<string> > uniq;    //set storing vector for both docs

  // read in the 2 files to be word counted
  for (int i=0; i < fcount; i++) {
	ifstream input_file;
	do {
	  cout << "Enter file " << i+1 << "'s name: "; //prompt the user for names of files
	  cin >> FILE; //reads file name user entered into FILE variable
	  input_file.open(FILE.c_str()
);
	  if (!input_file ) {
		cout << "Error opening file " << FILE << "! Try again." << endl;
	  }
	} while (!input_file);
	doc.push_back(FILE);
  }

  for (int i=0; i < fcount; i++) {
	set<string> uniqueWords;
	uniq.push_back(uniqueWords);

	string word;
	char letter;                //represents character in the inputfile.
	ifstream input_file(doc[i].c_str()); //opens the input file

	while(! input_file.eof()) { //while loop that continues until end of file is reached
	  input_file.get(letter);   //the next character is read into the stream
	  if(isalpha(letter)) { // check if the character is a letter
		word.push_back(tolower(letter));  //convert tolower using cctype lib
	  } else if (isspace(letter))
{       // check if the characteris a space
		if(word != "") {        //check if a word is stored
		  uniq[i].insert(word); //insert the current word to the vector
		  if (i == 0) { // if reading first input_file, add to firstmap
			wordcounter1[word]++;
		  } else {      // if reading second input_file, add to second map
			wordcounter2[word]++;
		  }
		  word = "";            //reset word
		}
	  }
	}


	//print out the count and the actual unique words.

	cout << "Count of unique words in file " << i+1 << ": " << uniq[i].size() << endl;
	cout << "Set of unique words in file " << i+1 << ":" << endl;



	int count = 0;
	for(set<string>::iterator it = uniq[i].begin(); it != uniq[i].end(); it++) {

	  if (i == 0) {
		cout  << *it << "---> " <<wordcounter1[*it]  << endl;
	  } else {
		cout  << *it << "---> " << wordcounter2[*it] << endl;
	  }
	  count++;
	}
  }

  set<string> intersection; //intersection of two sets is formed only by the elements that are presentin both sets
  set_intersection(uniq[0].begin(), uniq[0].end(), uniq[1].begin(),uniq[1].end(), inserter(intersection, intersection.begin()));

  //all the words from file 1 and2 are added to the union respectively
  set<string> unionOfSets = uniq[0]; //The union of two sets is formed by the elements that are present in either one of the sets, or inboth. Elements from the second range that have an equivalent element in the first range are not copied to the resulting range.
  for(set<string>::iterator it = uniq[1].begin(); it != uniq[1].end(); it++) {
	unionOfSets.insert(*it);
  }

  cout << "Jaccard similarity of file 1 and file 2: " << (double) intersection.size() / unionOfSets.size() << endl;

  return 0;


}