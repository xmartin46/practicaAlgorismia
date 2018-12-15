#include <iostream>		// cout
#include <algorithm>    // random_shuffle
#include <cstdlib>		// srand, rand
#include <vector>		// vector
#include <string>		// string
#include <fstream>		// open, close, 
#include "constAndRand.h"
using namespace std;

vector<int> randomize(int n) {
	// Insert all the first 50 integers
	vector<int> myvector(n);
 	for (int i = 0; i < n; ++i) myvector[i] = i;
 	
 	// using built-in random generator:
  	random_shuffle(myvector.begin(), myvector.end());

  	return myvector;
}

void putVector(vector<string> &v, const string filename) {
	fstream file; 
    string word; 
  
    // Open the file 
    file.open(filename); 
	
    // Extracting words from the file 
    while (file >> word) {
        v.push_back(word);
    }

    file.close();
}

int main() {
	// Put the 50 words of the document in this vector
	vector<string> words;
	putVector(words, "./20doc/HP.txt");
	
	// Set the random seed
	//		https://stackoverflow.com/questions/322938/recommended-way-to-initialize-srand
	//		We will use the time and the PID to get a good seed for the pseudo-random number generations
	unsigned long seed = genRand();
	srand (seed);
	//srand (time(NULL));
	
	// Vector that will have the first 20 numbers ordered in a random way
	vector<int> randomPos;
	
	// For all the 20 files we want
	for (int i = 0; i < 20; i++) {
		// Insert the first 50 integers in a random way
		randomPos = randomize(words.size());
		
		// Open the file and clear its content
		ofstream outfile;
		string path = ("./20doc/" + to_string(i) + ".txt");
		outfile.open(path.c_str(), ofstream::out | ofstream::trunc);
		
		// Write into the file the 50 words of the vector "words"
		for (int j = 0; j < randomPos.size() - 1; j++) {
			outfile << words[randomPos[j]] << " ";
		}

		// Doing this, we will not have the space in the end
		outfile << words[randomPos[randomPos.size() - 1]];
		
		// Close the file
		outfile.close();
	}
	
    return 0;
}
