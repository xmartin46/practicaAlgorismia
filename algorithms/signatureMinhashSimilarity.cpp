#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "kShingles.h"
#include "signatureMinHashSimilarity.h"
using namespace std;

/*
Obtenir una aproximacio del grau de similitud de Jaccard a traves d una representacio via signatures minhash basades 
en t funcions de hash. La mesura de similitud de dos signatures a i b amb t components es defineix com:
*/

int main() {
	int k;
	cout << "Insert the k value to do the k-Shingling: ";
	cin >> k;
	
	//string filePath1 = "./Jsim2documents/first.txt";
	//string filePath2 = "./Jsim2documents/second.txt";

	string filePath1 = "./20doc/13.txt";
	string filePath2 = "./20doc/0.txt";

	bool spaces = true;
	bool allLowercase = true;
	vector<unordered_set<string>> documents;

	unordered_set<string> D1 = kShingleString(filePath1, k, spaces, allLowercase);
	unordered_set<string> D2 = kShingleString(filePath2, k, spaces, allLowercase);

	unordered_set<int> I1 = kShingleInt(filePath1, k, spaces, allLowercase);
	unordered_set<int> I2 = kShingleInt(filePath2, k, spaces, allLowercase);

	double simS = signatureMinHashSimilarity(D1, D2);
	//double simD = signatureMinHashSimilarity(I1, I2);

	cout << endl << "The Jaccard Similarity using Strings as Shingles is: " << simS * 100 << "%" << endl;
	//cout << endl << "The Jaccard Similarity using Integers as Shingles is: " << simD * 100 << "%" << endl;
	//printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
