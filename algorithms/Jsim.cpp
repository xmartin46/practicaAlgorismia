#include <iostream>
#include <string>
#include <unordered_set>
#include "kShingles.h"
using namespace std;

/*
Obtenir la similitud de Jaccard de dos documents representats per conjunts de
k-shingles. Recordeu que el grau de similitud de Jaccard de dos conjunts A i
B es defineix com Jsim(A, B) = |A n B|.
							   |A U B|
*/

int main(int argc, char** argv) {
	int k;
	if (argc > 1)
		k = stoi(argv[1]);
	else {
		cout << "Insert the k value to do the k-Shingling: ";
		cin >> k;
	}
	
	
	//string filePath1 = "./Jsim2documents/first.txt";
	//string filePath2 = "./Jsim2documents/second.txt";

	string filePath1 = "./20doc/13.txt";
	string filePath2 = "./20doc/0.txt";

	bool spaces = true;
	bool allLowercase = true;
	
	unordered_set<string> S1 = kShingleString(filePath1, k, spaces, allLowercase);
	unordered_set<string> S2 = kShingleString(filePath2, k, spaces, allLowercase);

	//unordered_set<int> I1 = kShingleInt(filePath1, k, spaces, allLowercase);
	//unordered_set<int> I2 = kShingleInt(filePath2, k, spaces, allLowercase);
	double sim = jaccardSimilarity(S1, S2) * 100;
	//cout << endl << "The Jaccard Similarity using Strings as Shingles is: " << sim << "%" << endl;
	//cout << endl << "The Jaccard Similarity using Integers as Shingles is: " << jaccardSimilarity(I1, I2)*100 << "%" << endl;
	cout << sim;
}
