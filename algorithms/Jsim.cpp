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

int main() {
	int k;
	cout << "Insert the k value to do the k-Shingling: ";
	cin >> k;
	
	string filePath1 = "./Jsim2documents/first.txt";
	string filePath2 = "./Jsim2documents/second.txt";

	bool spaces = false;

	unordered_set<string> S1 = kShingleString(filePath1, k, spaces);
	unordered_set<string> S2 = kShingleString(filePath2, k, spaces);

	unordered_set<int> I1 = kShingleInt(filePath1, k, spaces);
	unordered_set<int> I2 = kShingleInt(filePath2, k, spaces);

	cout << endl << "The Jaccard Similarity using Strings as Shingles is: " << jaccardSimilarity(S1, S2)*100 << "%" << endl;
	cout << endl << "The Jaccard Similarity using Integers as Shingles is: " << jaccardSimilarity(I1, I2)*100 << "%" << endl;
}
