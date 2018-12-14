#include <iostream>		// cout
#include <algorithm>    // random_shuffle
#include <cstdlib>		// srand, rand
#include <ctime>		// time
#include <vector>		// vector
#include <string>		// string
#include <fstream>		// open, close, 
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
  
    // Counter of words
  	int i = 0;
	
    // Extracting words from the file 
    while (file >> word) {
        v[i] = word;
        i++;
    }
}

unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

int main() {
	// Put the 50 words of the document in this vector
	vector<string> words = vector<string>(50);
	putVector(words, "./20doc/documentBasic.txt");
	
	// Set the random seed
	//		https://stackoverflow.com/questions/322938/recommended-way-to-initialize-srand
	//		We will use the time and the PID to get a good seed for the pseudo-random number generations
	unsigned long seed = mix(clock(), time(NULL), getpid());
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
